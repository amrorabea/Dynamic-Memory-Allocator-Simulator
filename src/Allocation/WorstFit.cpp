#include "../../include/Allocation/WorstFit.h"
#define NOT_FOUND (-1)
#define MIN_SPACE (-1)

WorstFit::WorstFit(const std::vector<Partition> &_partitions) {
    // .. KEEP
}

bool WorstFit::allocate(Process &process, std::vector<Partition> &partitions) {
    int worstIndex = NOT_FOUND, maxAvailable = MIN_SPACE;

    for (int i = 0; i < partitions.size(); ++i) {
        int available = partitions[i].space - partitions[i].allocated;
        if (available >= process.space && available > maxAvailable) {
            maxAvailable = available;
            worstIndex = i;
        }
    }

    if (worstIndex != -1) {
        partitions[worstIndex].allocated += process.space;
        partitions[worstIndex].process_id.insert(process.id);
        process.allocated_at = partitions[worstIndex].id;
        return true;
    }
    return false;
}

bool WorstFit::deallocate(const int &process_id, std::map<int, Process> &processes, std::vector<Partition> &partitions) {
    Process &process = processes[process_id];
    for (auto &partition: partitions) {
        if (partition.process_id.find(process.id) != partition.process_id.end()) {
            partition.process_id.erase(process.id);
            partition.allocated -= process.space;
            process.allocated_at = -1;
            return true; // rmv success
        }
    }
    return false;
}

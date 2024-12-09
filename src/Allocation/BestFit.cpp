#include "../../include/Allocation/BestFit.h"
#define NOT_FOUND (-1)
#define MAX_SPACE (1000'000'000)

BestFit::BestFit(const std::vector<Partition> &_partitions) {
    // .. KEEP
}

bool BestFit::allocate(Process &process, std::vector<Partition> &partitions) {
    int best = NOT_FOUND, best_space = MAX_SPACE;
    for (int i = 0; i < partitions.size(); ++i) {
        if ((partitions[i].space - partitions[i].allocated) >= process.space && partitions[i].space < best_space) {
            best_space = partitions[i].space;
            best = i;
        }
    }
    if (best != NOT_FOUND) {
        partitions[best].allocated += process.space;
        partitions[best].process_id.insert(process.id);
        process.allocated_at = best;
        return true;
    }
    return false;
}

bool BestFit::deallocate(const int &process_id, std::vector<Process> &processes, std::vector<Partition> &partitions) {
    Process &process = processes[process_id];
    for (auto &partition: partitions) {
        if (partition.process_id.find(process.id) != partition.process_id.end()) {
            partition.process_id.erase(process.id);
            partition.allocated += process.space;
            process.allocated_at = -1;
            return true; // rmv success
        }
    }
    return false;
}

void format(std::vector<Process> &processes, std::vector<Partition> &partitions) {
    for (auto &partition: partitions) {
        partition.allocated = 0;
        for (auto id: partition.process_id) processes[id].allocated_at = -1;
        partition.process_id.clear();
    }
}

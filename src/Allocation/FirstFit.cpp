#include "../../include/Allocation/FirstFit.h"

bool FirstFit::allocate(Process &process, std::vector<Partition> &partitions) {
    for (auto &partition: partitions) {
        if ((partition.space - partition.allocated)>= process.space) {
            partition.process_id.insert(process.id);
            partition.allocated += process.space;
            process.allocated_at = partition.id;
            return true;
        }
    }
    return false;
}

bool FirstFit::deallocate(const int &process_id, std::map<int, Process> &processes, std::vector<Partition> &partitions) {
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

void format(std::vector<Process> &processes, std::vector<Partition> &partitions) {
    for (auto &partition: partitions) {
        partition.allocated = 0;
        for (auto id: partition.process_id) processes[id].allocated_at = -1;
        partition.process_id.clear();
    }
}

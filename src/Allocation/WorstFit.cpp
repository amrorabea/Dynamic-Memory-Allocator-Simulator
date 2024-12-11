#include <WorstFit.h>

#define NOT_FOUND (-1)
#define MIN_SPACE (-1)

WorstFit::WorstFit(const std::map<int, Partition> &partitions) {
    // .. KEEP
}

bool WorstFit::allocate(Process &process, std::map<int, Partition> &partitions) {
    int worse = NOT_FOUND, max_space = MIN_SPACE;

    for (const auto &[_, partition]: partitions) {
        int available = partition.space - partition.allocated;
        if (available >= process.space && available > max_space) {
            max_space = available;
            worse = _;
        }
    }

    if (worse != NOT_FOUND) {
        partitions[worse].allocated += process.space;
        partitions[worse].process_id.insert(process.id);
        process.allocated_at = partitions[worse].id;
        return true;
    }
    return false;
}

bool WorstFit::deallocate(const int &process_id, std::map<int, Process> &processes,
                          std::map<int, Partition> &partitions) {
    Process &process = processes[process_id];
    for (auto &[_, partition]: partitions) {
        if (partition.process_id.find(process.id) != partition.process_id.end()) {
            partition.process_id.erase(process.id);
            partition.allocated -= process.space;
            process.allocated_at = -1;
            return true; // rmv success
        }
    }
    return false;
}

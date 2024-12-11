#include <BestFit.h>
#define NOT_FOUND (-1)
#define MAX_SPACE (1000'000'000)

BestFit::BestFit(const std::map<int, Partition> &_partitions) {
    // .. KEEP
}

bool BestFit::allocate(Process &process, std::map<int, Partition> &partitions) {
    int best = NOT_FOUND, best_space = MAX_SPACE;

    for (const auto &[key, partition]: partitions) {
        int available = partition.space - partition.allocated;
        if (available >= process.space && available < best_space) {
            best_space = available;
            best = key;
        }
    }

    if (best != NOT_FOUND) {
        auto it = partitions.find(best);
        if (it != partitions.end()) {
            auto [_, partition] = *it;
            partition.allocated += process.space;
            partition.process_id.insert(process.id);
            process.allocated_at = partition.id;
            return true;
        }
    }
    return false;
}


bool BestFit::deallocate(const int &process_id, std::map<int, Process> &processes,
                         std::map<int, Partition> &partitions) {
    Process &process = processes[process_id];
    for (auto &[_, partition]: partitions) {
        if (partition.process_id.find(process.id) != partition.process_id.end()) {
            partition.process_id.erase(process.id);
            partition.allocated -= process.space;
            process.allocated_at = -1;
            processes.erase(process_id);
            return true; // rmv success
        }
    }
    return false;
}

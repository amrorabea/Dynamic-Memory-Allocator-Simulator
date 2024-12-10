#ifndef AllocationTechnique_H
#define AllocationTechnique_H
#include <set>
#include <map>

struct Partition {
    int id;
    std::set<int> process_id;
    int space{};
    int allocated{};

    Partition() : id(0) {
    }

    Partition(const int id, const int sp) : id(id), space(sp), allocated(0) {
    }
};


struct Process {
    int id{};
    int space{};
    int unallocated{};
    int allocated_at{};

    Process() {
    }

    Process(const int id, const int sp) : id(id), space(sp), unallocated(space), allocated_at(-1) {
    }
};

class AllocationTechnique {
public:
    bool allocate(Process &process, std::map<int, Partition> &partitions);

    bool deallocate(const int &process_id, std::map<int, Process> &processes, std::map<int, Partition> &partitions);

    ~AllocationTechnique();
};
#endif //AllocationTechnique_H

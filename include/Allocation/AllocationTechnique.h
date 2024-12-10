#ifndef AllocationTechnique_H
#define AllocationTechnique_H
#include <set>
#include <vector>
#include <map>

struct Partition {
    int id;
    std::set<int> process_id;
    int space{};
    int allocated{};

    Partition(const int id, const int sp) : space(sp), id(id) { }
};

struct Process {
    int id{};
    int space{};
    int unallocated{};
    int allocated_at{};

    Process() {};

    Process(const int id, const int sp) : id(id), space(sp), unallocated(space), allocated_at(-1) { }
};

class AllocationTechnique {
public:
    bool allocate(Process &process, std::vector<Partition> &partitions);

    bool deallocate(const int &process_id, std::map<int, Process> &processes, std::vector<Partition> &partitions);

    void format(std::vector<Process> &processes, std::vector<Partition> &partitions);

    ~AllocationTechnique();
};
#endif //AllocationTechnique_H

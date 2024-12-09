#ifndef AllocationTechnique_H
#define AllocationTechnique_H
#include <set>
#include <vector>

struct Partition {
    int id;
    std::set<int> process_id;
    int space{};
    int allocated{};
    bool is_free = 0;

    Partition(const int id, const int sp) : space(sp), id(id) { }
};

struct Process {
    int id;
    int space;
    int unallocated;
    int allocated_at;
    Process(const int id, const int sp) : id(id), space(sp), unallocated(space), allocated_at(-1) { }
};

class AllocationTechnique {
public:
    virtual bool allocate(Process &process, std::vector<Partition> &partitions) {};

    virtual bool deallocate(const int &process_id, std::vector<Process> &processes, std::vector<Partition> &partitions) {};

    virtual void format(std::vector<Process> &processes, std::vector<Partition> &partitions);

    virtual ~AllocationTechnique();
};
#endif //AllocationTechnique_H

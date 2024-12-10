#ifndef WORSTFIT_H
#define WORSTFIT_H
#include <AllocationTechnique.h>

class WorstFit : public AllocationTechnique {
public:
    WorstFit(const std::map<int, Partition> &partitions);

    static bool allocate(Process &process, std::map<int, Partition> &partitions);

    static bool deallocate(const int &process_id, std::map<int, Process> &processes,
                           std::map<int, Partition> &partitions);
};


#endif // WORSTFIT_H

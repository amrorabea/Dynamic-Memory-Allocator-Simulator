#ifndef BESTFIT_H
#define BESTFIT_H

#include <AllocationTechnique.h>

class BestFit : public AllocationTechnique {
public:
    BestFit(const std::map<int, Partition> &partitions);

    static bool allocate(Process &process, std::map<int, Partition> &partitions);

    static bool deallocate(const int &process_id, std::map<int, Process> &processes, std::map<int, Partition> &partitions);
};

#endif // BESTFIT_H

#ifndef FIRSTFIT_H
#define FIRSTFIT_H


#include "AllocationTechnique.h"

class FirstFit : public AllocationTechnique {
public:
    static bool allocate(Process &process, std::map<int, Partition> &partitions);

    static bool deallocate(const int &process_id, std::map<int, Process> &processes,
                           std::map<int, Partition> &partitions);
};

#endif // FIRSTFIT_H

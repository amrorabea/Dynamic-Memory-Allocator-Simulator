#ifndef BESTFIT_H
#define BESTFIT_H

#include "AllocationTechnique.h"

class BestFit : public AllocationTechnique {
public:
    BestFit(const std::vector<Partition> &partitions);

    static bool allocate(Process &process, std::vector<Partition> &partitions);

    static bool deallocate(const int &process_id, std::vector<Process> &processes, std::vector<Partition> &partitions);

    void format(std::vector<Process> &processes, std::vector<Partition> &partitions);
};

#endif // BESTFIT_H

#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "AllocationTechnique.h"

class FirstFit : public AllocationTechnique {
public:
    bool allocate(Process &process, std::vector<Partition> &partitions) override;

    bool deallocate(const int &process_id, std::vector<Process> &processes, std::vector<Partition> &partitions) override;

    void format(std::vector<Process> &processes, std::vector<Partition> &partitions) override;
};

#endif // FIRSTFIT_H

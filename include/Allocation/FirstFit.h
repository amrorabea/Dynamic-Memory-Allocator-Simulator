#ifndef FIRSTFIT_H
#define FIRSTFIT_H


#include "AllocationTechnique.h"

class FirstFit : public AllocationTechnique {
public:
    static bool allocate(Process &process, std::vector<Partition> &partitions);

    static bool deallocate(const int &process_id, std::map<int, Process> &processes, std::vector<Partition> &partitions);

    void format(std::vector<Process> &processes, std::vector<Partition> &partitions);
};

#endif // FIRSTFIT_H

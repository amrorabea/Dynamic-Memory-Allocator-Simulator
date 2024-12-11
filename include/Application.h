#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>
#include <map>
#include <AllocationTechnique.h>

class Application {
public:
    void Initialize();

private:
    std::vector<int> partitions;
    std::map<int, Partition> allocatedPartitions;
    std::map<int, Process> allocatedProcesses;

    std::map<int, Partition> bestPartitions;
    std::map<int, Partition> firstPartitions;
    std::map<int, Partition> worstPartitions;

    std::map<int, Process> firstProcesses;
    std::map<int, Process> bestProcesses;
    std::map<int, Process> worstProcesses;

    void LoadPartitions(const std::string &filename = "../data/partitions");

    void DisplayFirstWindow();

    void HandleAdminLogin();

    void DisplayUpdatePartitionsWindow();

    void HandleUserCommands();

    static void ExitApplication();

    static void DisplayInvalidInput(int x = 4, int y = 18, std::string msg = "Invalid choice. Please try again.",
                                    int sleep = 1500);

    static void DisplaySuccessMessage(const std::string &message, int x, int y);

    static void DisplayInvalidPassword();

    static std::string GetMaskedInput(int x, int y);

    void processesTable(int mode);

    void visualizeAll();
};

#endif // APPLICATION_H

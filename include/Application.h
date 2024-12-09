#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>

class Application {
public:
    void Initialize();

private:
    std::vector<int> partitions, allocated;
    void LoadPartitions(const std::string& filename = "../data/partitions");
    void DisplayFirstWindow();
    void HandleAdminLogin();
    void DisplayUpdatePartitionsWindow();
    void HandleUserCommands();
    static void ExitApplication();
    static void DisplayInvalidChoice();
    static void DisplayInvalidPassword();
    static std::string GetMaskedInput(int x, int y);

    static void processesTable(int mode);

};

#endif // APPLICATION_H

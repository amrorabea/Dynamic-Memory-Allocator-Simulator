#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>

class Application {
public:
    void Initialize();

private:
    std::vector<int> partitions;
    void LoadPartitions(const std::string& filename = "../data/partitions");
    void DisplayFirstWindow();
    void HandleAdminLogin();
    void DisplayUpdatePartitionsWindow();
    void HandleUserCommands();
    void ExitApplication();
    void DisplayInvalidChoice();
    void DisplayInvalidPassword();
    std::string GetMaskedInput(int x, int y);
};

#endif // APPLICATION_H

#include "../include/Application.h"
#include "../include/ConsoleHandler.h"
#include "../include/UI.h"
#include "../include/ColorCode.h"
#include "../include/Allocation/FirstFit.h"
#include "../include/Allocation/WorstFit.h"
#include "../include/Allocation/BestFit.h"

#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

void Application::Initialize() {
    LoadPartitions();
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    DisplayFirstWindow();
    // Exit is handled within DisplayFirstWindow's loop
}

void Application::LoadPartitions(const std::string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening the file: " << filename << "!" << endl;
        // Consider throwing an exception or handling the error gracefully
        exit(EXIT_FAILURE);
    }

    int value, i = 1;
    while (file >> value) {
        partitions.push_back(value);
        Partition newPartition(i++, value);
        allocatedPartitions.push_back(newPartition);
    }

    file.close();
}

void Application::DisplayFirstWindow() {
    while (true) {
        UI::DisplayTime(1, 1);
        UI::DisplayTitle("Dynamic Memory Allocator Simulator", 40, 5);
        UI::ClearRegion(2, 8, 86, 15); // Clear previous messages
        std::vector<std::string> asciiArt = {
                "------------------------------------------------------------------------------",
                "|                 Welcome to the Memory Allocation Simulator                 |",
                "|       Simulating First-Fit, Best-Fit, and Worst-Fit Memory Allocation      |",
                "------------------------------------------------------------------------------"
        };

        ConsoleHandler::SetColor(ColorCode::LightBlue);

        for (int i = 0; i < asciiArt.size(); i++) {
            ConsoleHandler::SetCursorPosition(18, 20 + (2 * i));
            cout << asciiArt[i];
        }
        ConsoleHandler::SetColor(ColorCode::Yellow);
        ConsoleHandler::SetCursorPosition(4, 10);
        cout << "1. Update partition values ";
        ConsoleHandler::SetColor(ColorCode::LightRed);
        cout << "(Admins ONLY)";
        ConsoleHandler::SetColor(ColorCode::Yellow);
        ConsoleHandler::SetCursorPosition(4, 12);
        cout << "2. Use default partitions";
        ConsoleHandler::SetCursorPosition(4, 14);
        cout << "3. Exit";
        ConsoleHandler::SetCursorPosition(4, 16);
        ConsoleHandler::SetColor(ColorCode::White);
        cout << "Enter your choice: ";


        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            DisplayInvalidInput();
            continue;
        }

        switch (choice) {
            case 1:
                HandleAdminLogin();
                break;
            case 2:
                HandleUserCommands();
                break;
            case 3:
                ExitApplication();
                return;
            default:
                DisplayInvalidInput();
                DisplayFirstWindow();
                break;
        }
    }
}

void Application::HandleAdminLogin() {
    const std::string adminPassword = "1";
    std::string inputPassword;

    while (true) {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        UI::DisplayTitle(" ", 55, 8);
        std::vector<std::string> title = {
                "                              Admin Login page                              ",
                "        Enter valid Admin password, or enter \"000\" to back to HomePage      ",
        };

        ConsoleHandler::SetColor(ColorCode::Cyan);

        for (int i = 0; i < title.size(); i++) {
            ConsoleHandler::SetCursorPosition(18, 7 + (2 * i));
            cout << title[i];
        }

        ConsoleHandler::SetColor(ColorCode::Yellow);
        ConsoleHandler::SetCursorPosition(30, 15);
        cout << "USERNAME: Admin";
        ConsoleHandler::SetCursorPosition(30, 16);
        cout << "PASSWORD: ";

        inputPassword = GetMaskedInput(41, 16);
        if (inputPassword == "000") {
            // Back to First Window
            ConsoleHandler::ClearConsole();
            UI::DrawBoxBorder();
            DisplayFirstWindow();
            return;
        } else if (inputPassword == adminPassword) {
            ConsoleHandler::ClearConsole();
            UI::DrawBoxBorder();
            DisplayUpdatePartitionsWindow();
            break;
        } else {
            DisplayInvalidPassword();
            DisplayFirstWindow();
        }
    }
}

void Application::DisplayUpdatePartitionsWindow() {
    ConsoleHandler::SetCursorPosition(15, 10);
    ConsoleHandler::SetColor(ColorCode::Yellow);
    cout << "Updating Partition Sizes";

    ofstream tempFile("temp.txt", std::ios::trunc);
    if (!tempFile.is_open()) {
        cerr << "Error opening the file for writing: temp.txt!" << endl;
        exit(EXIT_FAILURE);
    }


    while (true) {
        for (int i = 0; i < partitions.size(); i++) {
            ConsoleHandler::SetCursorPosition(90, 7 + i * 2);
            ConsoleHandler::SetColor(ColorCode::LightRed);
            cout << "partitions " << i + 1 << " value = " << partitions[i] << "     ";
        }
        ConsoleHandler::SetCursorPosition(5, 15);
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        cout << "Select partition id 1 : 8 to change it's value or 0 to exit to home page";
        ConsoleHandler::SetColor(ColorCode::LightCyan);
        ConsoleHandler::SetCursorPosition(20, 17);
        cout << "New partition id : ";
        ConsoleHandler::SetColor(ColorCode::White);
        int choice;
        cin >> choice;
        if (!(choice < 0 || choice > 8)) {
            if (choice == 0) {
                break;
            }
            ConsoleHandler::SetColor(ColorCode::LightCyan);
            ConsoleHandler::SetCursorPosition(20, 20);
            cout << "New value: ";
            ConsoleHandler::SetColor(ColorCode::White);
            int newValue;
            if (!(cin >> newValue)) {
                ConsoleHandler::SetColor(ColorCode::LightCyan);
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                ConsoleHandler::SetCursorPosition(20, 25);
                ConsoleHandler::SetColor(ColorCode::Red);
                cout << "Invalid input. Please enter an integer value.";
                Sleep(1500);

                ConsoleHandler::SetColor(ColorCode::LightCyan);

                ConsoleHandler::SetCursorPosition(20, 20);
                cout << "                                                 ";
                ConsoleHandler::SetCursorPosition(20, 20);
                cout << "New value: ";
                cin >> newValue;
            }
            partitions[choice - 1] = newValue;
        } else {
            ConsoleHandler::SetCursorPosition(20, 25);
            ConsoleHandler::SetColor(ColorCode::Red);
            cout << "Invalid input. Please enter an integer value between 0 and 8 Exclusive.";
            Sleep(1500);

        }
        // clear window after get value
        ConsoleHandler::SetCursorPosition(20, 25);
        cout << "                                                                              ";
        ConsoleHandler::SetCursorPosition(20, 17);
        cout << "                                                 ";
        ConsoleHandler::SetCursorPosition(20, 20);
        cout << "                                                 ";
    }

    for (int partition: partitions) {
        tempFile << partition << std::endl;
    }

    tempFile.close();

    if (remove("../data/partitions") != 0) {
        cerr << "Error deleting the file: partitions" << endl;
        exit(EXIT_FAILURE);
    }
    if (rename("temp.txt", "../data/partitions") != 0) {
        cerr << "Error renaming the file: temp.txt to partitions" << endl;
        exit(EXIT_FAILURE);
    }

    partitions.clear();
    LoadPartitions();

    // Return to the first window
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

void Application::HandleUserCommands() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);
    UI::DisplayTitle("Partitions MODE", 55, 5);
    ConsoleHandler::SetCursorPosition(4, 10);
    ConsoleHandler::SetColor(ColorCode::Yellow);
    cout << "1. Visualize all";
    ConsoleHandler::SetCursorPosition(4, 12);
    cout << "2. First-Fit";
    ConsoleHandler::SetCursorPosition(4, 14);
    cout << "3. Best-Fit";
    ConsoleHandler::SetCursorPosition(4, 16);
    cout << "4. Worst-Fit";
    ConsoleHandler::SetCursorPosition(4, 18);
    cout << "5. Back";

    ConsoleHandler::SetCursorPosition(4, 20);
    ConsoleHandler::SetColor(ColorCode::White);
    cout << "Enter your choice: ";

    int val;
    if (!(cin >> val)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        DisplayInvalidInput();
        HandleUserCommands();
    }

    if (val == 1 || val == 2 || val == 3 || val == 4) {
        ConsoleHandler::SetCursorPosition(4, 20);
        ConsoleHandler::SetColor(ColorCode::Green);
        switch (val) {
            case 1:
                cout << "Selected option: " << val << " (Functionality not implemented yet)";
                break;
            case 2:
                processesTable(2);
                break;
            case 3:
                processesTable(3);
                break;
            case 4:
                processesTable(4);
                break;
            default:
                break;
        }
    } else if (val == 5) {
        // Back to First Window
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
        return;
    } else {
        DisplayInvalidInput();
        HandleUserCommands();
    }


    Sleep(2000);
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

void Application::processesTable(int mode) {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);

    std::string titles[] = {"First Fit Technique", "Best Fit Technique", "Worst Fit Technique"};
    std::string title = "Manage Processes : " + titles[mode - 2];
    UI::DisplayTitle(title, 40, 1);

    UI::DrawTableBorder(114, 13, 3, 11);
    UI::DrawHorizontalLine(115, 3, 15);
    UI::DrawHorizontalLine(115, 3, 19);
    int vert = 26;
    for (int i = 0; i < partitions.size(); ++i) {
        UI::DrawVerticalLine(14, vert, 11), vert += 10;
        ConsoleHandler::SetCursorPosition(vert - 7, 10);
        cout << partitions[i];
    }

    ConsoleHandler::SetCursorPosition(5, 13);
    cout << "Processes ID";
    int x = 27, y = 12;
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        std::set<int> st = allocatedPartitions[i].process_id;
        ConsoleHandler::SetCursorPosition(x, y);
        int cnt = 0, def = x;
        for (auto el: st) {
            cout << ", "[cnt == 0] << el;
            ConsoleHandler::SetCursorPosition(x += 2, y);
            if (cnt == 2) y++, cnt = 0, x = def;
            cnt++;
        }
        x = (i + 1) * 10 + 27, y = 12;
    }
    ConsoleHandler::SetCursorPosition(5, 17);
    cout << "Allocated";
    x = 30, y = 17;
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        cout << allocatedPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y);
    }
    x = 30, y = 21;
    ConsoleHandler::SetCursorPosition(5, 21);
    cout << "Unallocated";
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        cout << allocatedPartitions[i].space - allocatedPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y);
    }

    ConsoleHandler::SetColor(ColorCode::Yellow);

    ConsoleHandler::SetCursorPosition(4, 4);
    cout << "1. Allocate";
    ConsoleHandler::SetCursorPosition(4, 6);
    cout << "2. Deallocate";
    ConsoleHandler::SetCursorPosition(4, 8);
    cout << "3. Back";
    ConsoleHandler::SetCursorPosition(4, 10);
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        ConsoleHandler::SetCursorPosition(4, 8);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 8);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 10);
        cout << "               ";
        int id, processSpace;
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "Process ID: ";
        std::string tmp;
        cin >> tmp;
        if (tmp.size() > 3) {
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"), processesTable(mode);
        }
        // cin >> id;
        id = std::stoi(tmp);
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "Process Space: ";
        cin >> processSpace;
        Process newProcess(id, processSpace);
        if (mode == 2) {
            FirstFit::allocate(newProcess, allocatedPartitions);
            allocatedProcesses[id] = newProcess;
            processesTable(2);
        } else if (mode == 3) {
            BestFit::allocate(newProcess, allocatedPartitions);
            allocatedProcesses[id] = newProcess;
            processesTable(3);
        } else {
            WorstFit::allocate(newProcess, allocatedPartitions);
            allocatedProcesses[id] = newProcess;
            processesTable(4);
        }
    } else if (choice == 2) {
        ConsoleHandler::SetCursorPosition(4, 8);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 8);
        cout << "                                   ";
        ConsoleHandler::SetCursorPosition(4, 10);
        cout << "                                   ";
        int id;
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "Process ID: ";
        cin >> id;
        // std::string temp; cin >> temp;
        // if (temp.size() > 3) DisplayInvalidInput(4, 10), processesTable(mode);
        // id = stoi(temp);
        if (mode == 2) {
            FirstFit::deallocate(id, allocatedProcesses, allocatedPartitions);
            processesTable(2);
        } else if (mode == 3) {
            BestFit::deallocate(id, allocatedProcesses, allocatedPartitions);
            processesTable(3);
        } else {
            WorstFit::deallocate(id, allocatedProcesses, allocatedPartitions);
            processesTable(4);
        }
    } else if (choice == 3) {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
    } else DisplayInvalidInput(4, 10), processesTable(mode);
    //
    // when adding new processes we will start from 17 and add 5 for each new value, MAX PARTITIONS IS 14
}

void Application::ExitApplication() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    ConsoleHandler::SetCursorPosition(35, 12);
    ConsoleHandler::SetColor(ColorCode::LightRed);
    cout << "Exiting the application. Goodbye!";
    Sleep(2000); // Pause for 2 seconds before exiting
    exit(EXIT_SUCCESS);
}

void Application::DisplayInvalidInput(int x, int y, std::string msg) {
    ConsoleHandler::SetCursorPosition(x, y);
    ConsoleHandler::SetColor(ColorCode::Red);
    cout << msg;
    Sleep(1500); // Wait for 1.5 seconds
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

void Application::DisplaySuccessMessage(const std::string &message, int x, int y) {
    ConsoleHandler::SetCursorPosition(x, y);
    ConsoleHandler::SetColor(ColorCode::Green);
    cout << message;
    Sleep(1500); // Display for 1.5 seconds
    ConsoleHandler::SetColor(ColorCode::White);
}

void Application::DisplayInvalidPassword() {
    ConsoleHandler::SetCursorPosition(20, 18);
    ConsoleHandler::SetColor(ColorCode::Red);
    cout << "Invalid Password. Try again.";
    Sleep(1500); // Wait for 1.5 seconds
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

std::string Application::GetMaskedInput(int x, int y) {
    std::string password;
    char ch;
    ConsoleHandler::SetCursorPosition(x, y);
    while ((ch = _getch()) != '\r') { // ('\r' == enter key)
        if (ch == '\b') { // ('\b' == Backspace)
            if (!password.empty()) {
                password.pop_back();
                ConsoleHandler::SetCursorPosition(--x, y);
                cout << ' ' << '\b';
            }
        } else if (ch != 0 && ch != 224) {
            password += ch;
            cout << '*';
            x++;
        }
    }
    cout << std::endl;
    return password;
}

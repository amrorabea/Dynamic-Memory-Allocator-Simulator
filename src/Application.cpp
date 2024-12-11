#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <set>
#include <Application.h>
#include <ConsoleHandler.h>
#include <UI.h>
#include <AllocationTechnique.h>
#include <FirstFit.h>
#include <BestFit.h>
#include <WorstFit.h>

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
        allocatedPartitions[i - 2] = newPartition;
    }

    file.close();
}

void Application::DisplayFirstWindow() {
    while (true) {
        UI::DisplayTime(1, 1);
        UI::DisplayTitle("Dynamic Memory Allocator Simulator", 40, 5);
        UI::ClearRegion(2, 8, 86, 15); // Clear previous messages
        std::vector<std::string> asciiArt = {
            "   -----------------------------------------------------------------------",
            " /     ` .  `      '   .` .       `    ` .  `     .  ` ' `   `     ' .  .  \\",
            "/  ` .  >  `   `   Welcome to the Memory AllocationSimulator    `  <   .    \\",
            "\\ `  >  Simulating First Fit, Best Fit, and Worst Fit Memory Allocation ` < /",
            " \\    `    .   `       `     .  ` '    `    ` .  `   `   '   .` .  ' .  .  /",
            // "   ------------------------------------------------------------------------",
        };


        for (int i = 0; i < asciiArt.size(); i++) {
            ConsoleHandler::SetCursorPosition(18, 19 + (2 * i));
            for (char c: asciiArt[i]) {
                if (c == '|' || c == '/' || c == '\\' || c == '<' || c == '>' ||
                    c == '`' || c == '.' || c == '\'' || c == '-') {
                    ConsoleHandler::SetColor(ColorCode::DarkGray);
                } else {
                    ConsoleHandler::SetColor(ColorCode::LightCyan);
                }
                std::cout << c;
            }
        }
        ConsoleHandler::SetColor(ColorCode::White);

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
            case 1: HandleAdminLogin();
                break;
            case 2: HandleUserCommands();
                break;
            case 3: ExitApplication();
                return;
            default: DisplayInvalidInput();
                DisplayFirstWindow();
                break;
        }
    }
}

void Application::HandleAdminLogin() {
    const std::string adminPassword = "admin";
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
        cout << "USERNAME: ";
        std::string userInput;
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        cin >> userInput;
        ConsoleHandler::SetCursorPosition(30, 16);
        ConsoleHandler::SetColor(ColorCode::Yellow);
        cout << "PASSWORD: ";
        ConsoleHandler::SetColor(ColorCode::DarkGray);

        inputPassword = GetMaskedInput(40, 16);
        if (inputPassword == "000") {
            ConsoleHandler::ClearConsole();
            UI::DrawBoxBorder();
            DisplayFirstWindow();
            return;
        }
        if (inputPassword == adminPassword && userInput == "admin") {
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
    ConsoleHandler::SetCursorPosition(20, 10);
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
        ConsoleHandler::SetCursorPosition(20, 15);
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        cout << "Select partition id 1 : 9 to change size.";
        ConsoleHandler::SetCursorPosition(20, 16);
        cout << "Enter 0 to return to home page.";
        ConsoleHandler::SetColor(ColorCode::LightCyan);
        ConsoleHandler::SetCursorPosition(20, 20);
        cout << "New partition id : ";
        ConsoleHandler::SetColor(ColorCode::White);
        int choice;
        cin >> choice;
        if (!(choice < 0 || choice > 9)) {
            if (choice == 0) {
                break;
            }
            ConsoleHandler::SetColor(ColorCode::LightCyan);
            ConsoleHandler::SetCursorPosition(20, 22);
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
            ConsoleHandler::SetCursorPosition(20, 26);
            ConsoleHandler::SetColor(ColorCode::Red);
            cout << "Invalid input. Please enter an integer value between 0 and 9 Exclusive.";
            Sleep(1500);
        }
        // clear window after get value
        ConsoleHandler::SetCursorPosition(20, 25);
        cout << "                                                                              ";
        ConsoleHandler::SetCursorPosition(20, 22);
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
    firstPartitions = allocatedPartitions;
    bestPartitions = allocatedPartitions;
    worstPartitions = allocatedPartitions;
    if (val == 1 || val == 2 || val == 3 || val == 4) {
        ConsoleHandler::SetCursorPosition(4, 20);
        ConsoleHandler::SetColor(ColorCode::Green);
        switch (val) {
            case 1: visualizeAll();
                break;
            case 2: FirstFit();
                break;
            case 3: BestFit();
                break;
            case 4: WorstFit();
                break;
            default: break;
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

void Application::FirstFit() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);

    std::string title = "Manage Processes : First Fit Technique";
    UI::DisplayTitle(title, 40, 1);

    UI::DrawTableBorder(114, 13, 3, 14);
    UI::DrawHorizontalLine(115, 3, 18);
    UI::DrawHorizontalLine(115, 3, 22);
    int vert = 26;
    for (int i = 0; i < partitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        UI::DrawVerticalLine(14, vert, 14), vert += 10;
        ConsoleHandler::SetColor(ColorCode::Brown);
        ConsoleHandler::SetCursorPosition(vert - 7, 13);
        cout << partitions[i];
    }

    ConsoleHandler::SetCursorPosition(5, 16);
    ConsoleHandler::SetColor(ColorCode::LightBlue);
    cout << "Processes ID";
    int x = 27, y = 15;
    for (int i = 0; i < firstPartitions.size(); ++i) {
        std::set<int> st = firstPartitions[i].process_id;
        ConsoleHandler::SetCursorPosition(x, y);
        int cnt = 0, def = x;
        for (auto el: st) {
            cout << ", "[cnt == 0] << el;
            ConsoleHandler::SetCursorPosition(x += 2, y);
            if (cnt == 2) y++, cnt = 0, x = def;
            cnt++;
        }
        x = (i + 1) * 10 + 27, y = 15;
    }
    ConsoleHandler::SetColor(ColorCode::LightRed);
    ConsoleHandler::SetCursorPosition(5, 20);
    cout << "Allocated";
    x = 30, y = 20;
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < firstPartitions.size(); ++i) {
        cout << firstPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y);
    }
    x = 30, y = 24;
    ConsoleHandler::SetColor(ColorCode::LightGreen);
    ConsoleHandler::SetCursorPosition(5, 24);
    cout << "Unallocated";
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < firstPartitions.size(); ++i) {
        cout << firstPartitions[i].space - firstPartitions[i].allocated;
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
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    FirstFit();
        }
        id = std::stoi(tmp);
        if (firstProcesses.find(id) != firstProcesses.end()) {
            DisplayInvalidInput(4, 6, "The id is already taken"),
                    FirstFit();
        }
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "Process Space: ";
        cin >> processSpace;
        bool can = 0, can_wait = 0;
        for (auto partition: partitions) {
            if (partition >= processSpace) {
                can_wait = 1;
                for (const auto &[_, part]: firstPartitions) {
                    if (part.space - part.allocated >= processSpace) {
                        can = 1;
                        break;
                    }
                }
            }
            if (can) break;
        }
        if (!can_wait) {
            DisplayInvalidInput(4, 8, "The process space is larger"
                                " than all partitions", 2000), FirstFit();
        }
        if (!can) {
            DisplayInvalidInput(4, 8, "The process space is larger than"
                                " all unallocated partitions, MUST Wait", 2000),
                    FirstFit();
        }
        Process newProcess(id, processSpace);
        FirstFit::allocate(newProcess, firstPartitions);
        firstProcesses[id] = newProcess;
        FirstFit();
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
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "Process ID: ";
        std::string tmp;
        cin >> tmp;
        if (tmp.size() > 3) {
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    FirstFit();
        }
        int id = std::stoi(tmp);
        if (firstProcesses.find(id) == firstProcesses.end()) {
            DisplayInvalidInput(4, 6, "The process id don't added before"),
                    FirstFit();
        }
        FirstFit::deallocate(id, firstProcesses, firstPartitions);
        FirstFit();
    } else if (choice == 3) {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
    } else DisplayInvalidInput(4, 10), FirstFit();
}

void Application::BestFit() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);

    std::string title = "Manage Processes : Best Fit Technique";
    UI::DisplayTitle(title, 40, 1);

    UI::DrawTableBorder(114, 13, 3, 14);
    UI::DrawHorizontalLine(115, 3, 18);
    UI::DrawHorizontalLine(115, 3, 22);
    int vert = 26;
    for (int i = 0; i < partitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        UI::DrawVerticalLine(14, vert, 14), vert += 10;
        ConsoleHandler::SetColor(ColorCode::Brown);
        ConsoleHandler::SetCursorPosition(vert - 7, 13);
        cout << partitions[i];
    }

    ConsoleHandler::SetCursorPosition(5, 16);
    ConsoleHandler::SetColor(ColorCode::LightBlue);
    cout << "Processes ID";
    int x = 27, y = 15;
    for (int i = 0; i < bestPartitions.size(); ++i) {
        std::set<int> st = bestPartitions[i].process_id;
        ConsoleHandler::SetCursorPosition(x, y);
        int cnt = 0, def = x;
        for (auto el: st) {
            cout << ", "[cnt == 0] << el;
            ConsoleHandler::SetCursorPosition(x += 2, y);
            if (cnt == 2) y++, cnt = 0, x = def;
            cnt++;
        }
        x = (i + 1) * 10 + 27, y = 15;
    }
    ConsoleHandler::SetColor(ColorCode::LightRed);
    ConsoleHandler::SetCursorPosition(5, 20);
    cout << "Allocated";
    x = 30, y = 20;
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < bestPartitions.size(); ++i) {
        cout << bestPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y);
    }
    x = 30, y = 24;
    ConsoleHandler::SetColor(ColorCode::LightGreen);
    ConsoleHandler::SetCursorPosition(5, 24);
    cout << "Unallocated";
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < bestPartitions.size(); ++i) {
        cout << bestPartitions[i].space - bestPartitions[i].allocated;
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
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    BestFit();
        }
        id = std::stoi(tmp);
        if (bestProcesses.find(id) != bestProcesses.end()) {
            DisplayInvalidInput(4, 6, "The id is already taken"),
                    BestFit();
        }
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "Process Space: ";
        cin >> processSpace;
        bool can = 0, can_wait = 0;
        for (auto partition: partitions) {
            if (partition >= processSpace) {
                can_wait = 1;
                for (const auto &[_, part]: bestPartitions) {
                    if (part.space - part.allocated >= processSpace) {
                        can = 1;
                        break;
                    }
                }
            }
            if (can) break;
        }
        if (!can_wait) {
            DisplayInvalidInput(4, 8, "The process space is larger"
                                " than all partitions", 2000), BestFit();
        }
        if (!can) {
            DisplayInvalidInput(4, 8, "The process space is larger than"
                                " all unallocated partitions, MUST Wait", 2000),
                    BestFit();
        }
        Process newProcess(id, processSpace);
        BestFit::allocate(newProcess, bestPartitions);
        bestProcesses[id] = newProcess;
        BestFit();
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
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "Process ID: ";
        std::string tmp;
        cin >> tmp;
        if (tmp.size() > 3) {
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    BestFit();
        }
        int id = std::stoi(tmp);
        if (bestProcesses.find(id) == bestProcesses.end()) {
            DisplayInvalidInput(4, 6, "The process id don't added before"),
                    BestFit();
        }
        BestFit::deallocate(id, bestProcesses, bestPartitions);
        BestFit();
    } else if (choice == 3) {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
    } else DisplayInvalidInput(4, 10), BestFit();
}

void Application::WorstFit() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);

    std::string title = "Manage Processes : Worst Fit Technique";
    UI::DisplayTitle(title, 40, 1);

    UI::DrawTableBorder(114, 13, 3, 14);
    UI::DrawHorizontalLine(115, 3, 18);
    UI::DrawHorizontalLine(115, 3, 22);
    int vert = 26;
    for (int i = 0; i < partitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        UI::DrawVerticalLine(14, vert, 14), vert += 10;
        ConsoleHandler::SetColor(ColorCode::Brown);
        ConsoleHandler::SetCursorPosition(vert - 7, 13);
        cout << partitions[i];
    }

    ConsoleHandler::SetCursorPosition(5, 16);
    ConsoleHandler::SetColor(ColorCode::LightBlue);
    cout << "Processes ID";
    int x = 27, y = 15;
    for (int i = 0; i < worstPartitions.size(); ++i) {
        std::set<int> st = worstPartitions[i].process_id;
        ConsoleHandler::SetCursorPosition(x, y);
        int cnt = 0, def = x;
        for (auto el: st) {
            cout << ", "[cnt == 0] << el;
            ConsoleHandler::SetCursorPosition(x += 2, y);
            if (cnt == 2) y++, cnt = 0, x = def;
            cnt++;
        }
        x = (i + 1) * 10 + 27, y = 15;
    }
    ConsoleHandler::SetColor(ColorCode::LightRed);
    ConsoleHandler::SetCursorPosition(5, 20);
    cout << "Allocated";
    x = 30, y = 20;
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < worstPartitions.size(); ++i) {
        cout << worstPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y);
    }
    x = 30, y = 24;
    ConsoleHandler::SetColor(ColorCode::LightGreen);
    ConsoleHandler::SetCursorPosition(5, 24);
    cout << "Unallocated";
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < worstPartitions.size(); ++i) {
        cout << worstPartitions[i].space - worstPartitions[i].allocated;
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
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    WorstFit();
        }
        id = std::stoi(tmp);
        if (worstProcesses.find(id) != worstProcesses.end()) {
            DisplayInvalidInput(4, 6, "The id is already taken"),
                    WorstFit();
        }
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "Process Space: ";
        cin >> processSpace;
        bool can = 0, can_wait = 0;
        for (auto partition: partitions) {
            if (partition >= processSpace) {
                can_wait = 1;
                for (const auto &[_, part]: worstPartitions) {
                    if (part.space - part.allocated >= processSpace) {
                        can = 1;
                        break;
                    }
                }
            }
            if (can) break;
        }
        if (!can_wait) {
            DisplayInvalidInput(4, 8, "The process space is larger"
                                " than all partitions", 2000), WorstFit();
        }
        if (!can) {
            DisplayInvalidInput(4, 8, "The process space is larger than"
                                " all unallocated partitions, MUST Wait", 2000),
                    WorstFit();
        }
        Process newProcess(id, processSpace);
        WorstFit::allocate(newProcess, worstPartitions);
        worstProcesses[id] = newProcess;
        WorstFit();
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
        ConsoleHandler::SetCursorPosition(4, 4);
        cout << "Process ID: ";
        std::string tmp;
        cin >> tmp;
        if (tmp.size() > 3) {
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    WorstFit();
        }
        int id = std::stoi(tmp);
        if (worstProcesses.find(id) == worstProcesses.end()) {
            DisplayInvalidInput(4, 6, "The process id don't added before"),
                    WorstFit();
        }
        WorstFit::deallocate(id, worstProcesses, worstPartitions);
        WorstFit();
    } else if (choice == 3) {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
    } else DisplayInvalidInput(4, 10), WorstFit();
}

void Application::visualizeAll() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    UI::DisplayTime(1, 1);


    UI::DisplayTitle("Visualize all processes", 45, 2);

    const char blk_ascii = 254;
    ConsoleHandler::SetCursorPosition(90, 5);
    ConsoleHandler::SetColor(ColorCode::LightBlue);
    cout << blk_ascii << "   " << "First Fit";
    ConsoleHandler::SetCursorPosition(90, 7);
    ConsoleHandler::SetColor(ColorCode::LightGreen);
    cout << blk_ascii << "   " << "Best Fit";
    ConsoleHandler::SetCursorPosition(90, 9);
    ConsoleHandler::SetColor(ColorCode::LightRed);
    cout << blk_ascii << "   " << "Worst Fit";


    UI::DrawTableBorder(114, 13, 3, 14);
    UI::DrawHorizontalLine(115, 3, 18);
    UI::DrawHorizontalLine(115, 3, 22);
    int vert = 26;
    for (int i = 0; i < partitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::DarkGray);
        UI::DrawVerticalLine(14, vert, 14), vert += 10;
        ConsoleHandler::SetColor(ColorCode::Brown);
        ConsoleHandler::SetCursorPosition(vert - 7, 13);
        cout << partitions[i];
    }

    ConsoleHandler::SetCursorPosition(5, 16);
    ConsoleHandler::SetColor(ColorCode::LightGray);

    cout << "Processes ID";
    int x = 27, y = 15;
    std::set<int> st;
    std::string s;
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        st = bestPartitions[i].process_id;
        x = (i) * 10 + 27, y = 15;
        ConsoleHandler::SetColor(ColorCode::LightBlue);
        ConsoleHandler::SetCursorPosition(x, y);
        int cnt = 0, def = x;
        s = "";
        for (auto el: st) {
            s += std::to_string(el);
            s += ", ";
        }
        if (s.size() > 8) cout << s.substr(0, 5) << "...";
        else cout << s.substr(0, s.size() - 2);
        st = bestPartitions[i].process_id;
        x = (i) * 10 + 27, y = 16;
        ConsoleHandler::SetColor(ColorCode::LightGreen);
        ConsoleHandler::SetCursorPosition(x, y);
        cnt = 0, def = x;
        s = "";
        for (auto el: st) {
            s += std::to_string(el);
            s += ", ";
        }
        if (s.size() > 8) cout << s.substr(0, 5) << "...";
        else cout << s.substr(0, s.size() - 2);
        st = worstPartitions[i].process_id;
        x = (i) * 10 + 27, y = 17;
        ConsoleHandler::SetColor(ColorCode::LightRed);
        ConsoleHandler::SetCursorPosition(x, y);
        cnt = 0, def = x;
        s = "";
        for (auto el: st) {
            s += std::to_string(el);
            s += ", ";
        }
        if (s.size() > 8) cout << s.substr(0, 6) << "...";
        else cout << s.substr(0, s.size() - 2);
    }
    ConsoleHandler::SetColor(ColorCode::LightGray);
    ConsoleHandler::SetCursorPosition(5, 20);
    cout << "Allocated";
    x = 30, y = 19;
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::LightBlue);
        cout << bestPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x, ++y);
        ConsoleHandler::SetColor(ColorCode::LightGreen);
        cout << bestPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x, ++y);
        ConsoleHandler::SetColor(ColorCode::LightRed);
        cout << worstPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y -= 2);
    }
    x = 30, y = 23;
    ConsoleHandler::SetColor(ColorCode::LightGray);
    ConsoleHandler::SetCursorPosition(5, 24);
    cout << "Unallocated";
    ConsoleHandler::SetCursorPosition(x, y);
    for (int i = 0; i < allocatedPartitions.size(); ++i) {
        ConsoleHandler::SetColor(ColorCode::LightBlue);
        cout << bestPartitions[i].space - bestPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x, ++y);
        ConsoleHandler::SetColor(ColorCode::LightGreen);
        cout << bestPartitions[i].space - bestPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x, ++y);
        ConsoleHandler::SetColor(ColorCode::LightRed);
        cout << worstPartitions[i].space - worstPartitions[i].allocated;
        ConsoleHandler::SetCursorPosition(x += 10, y -= 2);
    }

    ConsoleHandler::SetColor(ColorCode::Yellow);

    ConsoleHandler::SetCursorPosition(4, 4);
    cout << "1. Allocate";
    ConsoleHandler::SetCursorPosition(4, 6);
    cout << "2. Deallocate";
    ConsoleHandler::SetCursorPosition(4, 8);
    cout << "3. Back";
    ConsoleHandler::SetCursorPosition(4, 10);
    ConsoleHandler::SetColor(ColorCode::LightGray);
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
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    visualizeAll();
        }
        id = std::stoi(tmp);
        if (bestProcesses.find(id) != bestProcesses.end() &&
            bestProcesses.find(id) != bestProcesses.end() &&
            worstProcesses.find(id) != worstProcesses.end()) {
            DisplayInvalidInput(4, 6, "The id is already taken"),
                    visualizeAll();
        }
        ConsoleHandler::SetCursorPosition(4, 6);
        cout << "Process Space: ";
        cin >> processSpace;

        Process newProcess(id, processSpace);

        FirstFit::allocate(newProcess, bestPartitions);
        bestProcesses[id] = newProcess;

        BestFit::allocate(newProcess, bestPartitions);
        bestProcesses[id] = newProcess;

        WorstFit::allocate(newProcess, worstPartitions);
        worstProcesses[id] = newProcess;

        visualizeAll();
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
        std::string tmp;
        cin >> tmp;
        if (tmp.size() > 3) {
            DisplayInvalidInput(40, 26, "Large ID size, reenter another small id"),
                    visualizeAll();;
        }
        id = std::stoi(tmp);

        FirstFit::deallocate(id, bestProcesses, bestPartitions);

        BestFit::deallocate(id, bestProcesses, bestPartitions);

        WorstFit::deallocate(id, worstProcesses, worstPartitions);

        visualizeAll();
    } else if (choice == 3) {
        ConsoleHandler::ClearConsole();

        UI::DrawBoxBorder();

        DisplayFirstWindow();
    } else
        DisplayInvalidInput(4, 10),
                visualizeAll();
}

void Application::ExitApplication() {
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
    ConsoleHandler::SetCursorPosition(40, 12);
    ConsoleHandler::SetColor(ColorCode::LightRed);
    cout << "Exiting the application. Goodbye!";
    Sleep(2500);
    exit(EXIT_SUCCESS);
}

void Application::DisplayInvalidInput(int x, int y, std::string msg, int sleep) {
    ConsoleHandler::SetCursorPosition(x, y);
    ConsoleHandler::SetColor(ColorCode::Red);
    cout << msg;
    Sleep(sleep);
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

void Application::DisplaySuccessMessage(const std::string &message, int x, int y) {
    ConsoleHandler::SetCursorPosition(x, y);
    ConsoleHandler::SetColor(ColorCode::Green);
    cout << message;
    Sleep(1500);
    ConsoleHandler::SetColor(ColorCode::White);
}

void Application::DisplayInvalidPassword(std::string msg) {
    ConsoleHandler::SetCursorPosition(20, 18);
    ConsoleHandler::SetColor(ColorCode::Red);
    cout << msg;
    Sleep(1500);
    ConsoleHandler::ClearConsole();
    UI::DrawBoxBorder();
}

std::string Application::GetMaskedInput(int x, int y) {
    std::string password;
    char ch;
    ConsoleHandler::SetCursorPosition(x, y);
    while ((ch = _getch()) != '\r') {
        // ('\r' == enter key)
        if (ch == '\b') {
            // ('\b' == Backspace)
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

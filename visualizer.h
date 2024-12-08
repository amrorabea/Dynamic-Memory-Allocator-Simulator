#ifndef GUI_H
#define GUI_H

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

// Enumeration for color codes to enhance readability
enum class ColorCode {
    Black = 0,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
};

// Helper function to convert ColorCode to WORD
inline WORD GetColorAttribute(ColorCode foreground, ColorCode background) {
    return static_cast<WORD>((static_cast<int>(background) << 4) | (static_cast<int>(foreground)));
}

// Console handling class encapsulating all console-related functionalities
class ConsoleHandler {
public:
    // Sets the text color
    static void SetColor(ColorCode fontColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            WORD color = (csbi.wAttributes & 0xF0) | static_cast<int>(fontColor);
            SetConsoleTextAttribute(hConsole, color);
        }
    }

    // Sets both text and background color
    static void SetColorAndBackground(ColorCode fontColor, ColorCode backColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD color = GetColorAttribute(fontColor, backColor);
        SetConsoleTextAttribute(hConsole, color);
    }

    // Clears the console and sets the desired colors
    static void ClearConsole(ColorCode fontColor = ColorCode::White, ColorCode backColor = ColorCode::Black) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD consoleSize, charsWritten;
        COORD home = {0, 0};

        // Set colors
        SetColorAndBackground(fontColor, backColor);

        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
            FillConsoleOutputCharacter(hConsole, ' ', consoleSize, home, &charsWritten);
            FillConsoleOutputAttribute(hConsole, GetColorAttribute(fontColor, backColor), consoleSize, home, &charsWritten);
            SetConsoleCursorPosition(hConsole, home);
        }
    }

    // Sets the cursor position to (x, y)
    static void SetCursorPosition(int x, int y) {
        COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

// UI class handling window-related functionalities
class UI {
public:
    // Draws a box border with customizable size and position
    static void DrawBoxBorder(int width = 90, int height = 25, int offsetX = 0, int offsetY = 0) {
        ConsoleHandler::SetColor(ColorCode::DarkGray);

        // Top-left corner
        ConsoleHandler::SetCursorPosition(offsetX, offsetY);
        cout << char(201); // '╔'

        // Top border
        for (int i = 1; i < width - 1; ++i) {
            cout << char(205); // '═'
        }

        // Top-right corner
        cout << char(187); // '╗'

        // Sides
        for (int i = 1; i < height - 1; ++i) {
            ConsoleHandler::SetCursorPosition(offsetX, offsetY + i);
            cout << char(186); // '║'
            ConsoleHandler::SetCursorPosition(offsetX + width - 1, offsetY + i);
            cout << char(186); // '║'
        }

        // Bottom-left corner
        ConsoleHandler::SetCursorPosition(offsetX, offsetY + height - 1);
        cout << char(200); // '╚'

        // Bottom border
        for (int i = 1; i < width - 1; ++i) {
            cout << char(205); // '═'
        }

        // Bottom-right corner
        cout << char(188); // '╝'
    }

    // Displays the current time at the specified position
    static void DisplayTime(int x, int y) {
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        string timeStr = "Time: " + to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min);

        ConsoleHandler::SetCursorPosition(x, y);
        cout << timeStr;
    }

    // Displays the window title
    static void DisplayTitle(const string& title, int x, int y) {
        ConsoleHandler::SetColor(ColorCode::LightCyan);
        ConsoleHandler::SetCursorPosition(x, y);
        cout << title;
        ConsoleHandler::SetColor(ColorCode::White); // Reset to default
    }

    // Clears a specific region of the window
    static void ClearRegion(int startX, int startY, int width, int height) {
        for (int y = startY; y < startY + height; ++y) {
            ConsoleHandler::SetCursorPosition(startX, y);
            for (int x = startX; x < startX + width; ++x) {
                cout << ' ';
            }
        }
    }
};

// Application class handling the main logic
class Application {
private:
    vector<int> partitions;

public:
    // Initializes the application by loading partitions from a file
    void Initialize() {
        LoadPartitions();
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        DisplayFirstWindow();
        // Exit is handled within DisplayFirstWindow's loop
    }

private:
    // Loads partition values from the "partitions" file
    void LoadPartitions(const string& filename = "../data/partitions") {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening the file: " << filename << "!" << endl;
            exit(EXIT_FAILURE);
        }

        int value;
        while (file >> value) {
            partitions.push_back(value);
        }

        file.close();
    }

    // Saves partition values to the "partitions" file
    void SavePartitions(const string& filename = "../data/partitions") {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cerr << "Error opening the file for writing: " << filename << "!" << endl;
            exit(EXIT_FAILURE);
        }

        for (const auto& value : partitions) {
            file << value << endl;
        }

        file.close();
    }

    // Displays the first window with options
    void DisplayFirstWindow() {
        while (true) {
            UI::ClearRegion(2, 8, 86, 15); // Clear previous messages
            ConsoleHandler::SetCursorPosition(2, 10);
            ConsoleHandler::SetColor(ColorCode::Yellow);
            cout << "1. Update partition values (ADMINISTRATORS ONLY)";
            ConsoleHandler::SetCursorPosition(2, 12);
            cout << "2. Use default branches";
            ConsoleHandler::SetCursorPosition(2, 14);
            cout << "3. Exit";
            ConsoleHandler::SetCursorPosition(2, 16);
            ConsoleHandler::SetColor(ColorCode::White);
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

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
                    DisplayInvalidChoice();
                    break;
            }
        }
    }

    // Handles admin login
    void HandleAdminLogin() {
        const string adminPassword = "1";
        string inputPassword;

        while (true) {
            ConsoleHandler::ClearConsole();
            UI::DrawBoxBorder();
            UI::DisplayTitle("Admin Login", 31, 12);

            ConsoleHandler::SetColor(ColorCode::LightGreen);
            ConsoleHandler::SetCursorPosition(25, 13);
            cout << "Enter valid Admin password.";

            ConsoleHandler::SetColor(ColorCode::Yellow);
            ConsoleHandler::SetCursorPosition(30, 15);
            cout << "USERNAME: Admin";
            ConsoleHandler::SetCursorPosition(30, 16);
            cout << "PASSWORD: ";

            // Masked password input
            inputPassword = GetMaskedInput(41, 16);

            if (inputPassword == adminPassword) {
                ConsoleHandler::ClearConsole();
                UI::DrawBoxBorder();
                DisplayUpdatePartitionsWindow();
                break;
            } else {
                DisplayInvalidPassword();
            }
        }
    }

    // Displays the window for updating partitions
    void DisplayUpdatePartitionsWindow() {
        ConsoleHandler::SetCursorPosition(15, 10);
        ConsoleHandler::SetColor(ColorCode::Yellow);
        cout << "Updating Partition Sizes";

        ofstream tempFile("temp.txt", ios::trunc);
        if (!tempFile.is_open()) {
            cerr << "Error opening the file for writing: temp.txt!" << endl;
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < partitions.size(); ++i) {
            ConsoleHandler::SetCursorPosition(15, 15);
            ConsoleHandler::SetColor(ColorCode::LightCyan);
            cout << "Current partition's value: " << partitions[i];
            ConsoleHandler::SetCursorPosition(15, 16);
            cout << "New value: ";

            int newValue;
            cin >> newValue;
            partitions[i] = newValue;
            tempFile << newValue << endl;

            ConsoleHandler::SetCursorPosition(15, 17);
            ConsoleHandler::SetColor(ColorCode::LightGreen);
            cout << "New value: " << newValue;
            // Reset cursor for next input
            ConsoleHandler::SetCursorPosition(15, 18);
            cout << "                             "; // Clear previous input
        }

        tempFile.close();

        // Replace old partitions file with the updated one
        if (remove("../data/partitions") != 0) {
            cerr << "Error deleting the file: partitions" << endl;
            exit(EXIT_FAILURE);
        }
        if (rename("temp.txt", "../data/partitions") != 0) {
            cerr << "Error renaming the file: temp.txt to partitions" << endl;
            exit(EXIT_FAILURE);
        }

        // Reload partitions to reflect changes
        partitions.clear();
        LoadPartitions();

        // Return to the first window
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
    }

    // Handles user commands (placeholder for actual functionality)
    void HandleUserCommands() {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        ConsoleHandler::SetCursorPosition(15, 10);
        ConsoleHandler::SetColor(ColorCode::LightGreen);
        cout << "User Commands Interface (Not Implemented Yet)";
        // Implement actual user commands here
    }

    // Exits the application gracefully
    void ExitApplication() {
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
        ConsoleHandler::SetCursorPosition(35, 12);
        ConsoleHandler::SetColor(ColorCode::LightRed);
        cout << "Exiting the application. Goodbye!";
        Sleep(2000); // Pause for 2 seconds before exiting
        exit(EXIT_SUCCESS);
    }

    // Displays an invalid choice message
    void DisplayInvalidChoice() {
        ConsoleHandler::SetCursorPosition(2, 18);
        ConsoleHandler::SetColor(ColorCode::Red);
        cout << "Invalid choice. Please try again.";
        Sleep(1500); // Wait for 1.5 seconds
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
    }

    // Displays an invalid password message
    void DisplayInvalidPassword() {
        ConsoleHandler::SetCursorPosition(20, 18);
        ConsoleHandler::SetColor(ColorCode::Red);
        cout << "Invalid Password. Try again.";
        Sleep(1500); // Wait for 1.5 seconds
        ConsoleHandler::ClearConsole();
        UI::DrawBoxBorder();
    }

    // Gets masked input for password fields
    string GetMaskedInput(int x, int y) {
        string password;
        char ch;
        ConsoleHandler::SetCursorPosition(x, y);
        while ((ch = getch()) != '\r') { // Enter key
            if (ch == '\b') { // Backspace
                if (!password.empty()) {
                    password.pop_back();
                    ConsoleHandler::SetCursorPosition(--x, y);
                    cout << ' ' << '\b';
                }
            } else {
                password += ch;
                cout << '*';
                x++;
            }
        }
        cout << endl;
        return password;
    }
};

#endif // GUI_H
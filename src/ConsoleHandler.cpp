#include <ConsoleHandler.h>
#include <string>

inline WORD GetColorAttribute(ColorCode foreground, ColorCode background) {
    return static_cast<WORD>((static_cast<int>(background) << 4) | static_cast<int>(foreground));
}

void ConsoleHandler::SetColor(ColorCode fontColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        WORD color = (csbi.wAttributes & 0xF0) | static_cast<int>(fontColor);
        SetConsoleTextAttribute(hConsole, color);
    }
}

void ConsoleHandler::SetColorAndBackground(ColorCode fontColor, ColorCode backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = GetColorAttribute(fontColor, backgroundColor);
    SetConsoleTextAttribute(hConsole, color);
}

void ConsoleHandler::ClearConsole(ColorCode fontColor, ColorCode backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize, charsWritten;
    COORD home = {0, 0};

    SetColorAndBackground(fontColor, backgroundColor);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, ' ', consoleSize, home, &charsWritten);
        FillConsoleOutputAttribute(hConsole, GetColorAttribute(fontColor, backgroundColor), consoleSize, home,
                                   &charsWritten);
        SetConsoleCursorPosition(hConsole, home);
    }
}

void ConsoleHandler::SetCursorPosition(int x, int y) {
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#include "../include/UI.h"
#include "../include/ConsoleHandler.h"
#include "../include/ColorCode.h"
#include <iostream>
#include <ctime>

using std::cout;

void UI::DrawBoxBorder(int width, int height, int offsetX, int offsetY) {
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

void UI::DisplayTime(int x, int y) {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    char buffer[6];
    sprintf_s(buffer, "%02d:%02d", localTime->tm_hour, localTime->tm_min);
    std::string timeStr = "Time: " + std::string(buffer);

    ConsoleHandler::SetCursorPosition(x, y);
    std::cout << timeStr;
}

void UI::DisplayTitle(const std::string& title, int x, int y) {
    ConsoleHandler::SetColor(ColorCode::LightCyan);
    ConsoleHandler::SetCursorPosition(x, y);
    std::cout << title;
    ConsoleHandler::SetColor(ColorCode::White); // Reset to default
}

void UI::ClearRegion(int startX, int startY, int width, int height) {
    for (int y = startY; y < startY + height; ++y) {
        ConsoleHandler::SetCursorPosition(startX, y);
        for (int x = startX; x < startX + width; ++x) {
            std::cout << ' ';
        }
    }
}

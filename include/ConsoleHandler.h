#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <windows.h>
#include <ColorCode.h>

class ConsoleHandler {
public:
    static void SetColor(ColorCode fontColor);

    static void SetColorAndBackground(ColorCode fontColor, ColorCode backgroundColor);

    static void ClearConsole(ColorCode fontColor = ColorCode::White, ColorCode backgroundColor = ColorCode::Black);

    static void SetCursorPosition(int x, int y);
};

#endif // CONSOLEHANDLER_H

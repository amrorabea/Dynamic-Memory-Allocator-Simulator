#ifndef UI_H
#define UI_H
#include <string>

class UI {
public:
    static void DrawBoxBorder(int width = 120, int height = 30, int offsetX = 0, int offsetY = 0);

    static void DisplayTime(int x, int y);

    static void DisplayTitle(const std::string &title, int x, int y);

    static void ClearRegion(int startX, int startY, int width, int height);

    static void DrawTableBorder(int width, int height, int offsetX, int offsetY);

    static void DrawHorizontalLine(int width, int offsetX, int offsetY);

    static void DrawVerticalLine(int height, int offsetX, int offsetY);

    static void DrawSyriaFlag(int width, int offsetX, int offsetY);

};
#endif // UI_H

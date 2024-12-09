#ifndef UI_H
#define UI_H

#include <string>

class UI {
public:
    static void DrawBoxBorder(int width = 90, int height = 25, int offsetX = 0, int offsetY = 0);
    static void DisplayTime(int x, int y);
    static void DisplayTitle(const std::string& title, int x, int y);
    static void ClearRegion(int startX, int startY, int width, int height);
};

#endif // UI_H

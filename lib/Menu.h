#ifndef CONSOLEMENU_MENU_H
#define CONSOLEMENU_MENU_H
#include <windows.h>
#include <vector>
#include <string>

enum class MODE {
    MOUSE,
    KEYBOARD
};


struct ITEM {
    std::string Title;
    std::string Description;
    std::string Command;
};

class Menu {
private:
    MODE Mode;                  // 交互模式
    std::string Title;          // 菜单标题
    std::vector<ITEM> Items;    // 菜单选项
    std::string Tips;           // 菜单提示
    SHORT ConsoleHeight;        // 控制台高度属性
    SHORT ConsoleWidth;         // 控制台宽度属性

    // 获取控制台高,宽属性
    COORD GetConsoleSize();
    // 设置控制台宽度属性
    void SetConsoleWidth(SHORT _width);
    // 设置控制台高度属性
    void SetConsoleHeight(SHORT _height);
    // 设置控制台高,宽属性
    void SetConsoleSize(SHORT _width, SHORT _height);
    // 设置控制台标题属性
    void SetConsoleTitle(const std::string& _title);

    // 设置菜单标题
    void SetMenuTitle(const std::string& _title);
    // 设置菜单选项
    void SetMenuItems(const std::vector<ITEM>& _items);
    // 设置菜单提示
    void SetMenuTips(const std::string& _tips);
    // 设置菜单交互模式
    void SetMenuMode(MODE _mode);

private:





};


#endif //CONSOLEMENU_MENU_H

#include "Menu.h"

COORD Menu::GetConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(OUTPUT_HANDLE, &BufferInfo);
    ConsoleHeight = BufferInfo.dwSize.Y;
    ConsoleWidth = BufferInfo.dwSize.X;
}

void Menu::SetConsoleHeight(SHORT _height) {
    ConsoleHeight = _height;
}

void Menu::SetConsoleWidth(SHORT _width) {
    ConsoleWidth = _width;
}

void Menu::SetConsoleSize(SHORT _width, SHORT _height) {
    ConsoleHeight = _height;
    ConsoleWidth = _width;
}

void Menu::SetConsoleTitle_(const std::string &_title) {
    SetConsoleTitle(_title.c_str());
}

void Menu::SetMenuTitle(const std::string &_title) {
    Title = _title;
}

void Menu::SetMenuItems(const std::vector<ITEM> &_items) {
    Items = _items;
}

void Menu::SetMenuTips(const std::string &_tips) {
    Tips = _tips;
}

void Menu::SetMenuMode(MODE _mode) {
    Mode = _mode;
}

void Menu::GetDefaultStyle() {
    // 获取窗口缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(OUTPUT_HANDLE, &BufferInfo);
    // 获取初始定义的文本属性
    DefaultStyle = BufferInfo.wAttributes;
}

void Menu::SetConsoleStyle(WORD _style) {
    CurrentStyle = _style;
    SetConsoleTextAttribute(OUTPUT_HANDLE, _style);
}

void Menu::HideCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
    CursorInfo.bVisible = false;
    // 记录鼠标光标状态
    CursorState = CursorInfo.bVisible;
    SetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
}

void Menu::ShowCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
    CursorInfo.bVisible = true;
    // 记录鼠标光标状态
    CursorState = CursorInfo.bVisible;
    SetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
}

void Menu::InitMouseMode() {
    DWORD TempMode;
    GetConsoleMode(INPUT_HANDLE, &TempMode);
    // 记录控制台默认模式
    DefaultMode = TempMode;
    TempMode &= ~ENABLE_QUICK_EDIT_MODE;	// 禁用快速编辑模式
    TempMode &= ~ENABLE_INSERT_MODE;		// 禁用插入模式
    TempMode |= ENABLE_MOUSE_INPUT;			// 启用鼠标输入
    SetConsoleMode(INPUT_HANDLE, TempMode);
}

void Menu::RestoreConsoleMode() {
    SetConsoleMode(INPUT_HANDLE, DefaultMode);
    DefaultMode = 0;
}

void Menu::InitMenu(int _position) {
    // 初始化菜单位置
    int TotalItems = static_cast<int>(Items.size());
    int StartPosition = _position + 1;
    int EndPosition = StartPosition + TotalItems - 1;

    // 初始化菜单选项位置
    for (int i = 0; i < TotalItems; ++i) {
        Items[i].Index = i;
        Items[i].Position = {0, static_cast<SHORT>(StartPosition + i)};
        Items[i].Length = static_cast<SHORT>(4 + Items[i].Title.length());
    }
}

void Menu::DrawMenu() {
    // 绘制菜单标题
    std::cout << "[MENU] 请选择" << Title << std::endl;
    // 绘制菜单选项
    for (ITEM &item : Items) {
        std::cout << "[" << item.Index << "] " << item.Title << std::endl;
    }
    // 绘制菜单提示
    if (!Tips.empty()) {
        std::cout << "[TIPS] " << Tips << std::endl;
    }
}



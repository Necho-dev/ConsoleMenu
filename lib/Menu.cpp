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

void Menu::HideCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
    CursorInfo.bVisible = false;
    // ��¼�����״̬
    CursorState = CursorInfo.bVisible;
    SetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
}

void Menu::ShowCursor() {
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
    CursorInfo.bVisible = true;
    // ��¼�����״̬
    CursorState = CursorInfo.bVisible;
    SetConsoleCursorInfo(OUTPUT_HANDLE, &CursorInfo);
}

void Menu::InitMouseMode() {
    DWORD TempMode;
    GetConsoleMode(INPUT_HANDLE, &TempMode);
    // ��¼����̨Ĭ��ģʽ
    DefaultMode = TempMode;
    TempMode &= ~ENABLE_QUICK_EDIT_MODE;	// ���ÿ��ٱ༭ģʽ
    TempMode &= ~ENABLE_INSERT_MODE;		// ���ò���ģʽ
    TempMode |= ENABLE_MOUSE_INPUT;			// �����������
    SetConsoleMode(INPUT_HANDLE, TempMode);
}

void Menu::RestoreConsoleMode() {
    SetConsoleMode(INPUT_HANDLE, DefaultMode);
    DefaultMode = 0;
}

void Menu::InitMenu(int _position) {
    //
    int TotalItems = static_cast<int>(Items.size());
    int StartPosition = _position + 1;
    int EndPosition = StartPosition + TotalItems - 1;
    
}
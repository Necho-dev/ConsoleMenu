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
    // ��ȡ���ڻ�������Ϣ
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(OUTPUT_HANDLE, &BufferInfo);
    // ��ȡ��ʼ������ı�����
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
    // ��ʼ���˵�λ��
    int TotalItems = static_cast<int>(Items.size());
    int StartPosition = _position + 1;
    int EndPosition = StartPosition + TotalItems - 1;

    // ��ʼ���˵�ѡ��λ��
    for (int i = 0; i < TotalItems; ++i) {
        Items[i].Index = i;
        Items[i].Position = {0, static_cast<SHORT>(StartPosition + i)};
        Items[i].Length = static_cast<SHORT>(4 + Items[i].Title.length());
    }
}

void Menu::DrawMenu() {
    // ���Ʋ˵�����
    std::cout << "[MENU] ��ѡ��" << Title << std::endl;
    // ���Ʋ˵�ѡ��
    for (ITEM &item : Items) {
        std::cout << "[" << item.Index << "] " << item.Title << std::endl;
    }
    // ���Ʋ˵���ʾ
    if (!Tips.empty()) {
        std::cout << "[TIPS] " << Tips << std::endl;
    }
}



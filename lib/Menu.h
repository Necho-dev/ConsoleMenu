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
    MODE Mode;                  // ����ģʽ
    std::string Title;          // �˵�����
    std::vector<ITEM> Items;    // �˵�ѡ��
    std::string Tips;           // �˵���ʾ
    SHORT ConsoleHeight;        // ����̨�߶�����
    SHORT ConsoleWidth;         // ����̨�������

    // ��ȡ����̨��,������
    COORD GetConsoleSize();
    // ���ÿ���̨�������
    void SetConsoleWidth(SHORT _width);
    // ���ÿ���̨�߶�����
    void SetConsoleHeight(SHORT _height);
    // ���ÿ���̨��,������
    void SetConsoleSize(SHORT _width, SHORT _height);
    // ���ÿ���̨��������
    void SetConsoleTitle(const std::string& _title);

    // ���ò˵�����
    void SetMenuTitle(const std::string& _title);
    // ���ò˵�ѡ��
    void SetMenuItems(const std::vector<ITEM>& _items);
    // ���ò˵���ʾ
    void SetMenuTips(const std::string& _tips);
    // ���ò˵�����ģʽ
    void SetMenuMode(MODE _mode);

private:





};


#endif //CONSOLEMENU_MENU_H

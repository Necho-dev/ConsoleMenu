#ifndef CONSOLEMENU_MENU_H
#define CONSOLEMENU_MENU_H
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

#define INPUT_HANDLE GetStdHandle(STD_INPUT_HANDLE)
#define OUTPUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define SELECTED_STYLE static_cast<int>(FOREGROUND::BLACK) | static_cast<int>(BACKGROUND::WHITE)

// ����ģʽ
enum class MODE {
    MOUSE,
    KEYBOARD
};

// ���к�����
enum TYPE {
    NUMBER = 0,            // ����
    LETTER_UPPER = 'A',    // ��д��ĸ
    LETTER_LOWER = 'a',    // Сд��ĸ
};

// ����¼�
enum MOUSE {
    CLICK = 0x0,            // ��갴�����»��ɿ�ʱ����
    MOVED = 0x1,            // ����ƶ�ʱ����
    DBLCLICK = 0x2,         // ���ڶ��ΰ���ʱ����(���¼�ǰ���ᴥ��CLICK�¼�)
    WHEEL = 0x4,            // �����ֹ���ʱ����
    LEFT_BUTTON = 0x0001,   // ������
    RIGHT_BUTTON = 0x0002,  // ����Ҽ�
    MIDDLE_BUTTON = 0x0004, // ����м�
};

// �����¼�
enum KEYBOARD {
    ENTER = 13,             // �س���
    KEYUP = 72,             // ����"��"��
    KEYDOWN = 80,           // ����"��"��
};

// �˵�ѡ��ṹ��
struct ITEM {
    int Index;
    int Length;
    std::string Title;
    std::string Value;
    COORD Position;
//    TODO: �����¼�����
//    MOUSE MouseEvent;
//    KEYBOARD KeyboardEvent;

    // ���캯��
    ITEM() : Index(0), Length(0), Position({0, 0}) {}
    ITEM(std::string& title, std::string& value) : Index(0), Length(0), Title(title), Value(value), Position({0, 0}) {}

    // ���رȽ�("==")�����
    bool operator== (const COORD &MousePosition) const {
        if (Position.Y == MousePosition.Y and Position.X <= MousePosition.X and MousePosition.X < Position.X + Length) {
            return true;
        }
        return false;
    }

    // ���ظ�ֵ("=")�����
    ITEM& operator= (const ITEM& item) {
        if (this != &item) {
            Index = item.Index;
            Title = item.Title;
            Value = item.Value;
            Position = item.Position;
            Length = item.Length;
        }
    }

    // ��������
    ~ITEM() = default;

};

class Menu {
private:
    MODE Mode;                  // ����ģʽ
    WORD DefaultStyle;          // Ĭ����ʽ
    WORD CurrentStyle;          // ��ǰ��ʽ
    std::string Title;          // �˵�����
    std::vector<ITEM> Items;    // �˵�ѡ��
    std::string Tips;           // �˵���ʾ
    SHORT ConsoleHeight;        // ����̨�߶�����
    SHORT ConsoleWidth;         // ����̨�������
    DWORD DefaultMode;          // ����̨Ĭ��ģʽ
    bool CursorState;           // �����״̬


    // ��ȡ����̨��,������
    COORD GetConsoleSize();
    // ���ÿ���̨�������
    void SetConsoleWidth(SHORT _width);
    // ���ÿ���̨�߶�����
    void SetConsoleHeight(SHORT _height);
    // ���ÿ���̨��,������
    void SetConsoleSize(SHORT _width, SHORT _height);
    // ����ѡ��λ���Զ���������̨��,������
    void AutoSetConSoleSize(ITEM _item);
    // ���ÿ���̨��������
    static void SetConsoleTitle_(const std::string& _title);

    // ���ò˵�����
    void SetMenuTitle(const std::string& _title);
    // ���ò˵�ѡ��
    void SetMenuItems(const std::vector<ITEM>& _items);
    // ���ò˵���ʾ
    void SetMenuTips(const std::string& _tips);
    // ���ò˵�����ģʽ
    void SetMenuMode(MODE _mode);

    // ��ȡ����̨Ĭ����ʽ
    void GetDefaultStyle();
    // ���ÿ���̨��ʽ
    void SetConsoleStyle(WORD _style);


private:
    // ���������
    void HideCursor();
    // ��ʾ�����
    void ShowCursor();
    // ��ʼ����꽻��ģʽ
    void InitMouseMode();
    // �ָ�����̨����ģʽ
    void RestoreConsoleMode();

    // ��ʼ���˵�
    void InitMenu(int _position);
    // ���Ʋ˵�
    void DrawMenu();

public:
    // ���캯��
    Menu();
    // ��������
    ~Menu();

    // ��ʾ�˵�
    void Show();

};


#endif //CONSOLEMENU_MENU_H

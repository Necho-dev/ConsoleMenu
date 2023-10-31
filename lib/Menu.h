#ifndef CONSOLEMENU_MENU_H
#define CONSOLEMENU_MENU_H
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

#define INPUT_HANDLE GetStdHandle(STD_INPUT_HANDLE)
#define OUTPUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define SELECTED_STYLE static_cast<int>(FOREGROUND::BLACK) | static_cast<int>(BACKGROUND::WHITE)

// 交互模式
enum class MODE {
    MOUSE,
    KEYBOARD
};

// 序列号类型
enum TYPE {
    NUMBER = 0,            // 数字
    LETTER_UPPER = 'A',    // 大写字母
    LETTER_LOWER = 'a',    // 小写字母
};

// 鼠标事件
enum MOUSE {
    CLICK = 0x0,            // 鼠标按键按下或松开时触发
    MOVED = 0x1,            // 鼠标移动时触发
    DBLCLICK = 0x2,         // 鼠标第二次按下时触发(此事件前定会触发CLICK事件)
    WHEEL = 0x4,            // 鼠标滚轮滚动时触发
    LEFT_BUTTON = 0x0001,   // 鼠标左键
    RIGHT_BUTTON = 0x0002,  // 鼠标右键
    MIDDLE_BUTTON = 0x0004, // 鼠标中键
};

// 键盘事件
enum KEYBOARD {
    ENTER = 13,             // 回车键
    KEYUP = 72,             // 方向"↑"键
    KEYDOWN = 80,           // 方向"↓"键
};

// 菜单选项结构体
struct ITEM {
    int Index;
    int Length;
    std::string Title;
    std::string Value;
    COORD Position;
//    TODO: 触发事件定义
//    MOUSE MouseEvent;
//    KEYBOARD KeyboardEvent;

    // 构造函数
    ITEM() : Index(0), Length(0), Position({0, 0}) {}
    ITEM(std::string& title, std::string& value) : Index(0), Length(0), Title(title), Value(value), Position({0, 0}) {}

    // 重载比较("==")运算符
    bool operator== (const COORD &MousePosition) const {
        if (Position.Y == MousePosition.Y and Position.X <= MousePosition.X and MousePosition.X < Position.X + Length) {
            return true;
        }
        return false;
    }

    // 重载赋值("=")运算符
    ITEM& operator= (const ITEM& item) {
        if (this != &item) {
            Index = item.Index;
            Title = item.Title;
            Value = item.Value;
            Position = item.Position;
            Length = item.Length;
        }
    }

    // 析构函数
    ~ITEM() = default;

};

class Menu {
private:
    MODE Mode;                  // 交互模式
    WORD DefaultStyle;          // 默认样式
    WORD CurrentStyle;          // 当前样式
    std::string Title;          // 菜单标题
    std::vector<ITEM> Items;    // 菜单选项
    std::string Tips;           // 菜单提示
    SHORT ConsoleHeight;        // 控制台高度属性
    SHORT ConsoleWidth;         // 控制台宽度属性
    DWORD DefaultMode;          // 控制台默认模式
    bool CursorState;           // 鼠标光标状态


    // 获取控制台高,宽属性
    COORD GetConsoleSize();
    // 设置控制台宽度属性
    void SetConsoleWidth(SHORT _width);
    // 设置控制台高度属性
    void SetConsoleHeight(SHORT _height);
    // 设置控制台高,宽属性
    void SetConsoleSize(SHORT _width, SHORT _height);
    // 根据选项位置自动调整控制台高,宽属性
    void AutoSetConSoleSize(ITEM _item);
    // 设置控制台标题属性
    static void SetConsoleTitle_(const std::string& _title);

    // 设置菜单标题
    void SetMenuTitle(const std::string& _title);
    // 设置菜单选项
    void SetMenuItems(const std::vector<ITEM>& _items);
    // 设置菜单提示
    void SetMenuTips(const std::string& _tips);
    // 设置菜单交互模式
    void SetMenuMode(MODE _mode);

    // 获取控制台默认样式
    void GetDefaultStyle();
    // 设置控制台样式
    void SetConsoleStyle(WORD _style);


private:
    // 隐藏鼠标光标
    void HideCursor();
    // 显示鼠标光标
    void ShowCursor();
    // 初始化鼠标交互模式
    void InitMouseMode();
    // 恢复控制台交互模式
    void RestoreConsoleMode();

    // 初始化菜单
    void InitMenu(int _position);
    // 绘制菜单
    void DrawMenu();

public:
    // 构造函数
    Menu();
    // 析构函数
    ~Menu();

    // 显示菜单
    void Show();

};


#endif //CONSOLEMENU_MENU_H

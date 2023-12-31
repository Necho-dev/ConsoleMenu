#ifndef CONSOLEMENU_LOGS_H
#define CONSOLEMENU_LOGS_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Utils.h"
#include <iomanip>
#define INPUT_HANDLE GetStdHandle(STD_INPUT_HANDLE)
#define OUTPUT_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

enum MOUSE {
    CLICK = 0x0,            // 鼠标按键按下或松开时触发
    MOVED = 0x1,            // 鼠标移动时触发
    DBLCLICK = 0x2,         // 鼠标第二次按下时触发(此事件前定会触发CLICK事件)
    WHEEL = 0x4,            // 鼠标滚轮滚动时触发
    LEFT_BUTTON = 0x0001,   // 鼠标左键
    RIGHT_BUTTON = 0x0002,  // 鼠标右键
    MIDDLE_BUTTON = 0x0004, // 鼠标中键
};

enum class FOREGROUND {
    RED     =   FOREGROUND_INTENSITY | FOREGROUND_RED,
    BLUE    =   FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN   =   FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    PURPLE  =   FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW  =   FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    CYAN    =   FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
    WHITE   =   FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    GRAY    =   FOREGROUND_INTENSITY,
    BLACK   =   0
};

enum class BACKGROUND {
    RED     =   BACKGROUND_INTENSITY | BACKGROUND_RED,
    BLUE    =   BACKGROUND_INTENSITY | BACKGROUND_BLUE,
    GREEN   =   BACKGROUND_INTENSITY | BACKGROUND_GREEN,
    PURPLE  =   BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
    YELLOW  =   BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
    CYAN    =   BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
    WHITE   =   BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,
    GRAY    =   BACKGROUND_INTENSITY,
    BLACK   =   0
};

class Logs {
private:
    Logs();
    ~Logs();
    static WORD getOriginAttr(HANDLE _handle);
public:
    // 设置控制台输出的字体前景色
    static void echo(const char* Content, FOREGROUND FColor);
    static void echo(const std::string& Content, FOREGROUND FColor);

    // 设置控制台输出的字体前景色和背景色
    static void echo(const char* Content, FOREGROUND FColor, BACKGROUND BColor);
    static void echo(const std::string& Content, FOREGROUND FColor, BACKGROUND BColor);

    static void tips(const char* Content);
    static void tips(const std::string& Content);

    static void info(const char* Content);
    static void info(const std::string& Content);

    static void warn(const char* Content);
    static void warn(const std::string& Content);

    static void error(const char* Content);
    static void error(const std::string& Content);

    static void success(const char* Content);
    static void success(const std::string& Content);

    static int selectMenu(const std::vector<std::string>& choices, const std::string& title = "Select Menu");
    static int MouseMenu(const std::vector<std::string>& choices, const std::string& title = "Select Menu");

    static bool ProcessBar(int total=35, int wait=50);
};


#endif //CONSOLEMENU_LOGS_H

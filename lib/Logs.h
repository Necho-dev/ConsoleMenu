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
    CLICK = 0x0,            // ��갴�����»��ɿ�ʱ����
    MOVED = 0x1,            // ����ƶ�ʱ����
    DBLCLICK = 0x2,         // ���ڶ��ΰ���ʱ����(���¼�ǰ���ᴥ��CLICK�¼�)
    WHEEL = 0x4,            // �����ֹ���ʱ����
    LEFT_BUTTON = 0x0001,   // ������
    RIGHT_BUTTON = 0x0002,  // ����Ҽ�
    MIDDLE_BUTTON = 0x0004, // ����м�
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
    // ���ÿ���̨���������ǰ��ɫ
    static void echo(const char* Content, FOREGROUND FColor);
    static void echo(const std::string& Content, FOREGROUND FColor);

    // ���ÿ���̨���������ǰ��ɫ�ͱ���ɫ
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

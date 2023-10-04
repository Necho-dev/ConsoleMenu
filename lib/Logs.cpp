#include "Logs.h"

Logs::Logs() = default;

Logs::~Logs() = default;

WORD Logs::getOriginAttr(HANDLE _handle) {
    // 获取窗口缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(_handle, &BufferInfo);
    // 获取初始定义的文本属性
    return BufferInfo.wAttributes;
}

void Logs::echo(const char* Content, FOREGROUND FColor) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD OriginAttr = getOriginAttr(H);
    SetConsoleTextAttribute(H, static_cast<int>(FColor));
    std::cout << Content << std::endl;
    SetConsoleTextAttribute(H, OriginAttr);
}

void Logs::echo(const std::string& Content, FOREGROUND FColor) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD OriginAttr = getOriginAttr(H);
    SetConsoleTextAttribute(H, static_cast<int>(FColor));
    std::cout << Content << std::endl;
    SetConsoleTextAttribute(H, OriginAttr);
}

void Logs::echo(const char* Content, FOREGROUND FColor, BACKGROUND BColor) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD OriginAttr = getOriginAttr(H);
    SetConsoleTextAttribute(H, static_cast<int>(FColor) | static_cast<int>(BColor));
    std::cout << Content << std::endl;
    SetConsoleTextAttribute(H, OriginAttr);
}

void Logs::echo(const std::string& Content, FOREGROUND FColor, BACKGROUND BColor) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD OriginAttr = getOriginAttr(H);
    SetConsoleTextAttribute(H, static_cast<int>(FColor) | static_cast<int>(BColor));
    std::cout << Content << std::endl;
    SetConsoleTextAttribute(H, OriginAttr);
}

void Logs::tips(const char *Content) {
    const auto TipsColor = FOREGROUND::CYAN;
    echo(Utils::ToString("[TIPS] ", Content), TipsColor);
}

void Logs::tips(const std::string& Content) {
    const auto TipsColor = FOREGROUND::CYAN;
    echo(Utils::ToString("[TIPS] ", Content), TipsColor);
}

void Logs::info(const char *Content) {
    const auto InfoColor = FOREGROUND::BLUE;
    echo(Utils::ToString("[INFO] ", Content), InfoColor);
}

void Logs::info(const std::string& Content) {
    const auto InfoColor = FOREGROUND::BLUE;
    echo(Utils::ToString("[INFO] ", Content), InfoColor);
}

void Logs::warn(const char *Content) {
    const auto WarnColor = FOREGROUND::YELLOW;
    echo(Utils::ToString("[WARN] ", Content), WarnColor);
}

void Logs::warn(const std::string &Content) {
    const auto WarnColor = FOREGROUND::YELLOW;
    echo(Utils::ToString("[WARN] ", Content), WarnColor);
}

void Logs::error(const char *Content) {
    const auto ErrorColor = FOREGROUND::RED;
    echo(Utils::ToString("[ERROR] ", Content), ErrorColor);
}

void Logs::error(const std::string &Content) {
    const auto ErrorColor = FOREGROUND::RED;
    echo(Utils::ToString("[ERROR] ", Content), ErrorColor);
}

void Logs::success(const char *Content) {
    const auto SuccessColor = FOREGROUND::GREEN;
    echo(Utils::ToString("[SUCCESS] ", Content), SuccessColor);
}

void Logs::success(const std::string &Content) {
    const auto SuccessColor = FOREGROUND::GREEN;
    echo(Utils::ToString("[SUCCESS] ", Content), SuccessColor);
}

int Logs::selectMenu(const std::vector<std::string>& choices, const std::string &title) {
    // 获取窗口缓冲区信息
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(H, &BufferInfo);
    // 初始化菜单信息
    int totalChoices = static_cast<int>(choices.size());
    int startPosition = BufferInfo.dwCursorPosition.Y + 1;
    int endPosition = startPosition + totalChoices - 1;
    WORD defaultStyle = getOriginAttr(H);
    WORD selectedStyle = static_cast<int>(FOREGROUND::BLACK) | static_cast<int>(BACKGROUND::WHITE);

    // 控制台输出选择菜单
    echo(Utils::ToString("[MENU] 请选择", title, "："), FOREGROUND::WHITE);
    for (int i = 0; i < choices.size(); ++i) {
        echo(Utils::ToString("[", i, "] ", choices[i]), FOREGROUND::WHITE);
    }
    tips("按↑/↓键切换选项，回车键确认选择");

    // 设置初始光标和选择
    int choice = 0;
    SetConsoleCursorPosition(H, {0, static_cast<SHORT>(startPosition)});
    SetConsoleTextAttribute(H, selectedStyle);
    std::cout << Utils::ToString("[0] ", choices[0]);
    // 设置循环标志
    bool flag = true;
    while (true) {
        // 获取用户操作
        int ch = getch();
        // 获取当前光标位置
        CONSOLE_SCREEN_BUFFER_INFO NowBufferInfo;
        GetConsoleScreenBufferInfo(H, &NowBufferInfo);
        // 初始化光标位置
        int initPosition = NowBufferInfo.dwCursorPosition.Y;
        int Position = initPosition;
        // 若操作为方向"↑"键(72)
        if (ch == 72) {
            // 若光标在首行
            if (Position == startPosition) {
                // 直接移动光标至末行
                Position = endPosition;
            } else {
                // 移动光标至上一行
                Position = Position - 1;
            }
        // 若操作为方向"↓"键(80)
        } else if (ch == 80) {
            // 若光标在末行
            if (Position == endPosition) {
                // 直接移动光标至首行
                Position = startPosition;
            } else {
                // 移动光标至下一行
                Position = Position + 1;
            }
        // 若操作为回车"ENTER"键(13)
        } else if (ch == 13) {
            // 记录选择行
            choice = Position - startPosition;
            // 直接移动光标至控制台末尾
            Position = startPosition - 1;
            // 标记已选择
            flag = false;
        // 若操作为其他键
        } else {
            // 没有任何操作
            continue;
        }
        // 恢复当前选择行样式
        SetConsoleTextAttribute(H, defaultStyle);
        SetConsoleCursorPosition(H, {0, static_cast<SHORT>(initPosition)});
        std::cout << Utils::ToString("[", initPosition - startPosition, "] ", choices[initPosition - startPosition]);
        // 若已选择则直接返回选择
        if (!flag) {
            // 清除菜单
            for (int i = 0; i < totalChoices + 1; ++i) {
                SetConsoleCursorPosition(H, {0, static_cast<SHORT>(startPosition + i)});
                std::cout << std::string(BufferInfo.dwSize.X, ' ');
            }
            SetConsoleCursorPosition(H, {0, static_cast<SHORT>(Position)});
            echo(Utils::ToString("[OK] 您选择的", title, "：[", choice, "] ", choices[choice]), FOREGROUND::WHITE);
            return choice;
        };
        // 控制光标移动至指定位置
        SetConsoleCursorPosition(H, {0, static_cast<SHORT>(Position)});
        // 设置当前选择行样式
        SetConsoleTextAttribute(H, selectedStyle);
        std::cout << Utils::ToString("[", Position - startPosition, "] ", choices[Position - startPosition]);
    }
}

bool Logs::ProcessBar(int total, int wait) {
    // 获取窗口缓冲区信息
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    // 获取当前控制台光标位置
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(H, &BufferInfo);
    // 定义更新光标位置
    int Position = 9;
    SetConsoleTextAttribute(H, static_cast<int>(FOREGROUND::WHITE));
    // 初始化进度条 -
    std::cout << "\r正在保存 | ";
    // 控制台绘制进度条
    for (int i = 0; i < total; i++) {
        // 计算当前进度
        double progress = i * 100.0 / (total - 1);
        // 控制台输出进度
        if (i == total - 1) {
            SetConsoleCursorPosition(H, {0, BufferInfo.dwCursorPosition.Y});
            std::cout << "\r完成保存 | ";
        }
        SetConsoleCursorPosition(H, {static_cast<SHORT>(Position), BufferInfo.dwCursorPosition.Y});
        std::cout << Utils::Format("█ %0.2lf%%", progress);
        // 调整光标位置
        Position += 1;
        Sleep(wait);
    }
    std::cout << std::endl;
    return true;
}

int Logs::MouseMenu(const std::vector <std::string> &choices, const std::string &title) {
    // 初始化控制台属性
    DWORD Mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &Mode);
    Mode &= ~ENABLE_QUICK_EDIT_MODE;	// 禁用快速编辑模式
    Mode &= ~ENABLE_INSERT_MODE;		// 禁用插入模式
    Mode |= ENABLE_MOUSE_INPUT;			// 启用鼠标输入
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), Mode);

    // 隐藏鼠标光标
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);

    // 获取窗口缓冲区信息
    HANDLE H = OUTPUT_HANDLE;
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(H, &BufferInfo);

    // 初始化菜单信息
    int TotalChoices = static_cast<int>(choices.size());
    int StartPosition = BufferInfo.dwCursorPosition.Y + 1;
    int EndPosition = StartPosition + TotalChoices - 1;
    WORD defaultStyle = getOriginAttr(H);
    WORD selectedStyle = static_cast<int>(FOREGROUND::BLACK) | static_cast<int>(BACKGROUND::WHITE);

    // 控制台输出选择菜单
    echo(Utils::ToString("[MENU] 请选择", title, "："), FOREGROUND::WHITE);
    for (int i = 0; i < choices.size(); ++i) {
        echo(Utils::ToString("[", i, "] ", choices[i]), FOREGROUND::WHITE);
    }

    // 设置初始选择
    int choice = 0;

    bool flag = false;
    // 初始化光标位置
    int initPosition = StartPosition;
    int Position = initPosition;
    while (!flag) {
        INPUT_RECORD InputRecord;       // 输入事件
        DWORD Event;                    // 临时寄存
        MOUSE_EVENT_RECORD MouseEvent;  // 鼠标事件
        ReadConsoleInput(INPUT_HANDLE, &InputRecord, 1, &Event);
        // 是否为鼠标事件
        if (InputRecord.EventType == MOUSE_EVENT) {
            MouseEvent = InputRecord.Event.MouseEvent;
        }
        switch (MouseEvent.dwEventFlags) {
            case MOUSE::MOVED: {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, static_cast<SHORT>(8)});
                std::cout << Utils::ToString("MousePosition | ", MouseEvent.dwMousePosition.Y, "/", MouseEvent.dwMousePosition.X);
                Position = MouseEvent.dwMousePosition.Y;
                break;
            }
            case MOUSE::CLICK: {
                if (MouseEvent.dwButtonState and MouseEvent.dwButtonState != MOUSE::WHEEL) {
                    flag = true;
                }
                break;
            }
        }
        if (initPosition != Position && Position >= StartPosition && Position <= EndPosition) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, static_cast<SHORT>(9)});
            std::cout << Utils::ToString("Init/Current | ", initPosition, "/", Position);
            // 恢复当前选择行样式
            SetConsoleTextAttribute(H, defaultStyle);
            SetConsoleCursorPosition(H, {0, static_cast<SHORT>(initPosition)});
            std::cout << Utils::ToString("[", initPosition - StartPosition, "] ", choices[initPosition - StartPosition]);
            // 控制光标移动至指定位置
            SetConsoleCursorPosition(H, {0, static_cast<SHORT>(Position)});
            // 设置当前选择行样式
            SetConsoleTextAttribute(H, selectedStyle);
            std::cout << Utils::ToString("[", Position - StartPosition, "] ", choices[Position - StartPosition]);

            initPosition = Position;
        }
    }

    return 0;
}
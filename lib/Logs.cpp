#include "Logs.h"

Logs::Logs() = default;

Logs::~Logs() = default;

WORD Logs::getOriginAttr(HANDLE _handle) {
    // ��ȡ���ڻ�������Ϣ
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(_handle, &BufferInfo);
    // ��ȡ��ʼ������ı�����
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
    // ��ȡ���ڻ�������Ϣ
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(H, &BufferInfo);
    // ��ʼ���˵���Ϣ
    int totalChoices = static_cast<int>(choices.size());
    int startPosition = BufferInfo.dwCursorPosition.Y + 1;
    int endPosition = startPosition + totalChoices - 1;
    WORD defaultStyle = getOriginAttr(H);
    WORD selectedStyle = static_cast<int>(FOREGROUND::BLACK) | static_cast<int>(BACKGROUND::WHITE);

    // ����̨���ѡ��˵�
    echo(Utils::ToString("[MENU] ��ѡ��", title, "��"), FOREGROUND::WHITE);
    for (int i = 0; i < choices.size(); ++i) {
        echo(Utils::ToString("[", i, "] ", choices[i]), FOREGROUND::WHITE);
    }
    tips("����/�����л�ѡ��س���ȷ��ѡ��");

    // ���ó�ʼ����ѡ��
    int choice = 0;
    SetConsoleCursorPosition(H, {0, static_cast<SHORT>(startPosition)});
    SetConsoleTextAttribute(H, selectedStyle);
    std::cout << Utils::ToString("[0] ", choices[0]);
    // ����ѭ����־
    bool flag = true;
    while (true) {
        // ��ȡ�û�����
        int ch = getch();
        // ��ȡ��ǰ���λ��
        CONSOLE_SCREEN_BUFFER_INFO NowBufferInfo;
        GetConsoleScreenBufferInfo(H, &NowBufferInfo);
        // ��ʼ�����λ��
        int initPosition = NowBufferInfo.dwCursorPosition.Y;
        int Position = initPosition;
        // ������Ϊ����"��"��(72)
        if (ch == 72) {
            // �����������
            if (Position == startPosition) {
                // ֱ���ƶ������ĩ��
                Position = endPosition;
            } else {
                // �ƶ��������һ��
                Position = Position - 1;
            }
        // ������Ϊ����"��"��(80)
        } else if (ch == 80) {
            // �������ĩ��
            if (Position == endPosition) {
                // ֱ���ƶ����������
                Position = startPosition;
            } else {
                // �ƶ��������һ��
                Position = Position + 1;
            }
        // ������Ϊ�س�"ENTER"��(13)
        } else if (ch == 13) {
            // ��¼ѡ����
            choice = Position - startPosition;
            // ֱ���ƶ����������̨ĩβ
            Position = startPosition - 1;
            // �����ѡ��
            flag = false;
        // ������Ϊ������
        } else {
            // û���κβ���
            continue;
        }
        // �ָ���ǰѡ������ʽ
        SetConsoleTextAttribute(H, defaultStyle);
        SetConsoleCursorPosition(H, {0, static_cast<SHORT>(initPosition)});
        std::cout << Utils::ToString("[", initPosition - startPosition, "] ", choices[initPosition - startPosition]);
        // ����ѡ����ֱ�ӷ���ѡ��
        if (!flag) {
            // ����˵�
            for (int i = 0; i < totalChoices + 1; ++i) {
                SetConsoleCursorPosition(H, {0, static_cast<SHORT>(startPosition + i)});
                std::cout << std::string(BufferInfo.dwSize.X, ' ');
            }
            SetConsoleCursorPosition(H, {0, static_cast<SHORT>(Position)});
            echo(Utils::ToString("[OK] ��ѡ���", title, "��[", choice, "] ", choices[choice]), FOREGROUND::WHITE);
            return choice;
        };
        // ���ƹ���ƶ���ָ��λ��
        SetConsoleCursorPosition(H, {0, static_cast<SHORT>(Position)});
        // ���õ�ǰѡ������ʽ
        SetConsoleTextAttribute(H, selectedStyle);
        std::cout << Utils::ToString("[", Position - startPosition, "] ", choices[Position - startPosition]);
    }
}

bool Logs::ProcessBar(int total, int wait) {
    // ��ȡ���ڻ�������Ϣ
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    // ��ȡ��ǰ����̨���λ��
    CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
    GetConsoleScreenBufferInfo(H, &BufferInfo);
    // ������¹��λ��
    int Position = 9;
    SetConsoleTextAttribute(H, static_cast<int>(FOREGROUND::WHITE));
    // ��ʼ�������� -
    std::cout << "\r���ڱ��� | ";
    // ����̨���ƽ�����
    for (int i = 0; i < total; i++) {
        // ���㵱ǰ����
        double progress = i * 100.0 / (total - 1);
        // ����̨�������
        if (i == total - 1) {
            SetConsoleCursorPosition(H, {0, BufferInfo.dwCursorPosition.Y});
            std::cout << "\r��ɱ��� | ";
        }
        SetConsoleCursorPosition(H, {static_cast<SHORT>(Position), BufferInfo.dwCursorPosition.Y});
        std::cout << Utils::Format("�� %0.2lf%%", progress);
        // �������λ��
        Position += 1;
        Sleep(wait);
    }
    std::cout << std::endl;
    return true;
}

COORD GetCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO temp;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_INPUT_HANDLE), &temp);
    return temp.dwCursorPosition;
}

// �ȴ�����¼����¼���������ƶ�����������ֹ�����һ�������������¼�
MOUSE_EVENT_RECORD waitMouseEvent(bool move = true) {
    INPUT_RECORD record; //�����¼�
    DWORD reg;           //��ʱ�Ĵ�
    while (true) {
        Sleep(10);
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &record, 1, &reg);                                  //�������¼�����record
        if (record.EventType == MOUSE_EVENT and (move | (record.Event.MouseEvent.dwEventFlags != MOUSE_MOVED))) //������¼� && �ƶ��¼���ģʽ��Ӧ
            return record.Event.MouseEvent;
    }
}

int Logs::MouseMenu(const std::vector <std::string> &choices, const std::string &title) {
    DWORD Mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &Mode);
    Mode &= ~ENABLE_QUICK_EDIT_MODE;	//�Ƴ����ٱ༭ģʽ
    Mode &= ~ENABLE_INSERT_MODE;		//�Ƴ�����ģʽ
    Mode |= ENABLE_MOUSE_INPUT;			//�����������
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), Mode);

    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);

    MOUSE_EVENT_RECORD mouseEvent;

    // ����̨���ѡ��˵�
    echo(Utils::ToString("[MENU] ��ѡ��", title, "��"), FOREGROUND::WHITE);
    for (int i = 0; i < choices.size(); ++i) {
        echo(Utils::ToString("[", i, "] ", choices[i]), FOREGROUND::WHITE);
    }

    bool isExit = false;
    while (!isExit) {
        mouseEvent = waitMouseEvent();
        switch (mouseEvent.dwEventFlags) {
            case mouseMove: {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, static_cast<SHORT>(8)});
                std::cout << Utils::ToString("MousePosition | ", mouseEvent.dwMousePosition.Y, "/", mouseEvent.dwMousePosition.X);
//                refresh(mouseEvent.dwMousePosition);
                break;
            }
            case mouseClick: {
                if (mouseEvent.dwButtonState and mouseEvent.dwButtonState != mouseWheel) {
//                    isExit = implement(mouseEvent);
                    isExit = true;
                }
                break;
            }
        }
    }

    return 0;
}
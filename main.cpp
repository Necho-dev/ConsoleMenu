#include <iostream>
#include "lib/Logs.h"


int main() {
    system("cls"); // ����

    std::vector<std::string> Values = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> Items = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};

    // ����̨�˵� ������
    int MouseChoice = Logs::MouseMenu(Items, "���ѡ��˵�");
    std::cout << Values[MouseChoice] << std::endl;

    // ����̨�˵� ���̲���
    int KeyboardChoice = Logs::selectMenu(Items, "����ѡ��˵�");
    std::cout << Values[KeyboardChoice] << std::endl;

    system("pause");
    return 0;
}
#include <iostream>
#include "lib/Logs.h"


int main() {
    system("cls"); // ����

    std::vector<std::string> imageTypes = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> imageChoices = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};

    // ����̨�˵� ������
    int MouseChoice = Logs::MouseMenu(imageChoices, "���ѡ��˵�");
    std::cout << imageTypes[MouseChoice] << std::endl;

    // ����̨�˵� ���̲���
    int KeyboardChoice = Logs::selectMenu(imageChoices, "����ѡ��˵�");
    std::cout << imageTypes[KeyboardChoice] << std::endl;

    system("pause");
    return 0;
}
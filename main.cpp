#include <iostream>
#include "lib/Logs.h"
#include "lib/Utils.h"
//#include "ConsoleGUI.h"
//
//bool draw(Parameter data) {
//    std::cout << "Hello World" << std::endl;
//    system("pause");
//    return false;
//}
//
//int main() {
//    Menu menu;
//    menu.push_back("HELLO", draw);
//    menu.push_back("EXIT", exitMenu);
//    menu.showMenu();
//    return 0;
//}

int main() {
    system("cls"); // ����

    std::vector<std::string> imageTypes = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> imageChoices = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};
//    std::string imageType = imageTypes[Logs::selectMenu(imageChoices, "ͼ�񱣴��ʽ")];
//    std::string imageType1 = imageTypes[Logs::selectMenu(imageChoices, "ͼ�񱣴��ʽ")];
//    std::cout << imageType << std::endl;
//    std::cout << imageType1 << std::endl;
//    std::cout << "Hello, World!" << std::endl;

    // ����̨������
    Logs::MouseMenu(imageChoices, "���ѡ��˵�");
    system("pause");
    return 0;
}
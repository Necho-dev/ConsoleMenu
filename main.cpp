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
    system("cls"); // 清屏

    std::vector<std::string> imageTypes = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> imageChoices = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};
//    std::string imageType = imageTypes[Logs::selectMenu(imageChoices, "图像保存格式")];
//    std::string imageType1 = imageTypes[Logs::selectMenu(imageChoices, "图像保存格式")];
//    std::cout << imageType << std::endl;
//    std::cout << imageType1 << std::endl;
//    std::cout << "Hello, World!" << std::endl;

    // 控制台鼠标操作
    int c1 = Logs::MouseMenu(imageChoices, "鼠标选择菜单");
    int c2 = Logs::MouseMenu(imageChoices, "鼠标选择菜单");
    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    system("pause");
    return 0;
}
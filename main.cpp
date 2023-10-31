#include <iostream>
#include "lib/Logs.h"


int main() {
    system("cls"); // 清屏

    std::vector<std::string> imageTypes = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> imageChoices = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};

    // 控制台菜单 鼠标操作
    int MouseChoice = Logs::MouseMenu(imageChoices, "鼠标选择菜单");
    std::cout << imageTypes[MouseChoice] << std::endl;

    // 控制台菜单 键盘操作
    int KeyboardChoice = Logs::selectMenu(imageChoices, "键盘选择菜单");
    std::cout << imageTypes[KeyboardChoice] << std::endl;

    system("pause");
    return 0;
}
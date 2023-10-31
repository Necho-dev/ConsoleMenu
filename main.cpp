#include <iostream>
#include "lib/Logs.h"


int main() {
    system("cls"); // 清屏

    std::vector<std::string> Values = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
    std::vector<std::string> Items = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};

    // 控制台菜单 鼠标操作
    int MouseChoice = Logs::MouseMenu(Items, "鼠标选择菜单");
    std::cout << Values[MouseChoice] << std::endl;

    // 控制台菜单 键盘操作
    int KeyboardChoice = Logs::selectMenu(Items, "键盘选择菜单");
    std::cout << Values[KeyboardChoice] << std::endl;

    system("pause");
    return 0;
}
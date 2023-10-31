# ConsoleMenu

## 开发进度

- - [x] 键盘方向键(↑/↓)交互
- - [x] 鼠标选择交互
- - [ ] 独立封装`Menu`类 (封装进行中)
- - [ ] 封装为单文件模块 `hpp`

## 使用方法详解

- ##### 引用`Logs.h`头文件

```c++
#include "lib/Logs.h"
```

- ##### 定义选项(`Items`) 和对应值(`Values`)

```c++
std::vector<std::string> Values = {"IMAGE::NONE", "IMAGE::JPG", "IMAGE::PNG", "IMAGE::BMP", "EXIT", "IMAGE::JPG"};
std::vector<std::string> Items = {"NONE", "JPG", "PNG", "BMP", "EXIT", "JPG"};
```

- ##### 调用控制台菜单 - 鼠标操作 `MouseMenu()`

```c++
// 控制台菜单 鼠标操作
int MouseChoice = Logs::MouseMenu(Items, "鼠标选择菜单");
```

- ##### 调用控制台菜单 - 键盘操作 `selectMenu()`

```c++
// 控制台菜单 键盘操作
int KeyboardChoice = Logs::selectMenu(Items, "键盘选择菜单");
```



- ##### 样例代码

```c++
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
```


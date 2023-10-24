cmake_minimum_required(VERSION 3.26)
project(ConsoleMenu)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE HEAD_FILES CONFIGURE_DEPENDS "lib/*.h")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "lib/*.cpp")
add_executable(ConsoleMenu main.cpp ${HEAD_FILES} ${SOURCE_FILES}
        ConsoleGUI.h
        lib/Menu.cpp
        lib/Menu.h)

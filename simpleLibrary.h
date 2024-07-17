#pragma once

#include <iostream>
#include <fstream>
#include <assert.h>
#include <windows.h>
#include <chrono>

namespace simpleLibrary
{

inline void clearScreen() { system("cls"); }
inline void pause() { std::cin.get(); }

void printFile(const std::string fileName)
{
    std::ifstream file(fileName);
    assert(file.is_open() && "CANNOT OPEN FILE ");
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    file.close();
}

void setTitle(std::string title)
{
    SetConsoleTitleA(title.c_str());
}

void setWindowSize(int WIDTH, int HEIGHT)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, r.left, r.top, WIDTH, HEIGHT, TRUE);
}
}
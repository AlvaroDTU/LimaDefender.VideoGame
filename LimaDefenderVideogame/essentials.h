#pragma once
#include "windows.h"
#include "cctype"
#include "conio.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace System;
using namespace std;
void gotoxy(int x, int y) {
    Console::SetCursorPosition(x, y);
}
void setTextColorRGB(int r, int g, int b) {
    cout << "\x1b[38;2;" << r << ';' << g << ';' << b << "m";
}

void setBackgroundColor(int r, int g, int b) {
    cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";
}
void resetColors() {
    cout << "\x1b[0m";
}
void printTextCenter(int width, string text, int y) {
    gotoxy((width - (int)text.length()) / 2, y);
    cout << text;
}

bool changeWindowSize(int width, int height) {
    if (width < 1 || height < 1) return false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return false;

    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return false;

    COORD newBuf{
        (SHORT)max(width,  (int)csbi.dwSize.X),
        (SHORT)max(height, (int)csbi.dwSize.Y)
    };
    if (!SetConsoleScreenBufferSize(h, newBuf)) return false;

    SMALL_RECT win{ 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
    return SetConsoleWindowInfo(h, TRUE, &win) != 0;
}

bool lockNoScroll(int width, int height) {
    if (width < 1 || height < 1) return false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return false;

    COORD largest = GetLargestConsoleWindowSize(h);
    if (width > largest.X) width = largest.X;
    if (height > largest.Y) height = largest.Y;

    SetConsoleCursorPosition(h, { 0,0 });

    SMALL_RECT tiny{ 0,0,0,0 };
    if (!SetConsoleWindowInfo(h, TRUE, &tiny)) return false;

    COORD buf{ (SHORT)width, (SHORT)height };
    if (!SetConsoleScreenBufferSize(h, buf)) return false;

    SMALL_RECT win{ 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
    return SetConsoleWindowInfo(h, TRUE, &win) != 0;
}

void fillBackgroundRGB(int r, int g, int b) {
    setBackgroundColor(r, g, b);
    cout << "\x1b[2J\x1b[H";
    cout.flush();
}
#ifndef UI_CONSOLE_GLOBAL_H_INCLUDED
#define UI_CONSOLE_GLOBAL_H_INCLUDED

#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

namespace Console
{
    unsigned short GetX();
    unsigned short GetY();
    void GotoXY(unsigned short xCor, unsigned short yCor);
    void ClearRect(unsigned short xCor, unsigned short yCor, unsigned short w, unsigned short h);
    void ClearScreen(unsigned short xCor, unsigned short yCor);
	void FlareClear(unsigned int useBG, unsigned int finalText, unsigned int finalBG);
    void SetWindowSize(unsigned short width, unsigned short height);
    unsigned short GetWindowWidth();
    unsigned short GetWindowHeight();

    void SetWindowTitle(const char* titleCstring);
    void SetCoding(int N);
}

#endif // UI_CONSOLE_GLOBAL_H_INCLUDED

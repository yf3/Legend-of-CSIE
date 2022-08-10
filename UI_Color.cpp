#include "UI_Color.h"

UI_Color::UI_Color()
{
    //ctor
}

UI_Color::~UI_Color()
{
    //dtor
}

void UI_Color::SetColor(int textUI_Color, int bgUI_Color)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    int colorMixCode=textUI_Color+bgUI_Color;
    SetConsoleTextAttribute(hStdout, colorMixCode);
}

int UI_Color::ProduceColorStyle(int textUI_Color, int bgUI_Color)
{
    return textUI_Color+bgUI_Color;
}

void UI_Color::SetColorStyle(int colorstyleCode)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, colorstyleCode);
}

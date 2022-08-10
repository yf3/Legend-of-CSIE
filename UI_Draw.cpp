#include "UI_Draw.h"
#include "UI_Console_Global.h"

#include <iostream>

using std::map;
using std::string;

UI_Draw::UI_Draw() : spaceText(color.TEXT_COLOR_BLACK), spaceBG(color.BG_COLOR_BLACK), filledText(color.TEXT_COLOR_LIGHT_GREEN), filledBG(color.BG_COLOR_BLACK)
{
    bigChar5x5['7']="\
88888\n\
    8\n\
    8\n\
    8\n\
    8\n";
    bigChar5x5['8']="\
88888\n\
8   8\n\
88888\n\
8   8\n\
88888\n";
    bigChar5x5['D']="\
8888 \n\
8   8\n\
8   8\n\
8   8\n\
8888 \n";
    bigChar5x5['E']="\
88888\n\
8    \n\
88888\n\
8    \n\
88888\n";
    bigChar5x5['F']="\
88888\n\
8    \n\
88888\n\
8    \n\
8    \n";
    bigChar5x5['H']="\
8   8\n\
8   8\n\
88888\n\
8   8\n\
8   8\n";
    bigChar5x5['I']="\
 888 \n\
  8  \n\
  8  \n\
  8  \n\
 888 \n";
    bigChar5x5['L']="\
8    \n\
8    \n\
8    \n\
8    \n\
88888\n";
    bigChar5x5['M']="\
8   8\n\
88 88\n\
8 8 8\n\
8   8\n\
8   8\n";
    bigChar5x5['N']="\
8   8\n\
88  8\n\
8 8 8\n\
8  88\n\
8   8\n";
	bigChar5x5['O']="\
 888 \n\
8   8\n\
8   8\n\
8   8\n\
 888 \n";
    bigChar5x5['R']="\
88888\n\
8   8\n\
88888\n\
8  8 \n\
8   8\n";
    bigChar5x5['S']="\
 888 \n\
8    \n\
 888 \n\
    8\n\
 888 \n";
    bigChar5x5['T']="\
88888\n\
  8  \n\
  8  \n\
  8  \n\
  8  \n";
    bigChar5x5['U']="\
8   8\n\
8   8\n\
8   8\n\
8   8\n\
 888 \n";
    bigChar5x5['W']="\
8   8\n\
8   8\n\
8 8 8\n\
88 88\n\
8   8\n";
    bigChar5x5['Y']="\
8   8\n\
 8 8 \n\
  8  \n\
  8  \n\
  8  \n";
    bigChar5x5[' ']="\
     \n\
     \n\
     \n\
     \n\
     \n";
    bigChar5x5['!']="\
 888 \n\
 888 \n\
  8  \n\
     \n\
  8  \n";
    bigChar5x5['_']="\
     \n\
     \n\
     \n\
     \n\
88888\n";
}

void UI_Draw::DrawBigChar(unsigned short x, unsigned short y, char ch)
{
    Console::GotoXY(x, y);
    std::string::iterator endIt=bigChar5x5[ch].end();
    for (std::string::iterator it=bigChar5x5[ch].begin();it<endIt;++it)
    {
        if (*it==' ')
            color.SetColor(spaceText, spaceBG);
        else
            color.SetColor(filledText, filledBG);
        std::cout << *it;
        if (*it=='\n')
            Console::GotoXY(x, Console::GetY());
    }
    color.SetColorStyle(color.DEFAULT_COLOR_STYLE);
}

void UI_Draw::DrawBigCharString(unsigned short x, unsigned short y, const string& str)
{
    unsigned short xPos=x;
    unsigned short iX=x;
    std::string::const_iterator endIt=str.end();
    for (std::string::const_iterator itStr=str.begin();itStr<endIt;++itStr)
    {
        DrawBigChar(xPos, y, *itStr);
        xPos+=6;
    }
    Console::GotoXY(iX, Console::GetY());
}

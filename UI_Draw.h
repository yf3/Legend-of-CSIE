#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>
#include <map>

#include "UI_Color.h"

using std::string;
using std::map;

class UI_Draw
{
    public:
        UI_Draw();
        void DrawBigChar(unsigned short x, unsigned short y, char ch);
        void DrawBigCharString(unsigned short x, unsigned short y, const string& str);
        inline void SetFilledText(unsigned int c) {filledText=c;}
    private:
        UI_Color color;
        unsigned int spaceText;
        unsigned int spaceBG;
        unsigned int filledText;
        unsigned int filledBG;
        map<char, string> bigChar5x5;
};

#endif // UI_DRAW_H

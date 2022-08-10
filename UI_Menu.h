#ifndef UI_MENU_H
#define UI_MENU_H

#include <iostream>
#include <string>
#include <vector>

#include "UI_Color.h"
#include "Ctrl_UDLR.h"
#include "UI_Console_Global.h"

using std::vector;
using std::string;

class UI_Menu
{
    public:
        UI_Menu();
        UI_Menu(bool type, vector<string>& mList, unsigned short x, unsigned short y); // vert/hor, contents, coordination
        ~UI_Menu();
        void Push_Back(const string&);
        void SetMenuContents(const vector<string>& mList);
        void SetPositon(unsigned short x, unsigned short y);
        void SetMenuColor(unsigned int nText, unsigned int nBG, unsigned int aText, unsigned int aBG);
        void SetFilledColor(unsigned int fText, unsigned int fBG);
        void SetHint(unsigned int selectHint,vector<string>& hintList,unsigned short HintX,unsigned short HintY);
        unsigned int MenuProcess();
        unsigned int MenuProcess(vector<string>& hintList,unsigned short xHint,unsigned short yHint);
        void Output(unsigned short xCor, unsigned short yCor);
    private:
        bool vertType; // true:vertical false:horizontal
        bool inMenu;
        unsigned short xPos;
        unsigned short yPos;
        unsigned int selectingIndex;
        vector<string> menuList;
        UI_Color menuColor;
        unsigned int normalColorText;
        unsigned int normalColorBG;
        unsigned int activeColorText;
        unsigned int activeColorBG;
        unsigned int filledText;
        unsigned int filledBG;
};

#endif // UI_MENU_H

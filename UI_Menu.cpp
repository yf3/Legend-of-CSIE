#include "UI_Menu.h"
#include "UI_Console_Global.h"

UI_Menu::UI_Menu() :
 vertType(true), inMenu(false),xPos(0), yPos(0), selectingIndex(0),
 normalColorText(menuColor.TEXT_COLOR_BLACK), normalColorBG(menuColor.BG_COLOR_LIGHT_WHITE),
 activeColorText(menuColor.TEXT_COLOR_BLACK), activeColorBG(menuColor.BG_COLOR_LIGHT_CYAN),
 filledText(menuColor.TEXT_COLOR_LIGHT_RED), filledBG(menuColor.BG_COLOR_LIGHT_RED)
{
    //ctor
}

UI_Menu::UI_Menu(bool type, vector<string>& mList, unsigned short x, unsigned short y) :
 vertType(type), inMenu(false), xPos(x), yPos(y), selectingIndex(0),
 normalColorText(menuColor.TEXT_COLOR_BLACK), normalColorBG(menuColor.BG_COLOR_LIGHT_WHITE),
 activeColorText(menuColor.TEXT_COLOR_BLACK), activeColorBG(menuColor.BG_COLOR_LIGHT_CYAN),
 filledText(menuColor.TEXT_COLOR_LIGHT_RED), filledBG(menuColor.BG_COLOR_LIGHT_RED)
{
    for (std::vector<std::string>::iterator iter = mList.begin(); iter != mList.end() ; ++iter)
        menuList.push_back(*iter);
}

UI_Menu::~UI_Menu()
{
    menuList.clear();
}

void UI_Menu::Push_Back(const string& str)
{
    menuList.push_back(str);
}

void UI_Menu::SetMenuContents(const vector<string>& mList)
{
    menuList.clear();
    menuList=mList;
}

void UI_Menu::SetPositon(unsigned short x, unsigned short y)
{
    xPos=x;
    yPos=y;
}

void UI_Menu::SetMenuColor(unsigned int nText, unsigned int nBG, unsigned int aText, unsigned int aBG)
{
    normalColorText=nText;
    normalColorBG=nBG;

    activeColorText=aText;
    activeColorBG=aBG;
}

void UI_Menu::SetFilledColor(unsigned int fText, unsigned int fBG)
{
    filledText=fText;
    filledBG=fBG;
}

void UI_Menu::SetHint(unsigned int selectHint,vector<string>& hintList ,unsigned short HintX,unsigned short HintY)
{
	menuColor.SetColor(filledText, filledBG);
	Console::ClearRect(HintX,HintY,65,2);
    Console::GotoXY(HintX,HintY);
    std::cout<< hintList[selectHint];
}

unsigned int UI_Menu::MenuProcess()
{
    Ctrl_UDLR key;
    const unsigned int maxI=menuList.size()-1;
    inMenu=true;
    selectingIndex=0;
    //menuColor.SetColorStyle(menuColor.DEFAULT_COLOR_STYLE);

    while (inMenu)
    {
        Output(xPos, yPos);
        switch (key.Ctrl_UDLR_Return())
        {
            case key.Up:
                if (vertType)
                {
                    if (selectingIndex==0) selectingIndex=maxI;
                    else --selectingIndex;
                }
                break;
            case key.Down:
                if (vertType)
                {
                    if (selectingIndex==maxI) selectingIndex=0;
                    else ++selectingIndex;
                }
                break;
            case key.Left:
                if (!vertType)
                {
                    if (selectingIndex==0) selectingIndex=maxI;
                    else --selectingIndex;
                }
                break;
            case key.Right:
                if (!vertType)
                {
                    if (selectingIndex==maxI) selectingIndex=0;
                    else ++selectingIndex;
                }
                break;
            case key.Selected:
                inMenu=false;
                break;
            default:
                break;
        }
    }
    return selectingIndex;
}

unsigned int UI_Menu::MenuProcess(vector<string>& hintList,unsigned short xHint,unsigned short yHint)
{
    Ctrl_UDLR key;
    const unsigned int maxI=menuList.size()-1;
    inMenu=true;
    selectingIndex=0;
    Console::GotoXY(xHint,yHint);
    Console::ClearRect(xHint,yHint,65,2);
    std::cout<<hintList[0];
    /*menuColor.SetColorStyle(menuColor.DEFAULT_COLOR_STYLE);*/


    while (inMenu)
    {
        Output(xPos, yPos);
        switch (key.Ctrl_UDLR_Return())
        {

            case key.Up:
                if (vertType)
                {
                    if (selectingIndex==0) selectingIndex=maxI;
                    else --selectingIndex;
                    SetHint(selectingIndex,hintList,xHint,yHint);
                }
                break;
            case key.Down:
                if (vertType)
                {
                    if (selectingIndex==maxI) selectingIndex=0;
                    else ++selectingIndex;
                    SetHint(selectingIndex,hintList,xHint,yHint);
                }
                break;
            case key.Left:
                if (!vertType)
                {
                    if (selectingIndex==0) selectingIndex=maxI;
                    else --selectingIndex;
                    SetHint(selectingIndex,hintList,xHint,yHint);
                }
                break;
            case key.Right:
                if (!vertType)
                {
                    if (selectingIndex==maxI) selectingIndex=0;
                    else ++selectingIndex;
                    SetHint(selectingIndex,hintList,xHint,yHint);
                }
                break;
            case key.Selected:
                inMenu=false;
                SetHint(selectingIndex,hintList,xHint,yHint);

                break;
            default:
                break;
        }

    }
    Console::ClearRect(xHint,yHint,65,2);
    return selectingIndex;
}

void UI_Menu::Output(unsigned short xCor, unsigned short yCor)
{
    Console::GotoXY(xCor, yCor);
    for (unsigned int i=0;i<menuList.size();++i)
    {
        if (selectingIndex==i && inMenu==true)
        {
            if (vertType)
            {
                menuColor.SetColor(activeColorText, activeColorBG);
                for (string::iterator it=menuList[i].begin();it<menuList[i].end();++it)
                {
                    if (*it=='*')
                        menuColor.SetColor(filledText, filledBG);

                    std::cout<<*it;
                    if (*it=='\n')
                        Console::GotoXY(xPos, Console::GetY());
                    menuColor.SetColor(activeColorText, activeColorBG);
                }
                if (i<menuList.size()-1)
                    Console::GotoXY(xPos, Console::GetY()+1);
            }
            else
            {
                menuColor.SetColor(activeColorText, activeColorBG);
                std::cout<<menuList[i];
                if (i<menuList.size()-1)
                    Console::GotoXY(Console::GetX(), Console::GetY());
            }
        }
        else
        {
            menuColor.SetColor(normalColorText, normalColorBG);
            if (vertType)
            {
                for (string::iterator it=menuList[i].begin();it<menuList[i].end();++it)
                {
                    if (*it=='*')
                        menuColor.SetColor(menuColor.TEXT_COLOR_LIGHT_RED, menuColor.BG_COLOR_LIGHT_RED);
                    std::cout<<*it;
                    if (*it=='\n')
                        Console::GotoXY(xPos, Console::GetY());
                    menuColor.SetColor(normalColorText, normalColorBG);
                }
                if (i<menuList.size()-1)
                    Console::GotoXY(xPos, Console::GetY()+1);
            }
            else
            {
                std::cout<<menuList[i];
                if (i<menuList.size()-1)
                    Console::GotoXY(Console::GetX(), Console::GetY()); // last?
            }
        }
    }
    menuColor.SetColorStyle(menuColor.DEFAULT_COLOR_STYLE);
}

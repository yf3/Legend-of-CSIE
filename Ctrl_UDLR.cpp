#include "Ctrl_UDLR.h"

int Ctrl_UDLR::Ctrl_UDLR_Return()
{
    int input;
    input=getch();
    if (input==224){
        input=getch();
        switch(input)
        {
             case 72:return Up;
             case 80:return Down;
             case 75:return Left;
             case 77:return Right;
             default:break;
        }
    }
    else if (input==13)
        return Selected;
    else
        return -1;
}

Ctrl_UDLR::Ctrl_UDLR()
{
    //ctor
}

Ctrl_UDLR::~Ctrl_UDLR()
{
    //dtor
}

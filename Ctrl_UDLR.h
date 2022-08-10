#ifndef CTRL_UDLR_H
#define CTRL_UDLR_H

#include <conio.h>

class Ctrl_UDLR
{
    public:
        Ctrl_UDLR();
        virtual ~Ctrl_UDLR();
        int Ctrl_UDLR_Return();
        enum control {Up, Down, Left, Right, Selected};
    protected:
    private:
};

#endif // CTRL_UDLR_H

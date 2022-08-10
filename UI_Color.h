#ifndef UI_COLOR_H
#define UI_COLOR_H

#include <windows.h>

class UI_Color
{
    public:
        UI_Color();
        virtual ~UI_Color();
        void SetColor(int text, int bg);
        int ProduceColorStyle(int text, int bg);
        void SetColorStyle(int);

        enum basicUI_Color{

        /*****************
        *   Text UI_Colors  *
        *****************/

        TEXT_COLOR_BLACK=0,
        // DARK
        TEXT_COLOR_BLUE=1,
        TEXT_COLOR_GREEN=2,
        TEXT_COLOR_CYAN=3,
        TEXT_COLOR_RED=4,
        TEXT_COLOR_PURPLE=5,
        TEXT_COLOR_GOLD=6,
        TEXT_COLOR_WHITE=7,
        TEXT_COLOR_GRAY=8,
        // LIGHT
        TEXT_COLOR_LIGHT_BLUE=9,
        TEXT_COLOR_LIGHT_GREEN=10,
        TEXT_COLOR_LIGHT_CYAN=11,
        TEXT_COLOR_LIGHT_RED=12,
        TEXT_COLOR_PINK=13,
        TEXT_COLOR_YELLOW=14,
        TEXT_COLOR_LIGHT_WHITE=15,


        /*********************
        *  BackGround UI_Colors *
        *********************/

        BG_COLOR_BLACK=0,
        // DARK
        BG_COLOR_BLUE=16,
        BG_COLOR_GREEN=32,
        BG_COLOR_CYAN=48,
        BG_COLOR_RED=64,
        BG_COLOR_PURPLE=80,
        BG_COLOR_GOLD=96,
        BG_COLOR_WHITE=112,
        // LIGHT
        BG_COLOR_LIGHT_BLUE=144,
        BG_COLOR_LIGHT_GREEN=160,
        BG_COLOR_LIGHT_CYAN=176,
        BG_COLOR_LIGHT_RED=192,
        BG_COLOR_PINK=208,
        BG_COLOR_YELLOW=224,
        BG_COLOR_LIGHT_WHITE=240,

        DEFAULT_COLOR_STYLE=7,
        MENU_CS_SELECTING=176,
        MENU_CS_DEFAULT=112
        };
};

#endif // UI_COLOR_H

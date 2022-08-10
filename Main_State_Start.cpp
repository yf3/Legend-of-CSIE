#include "Main_State.h"
#include "UI_Console_Global.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ctrl_UDLR.h"
#include "UI_Color.h"
#include "UI_Menu.h"
using namespace std;

Start::Start()
{
    //ctor
}
Start::~Start()
{
    //dtor
}
Start::Start(const Start &other)
{
    //copy ctor
}

void Twinkle()
{
    const char twinkle[]="\
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	while (true)
	{
		Console::GotoXY(0, 13);
		UI_Color temp;
		unsigned int j = 0;
		Sleep(500);
		temp.SetColor(temp.TEXT_COLOR_PINK, temp.BG_COLOR_BLACK);
		while (twinkle[j])
		{
			cout << twinkle[j++];
		}
		Console::GotoXY(70, 20);
		cout << "Press any key to start...";
		Console::GotoXY(0, 13);
		Sleep(500);
		temp.SetColorStyle(temp.DEFAULT_COLOR_STYLE);
		j = 0;
		while (twinkle[j])
		{
			cout << twinkle[j++];
		}
		Console::GotoXY(70, 20);
		cout << "Press any key to start...";
		int input = kbhit();
		if (input)
		{
			Console::ClearRect(0, 13, 178, 17);
			getch();
			break;
		}
	}
}


void Start::handle()
{
    Console::SetWindowTitle("Legend of CSIE");
    Console::SetWindowSize(178, 40);
    UI_Color titleColor;
	titleColor.SetColorStyle(titleColor.DEFAULT_COLOR_STYLE);
	Console::ClearScreen(0, 0);
    cout<<endl;
    const char title_180x12[]="\
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\
................................................................................................................................................................................\n\
....EEEE........WEEEEEEEEEE......AWEEEENEM.....EEEEEEEEEE...EEEE8.....EEEE...EEEEEEEEEEE...........................EEEEE..........AWEEENEM.....AEEEEDN....EEEEE...EEEEEEEEEE....\n\
....EEEE........WEEEEEEEEEE....WEEEEEEEEEEM....EEEEEEEEEE...EEEEED....EEEE...EEEEEEEEEEEED........................EEEE..........IEEEEEEEEED..MEEEEEEEEE....EEE....EEEEEEEEEE....\n\
....EEEE........WEEE..........EEEE.............EEE..........EEE+EEE...EEEE...EEEE......EEEE..........IEEEEEN....EEEEEEEE.......EEEN..........EEEE..........EEE....EEE...........\n\
....EEEE........WEEEEEEEEE...EEEE..............EEEEEEEEEE...EEE..EEE..NEEE...EEEE......+EEEE.......EEEEEEEEEEE....EEE.........EEEE...........WEEEEEE.......EEE....EEEEEEEEEE....\n\
....EEEE........WEEEEEEEEE...EEEE....EEEEEEE...EEEEEEEEEE...EEE...EEE.7EEE...EEEE......+EEEE......IEEE.....EEEE...EEE.........EEEE...............EEEEEEW...EEE....EEEEEEEEEE....\n\
....EEEE........WEEE.........LEEEE......EEEN...EEE..........EEE....EEE7EEE...EEEE......EEEE.......IEEE.....DEEE...EEE.........WEEEM.................EEEE...EEE....EEE...........\n\
....EEEEEEEEEE..WEEEEEEEEEE....NEEEEEEEEEEEN...EEEEEEEEEE...EEE.....+EEEEE...EEEEEEEEEEEEW.........EEEEEOEEEEE....EEE...........EEEEEEEEEEW..EEEEEEEEEE....EEE....EEEEEEEEEE....\n\
....EEEEEEEEEE..WEEEEEEEEEE......WWWWWWWWWW....EEEEEEEEEE...EEE......+EEEE...EEEEEEEEEEW.............LEEEEEW......EEE..............LEEEEEW....LEEEEEW.....EEEEE...EEEEEEEEEE....\n\
................................................................................................................................................................................\n\
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    const string startStr="\
***** ***** ***** ***** *****\n\
*       *   *   * *   *   *  \n\
*****   *   ***** *****   *  \n\
    *   *   *   * *  *    *  \n\
*****   *   *   * *   *   *  \n";
    const string exitStr="\
   ***** ** **  ***  *****   \n\
   *      * *    *     *     \n\
   *****   *     *     *     \n\
   *      * *    *     *     \n\
   ***** ** **  ***    *     \n";

//    const char twinkle[]="\
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    vector<string> mainMenuList={startStr, exitStr};
    UI_Menu mainMenu(true, mainMenuList, 70, 18);
	mainMenu.SetMenuColor(titleColor.TEXT_COLOR_BLACK, titleColor.BG_COLOR_BLACK, titleColor.TEXT_COLOR_BLACK, titleColor.BG_COLOR_LIGHT_WHITE);

    unsigned int i=0;
    while (title_180x12[i])
    {
        if (title_180x12[i]=='.')
            titleColor.SetColor(titleColor.TEXT_COLOR_PURPLE, titleColor.BG_COLOR_PURPLE);
        else
            titleColor.SetColor(titleColor.TEXT_COLOR_YELLOW, titleColor.BG_COLOR_PURPLE);
        cout<< title_180x12[i++];
    }
    titleColor.SetColorStyle(titleColor.DEFAULT_COLOR_STYLE);
    cout.flush();
	Console::GotoXY(140, 36);
	cout << "https://www.facebook.com/csiesir87";

	Twinkle();

    unsigned int mainOption=mainMenu.MenuProcess();
    switch (mainOption)
    {
        case 0:
            break;
        case 1:
			exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}



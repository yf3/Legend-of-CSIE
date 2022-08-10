#include <iostream>
#include <cstdlib>
#include "Main_Function.h"
#include "Main_Menu.h"
#include "Main_State.h"
#include "Data_ChaMas.h"
#include "Data_ChaMasDog.h"
#include "Data_ChaMasSor.h"
#include "Data_Random.h"
#include "Ctrl_UDLR.h"//include gotoxy()
#include "UI_Color.h"
#include "UI_Menu.h"

#define START
#define STORY1
#define QUESTION
#define MAP1
#define MAP2

using namespace std;

int main()
{
	Main_Menu menu;
	//menu use to change state
	Ctrl_UDLR ctrl;

    //.Enter:Press Enter to Update
	//.Update:system("CLS")
	//Create MainMaster
	Data_ChaMas SIR87;
	Data_ChaMasDog LITTLE87;
	Data_ChaMasSor SORRY;

#ifdef START
	menu.change_state(Start::CreateInstance());
	menu.handle();
	Console::ClearScreen(0,0);
#endif //START


#ifdef STORY1
	menu.change_state(Story::CreateInstance());
	menu.handle();
#endif //STORY1


#ifdef QUESTION
	Main::Question(SIR87);
#endif // QUESTION


#ifdef MAP1
	Main::Map1(SIR87,LITTLE87);
#endif // MAP1

#ifdef MAP2
    Main::Map2(SIR87,LITTLE87, SORRY);

#endif // MAP2
	menu.change_state(End::CreateInstance());
	menu.handle();

	return 0;
}



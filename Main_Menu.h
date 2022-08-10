#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include <iostream>
#include "Main_Menu.h"
#include "Main_State.h"


class Main_Menu {
	public:
	Main_Menu():current_state(0){;}
	~Main_Menu(){;}

	void handle(){
		current_state->handle();
	}
	void change_state(Main_State* state){
		current_state = state;
	}

	protected:
	Main_State* current_state;
};


#endif // MAIN_MENU_H_INCLUDED

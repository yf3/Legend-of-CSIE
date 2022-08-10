CC=g++
CXXFLAGS=-std=c++11

game: main.o Main_Fighting.o Main_Function.o Main_State_Start.o Main_State_Story.o Main_State_End.o Data_Cha.o Data_ChaEnemy.o Data_ChaMas.o Data_ChaMasDog.o Data_ChaMasSor.o Data_Random.o Data_NPC.o Ctrl_UDLR.o UI_Color.o UI_Draw.o UI_Console_Global.o UI_Dialogue.o UI_Menu.o
	$(CC) -o game main.o Main_Fighting.o Main_Function.o Main_State_Start.o Main_State_Story.o Main_State_End.o Data_Cha.o Data_ChaEnemy.o Data_ChaMas.o Data_ChaMasDog.o Data_ChaMasSor.o Data_Random.o Data_NPC.o Ctrl_UDLR.o UI_Color.o UI_Draw.o UI_Console_Global.o UI_Dialogue.o UI_Menu.o
	
main.o: main.cpp Main_Function.h Main_Menu.h Main_State.h Data_ChaMas.h Data_ChaMasDog.h Data_ChaMasSor.h Data_Random.h Ctrl_UDLR.h UI_Color.h UI_Menu.h
	$(CC) -c $(CXXFLAGS) main.cpp

# not in main
Main_Fighting.o: Main_Fighting.cpp Main_Fighting.h
	$(CC) -c $(CXXFLAGS) Main_Fighting.cpp

Main_Function.o: Main_Function.cpp Main_Function.h Ctrl_UDLR.h UI_Menu.h UI_Console_Global.h UI_Color.h UI_Dialogue.h UI_Draw.h Data_Cha.h Data_ChaEnemy.h Data_ChaMas.h Data_ChaMasDog.h Data_ChaMasSor.h Data_Random.h
	$(CC) -c $(CXXFLAGS) Main_Function.cpp
	
# Main_Menu

Main_State_Start.o: Main_State_Start.cpp Main_State.h UI_Console_Global.h Ctrl_UDLR.h UI_Color.h UI_Menu.h
	$(CC) -c $(CXXFLAGS) Main_State_Start.cpp

Main_State_Story.o: Main_State_Story.cpp Main_State.h Ctrl_UDLR.h UI_Menu.h
	$(CC) -c $(CXXFLAGS) Main_State_Story.cpp

Main_State_End.o: Main_State_End.cpp Main_State.h
	$(CC) -c $(CXXFLAGS) Main_State_End.cpp

# not in main
Data_Cha.o: Data_Cha.cpp Data_Cha.h
	$(CC) -std=c++11 -c $(CXXFLAGS) Data_Cha.cpp

# not in main
Data_ChaEnemy.o: Data_ChaEnemy.cpp Data_ChaEnemy.h
	$(CC) -c $(CXXFLAGS) Data_ChaEnemy.cpp

Data_ChaMas.o: Data_ChaMas.cpp Data_ChaMas.h
	$(CC) -c $(CXXFLAGS) Data_ChaMas.cpp

Data_ChaMasDog.o: Data_ChaMasDog.cpp Data_ChaMasDog.h
	$(CC) -c $(CXXFLAGS) Data_ChaMasDog.cpp

Data_ChaMasSor.o: Data_ChaMasSor.cpp Data_ChaMasSor.h
	$(CC) -c $(CXXFLAGS) Data_ChaMasSor.cpp

Data_Random.o: Data_Random.cpp Data_Random.h
	$(CC) -c $(CXXFLAGS) Data_Random.cpp

# not in main
Data_NPC.o : Data_NPC.cpp Data_NPC.h
	$(CC) -c $(CXXFLAGS) Data_NPC.cpp

Ctrl_UDLR.o: Ctrl_UDLR.cpp Ctrl_UDLR.h
	$(CC) -c $(CXXFLAGS) Ctrl_UDLR.cpp

UI_Color.o: UI_Color.cpp UI_Color.h
	$(CC) -c $(CXXFLAGS) UI_Color.cpp

# not in main
UI_Draw.o: UI_Draw.cpp UI_Draw.h UI_Console_Global.h
	$(CC) -c $(CXXFLAGS) UI_Draw.cpp

# not in main
UI_Console_Global.o: UI_Console_Global.cpp UI_Console_Global.h UI_Color.h
	$(CC) -c $(CXXFLAGS) UI_Console_Global.cpp

# not in main
UI_Dialogue.o: UI_Dialogue.cpp UI_Dialogue.h
	$(CC) -c $(CXXFLAGS) UI_Dialogue.cpp

UI_Menu.o: UI_Menu.cpp UI_Menu.h UI_Console_Global.h
	$(CC) -c $(CXXFLAGS) UI_Menu.cpp

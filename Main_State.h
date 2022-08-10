#ifndef MAIN_STATE_H_INCLUDED
#define MAIN_STATE_H_INCLUDED

#include "Data_ChaMas.h"
#include <iostream>

class Main_State {
	public:
	virtual void handle() = 0;
};

class Start : public Main_State {
	public:
    Start();
	~Start();
	Start(const Start &other);
	static Start* CreateInstance() {
		static Start instance;
		return &instance;
	}
	void handle();
};



class End : public Main_State {
	public:
    End();
	~End();
	End(const End &other);
	static End* CreateInstance() {
		static End instance;
		return &instance;
	}
	void handle();
};

class Story : public Main_State{
    public:
    Story();
	~Story();
	Story(const Story &other);
	static Story* CreateInstance() {
		static Story instance;
		return &instance;
	}
	void handle();
};


class Map1: public Main_State{
    public:
    Map1();
	~Map1();
	Map1(const Map1 &other);
	static Map1* CreateInstance() {
		static Map1 instance;
		return &instance;
	}
	void handle();
};

class Map2: public Main_State{
    public:
    Map2();
	~Map2();
	Map2(const Map2 &other);
	static Map2* CreateInstance() {
		static Map2 instance;
		return &instance;
	}
	void handle();
};

class Question: public Main_State{
    public:
    Question();
	~Question();
	Question(const Question &other);
	static Question* CreateInstance() {
		static Question instance;
		return &instance;
	}
	void handle();

};



#endif // MAIN_STATE_H_INCLUDED

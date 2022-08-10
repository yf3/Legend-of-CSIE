#ifndef MAIN_FUNCTION_H_INCLUDED
#define MAIN_FUNCTION_H_INCLUDED
#include "Data_ChaMas.h"
#include "Data_ChaMasDog.h"
#include "Data_ChaMasSor.h"
#include "Data_ChaEnemy.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

namespace Main
{
	void MainDisplay(const string&);
	void Question(Data_ChaMas &Mas);
	void Map1(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87);
	void Fighting_Result(string title, unsigned int FightingRound, unsigned int expI, unsigned int expF, unsigned int moneyI, unsigned int moneyF, Data_ChaMas& SIR87, bool sorryJoin);
	int Fighting(int InMap, Data_ChaMas &SIR87, Data_ChaMasDog &LITTLE87, unsigned short& Round, int& Exp, int& Money);
	int Fighting(int InMap, Data_ChaMas &SIR87, Data_ChaMasDog &LITTLE87, Data_ChaMasSor &SORRY, unsigned short& Round, int& Exp, int& Money);
	void Map2(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, Data_ChaMasSor& SORRY);
	//int Fighting(Data_ChaMas SIR87,Data_ChaMasDog LITTLE87,Data_ChaMasSor SORRY);

}


#endif // MAIN_FUNCTION_H_INCLUDED

#pragma once
#include "Data_ChaMas.h"
class Data_ChaMas;
class Data_NPC
{
public:
	Data_NPC();
	virtual ~Data_NPC();
	int Data_NPCDiviner(Data_ChaMas&); //if Lv >= 15 return 1,else return 0; 
	int Data_NPCSeller(Data_ChaMas&,int); //enter 1~5 for potion 6~8 for equipment
										  //return 1 = purchase success, 0 = fail
										  //return 2 = already wear(for equpi)
	void Data_NPCGaySan(Data_ChaMas&); //Money += 3000
};


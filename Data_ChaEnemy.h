#ifndef DATA_CHAENEMY_H
#define DATA_CHAENEMY_H

#include "Data_Cha.h"
#include <iostream>
#include <vector>
#include <cstring>

//6/2 add assignment operator


class Data_ChaEnemy :public Data_Cha
{
public:
	Data_ChaEnemy();
	virtual ~Data_ChaEnemy();
	int GetEMoney(){ return eMoney; };
	int GetEExp(){ return eExp; };
	int GetElv(){ return eLv; };
	std::string GetType(){ return type; };
	std::string GetSkill(int a){ return skill[a]; };

	void operator = (Data_ChaEnemy);//assignment operator

	void SetEMoney(int a){ eMoney = a; };
	void SetEExp(int a){ eExp = a; };
	void SetELv(int a){ eLv = a; };
	void SetType(std::string a){ type = a; };
	void SetCalculus(int);
	void SetCrazyDog(int);
	void SetCuteSnail(int);
	void SetNDHUBird(int);
	void SetSmallWaveBreaker();
	void SetWaveBreaker();
	void SetSkill(std::string a){ skill.push_back(a); };
private:
	int eMoney;
	int eExp;
	int eLv;
	std::string type;
	std::vector<std::string> skill;
};
#endif // DATA_CHAENEMY_H



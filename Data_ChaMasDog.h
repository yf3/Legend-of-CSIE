#ifndef DATA_CHAMASDOG_H
#define DATA_CHAMASDOG_H

#include "Data_ChaMas.h"
class Data_ChaMasDog :
	public Data_ChaMas
{
public:
	Data_ChaMasDog();
	virtual ~Data_ChaMasDog();
	void LvUp();
	void SetHeal(int a){ heal = a; };
	int GetHeal(){ return heal; };
	int UseSkillOne();  //Buff skill
	int UseSkillTwo(std::vector<Data_ChaEnemy>& enemy,int a);  //Buff skill
	int UseSkillThr(std::vector<Data_ChaEnemy>&,int);
	void InitialArray();
private:
	int dSkillMp[3];
	double dSkillCoefficient[3];
	int heal;
};

#endif // DATA_CHAMASDOG_H

#ifndef DATA_CHAMASSOR_H
#define DATA_CHAMASSOR_H

#include "Data_ChaMas.h"



class Data_ChaMasSor :
	public Data_ChaMas
{
public:
	Data_ChaMasSor();
	virtual ~Data_ChaMasSor();
	void LvUp();
	void SetHeal(int a){ heal = a; };
	int GetHeal(){ return heal; };
	int UseSkillOne();  //Buff skill
	int UseSkillTwo(std::vector<Data_ChaEnemy>&,int);
	int UseSkillThr(std::vector<Data_ChaEnemy>&,int);
	void InitialArray();
private:
	int sSkillMp[3] ;
	double sSkillCoefficient[3] ;
	int heal;

};

#endif // DATA_CHAMASSOR_H

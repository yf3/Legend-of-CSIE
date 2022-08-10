#ifndef DATA_CHAMAS_H
#define DATA_CHAMAS_H

#include "Data_Cha.h"
#include "Data_ChaEnemy.h"
#include <iostream>
#include <vector>

class Data_ChaMas :
	public Data_Cha
{
public:
	Data_ChaMas();
	virtual ~Data_ChaMas();
	int GetMoney(){ return money; };
	int GetExp(){ return exp; };
	int GetLv(){ return lv; };
	int GetMaxMp(){ return maxMp; };
	int GetMaxExp(){ return maxExp; };
	int GetBuffTime(){ return buffTime; };
	int GetPotionTime(){ return potionTime; };
	int GetDamage(){ return damage; };
	std::string GetChaName(){ return chaName; };

	void SetMoney(int a){ money = a; };
	void SetExp(int a){ exp = a; };
	void SetLv(int a){ lv = a; };
	void SetMaxMp(int a){ maxMp = a; };
	void SetMaxExp(int a){ maxExp = a; };
	void SetBuffTime(int a){ buffTime = a; };
	void SetPotionTime(int a){ potionTime = a; };
	void SetChaName(std::string a){ chaName = a; };
	void SetDamage(int a){ damage = a; };

	virtual void LvUp();
	void ChooseMaster(int);
	int CheckLvUp();

	int UsePotion(int);
	//return 1->use success, return 2->don't have enough potion, return 0->Hp/Mp is full
	virtual int GetPotion(int a){ return potionList[a - 1]; };
	virtual void SetPotion(int a, int b){ potionList[a - 1] = b; };

	int UseSkillOne();  //Buff skill
	int UseSkillTwo(std::vector<Data_ChaEnemy>&, int); //int = target No.
	int UseSkillThr(std::vector<Data_ChaEnemy>& enemy, int a);//

	std::string GetSkillName(int a){ return skillName[a - 1]; };
	void SetSkillName(int a, std::string b){ skillName[a - 1] = b; };
	void ChangeSuit(int);
	int GetSuit(){ return suit; };
	void SetSuit(int a){ suit = a; };
	virtual void InitialArray();
private:
	int money, exp, lv;
	int maxMp, maxExp;
	int damage;
	int buffTime;
	int potionTime;
	int suit;
	std::string skillName[3];
	std::string chaName;
	int mSkillMp[3];
	double mSkillCoefficient[3];
	int potionList[5];
};

#endif // DATA_CHAMAS_H

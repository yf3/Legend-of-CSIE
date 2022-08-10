#include "Data_ChaMasSor.h"


Data_ChaMasSor::Data_ChaMasSor() :Data_ChaMas()
{
	SetHp(1500);
	SetMp(660);
	SetAtk(460);
	SetMaxHp(1500);
	SetMaxMp(660);
	SetPotion(1, 5);
	SetPotion(2, 0);
	SetPotion(3, 5);
	SetPotion(4, 0);
	SetPotion(5, 0);
	SetSkillName(1, "The EX warrior's dignity");
	SetSkillName(2, "I was strong before");
	SetSkillName(3, "Mouth cannon");
	SetChaName("Weak Warrior Sorry");
	InitialArray();
	SetMaxExp(GetLv() * 110);
}

Data_ChaMasSor::~Data_ChaMasSor()
{
}

void Data_ChaMasSor::LvUp()
{
	SetMaxHp(GetMaxHp() + 80);
	SetMaxMp(GetMaxMp() + 20);
	SetHp(GetHp() + 20);
	SetMp(GetMp() + 80);
	SetAtk(GetDamage() + 20);
	SetLv(GetLv() + 1);
	SetExp(0);
	SetMaxExp(GetLv() * 110);
}

int Data_ChaMasSor::UseSkillOne()
{
	if (GetMp() >= sSkillMp[1] && GetHp() < GetMaxHp()){
		SetMp(GetMp() - sSkillMp[1]);
		SetHp(GetMaxHp());
		return 1;
	}
	else
		return 0;
}

int Data_ChaMasSor::UseSkillTwo(std::vector<Data_ChaEnemy>& enemy,int a)
{
	 if (GetMp() >= sSkillMp[1]){
		SetMp(GetMp() - sSkillMp[1]);

		int tmp = GetDamage()*sSkillCoefficient[1];

		if (enemy[a].GetHp() <= tmp){
			enemy[a].SetHp(0);
			return 1;
		}
		else{
			enemy[a].SetHp(enemy[a].GetHp() - tmp);
			return 1;
		}
	}
	else
		return 0;
}

int Data_ChaMasSor::UseSkillThr(std::vector<Data_ChaEnemy>& enemy,int a)
{
	if (GetMp() >= sSkillMp[2]){
		SetMp(GetMp() - sSkillMp[2]);
		int tmp = GetDamage()*sSkillCoefficient[2];
		for (int i = 0; i < enemy.size(); i++){
			if (enemy[i].GetHp() <= tmp){
				enemy[i].SetHp(0);
			}
			else{
				enemy[i].SetHp(enemy[i].GetHp() - tmp);
			}
		}
		return 1;
	}
	else
		return 0;
}

void Data_ChaMasSor::InitialArray()
{
	sSkillMp[0] = 150;
	sSkillMp[1] = 400;
	sSkillMp[2] = 150;
	sSkillCoefficient[0] = 1.2;
	sSkillCoefficient[1] = 0.2;
	sSkillCoefficient[2] = 1.2;
}

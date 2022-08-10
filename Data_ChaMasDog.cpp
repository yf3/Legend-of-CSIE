#include "Data_ChaMasDog.h"


Data_ChaMasDog::Data_ChaMasDog() :Data_ChaMas()
{
	SetHp(300);
	SetMp(300);
	SetAtk(100);
	SetMaxHp(300);
	SetMaxMp(300);
	SetHeal(0);
	SetPotion(1, 5);
	SetPotion(2, 0);
	SetPotion(3, 5);
	SetPotion(4, 0);
	SetPotion(5, 0);
	SetSkillName(1, "Bark");
	SetSkillName(2,"Attack! School Dog");
	SetSkillName(3,"Bite");
	InitialArray();
	SetChaName("Little 87");
	SetMaxExp(GetLv() * 110);
}

Data_ChaMasDog::~Data_ChaMasDog()
{
}

void Data_ChaMasDog::LvUp()
{
	SetMaxHp(GetMaxHp() + 50);
	SetMaxMp(GetMaxMp() + 10);
	SetHp(GetHp() + 50);
	SetMp(GetMp() + 10);
	SetAtk(GetDamage() + 10);
	SetLv(GetLv() + 1);
	SetExp(0);
	SetMaxExp(GetLv() * 110);
}

int Data_ChaMasDog::UseSkillOne()
{
    if (GetMp() >= dSkillMp[1] && GetHp() < GetMaxHp()){
		SetMp(GetMp() - dSkillMp[1]);
		SetHp(GetMaxHp());
		return 1;
	}
	else
		return 0;

}

int Data_ChaMasDog::UseSkillTwo(std::vector<Data_ChaEnemy>& enemy,int a)
{
    if (GetMp() >= dSkillMp[1]){
		SetMp(GetMp() - dSkillMp[1]);

		int tmp = GetDamage()*dSkillCoefficient[1];

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

int Data_ChaMasDog::UseSkillThr(std::vector<Data_ChaEnemy>& enemy,int a)
{
	if (GetMp() >= dSkillMp[2]){
		SetMp(GetMp() - dSkillMp[2]);
		int tmp = GetDamage()*dSkillCoefficient[2];
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

void Data_ChaMasDog::InitialArray()
{
	dSkillMp[0] = 200;
	dSkillMp[1] = 150;
	dSkillMp[2] = 150;
	dSkillCoefficient[0] = 1.2;
	dSkillCoefficient[1] = 1.5;
	dSkillCoefficient[2] = 1.2;
}

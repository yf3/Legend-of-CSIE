#include "Data_ChaMas.h"

Data_ChaMas::Data_ChaMas()
{
	SetMoney(0);
	SetExp(0);
	SetMaxExp(0);
	SetMaxMp(0);
	SetBuffTime(-2);
	SetPotionTime(-2);
	SetLv(1);
	SetPotion(1,5);
	SetPotion(2,0);
	SetPotion(3,5);
	SetPotion(4,0);
	SetPotion(5,0);
	skillName[0] = "Fiddle the bangs";
	skillName[1] = "Wash wash sleep la";
	skillName[2] = "Ride the bike without hand";
	chaName = "Sir 87";
	SetSuit(0);
	InitialArray();
}

Data_ChaMas::~Data_ChaMas()
{
}

void Data_ChaMas::InitialArray()
{
	mSkillMp[0] = 150;
	mSkillMp[1] = 100;
	mSkillMp[2] = 150;
	mSkillCoefficient[0] = 1.5;
	mSkillCoefficient[1] = 1.5;
	mSkillCoefficient[2] = 1.2;
}

void Data_ChaMas::LvUp()
{
	SetHp(GetHp() + 100);
	SetMp(GetMp() + 100);
	SetAtk(GetAtk() + 100);
	SetDamage(GetAtk());
	SetMaxHp(GetMaxHp() + 100);
	SetMaxMp(GetMaxHp() + 100);
	SetLv(GetLv() + 1);
	//SetExp(0);
	SetMaxExp(GetLv() * 110);
}

int Data_ChaMas::CheckLvUp()
{
	if (GetExp() >= (110 * GetLv()))
    {
        
        return 1;
    }
    else
        return 0;

}

void Data_ChaMas::ChooseMaster(int Order)
{
	switch (Order)
	{
	case 1:
		SetHp(500);
		SetMp(500);
		SetAtk(200);
		SetMaxHp(500);
		SetMaxMp(500);
		SetMaxExp(GetLv() * 110);
		break;
	case 2:
		SetHp(700);
		SetMp(300);
		SetAtk(100);
		SetMaxHp(700);
		SetMaxMp(300);
		SetMaxExp(GetLv() * 110);
		break;
	case 3:
		SetHp(600);
		SetMp(450);
		SetAtk(100);
		SetMaxHp(600);
		SetMaxMp(450);
		SetMaxExp(GetLv() * 110);
		break;
	case 4:
		SetHp(550);
		SetMp(300);
		SetAtk(150);
		SetMaxHp(550);
		SetMaxMp(300);
		SetMaxExp(GetLv() * 110);
		break;
	}
	SetDamage(GetAtk());
}

int Data_ChaMas::UsePotion(int a)
{
    a-=1;
	switch (a){
	case 0:
		if (GetPotion(a) > 0 && GetHp() != GetMaxHp()){
			SetPotion(a, GetPotion(a) - 1);
			SetHp(GetHp() + 400);
			if(GetHp()>GetMaxHp())
            {
                SetHp(GetMaxHp());
            }
			return 1;
		}
		else if (GetPotion(a) == 0)
			return 2;
		else if (GetMaxHp() == GetHp())
			return 0;

	case 1:
		if (GetPotion(a) > 0 && GetHp() != GetMaxHp()){
			SetPotion(a, GetPotion(a) - 1);
			SetHp(GetHp() + 800);
			if(GetHp()>GetMaxHp())
            {
                SetHp(GetMaxHp());
            }
			return 1;
		}
		else if (GetPotion(a) == 0)
			return 2;
		else if (GetMaxHp() == GetHp())
			return 0;

	case 2:
		if (GetPotion(a) > 0 && GetMp() != GetMaxMp()){
			SetPotion(a, GetPotion(a) - 1);
			SetMp(GetMp() + 400);
			if(GetMp()>GetMaxMp())
            {
                SetMp(GetMaxMp());
            }
			return 1;
		}
		else if (GetPotion(a) == 0)
			return 2;
		else if (GetMaxMp() == GetMp())
			return 0;

	case 3:
		if (GetPotion(a) > 0 && GetMp() != GetMaxMp()){
			SetPotion(a, GetPotion(a) - 1);
			SetMp(GetMp() + 800);
			if(GetMp()>GetMaxMp())
            {
                SetMp(GetMaxMp());
            }
			return 1;
		}
		else if (GetPotion(a) == 0)
			return 2;
		else if (GetMaxMp() == GetMp())
			return 0;

	case 4:
		if (GetPotion(a) > 0){
			SetPotion(a, GetPotion(a) - 1);
			SetPotionTime(2);
			SetDamage(GetDamage()*1.5);
			return 1;
		}
		else if (GetPotion(a) == 0)
			return 2;

	}
}

int Data_ChaMas::UseSkillOne()
{

	if (GetMp() >= mSkillMp[0]){
		SetMp(GetMp() - mSkillMp[0]);
		SetBuffTime(2);
		SetDamage(GetDamage()*mSkillCoefficient[0]);
		return 1;
	}
	else
		return 0;

}

int Data_ChaMas::UseSkillTwo(std::vector<Data_ChaEnemy>& enemy,int a)
{

	if (GetMp() >= mSkillMp[1]){
		SetMp(GetMp() - mSkillMp[1]);

		int tmp = GetDamage()*mSkillCoefficient[1];

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

int Data_ChaMas::UseSkillThr(std::vector<Data_ChaEnemy>& enemy,int a)
{

	if (GetMp() >= mSkillMp[2]){
		SetMp(GetMp() - mSkillMp[2]);
		int tmp = GetDamage()*mSkillCoefficient[2];
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

void Data_ChaMas::ChangeSuit(int a)
{
	switch (GetSuit()){
	case 0:
		switch (a){
		case 5:
			SetMaxHp(GetMaxHp() + 400);
			SetMaxMp(GetMaxMp() + 300);
			SetMoney(GetMoney() - 3200);
			SetSuit(1);
			break;
		case 6:
			SetMaxHp(GetMaxHp() + 900);
			SetMaxMp(GetMaxMp() + 200);
			SetMoney(GetMoney() - 6000);
			SetSuit(2);
			break;
		case 7:
			SetAtk(GetDamage() + 350);
			SetMoney(GetMoney() - 6000);
			SetSuit(3);
			break;
		}
		break;
	case 1:
		SetMaxHp(GetMaxHp() - 400);
		SetMaxMp(GetMaxMp() - 300);
		switch (a){
		case 5:
			SetMaxHp(GetMaxHp() + 400);
			SetMaxMp(GetMaxMp() + 300);
			SetMoney(GetMoney() - 3200);
			SetSuit(1);
			break;
		case 6:
			SetMaxHp(GetMaxHp() + 900);
			SetMaxMp(GetMaxMp() + 200);
			SetMoney(GetMoney() - 6000);
			SetSuit(2);
			break;
		case 7:
			SetAtk(GetDamage() + 350);
			SetMoney(GetMoney() - 6000);
			SetSuit(3);
			break;
		}
		break;
	case 2:
		SetMaxHp(GetMaxHp() - 400);
		SetMaxMp(GetMaxMp() - 300);
		switch (a){
		case 5:
			SetMaxHp(GetMaxHp() + 400);
			SetMaxMp(GetMaxMp() + 300);
			SetMoney(GetMoney() - 3200);
			SetSuit(1);
			break;
		case 6:
			SetMaxHp(GetMaxHp() + 900);
			SetMaxMp(GetMaxMp() + 200);
			SetMoney(GetMoney() - 6000);
			SetSuit(2);
			break;
		case 7:
			SetAtk(GetDamage() + 350);
			SetMoney(GetMoney() - 6000);
			SetSuit(3);
			break;
		}
		break;
	case 3:
		SetAtk(GetDamage() - 350);
		switch (a){
		case 5:
			SetMaxHp(GetMaxHp() + 400);
			SetMaxMp(GetMaxMp() + 300);
			SetMoney(GetMoney() - 3200);
			SetSuit(1);
			break;
		case 6:
			SetMaxHp(GetMaxHp() + 900);
			SetMaxMp(GetMaxMp() + 200);
			SetMoney(GetMoney() - 6000);
			SetSuit(2);
			break;
		case 7:
			SetAtk(GetDamage() + 350);
			SetMoney(GetMoney() - 6000);
			SetSuit(3);
			break;
		}
		break;
	}
}

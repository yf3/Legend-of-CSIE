#include "Data_NPC.h"


Data_NPC::Data_NPC()
{
}


Data_NPC::~Data_NPC()
{
}

int Data_NPCDiviner(Data_ChaMas& mas)
{
	if (mas.GetLv() >= 15)
		return 1;
	else return 0;
}

int Data_NPCSeller( Data_ChaMas& mas,int a)
{
	a -= 1;
	switch (a){
	case 0:
		if (mas.GetMoney() >= 200){
			mas.SetMoney(mas.GetMoney() - 200);
			mas.SetPotion(a, mas.GetPotion(a) + 1);
			return 1;
		}
		else
			return 0;
	case 1:
		if (mas.GetMoney() >= 500){
			mas.SetMoney(mas.GetMoney() - 500);
			mas.SetPotion(a, mas.GetPotion(a) + 1);
			return 1;
		}
		else
			return 0;
	case 2:
		if (mas.GetMoney() >= 200){
			mas.SetMoney(mas.GetMoney() - 200);
			mas.SetPotion(a, mas.GetPotion(a) + 1);
			return 1;
		}
		else
			return 0;
	case 3:
		if (mas.GetMoney() >= 500){
			mas.SetMoney(mas.GetMoney() - 500);
			mas.SetPotion(a, mas.GetPotion(a) + 1);
			return 1;
		}
		else
			return 0;
	case 4:
		if (mas.GetMoney() >= 1000){
			mas.SetMoney(mas.GetMoney() - 1000);
			mas.SetPotion(a, mas.GetPotion(a) + 1);
			return 1;
		}
		else
			return 0;
	case 5:
		if (mas.GetMoney() >= 3200 && mas.GetSuit() != 1){
			mas.ChangeSuit(a);
			return 1;
		}
		else if (mas.GetMoney() < 3200)
			return 0;
		else if (mas.GetSuit() == 1)
			return 2;
	case 6:
		if (mas.GetMoney() >= 5200 && mas.GetSuit() != 2){
			mas.ChangeSuit(a);
			return 1;
		}
		else if (mas.GetMoney() < 5200)
			return 0;
		else if (mas.GetSuit() == 2)
			return 2;
	case 7:
		if (mas.GetMoney() >= 6000 && mas.GetSuit() != 3){
			mas.ChangeSuit(a);
			return 1;
		}
		else if (mas.GetMoney() < 6000)
			return 0;
		else if (mas.GetSuit() == 3)
			return 2;
	}
}

void Data_NPCGaySan(Data_ChaMas& mas)
{
	mas.SetMoney(mas.GetMoney() + 3000);
}
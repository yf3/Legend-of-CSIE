#include "Data_ChaEnemy.h"
//6/2 add assignment operator

Data_ChaEnemy::Data_ChaEnemy()
{
}

Data_ChaEnemy::~Data_ChaEnemy()
{
}

void Data_ChaEnemy::SetCalculus(int a)
{
	SetType("Calculus");
	std::string skill("You will never pass!");
	if (a == 1){
		SetHp(2100);
		SetAtk(480);
		SetELv(10);
		SetSkill(skill);
		SetEMoney(480);
		SetEExp(550);
		SetMaxHp(2100);
	}
	if (a == 2){
		SetHp(2500);
		SetAtk(530);
		SetELv(11);
		SetSkill(skill);
		SetEMoney(530);
		SetEExp(620);
		SetMaxHp(2500);
	}
	if (a == 3){
		SetHp(2900);
		SetAtk(580);
		SetELv(12);
		SetSkill(skill);
		SetEMoney(580);
		SetEExp(690);
		SetMaxHp(2900);
	}
}

void Data_ChaEnemy::SetCrazyDog(int a)
{
	SetType("CrazyDog");
	std::string skill("Woooooooooooof~");
	if (a == 1){
		SetHp(500);
		SetAtk(180);
		SetELv(4);
		SetSkill(skill);
		SetEMoney(180);
		SetEExp(170);
		SetMaxHp(500);
	}
	if (a == 2){
		SetHp(700);
		SetAtk(230);
		SetELv(5);
		SetSkill(skill);
		SetEMoney(230);
		SetEExp(220);
		SetMaxHp(700);
	}
	if (a == 3){
		SetHp(900);
		SetAtk(280);
		SetELv(6);
		SetSkill(skill);
		SetEMoney(280);
		SetEExp(270);
		SetMaxHp(900);
	}
}

void Data_ChaEnemy::SetCuteSnail(int a)
{
	SetType("CuteSnail");
	std::string skill("Meeeeeeeeoooooooow~");
	if (a == 1){
		SetHp(300);
		SetAtk(50);
		SetELv(1);
		SetSkill(skill);
		SetEMoney(30);
		SetEExp(40);
		SetMaxHp(300);
	}
	if (a == 2){
		SetHp(350);
		SetAtk(100);
		SetELv(2);
		SetSkill(skill);
		SetEMoney(80);
		SetEExp(90);
		SetMaxHp(350);
	}
	if (a == 3){
		SetHp(400);
		SetAtk(150);
		SetELv(3);
		SetSkill(skill);
		SetEMoney(130);
		SetEExp(140);
		SetMaxHp(400);
	}
}

void Data_ChaEnemy::SetNDHUBird(int a)
{
	SetType("NDHUBird");
	std::string skill("WTF! I am protected species~");
	if (a == 1){
		SetHp(1200);
		SetAtk(330);
		SetELv(7);
		SetSkill(skill);
		SetEMoney(330);
		SetEExp(330);
		SetMaxHp(1200);
	}
	if (a == 2){
		SetHp(1500);
		SetAtk(380);
		SetELv(8);
		SetSkill(skill);
		SetEMoney(380);
		SetEExp(390);
		SetMaxHp(1500);
	}
	if (a == 3){
		SetHp(1800);
		SetAtk(430);
		SetELv(9);
		SetSkill(skill);
		SetEMoney(430);
		SetEExp(450);
		SetMaxHp(1800);
	}
}

void Data_ChaEnemy::SetSmallWaveBreaker()
{
	SetType("SmallWaveBreaker");
	std::string skill("For the king!");
	SetHp(4000);
	SetAtk(100);
	SetELv(50);
	SetSkill(skill);
	SetEMoney(0);
	SetMaxHp(4000);
	SetEExp(10);
}

void Data_ChaEnemy::SetWaveBreaker()
{
	SetType("WaveBreaker");
	std::string skill1("Shut the fuck up!");
	std::string skill2("Give you a super wavebreaker!");
	std::string skill3("Say goodbye to your head >_O");
	std::string skill4("Let you hear the voice of the crying sea!");

	SetHp(7000);
	SetAtk(1000);
	SetELv(9999);
	SetSkill(skill1);
	SetSkill(skill2);
	SetSkill(skill3);
	SetSkill(skill4);
	SetEMoney(500);
	SetEExp(1000);
	SetMaxHp(7000);

}

void Data_ChaEnemy::operator  = (Data_ChaEnemy rhs)
{
    this->SetHp(rhs.GetHp());
	this->SetAtk(rhs.GetAtk());
	this->SetELv(rhs.GetElv());
	this->SetEMoney(rhs.GetEMoney());
	this->SetEExp(rhs.GetEExp());
	this->SetMaxHp(rhs.GetMaxHp());
	this->SetType(rhs.GetType());
    skill.resize(rhs.skill.size());
    memcpy(&skill[0], &rhs.skill[0], rhs.skill.size() * sizeof(Data_ChaEnemy));
}

#include "Main_Function.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>

#include "Main_Fighting.h"

#include "Ctrl_UDLR.h"
#include "UI_Menu.h"
#include "UI_Console_Global.h"
#include "UI_Color.h"
#include "UI_Dialogue.h"
#include "UI_Draw.h"

#include "Data_Cha.h"
#include "Data_ChaEnemy.h"
#include "Data_ChaMas.h"
#include "Data_ChaMasDog.h"
#include "Data_ChaMasSor.h"
#include "Data_Random.h"

#define FIGHTING_RESULT
#define MAP1
#define MAP2
#define FIGHTING
#define SORRYIN

bool sorryJoin=false;

using namespace std;

void Main::MainDisplay(const string& displayFstream)
{
	if (displayFstream == "#S")
	{
		cout << endl << endl;
	}
	else if (displayFstream == "#E")
	{
		cout << endl << endl << "\t" << ">...........(Next)";
		cin.ignore(100, '\n');
		system("CLS");
	}
	else if (displayFstream == "@P")
	{
		cout << endl << endl << "\t" << ">";
		cin.ignore(100, '\n');
		cout << endl;
	}
	else if (displayFstream == "@N")
	{
		cout << endl << endl;
		Sleep(300);
	}
	else if (displayFstream != "")
	{
		cout << "\t";
		for (string::const_iterator iter = displayFstream.begin(); iter<displayFstream.end(); ++iter)
		{
			UI_Color color87;
			if (*iter == '/')
			{
				color87.SetColor(color87.TEXT_COLOR_YELLOW, color87.BG_COLOR_PINK);
			}
			else if (*iter == '|')
			{
				color87.SetColorStyle(color87.DEFAULT_COLOR_STYLE);
			}
			else
			{
				cout << *iter;
				Sleep(50);
			}
		}
	}
}

void Main::Question(Data_ChaMas &Mas)
{
	Console::SetWindowSize(120, 40);
	Console::SetWindowTitle("Legend of CSIE");


	Console::GotoXY(30, 8);
	cout << "看完這故事後,";
	Console::GotoXY(30, 9);
	cout << "你覺得主角是怎樣的人呢 ?";

	vector<string> masterQueList = { "高富帥\n", "小屁孩\n", "就是個八七\n", "廢宅" };

	UI_Menu Question(true, masterQueList, 30, 11);
	UI_Color qColor;
	Question.SetMenuColor(qColor.TEXT_COLOR_LIGHT_WHITE, qColor.BG_COLOR_BLACK, qColor.TEXT_COLOR_YELLOW, qColor.BG_COLOR_GREEN);
	int masterNumber = Question.MenuProcess();

	Mas.ChooseMaster(masterNumber + 1);
	//switch case in ChooseMaster is 1~4
	Console::ClearScreen(0, 0);
}

#ifdef FIGHTING
int Main::Fighting(int InMap, Data_ChaMas &SIR87, Data_ChaMasDog &LITTLE87, unsigned short& Round, int& Exp, int& Money)
{
	Main_Fighting fighting(SIR87, InMap);
	//call SIR87 to get Master Level, in map1
	SIR87.SetHp(SIR87.GetMaxHp());
	LITTLE87.SetHp(LITTLE87.GetMaxHp());
	SIR87.SetMp(SIR87.GetMaxMp());
	LITTLE87.SetMp(LITTLE87.GetMaxMp());
	SIR87.SetDamage(SIR87.GetAtk());
	LITTLE87.SetDamage(LITTLE87.GetAtk());

	fighting.teamList = { SIR87, LITTLE87 };

	unsigned short xHp = 28;//UI
	unsigned short yHp = 2;//UI


	/******************************************************************************************
	*                        Data_ChaMas's skill and hint list                               *
	******************************************************************************************/

	vector<string> little87skillList = { "Iden", "Bark!", "Bite!" };
	vector<string> little87skillHint = {
		"(200MP)\n\        HP = Max HP",
		"(150MP)\n\        Attack with 150% damage to an enemy",
		"(150MP)\n\        Attack with 120% damage to all enemy" };

	vector<string> sir87skillList = { "Settling Hair", "Wash Wash Sleep", "Hands-free Riding" };
	vector<string> sir87skillHint = {
		"(150MP)\n\        Attack increase 50% in following 2 rounds.",
		"(100MP)\n\        Attack with 150% damage to an enemy.",
		"(150MP)\n\        Attack with 120% damage to all enemy." };


	/*******************************************************************************************/

	UI_Color fightingColor;
	fightingColor.SetColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE);

	while (true)
	{

		UI_Menu enemyMenu(true, fighting.GetEnemyList(), 8, 2);
		enemyMenu.SetMenuColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE, fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_CYAN);
		enemyMenu.Output(8, 2);
		fightingColor.SetColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE);
		Console::ClearRect(xHp, yHp, 40, 4);
		fighting.ShowHP(xHp, yHp);

		vector<Data_ChaMas> teamList = { SIR87, LITTLE87 };

		Console::ClearRect(8, 20, 100, 5);
		fighting.ShowMasHPMP(8, 20, SIR87);
		fighting.ShowMasHPMP(38, 20, LITTLE87);

		/**********************************************
		Master Turn
		**********************************************/

		if ((fighting.GetRoundNumber() % teamList.size() == 0 && SIR87.GetHp()>0) || LITTLE87.GetHp() <= 0)
		{
			SIR87.SetBuffTime(SIR87.GetBuffTime() - 1);
			SIR87.SetPotionTime(SIR87.GetPotionTime() - 1);
			fighting.FightingTurn(SIR87, sir87skillList, sir87skillHint);
			fighting.ShowMasHPMP(8, 20, SIR87);
			fighting.ShowMasHPMP(38, 20, LITTLE87);

			/*bug*/
			if (SIR87.GetBuffTime() == 0)
			{
				SIR87.SetDamage(SIR87.GetAtk());
			}
			if (SIR87.GetPotionTime() == 0)
			{
				SIR87.SetDamage(SIR87.GetAtk());
			}

		}
		else if ((fighting.GetRoundNumber() % teamList.size() == 1 && LITTLE87.GetHp()>0) || SIR87.GetHp() <= 0)
		{
			fighting.FightingTurn(LITTLE87, little87skillList, little87skillHint);
			fighting.ShowMasHPMP(8, 20, SIR87);
			fighting.ShowMasHPMP(38, 20, LITTLE87);
			if (LITTLE87.GetBuffTime() == 0)
			{
				LITTLE87.SetDamage(LITTLE87.GetAtk());
			}
			if (LITTLE87.GetPotionTime() == 0)
			{
				LITTLE87.SetDamage(LITTLE87.GetAtk());
			}
		}

		/**********************************************
		CHECK WIN,LOSE, or Enemy Turn
		**********************************************/

		if (fighting.GetRoundEndYN() == 1)//Round End
		{

			fighting.SetRoundNumber(fighting.GetRoundNumber() + 1);

			if (fighting.CheckEnemies() == 1)//All enemies died
			{
				/**********
				*  WIN   *
				**********/
				for (int i = 0; i<fighting.GetEnemyType().size(); i++)
				{

					Exp += fighting.GetEnemyData(i).GetEExp();
					Money += fighting.GetEnemyData(i).GetEMoney();

				}
				SIR87.SetExp(SIR87.GetExp() + Exp);
				SIR87.SetMoney(SIR87.GetMoney() + Money);
				Round = fighting.GetRoundNumber() - 1;
				return 0;
			}

			else
			{
				/******************
				*  Enemies Turn  *
				******************/

				if (SIR87.GetHp() <= 0 || LITTLE87.GetHp() <= 0)
				{

					for (int i = 0; i<fighting.GetEnemyType().size(); i++)
					{
						if (fighting.GetEnemyData(i).GetHp() > 0)
						{
							if (LITTLE87.GetHp() <= 0)
							{
								SIR87.SetHp(SIR87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (SIR87.GetHp()<0)
								{
									SIR87.SetHp(0);
								}
							}

							else
							{
								LITTLE87.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (LITTLE87.GetHp()<0)
								{
									LITTLE87.SetHp(0);
								}
							}

						}

					}
				}
				else
				{
					for (int i = 0; i<fighting.GetEnemyType().size(); i++)
					{
						int attackWho = rand() % teamList.size();
						if (fighting.GetEnemyData(i).GetHp()>0)
						{
							if (attackWho == 0)
							{
								SIR87.SetHp(SIR87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (SIR87.GetHp()<0)
								{
									SIR87.SetHp(0);
								}
							}
							else
							{
								LITTLE87.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (LITTLE87.GetHp()<0)
								{
									LITTLE87.SetHp(0);
								}
							}

						}

					}

				}

				if (SIR87.GetHp() <= 0 && LITTLE87.GetHp() <= 0)
				{
					/**********
					*  LOSE  *
					**********/
					Console::ClearRect(8, 20, 70, 5);
					
					fighting.ShowMasHPMP(8, 20, SIR87);
					fighting.ShowMasHPMP(38, 20, LITTLE87);
					Round = fighting.GetRoundNumber() - 1;
					return 1;
				}
			}
		}
	}
}
#endif //FIGHTING
#ifdef SORRYIN
int Main::Fighting(int InMap, Data_ChaMas &SIR87, Data_ChaMasDog &LITTLE87, Data_ChaMasSor &SORRY, unsigned short& Round, int& Exp, int& Money)
{
	Main_Fighting fighting(SIR87, InMap);
	//call SIR87 to get Master Level, in Boss
	SIR87.SetHp(SIR87.GetMaxHp());
	LITTLE87.SetHp(LITTLE87.GetMaxHp());
	SORRY.SetHp(SORRY.GetMaxHp());

	SIR87.SetMp(SIR87.GetMaxMp());
	LITTLE87.SetMp(LITTLE87.GetMaxMp());
	SORRY.SetMp(SORRY.GetMaxMp());

	SIR87.SetDamage(SIR87.GetAtk());
	LITTLE87.SetDamage(LITTLE87.GetAtk());
	SORRY.SetDamage(SORRY.GetAtk());

	fighting.teamList = { SIR87, LITTLE87, SORRY };

	unsigned short xHp = 28;//UI
	unsigned short yHp = 2;//UI

	UI_Color fightingColor;
	fightingColor.SetColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE);

	/******************************************************************************************
	*                        Data_ChaMas's skill and hint list                               *
	******************************************************************************************/

	vector<string> little87skillList = { "Iden", "Bark!", "Bite!" };
	vector<string> little87skillHint = {
		"(200MP)\n\        HP = Max HP",
		"(150MP)\n\        Attack with 150% damage to an enemy",
		"(150MP)\n\        Attack with 120% damage to all enemy" };

	vector<string> sir87skillList = { "Settling Hair", "Wash Wash Sleep", "Hands-free Riding" };
	vector<string> sir87skillHint = {
		"(150MP)\n\        Attack increase 50% in following 2 rounds.",
		"(100MP)\n\        Attack with 150% damage to an enemy.",
		"(150MP)\n\        Attack with 120% damage to all enemy." };

	vector<string> sorryskillList = { "Iden", "I Was Strong Before", "Mouth cannon" };
	vector<string> sorryskillHint = {
		"(200MP)\n\        HP = Max HP",
		"(150MP)\n\        Attack with 150% damage to an enemy",
		"(150MP)\n\        Attack with 120% damage to all enemy" };


	/*******************************************************************************************/



	while (true)
	{

		UI_Menu enemyMenu(true, fighting.GetEnemyList(), 8, 2);
		enemyMenu.SetMenuColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE, fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_CYAN);
		enemyMenu.Output(8, 2);
		fightingColor.SetColor(fightingColor.TEXT_COLOR_BLACK, fightingColor.BG_COLOR_WHITE);

		Console::ClearRect(xHp, yHp, 40, 4);
		fighting.ShowHP(xHp, yHp);

		vector<Data_ChaMas> teamList = { SIR87, LITTLE87, SORRY };
		Console::ClearRect(8, 20, 120, 5);
		fighting.ShowMasHPMP(8, 20, SIR87);
		fighting.ShowMasHPMP(38, 20, LITTLE87);
		fighting.ShowMasHPMP(68, 20, SORRY);


		/**********************************************
		Master Turn
		**********************************************/

		if ((fighting.GetRoundNumber() % 3 == 0 && SIR87.GetHp()>0) || (LITTLE87.GetHp() <= 0 && SIR87.GetHp()>0) || (SIR87.GetHp()>0 && SORRY.GetHp() <= 0))
		{
			SIR87.SetBuffTime(SIR87.GetBuffTime() - 1);
			SIR87.SetPotionTime(SIR87.GetPotionTime() - 1);
			fighting.FightingTurn(SIR87, sir87skillList, sir87skillHint);
			Console::ClearRect(8, 20, 120, 5);
			fighting.ShowMasHPMP(8, 20, SIR87);
			fighting.ShowMasHPMP(38, 20, LITTLE87);
			fighting.ShowMasHPMP(68, 20, SORRY);

			/*bug*/
			if (SIR87.GetBuffTime() == 0)
			{
				SIR87.SetDamage(SIR87.GetAtk());
			}
			if (SIR87.GetPotionTime() == 0)
			{
				SIR87.SetDamage(SIR87.GetAtk());
			}

		}
		else if ((fighting.GetRoundNumber() % 3 == 1 && LITTLE87.GetHp()>0) || (SIR87.GetHp() <= 0 && LITTLE87.GetHp()>0) || (LITTLE87.GetHp()>0 && SORRY.GetHp() <= 0))
		{
			fighting.FightingTurn(LITTLE87, little87skillList, little87skillHint);
			Console::ClearRect(8, 20, 120, 5);
			fighting.ShowMasHPMP(8, 20, SIR87);
			fighting.ShowMasHPMP(38, 20, LITTLE87);
			fighting.ShowMasHPMP(68, 20, SORRY);
			if (LITTLE87.GetBuffTime() == 0)
			{
				LITTLE87.SetDamage(LITTLE87.GetAtk());
			}
			if (LITTLE87.GetPotionTime() == 0)
			{
				LITTLE87.SetDamage(LITTLE87.GetAtk());
			}
		}

		else
		{
			fighting.FightingTurn(SORRY, sorryskillList, sorryskillHint);
			Console::ClearRect(8, 20, 120, 5);
			fighting.ShowMasHPMP(8, 20, SIR87);
			fighting.ShowMasHPMP(38, 20, LITTLE87);
			fighting.ShowMasHPMP(68, 20, SORRY);
			if (SORRY.GetBuffTime() == 0)
			{
				SORRY.SetDamage(SORRY.GetAtk());
			}
			if (SORRY.GetPotionTime() == 0)
			{
				SORRY.SetDamage(SORRY.GetAtk());
			}
		}


		/**********************************************
		CHECK WIN,LOSE, or Enemy Turn
		**********************************************/

		if (fighting.GetRoundEndYN() == 1)//Round End
		{

			fighting.SetRoundNumber(fighting.GetRoundNumber() + 1);

			if (fighting.CheckEnemies() == 1)//All enemies died
			{
				/**********
				*  WIN   *
				**********/
				for (int i = 0; i<fighting.GetEnemyType().size(); i++)
				{

					Exp += fighting.GetEnemyData(i).GetEExp();
					Money += fighting.GetEnemyData(i).GetEMoney();

				}
				SIR87.SetExp(SIR87.GetExp() + Exp);
				SIR87.SetMoney(SIR87.GetMoney() + Money);
				Round = fighting.GetRoundNumber() - 1;
				return 0;
			}

			else
			{
				/******************
				*  Enemies Turn  *
				******************/

				for (int i = 0; i<fighting.GetEnemyType().size(); i++)
				{
					int attackWho = rand() % 3;


					if (fighting.GetEnemyData(i).GetHp()>0)
					{
						if (attackWho == 0 && SIR87.GetHp()>0)
						{
							SIR87.SetHp(SIR87.GetHp() - fighting.GetEnemyData(i).GetAtk());
							if (SIR87.GetHp()<0)
							{
								SIR87.SetHp(0);
							}
						}

						else if (attackWho == 1 && LITTLE87.GetHp()>0)
						{
							LITTLE87.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
							if (LITTLE87.GetHp()<0)
							{
								LITTLE87.SetHp(0);
							}
						}

						else if (attackWho == 2 && SORRY.GetHp()>0)
						{
							SORRY.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
							if (SORRY.GetHp()<0)
							{
								SORRY.SetHp(0);
							}
						}

						else
						{
							attackWho = (attackWho + 1) % 3;
							if (attackWho == 0 && SIR87.GetHp()>0)
							{
								SIR87.SetHp(SIR87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (SIR87.GetHp()<0)
								{
									SIR87.SetHp(0);
								}
							}

							else if (attackWho == 1 && LITTLE87.GetHp()>0)
							{
								LITTLE87.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (LITTLE87.GetHp()<0)
								{
									LITTLE87.SetHp(0);
								}
							}

							else if (attackWho == 2 && SORRY.GetHp()>0)
							{
								SORRY.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
								if (SORRY.GetHp()<0)
								{
									SORRY.SetHp(0);
								}
							}
							else
							{
								attackWho = (attackWho + 1) % 3;
								if (attackWho == 0 && SIR87.GetHp()>0)
								{
									SIR87.SetHp(SIR87.GetHp() - fighting.GetEnemyData(i).GetAtk());
									if (SIR87.GetHp()<0)
									{
										SIR87.SetHp(0);
									}
								}

								else if (attackWho == 1 && LITTLE87.GetHp()>0)
								{
									LITTLE87.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
									if (LITTLE87.GetHp()<0)
									{
										LITTLE87.SetHp(0);
									}
								}

								else if (attackWho == 2 && SORRY.GetHp()>0)
								{
									SORRY.SetHp(LITTLE87.GetHp() - fighting.GetEnemyData(i).GetAtk());
									if (SORRY.GetHp()<0)
									{
										SORRY.SetHp(0);
									}
								}
							}


						}

					}

				}



				if (SIR87.GetHp() <= 0 && LITTLE87.GetHp() <= 0 && SORRY.GetHp() <= 0)
				{
					/**********
					*  LOSE  *
					**********/
					Console::ClearRect(8, 20, 120, 5);
					fighting.ShowMasHPMP(8, 20, SIR87);
					fighting.ShowMasHPMP(38, 20, LITTLE87);
					fighting.ShowMasHPMP(68, 20, SORRY);
					Round = fighting.GetRoundNumber() - 1;
					return 1;
				}
			}
		}
	}
}

#endif // SORRYIN


#ifdef FIGHTING_RESULT
void ShowRoundsMoney(const unsigned short xShow, unsigned short yShow, const unsigned int& roundsUse, const unsigned int& moneyInitial, const unsigned int& moneyFinal)
{
	UI_Color numColor;
	Console::GotoXY(xShow, yShow);
	cout << "Rounds Used: ";
	Console::GotoXY(xShow + 13, yShow);
	cout << roundsUse;

	yShow++;
	Console::GotoXY(xShow, yShow);
	cout << "$  : ";
	numColor.SetColor(numColor.TEXT_COLOR_LIGHT_CYAN, numColor.BG_COLOR_BLACK);
	cout << moneyInitial;

	Sleep(1000);
	Console::ClearRect(xShow + 5, yShow, 10, 1);
	for (unsigned int i = moneyInitial;; i += 3)
	{
		if (i<moneyFinal)
		{
			Console::GotoXY(xShow + 5, yShow);
			cout << i;
			Sleep(5);
			Console::ClearRect(xShow + 5, yShow, 10, 1);
		}
		else
		{
			numColor.SetColor(numColor.TEXT_COLOR_LIGHT_RED, numColor.BG_COLOR_BLACK);
			Console::GotoXY(xShow + 5, yShow);
			cout << moneyFinal;
			numColor.SetColorStyle(numColor.DEFAULT_COLOR_STYLE);
			break;
		}
	}
}
void ShowExpLevel(const unsigned short xShow, const unsigned short yShow, const unsigned int& expInitial, const unsigned int& expFinal)
{
	UI_Color numColor;
	Console::GotoXY(xShow, yShow);

	cout << "Exp: ";

	Console::GotoXY(xShow + 5, yShow);
	numColor.SetColor(numColor.TEXT_COLOR_LIGHT_CYAN, numColor.BG_COLOR_BLACK);
	cout << expInitial;

	Sleep(1000);
	Console::ClearRect(xShow + 5, yShow, 10, 1);
	for (unsigned int i = expInitial;; i += 7)
	{
		if (i<expFinal)
		{
			Console::GotoXY(xShow + 5, yShow);
			cout << i;
			Sleep(5);
			Console::ClearRect(xShow + 5, yShow, 10, 1);
		}
		else
		{
			numColor.SetColor(numColor.TEXT_COLOR_LIGHT_RED, numColor.BG_COLOR_BLACK);
			Console::GotoXY(xShow + 5, yShow);
			cout << expFinal;
			numColor.SetColorStyle(numColor.DEFAULT_COLOR_STYLE);
			break;
		}
	}

}

void ShowLevelUP(const unsigned short xShow, unsigned short yShow, bool up, const unsigned short seperate, bool sorryJoin)
{
	UI_Color numColor;
	int i = 0;
	while (i<5)
	{
		if (i % 2)
		{
			numColor.SetColor(numColor.TEXT_COLOR_PINK, numColor.BG_COLOR_BLACK);
		}
		else
		{
			numColor.SetColor(numColor.TEXT_COLOR_YELLOW, numColor.BG_COLOR_BLACK);
		}
		++i;
		Console::GotoXY(xShow, yShow);
		cout << "Level UP!";
		Console::GotoXY(xShow, yShow + seperate);
		cout << "Level UP!";
		if (sorryJoin)
		{
			Console::GotoXY(xShow, yShow + seperate + seperate);
			cout << "Level UP!";
		}
		Sleep(600);
	}
}

void Main::Fighting_Result(string title, unsigned int FightingRound, unsigned int expI, unsigned int expF, unsigned int moneyI, unsigned int moneyF, Data_ChaMas& SIR87, bool sorryJoin)
{
	UI_Color temp;
	temp.SetColorStyle(temp.DEFAULT_COLOR_STYLE);
	Console::SetWindowSize(120, 40);
	Console::ClearScreen(0, 0);
	UI_Draw drawBig;

	string sir87Str("SIR 87");
	string little87Str("LITTLE 87");
	string sorryStr("SORRY");
	const unsigned short TITLE_LEFT_BOUND = 20;
	const unsigned short SIR87_LEFT_BOUND = 23;
	const unsigned short LITTLE87_LEFT_BOUND = 5;
	const unsigned short SORRY_LEFT_BOUND = 29;
	const unsigned short NAME_UPPER_BOUND = 15;
	const unsigned short NAME_SEPRETE = 6;

	drawBig.SetFilledText(temp.TEXT_COLOR_LIGHT_GREEN);
	drawBig.DrawBigCharString(TITLE_LEFT_BOUND, 1, title);
	drawBig.SetFilledText(temp.TEXT_COLOR_YELLOW);
	drawBig.DrawBigCharString(SIR87_LEFT_BOUND, NAME_UPPER_BOUND, sir87Str);
	drawBig.DrawBigCharString(LITTLE87_LEFT_BOUND, NAME_UPPER_BOUND + NAME_SEPRETE, little87Str);
	if (sorryJoin)
		drawBig.DrawBigCharString(SORRY_LEFT_BOUND, NAME_UPPER_BOUND + NAME_SEPRETE + NAME_SEPRETE, sorryStr);


	const unsigned short INFO_X_POS = 65;
	const unsigned short INFO_Y_POS = NAME_UPPER_BOUND + 1;

	ShowRoundsMoney(50, 10, FightingRound + 1, moneyI, moneyF);
	ShowExpLevel(INFO_X_POS, INFO_Y_POS, expI, expF);
	ShowExpLevel(INFO_X_POS, INFO_Y_POS + NAME_SEPRETE, expI, expF);
	if (sorryJoin)
		ShowExpLevel(INFO_X_POS, INFO_Y_POS + NAME_SEPRETE + NAME_SEPRETE, expI, expF);

	if (SIR87.CheckLvUp() == 1)
	{
		ShowLevelUP(INFO_X_POS, INFO_Y_POS + 2, true, NAME_SEPRETE, sorryJoin);
	}

	cin.get();
}
#endif //FIGHTING_RESULT

#ifdef MAP1
void ShowPosition(const unsigned short& x, const unsigned short& y);
void ShowPlayer(unsigned short& x, unsigned short& y);
void ShowInteraction(const string& diaName);
void ShowMap(const string& activeMap);
void ShowMapFile(const string& mapFileName, string& stdMapStr);
int ControlSection(const string& activeMap, unsigned short& x, unsigned short& y, Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, bool& reload);
void SalesPerson(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87);
void GaySen();
void James(Data_ChaMas& SIR87);


void ShowPosition(const unsigned short& x, const unsigned short& y)
{
	Console::ClearRect(100, 1, 20, 1);
	Console::GotoXY(85, 1);
	cout << "Your position: " << "x: " << x - 5 << " y: " << y - 3;
}

void ShowPlayer(unsigned short& x, unsigned short& y)
{
	UI_Color playerColor;
	playerColor.SetColorStyle(playerColor.MENU_CS_DEFAULT);
	Console::GotoXY(x, y);
	cout << "Q";
}

void ShowInteraction(const string& diaName)
{
	UI_Color interColor;
	if (diaName == "defaultHint")
		interColor.SetColor(interColor.TEXT_COLOR_BLACK, interColor.BG_COLOR_WHITE);
	else
		interColor.SetColor(interColor.TEXT_COLOR_LIGHT_WHITE, interColor.BG_COLOR_BLUE);
	Console::ClearRect(5, 34, 110, 5);

	UI_Dialogue dialogue;
	string str;
	str = dialogue.GetDialogue(diaName);
	const string::iterator endIt = str.end();
	for (string::iterator iter = str.begin(); iter<endIt; ++iter)
	{
		cout << *iter;
		if (*iter == '\n')
		{
			Console::GotoXY(5, Console::GetY());
		}
	}
	if (diaName != "defaultHint" && diaName!="emptyStr")
		cin.ignore(100, '\n');

}

void ShowMap(const string& activeMap)
{
	UI_Color mapColor;
	string::const_iterator endIT = activeMap.end();
	Console::GotoXY(5, 3);

	mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
	for (string::const_iterator it = activeMap.begin(); it<endIT; ++it)
	{
		switch (*it)
		{
		case ' ':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_BLACK);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
			break;
		case '\n':
			cout << *it;
			Console::GotoXY(5, Console::GetY());
			break;
		case 'G':
			mapColor.SetColor(mapColor.TEXT_COLOR_PINK, mapColor.BG_COLOR_PURPLE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
			break;
		case 'S':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_GREEN);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
			break;
		case 'J':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_GOLD);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
			break;
		case 'D':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_BLACK);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_RED, mapColor.BG_COLOR_BLACK);
			break;
		default:
			cout << *it;
			break;
		}
	}
}

int ControlSection(const string& activeMap, unsigned short& x, unsigned short& y, Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, bool& reload)
{
	unsigned short xCor = x - 5;
	unsigned short yCor = y - 3;
	ShowPlayer(x, y);
	Data_Random meetEnemy;

	unsigned int currentIndex = 111 * yCor + xCor;
	unsigned int upIndex = currentIndex - 111;
	unsigned int downIndex = currentIndex + 111;
	unsigned int leftIndex = currentIndex - 1;
	unsigned int rightIndex = currentIndex + 1;

	UI_Color roadColor;
	roadColor.SetColorStyle(roadColor.DEFAULT_COLOR_STYLE);
	Ctrl_UDLR key;
	Data_Random fight;




	switch (key.Ctrl_UDLR_Return())
	{
	case key.Up:
		if (activeMap[upIndex] == ' ')
		{
			Console::ClearRect(x, y, 1, 1);
			--y;
		}

		if (meetEnemy.MeetEnemy() == 1)
		{
			ShowInteraction("map1Fight");
			reload = true;
			roadColor.SetColor(roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			Console::FlareClear(roadColor.BG_COLOR_BLACK, roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			//Console::ClearScreen(0, 0);
			unsigned short FightingRound = 0;
			int FightingExp = 0;
			int FightingMoney = 0;

			unsigned short WL = Main::Fighting(1, SIR87, LITTLE87, FightingRound, FightingExp, FightingMoney);
			if (WL == 0) //WIN
			{//UI_WIN
				
				Main::Fighting_Result("YOU WIN! TWT", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				if (SIR87.CheckLvUp() == 1)
				{
					SIR87.LvUp();
					int tmp = SIR87.GetExp() - (110 * SIR87.GetLv());
					SIR87.SetExp(tmp);
					LITTLE87.LvUp();
				}
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}

			else //LOSE
			{//UI_LOSE
				Main::Fighting_Result("YOU LOSE! T_T", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);

				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}
		}
		break;


	case key.Down:
		if (activeMap[downIndex] == ' ')
		{
			Console::ClearRect(x, y, 1, 1);
			++y;
		}

		if (meetEnemy.MeetEnemy() == 1)
		{
			ShowInteraction("map1Fight");
			reload = true;
			roadColor.SetColor(roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			Console::FlareClear(roadColor.BG_COLOR_BLACK, roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			//Console::ClearScreen(0, 0);
			unsigned short FightingRound = 0;
			int FightingExp = 0;
			int FightingMoney = 0;

			unsigned short WL = Main::Fighting(1, SIR87, LITTLE87, FightingRound, FightingExp, FightingMoney);
			if (WL == 0) //WIN
			{//UI_WIN
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU WIN! TWT", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				if (SIR87.CheckLvUp() == 1)
				{
					SIR87.LvUp();
					int tmp = SIR87.GetExp() - (110 * SIR87.GetLv());
					SIR87.SetExp(tmp);
					LITTLE87.LvUp();
				}
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}

			else //LOSE
			{//UI_LOSE
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU LOSE! T_T", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}
		}
		break;

	case key.Left:
		if (activeMap[leftIndex] == ' ')
		{
			Console::ClearRect(x, y, 1, 1);
			--x;
		}
		else if (activeMap[leftIndex] == 'D')
			return 1;

		if (meetEnemy.MeetEnemy() == 1)
		{
			ShowInteraction("map1Fight");
			reload = true;
			roadColor.SetColor(roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			Console::FlareClear(roadColor.BG_COLOR_BLACK, roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			//Console::ClearScreen(0, 0);
			unsigned short FightingRound = 0;
			int FightingExp = 0;
			int FightingMoney = 0;

			unsigned short WL = Main::Fighting(1, SIR87, LITTLE87, FightingRound, FightingExp, FightingMoney);
			if (WL == 0) //WIN
			{//UI_WIN
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU WIN! TWT", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				if (SIR87.CheckLvUp() == 1)
				{
					SIR87.LvUp();
					int tmp = SIR87.GetExp() - (110 * SIR87.GetLv());
					SIR87.SetExp(tmp);
					LITTLE87.LvUp();
				}
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}

			else //LOSE
			{//UI_LOSE
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU LOSE! T_T", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}
		}
		break;


	case key.Right:
		if (activeMap[rightIndex] == ' ')
		{
			Console::ClearRect(x, y, 1, 1);
			++x;
		}

		if (meetEnemy.MeetEnemy() == 1)
		{
			ShowInteraction("map1Fight");
			reload = true;
			roadColor.SetColor(roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			Console::FlareClear(roadColor.BG_COLOR_BLACK, roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_WHITE);
			//Console::ClearScreen(0, 0);
			unsigned short FightingRound = 0;
			int FightingExp = 0;
			int FightingMoney = 0;

			unsigned short WL = Main::Fighting(1, SIR87, LITTLE87, FightingRound, FightingExp, FightingMoney);
			if (WL == 0) //WIN
			{//UI_WIN
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU WIN! TWT", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				if (SIR87.CheckLvUp() == 1)
				{
					SIR87.LvUp();
					int tmp = SIR87.GetExp() - (110 * SIR87.GetLv());
					SIR87.SetExp(tmp);
					LITTLE87.LvUp();
				}
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}

			else //LOSE
			{//UI_LOSE
				Console::ClearScreen(0, 0);
				Main::Fighting_Result("YOU LOSE! T_T", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
				UI_Color bgColor;
				unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				bgColor.SetColorStyle(bgDefault);
				Console::ClearScreen(0, 0);
			}
		}
		break;


	case key.Selected:
		if (activeMap[upIndex] == 'S' || activeMap[downIndex] == 'S' || activeMap[leftIndex] == 'S' || activeMap[rightIndex] == 'S')
			SalesPerson(SIR87, LITTLE87);
		else if (activeMap[upIndex] == 'G' || activeMap[downIndex] == 'G' || activeMap[leftIndex] == 'G' || activeMap[rightIndex] == 'G')
			GaySen();
		else if (activeMap[upIndex] == 'J' || activeMap[downIndex] == 'J' || activeMap[leftIndex] == 'J' || activeMap[rightIndex] == 'J')
			James(SIR87);

		break;
	default:
		break;
	}
	return 0;
}

void SalesPerson(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87)
{
	ShowInteraction("saleStart");
	ShowInteraction("emptyStr"); // to clear
	vector<string> typeList = { "裝備", "藥水", "取消" };
	vector<string> potionList = { "Basic HP Potion:Recover 400 HP", "Super HP Potion:Recover 800 HP", "Basic MP Potion:Recover 400 MP", "Super MP Potion:Recover 800 MP", "Attack Bonus Potion:Atk x 1.5" };
	UI_Color saleColor;
	UI_Menu typeMenu(true, typeList, 5, 34);
	UI_Menu potionMenu(true, potionList, 5, 34);
	
	unsigned int typeOption = typeMenu.MenuProcess();
	switch (typeOption)
	{
	case 0:
		ShowInteraction("saleEq");
		break;
	case 1:
	{
		ShowInteraction("emptyStr");
		unsigned int potionOption = potionMenu.MenuProcess();
		switch (potionOption)
		{
		case 0:
			SIR87.SetPotion(0, SIR87.GetPotion(0)+1);
			LITTLE87.SetPotion(0, LITTLE87.GetPotion(0) + 1);
			break;
		case 1:
			SIR87.SetPotion(1, SIR87.GetPotion(1) + 1);
			LITTLE87.SetPotion(1, LITTLE87.GetPotion(1) + 1);
			break;
		case 2:
			SIR87.SetPotion(2, SIR87.GetPotion(2) + 1);
			LITTLE87.SetPotion(2, LITTLE87.GetPotion(2) + 1);
			break;
		case 3:
			SIR87.SetPotion(3, SIR87.GetPotion(3) + 1);
			LITTLE87.SetPotion(3, LITTLE87.GetPotion(3) + 1);
			break;
		case 4:
			SIR87.SetPotion(4, SIR87.GetPotion(4) + 1);
			LITTLE87.SetPotion(4, LITTLE87.GetPotion(4) + 1);
			break;
		}
		ShowInteraction("saleFinish");
		break;
	}
	case 2:
		ShowInteraction("saleCancel");
		break;
	}
	ShowInteraction("defaultHint");
}

void GaySen()
{
	ShowInteraction("gayStart");
	ShowInteraction("emptyStr"); // to clear
	vector<string> typeList = { "換錢", "取消" };
	UI_Menu typeMenu(true, typeList, 5, 34);
	unsigned int typeOption = typeMenu.MenuProcess();
	switch (typeOption)
	{
	case 0:
		ShowInteraction("gayFinish1");
		ShowInteraction("gayFinish2");
		break;
	case 1:
		ShowInteraction("gayCancel");
		break;
	}
	ShowInteraction("defaultHint");
}

void James(Data_ChaMas& SIR87)
{
	ShowInteraction("jamesStart");
	ShowInteraction("emptyStr"); // to clear
	vector<string> typeList = { "都算都算", "洗洗睡啦"};
	UI_Menu typeMenu(true, typeList, 5, 34);
	unsigned int typeOption = typeMenu.MenuProcess();
	switch (typeOption)
	{
		case 0:
		{
			int lv = SIR87.GetLv();
			if (lv < 10)
				ShowInteraction("jamesUnder");
			else if (lv < 15)
				ShowInteraction("jamesAbout");
			else
				ShowInteraction("jamesOver");
			break;
		}
		case 1:
			ShowInteraction("jamesCancel");
			break;
	}
	ShowInteraction("defaultHint");
}

void Main::Map1(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87)
{
	Console::SetWindowSize(120, 40);
	unsigned short mXpos = 111;
	unsigned short mYpos = 31;
	UI_Color bgColor;
	unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
	bgColor.SetColorStyle(bgDefault);
	Console::ClearScreen(0, 0);

	//Console::GotoXY(5, 1);
	//cout << "NDHU MAP";
	//Console::GotoXY(20, 1);
	//cout << "Player Icon:Q";

	//ShowPosition(mXpos, mYpos);

	const string ndhuMap("\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
H                                  HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHHHHHH\n\
D                                  HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHHHHH\n\
H                                  HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHHHHHH  HHHHHHHHHHHHHHHHHH\n\
HH   HHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHH\n\
HH J HHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHH   HHHHHHHHHH    HHHHHHH\n\
HH   HHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHH   HHHHHHHHHH HHH   HHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH HHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH    HHHHHHHHHHHHHH HHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HH  HHHHHHHH      HHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HHHHHHHH  HHH  HHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHH            HHHHHHHHHHHHHHHHHHHHHHHHHHHHH  HHHHHHHH     HHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHH     G      HHHHHHHHHHHHHHHHHHHHHHHHHH    HHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHH            HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHH                   HHHH    HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHH                   HHHH    HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHH                   HHHH    HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH            HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH                                                        HHHHHHHHHHH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH                                                        HHHHHHHHHHH\n\
HHH           H          HHHHHHHHHHHHHHHHHH                                                        HHHHHHHHHHH\n\
HHH   HHHHH   H   HHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHH   HHHHHHHHHHH\n\
HHH   HHHHH   H   HHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HHHHHHHHHHHH   HHHHHHHHHHH\n\
HHH           HHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH                           HH\n\
HHH   HHHHH   HHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH         S                 HH\n\
HHH   HHHHH   HHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH                           HH\n\
HHH           HHHHHHHH   HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH   HH\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");

	bool reload = true;
	while (true)
	{
		Console::GotoXY(5, 1);
		cout << "NDHU MAP";
		Console::GotoXY(20, 1);
		cout << "Player Icon:Q";

		ShowPosition(mXpos, mYpos);

		if (reload)
		{
			Console::GotoXY(5, 1);
			cout << "NDHU MAP";
			Console::GotoXY(20, 1);
			cout << "Player Icon:Q";
			ShowMap(ndhuMap);
			ShowInteraction("defaultHint");
			reload = false;
		}

		int EnterMap2 = ControlSection(ndhuMap, mXpos, mYpos, SIR87, LITTLE87, reload);
		Console::GotoXY(40, 1);
		bgColor.SetColorStyle(bgDefault);
		cout << "LV:" << SIR87.GetLv() << " Money:" << SIR87.GetMoney();
		if (EnterMap2 == 1)
		{
			Console::FlareClear(bgColor.BG_COLOR_BLACK, bgColor.TEXT_COLOR_LIGHT_WHITE, bgColor.BG_COLOR_BLACK);
			UI_Color bgColor;
			bgColor.SetColorStyle(bgColor.DEFAULT_COLOR_STYLE);
			Console::ClearScreen(0, 0);

			ifstream storyStream("storyToMap2.txt");
			if (storyStream.fail())
			{
				cout << "Load Fail!" << endl;
			}
			string storyLine;
			while (getline(storyStream, storyLine))
			{
				Main::MainDisplay(storyLine);
			}
			storyStream.close();
			break;
		}
		bgColor.SetColorStyle(bgDefault);
		ShowPosition(mXpos, mYpos);
	}
}

#endif // MAP1

#ifdef MAP2
void ShowPlayer2(const unsigned short& x, const unsigned short& y);
void GoUpStair(const unsigned short currentIndex, unsigned short& y, const string& activeMap);
void GoDownStair(const unsigned short currentIndex, unsigned short& y, const string& activeMap);
void ShowInteraction2(const string& diaName);
void ShowSeaMap(const string& activeMap);
void ReDrawMap(const unsigned short& currentIndex, const unsigned short& leftX, const unsigned short& upY, const string& activeMap);
void EraseBigObject(string& activeMap, unsigned short rightIndex, unsigned int width, unsigned int height);
void BossDisplay(const string& displayFstream);
void ControlSection2(string& activeMap, unsigned short& x, unsigned short& y, Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, Data_ChaMasSor& SORRY, bool& reload, int& mapState);


void Main::Map2(Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, Data_ChaMasSor& SORRY)
{
	Console::SetWindowSize(120, 40);
	unsigned short mXpos = 0;
	unsigned short mYpos = 29;
	UI_Color bgColor;
	unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
	bgColor.SetColorStyle(bgDefault);
	Console::ClearScreen(0, 0);

	Console::GotoXY(5, 1);
	cout << "消波塊海線";


	string seaMapStart("\
-----------------------------------------------------------------------------------------------------------------------\n\
                                                                                                                       \n\
                                                                             ~~~~~~~~~~~~~~~~~~                        \n\
               ~~~~~~~~~                                                  ~~~~~~~~~~~~~                                \n\
                ~~~~~~~                                                             ~~~~~~                             \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                ~~~~                                                                   \n\
                                            ~~~~~~~~~~~~~                                                              \n\
                                                  ~~~~~~~~~~                                                           \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                  {                       }                                                            \n\
                                                                                                                       \n\
                                   ###HHHHHHHHHHHHHHHHH###                                                             \n\
                                   ###HHHHHHHHHHHHHHHHH###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###                 ###                                                             \n\
                                   ###}               {###                                                             \n\
                                   ###                 ###                                                             \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
-----------------------------------------------------------------------------------------------------------------------\n");

	string seaMapSorry("\
-----------------------------------------------------------------------------------------------------------------------\n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                                                                                                       \n\
                                               O                                                                       \n\
              {                             S< | >                                          }                          \n\
                                             /   |                                                                     \n\
               ###HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH###                           \n\
               ###HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###                                                                       ###                           \n\
               ###}                                                                     {###                           \n\
               ###                                                                       ###                           \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
-----------------------------------------------------------------------------------------------------------------------\n");
	
	
	string seaMapBoss("\
-----------------------------------------------------------------------------------------------------------------------\n\
                                                                                                          @@@          \n\
            /                                                                                 @        @@     @@@      \n\
           /                                                                      Z            @@    @@          @  @@@\n\
          /                                                                         Z      / |  @@@@@             @@@  \n\
         /________                                                                    Z   /  |    @@@             @    \n\
                  /                                                                       |  |     @               @   \n\
                 /                              /                                         |  |    @  ___ ''_____   @   \n\
                /                              /                                          |  |    @                @   \n\
               /                              /                                           |  |   @   __________    @   \n\
                                             /________                                    |  |   @   |_______  |   @   \n\
                                                      /                                   |__|   @           |_|   @   \n\
                                                     /                                     ||    @                @    \n\
                                                    /                                      ||     @              @     \n\
                                                   /                                       ||       @           @      \n\
                                                                                           ||          @        @      \n\
                                                                                           ||          @         @@    \n\
                                                                                           ||         @             @  \n\
                                                                                           ||        @               @ \n\
                                                                                          @@@   @@@@  @         @@@@  @\n\
                                                                                         @    @@     @  @      @    @  \n\
                                                                                        @        @@@    @      @    @  \n\
                                                                                         @   @@@        @      @    @  \n\
                                                                                          @@@          @       @    @  \n\
                                                                                           ||       @@          @@  @  \n\
                                                                                           ||    @@                @@@@\n\
                                                                                b          || @@                    @@@\n\
                                                                                           ||@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n\
-----------------------------------------------------------------------------------------------------------------------\n");

	ShowSeaMap(seaMapStart);
	ShowPlayer2(mXpos, mYpos);

	ShowInteraction2("map2Start");
	ShowInteraction2("map2Hint");

	bool inMap2 = true;
	bool reload = true;
	int mapState = 0;
	while (inMap2)
	{

		switch (mapState)
		{
		case 0:
			ControlSection2(seaMapStart, mXpos, mYpos, SIR87, LITTLE87, SORRY, reload, mapState);
			break;
		case 1:
			if (reload)
			{
				mXpos = 0;
				mYpos = 29;
				ShowSeaMap(seaMapSorry);
				ShowPlayer2(mXpos, mYpos);
				reload = false;
			}
			ControlSection2(seaMapSorry, mXpos, mYpos, SIR87, LITTLE87, SORRY, reload, mapState);
			break;
		case 2:
			if (reload)
			{
				mXpos = 0;
				mYpos = 29;
				ShowSeaMap(seaMapBoss);
				ShowPlayer2(mXpos, mYpos);
				reload = false;
			}
			ControlSection2(seaMapBoss, mXpos, mYpos, SIR87, LITTLE87, SORRY, reload, mapState);
			break;
		case 3:
			break;
		default:
			break;
		}
		/*************************************************
		something wrong with BG_COLOR when FIGHTING
		*************************************************/
		bgColor.SetColorStyle(bgDefault);
	}
}

void ShowPlayer2(const unsigned short& x, const unsigned short& y)
{
	UI_Color playerColor;
	playerColor.SetColor(playerColor.TEXT_COLOR_BLUE, playerColor.BG_COLOR_LIGHT_WHITE);
	Console::GotoXY(x, y);
	cout << "_Q_";
	Console::GotoXY(x, y + 1);
	cout << "/ \\";
}

void GoUpStair(const unsigned short currentIndex, unsigned short& y, const string& activeMap)
{
	unsigned short newIndex = currentIndex;
	while (activeMap[newIndex] == '#')
	{
		newIndex -= 120;
		--y;
	}
	newIndex -= 120; // headUP
	--y;
	unsigned short xPos = newIndex % 120;
	unsigned short yPos = (newIndex - xPos) / 120 + 3;
	ShowPlayer2(xPos, yPos);
}

void GoDownStair(const unsigned short currentIndex, unsigned short& y, const string& activeMap)
{
	unsigned short newIndex = currentIndex;
	while (activeMap[newIndex + 240] == '#')
	{
		newIndex += 120;
		++y;
	}
	unsigned short xPos = newIndex % 120;
	unsigned short yPos = (newIndex - xPos) / 120 + 3;
	ShowPlayer2(xPos, yPos);
}

void ShowInteraction2(const string& diaName)
{
	UI_Color interColor;
	if (diaName == "map2Hint")
		interColor.SetColor(interColor.TEXT_COLOR_BLACK, interColor.BG_COLOR_WHITE);
	else
		interColor.SetColor(interColor.TEXT_COLOR_LIGHT_WHITE, interColor.BG_COLOR_BLUE);
	Console::ClearRect(5, 34, 110, 5);

	UI_Dialogue dialogue;
	string str;
	str = dialogue.GetDialogue(diaName);
	const string::iterator endIt = str.end();
	for (string::iterator iter = str.begin(); iter<endIt; ++iter)
	{
		cout << *iter;
		if (*iter == '\n')
		{
			Console::GotoXY(5, Console::GetY());
		}
	}
	if (diaName == "map2Hint")
		getch();
	else
		cin.ignore(100, '\n'); 
}

void ShowSeaMap(const string& activeMap)
{
	UI_Color mapColor;
	string::const_iterator endIT = activeMap.end();
	Console::GotoXY(0, 3);

	mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
	for (string::const_iterator it = activeMap.begin(); it<endIT; ++it)
	{
		switch (*it)
		{
		case '-':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_BLACK);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case ' ':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case '~':
			mapColor.SetColor(mapColor.TEXT_COLOR_WHITE, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case '\n':
			cout << *it;
			Console::GotoXY(0, Console::GetY());
			break;
		case '#':
			mapColor.SetColor(mapColor.TEXT_COLOR_BLACK, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case '}':
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_WHITE, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case '{':
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_WHITE, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case 'S':
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_WHITE, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		case 'b':
			mapColor.SetColor(mapColor.TEXT_COLOR_LIGHT_WHITE, mapColor.BG_COLOR_LIGHT_WHITE);
			cout << *it;
			mapColor.SetColor(mapColor.TEXT_COLOR_GOLD, mapColor.BG_COLOR_LIGHT_WHITE);
			break;
		default:
			cout << *it;
			break;
		}
	}
}

void ReDrawMap(const unsigned short& currentIndex, const unsigned short& leftX, const unsigned short& upY, const string& activeMap)
{
	Console::GotoXY(leftX, upY);
	for (unsigned int i = 0; i<3; ++i)
		cout << activeMap[currentIndex + i];
	Console::GotoXY(leftX, upY + 1);
	for (unsigned int i = 0; i<3; ++i)
		cout << activeMap[currentIndex + 120 + i];
}

void EraseBigObject(string& activeMap, unsigned short rightIndex, unsigned int width, unsigned int height)
{
	UI_Color whiteBG;
	whiteBG.SetColor(whiteBG.TEXT_COLOR_BLACK, whiteBG.BG_COLOR_LIGHT_WHITE);
	unsigned short baseIndex=rightIndex-120;
	unsigned short xCor = baseIndex % 120;
	unsigned short yCor = baseIndex / 120 + 3;
	for (unsigned int j = 0; j < height; ++j)
	{
		Console::GotoXY(xCor, yCor);
		for (unsigned int i = 0; i < width; ++i)
		{
			activeMap[baseIndex + i] = ' ';
			cout << ' ';
		}
		baseIndex += 120;
		++yCor;
	}
}

void BossDisplay(const string& displayFstream)
{
	if (displayFstream == "#S")
	{
		cout << endl << endl;
	}
	else if (displayFstream == "#E")
	{
		cout << endl << endl << "\t" << ">...........(Next)";
		cin.ignore(100, '\n');
		system("CLS");
	}
	else if (displayFstream == "@P")
	{
		cout << endl << endl << "\t" << ">";
		cin.ignore(100, '\n');
		cout << endl;
	}
	else if (displayFstream == "@N")
	{
		cout << endl << endl;
		Sleep(300);
	}
	else if (displayFstream != "")
	{
		cout << "\t";
		for (string::const_iterator iter = displayFstream.begin(); iter<displayFstream.end(); ++iter)
		{
			UI_Color color87;
			if (*iter == '/')
			{
				color87.SetColor(color87.TEXT_COLOR_YELLOW, color87.BG_COLOR_PINK);
			}
			else if (*iter == '*')
				color87.SetColor(color87.TEXT_COLOR_BLACK, color87.BG_COLOR_GOLD);
			else if (*iter == '&')
				color87.SetColor(color87.TEXT_COLOR_BLUE, color87.BG_COLOR_WHITE);
			else if (*iter == '|')
			{
				color87.SetColorStyle(color87.DEFAULT_COLOR_STYLE);
			}
			else
			{
				cout << *iter;
				Sleep(10);
			}
		}
	}
}

void ControlSection2(string& activeMap, unsigned short& x, unsigned short& y, Data_ChaMas& SIR87, Data_ChaMasDog& LITTLE87, Data_ChaMasSor& SORRY, bool& reload, int& mapState)
{
	// Coordinates on Map-Only Screen
	unsigned short xCor = x;
	unsigned short yCor = y - 3;
	ShowPlayer2(x, y);

	// Indexes in the Map String
	unsigned int currentIndex = 120 * yCor + xCor; // Current Index of the Upper-left Corner
	unsigned int upIndex = currentIndex - 120; // Index above currentIndex
	unsigned int downIndex = currentIndex + 240; // Index under the Lower-Left Corner
	unsigned int leftIndex = 3601;
	if (xCor)
		leftIndex = currentIndex - 1; // Left Index of player(upper)
	else
		leftIndex = 3601;
	unsigned int rightIndex = 3;
	if (xCor != 116)
		rightIndex = currentIndex + 3; // Right Index of player(upper)
	else
		rightIndex = 3601;



	UI_Color roadColor;
	roadColor.SetColor(roadColor.TEXT_COLOR_BLACK, roadColor.BG_COLOR_LIGHT_WHITE);
	Ctrl_UDLR key;
	Data_Random fight;

	switch (key.Ctrl_UDLR_Return())
	{
	case key.Up:
		if (activeMap[upIndex] == '#')
		{
			ReDrawMap(currentIndex, x, y, activeMap);
			GoUpStair(currentIndex, y, activeMap);
		}
		break;
	case key.Down:
		if (activeMap[downIndex] == '#')
		{
			ReDrawMap(currentIndex, x, y, activeMap);
			GoDownStair(currentIndex, y, activeMap);
		}
		break;
	case key.Left:
		if (activeMap[leftIndex] != '{' && leftIndex != 3601)
		{
			ReDrawMap(currentIndex, x, y, activeMap);
			--x;
		}
		break;
	case key.Right:
		if (rightIndex != 3601 && activeMap[rightIndex] != '}')
		{
			if (activeMap[rightIndex] == 'F')
			{
				// Fight!!!
				Console::ClearScreen(0, 0);
				unsigned short FightingRound = 0;
				int FightingExp = 0;
				int FightingMoney = 0;

				unsigned short WL = Main::Fighting(2, SIR87, LITTLE87, FightingRound, FightingExp, FightingMoney);
				if (WL == 0) //WIN
				{//UI_WIN
					Console::ClearScreen(0, 0);
					Main::Fighting_Result("YOU WIN! TWT", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
					if (SIR87.CheckLvUp() == 1)
					{
						SIR87.LvUp();
						int tmp = SIR87.GetExp() - (110 * SIR87.GetLv());
						SIR87.SetExp(tmp);
						LITTLE87.LvUp();
						if (sorryJoin)
							SORRY.LvUp();
					}
					UI_Color bgColor;
					unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
					bgColor.SetColorStyle(bgDefault);
					Console::ClearScreen(0, 0);
				}

				else //LOSE
				{//UI_LOSE
					Console::ClearScreen(0, 0);
					Main::Fighting_Result("YOU LOSE! T_T", FightingRound, SIR87.GetExp() - FightingExp, SIR87.GetExp(), SIR87.GetMoney() - FightingMoney, SIR87.GetMoney(), SIR87, sorryJoin);
					UI_Color bgColor;
					unsigned int bgDefault = bgColor.ProduceColorStyle(bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
					bgColor.SetColorStyle(bgDefault);
					Console::ClearScreen(0, 0);
				}
			}
			else if (activeMap[rightIndex] == 'S') // Meet Sorry
			{
				// Meet Sorry
				vector<string> mSorryKeys = { "meetSorryBegin", "meetSorry1", "meetSorry2", "meetSorry3", "meetSorry4", "meetSorry5",
					"meetSorry6",
					"meetSorry7",
					"meetSorry8",
					"meetSorry9",
					"meetSorry10",
					"meetSorry11",
					"meetSorry12",
					"meetSorry13",
					"meetSorry14",
					"meetSorryEnd" };
				ShowInteraction("meetSorryHint");
				for_each(mSorryKeys.begin(), mSorryKeys.end(), ShowInteraction2);
				EraseBigObject(activeMap, rightIndex, 6, 3);
				sorryJoin = true;
				ShowInteraction2("map2Hint");
			}
			else if (activeMap[rightIndex] == 'b')
			{
				// Boss 
				UI_Color bgColor;
				bgColor.SetColorStyle(bgColor.DEFAULT_COLOR_STYLE);
				Console::ClearScreen(0, 0);

				ifstream storyStream("storyBoss.txt");
				if (storyStream.fail())
				{
					cout << "Load Fail!" << endl;
				}
				string storyLine;
				while (getline(storyStream, storyLine))
				{
					BossDisplay(storyLine);
				}
				storyStream.close();

				// Fight!!!
				Console::FlareClear(bgColor.BG_COLOR_WHITE, bgColor.TEXT_COLOR_BLACK, bgColor.BG_COLOR_WHITE);
				unsigned short FightingRound = 0;
				int FightingExp = 0;
				int FightingMoney = 0;

				unsigned short WL = Main::Fighting(3, SIR87, LITTLE87, SORRY, FightingRound, FightingExp, FightingMoney);
				if (WL == 0) //WIN
				{
					Console::FlareClear(bgColor.BG_COLOR_GREEN, bgColor.TEXT_COLOR_LIGHT_WHITE, bgColor.BG_COLOR_BLACK);
					++mapState;
					bgColor.SetColorStyle(bgColor.DEFAULT_COLOR_STYLE);
					Console::ClearScreen(0, 0);

					ifstream storyStream("storyHE.txt");
					if (storyStream.fail())
					{
						cout << "Load Fail!" << endl;
					}
					string storyLine;
					while (getline(storyStream, storyLine))
					{
						BossDisplay(storyLine);
					}
					cin.ignore(1000, '\n');
					
					exit(EXIT_SUCCESS);
				}

				else //LOSE
				{//UI_LOSE
					Console::FlareClear(bgColor.BG_COLOR_RED, bgColor.TEXT_COLOR_LIGHT_WHITE, bgColor.BG_COLOR_BLACK);
					++mapState;
					bgColor.SetColorStyle(bgColor.DEFAULT_COLOR_STYLE);
					Console::ClearScreen(0, 0);

					ifstream storyStream("storyBD.txt");
					if (storyStream.fail())
					{
						cout << "Load Fail!" << endl;
					}
					string storyLine;
					while (getline(storyStream, storyLine))
					{
						BossDisplay(storyLine);
					}
					storyStream.close();
					Console::FlareClear(bgColor.BG_COLOR_RED, bgColor.TEXT_COLOR_PINK, bgColor.BG_COLOR_BLACK);
					ifstream bdStoryStream("bdPic.txt");
					if (bdStoryStream.fail())
					{
						cout << "Load Fail!" << endl;
					}
					Console::GotoXY(10, 3);
					while (getline(bdStoryStream, storyLine))
					{
						Console::GotoXY(10, Console::GetY());
						cout << storyLine << endl;
					}
					cin.ignore(1000, '\n');
					bdStoryStream.close();
					exit(EXIT_SUCCESS);
				}
			}
			else
			{
				ReDrawMap(currentIndex, x, y, activeMap);
				++x;
			}
		}
		else if (xCor == 116)
		{
			++mapState;
			reload = true;
			rightIndex = 3;
			return;
		}
		break;
	case key.Selected:
		break;
	default:
		break;
	}
}

#endif // MAP2

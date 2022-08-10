#include "Main_Fighting.h"

using namespace std;


Main_Fighting::Main_Fighting()
{

}

Main_Fighting::Main_Fighting(Data_ChaMas SIR87, int a) :roundEndYN(0), roundNumber(0)
{
	const int enemy_min = 2; //(1~4)
	const int enemy_MAX = 4; //(3~4)
	//meetEnemy when SIR87's Level >= (Level)
	const int meetCuteSnail = 1;
	const int meetCrazyDog = 3;
	const int meetNDHUBird = 6;
	const int meetCalculus = 8;
	//in map2 how many enemy
	const int SWBAmount = 1;



	//Create the enemyList
	//(string) enemyList <be used in MENU and showHP>
	//(Data_ChaEnemy) enemyType
	//case 1: in Map1
	//case 2: in Map2
	//case 3: Boss

	Data_ChaEnemy tmp;
	switch (a)
	{
	case 1:
	{
			  srand(time(NULL));
			  int amount = (rand() % enemy_MAX) + 1;//amount
			  if (amount<enemy_min) amount = enemy_min;

			  int SetEnemy;
			  if (SIR87.GetLv() >= meetCalculus)SetEnemy = 4;
			  else if (SIR87.GetLv() >= meetNDHUBird)SetEnemy = 3;
			  else if (SIR87.GetLv() >= meetCrazyDog)SetEnemy = 2;
			  else if (SIR87.GetLv() >= meetCuteSnail)SetEnemy = 1;

			  for (int i = 0; i<amount; i++)
			  {
				  int which = rand() % (SetEnemy);
				  switch (which)
				  {
				  case 0:
					  tmp.SetCuteSnail(rand() % 3 + 1);//Different Level
					  break;
				  case 1:
					  tmp.SetCrazyDog(rand() % 3 + 1);
					  break;
				  case 2:
					  tmp.SetNDHUBird(rand() % 3 + 1);
					  break;
				  case 3:
					  tmp.SetCalculus(rand() % 3 + 1);
					  break;
				  }
				  enemyType.push_back(tmp);
				  enemyList.push_back(tmp.GetType());
			  }

			  break;
	}


	case 2:
	{
			  for (int i = 0; i<SWBAmount; i++)//set amount of SmallWaveBreaker
			  {
				  tmp.SetSmallWaveBreaker();
				  enemyType.push_back(tmp);
				  enemyList.push_back(tmp.GetType());
			  }
			  break;
	}

	case 3:
	{
			  tmp.SetWaveBreaker();
			  enemyType.push_back(tmp);
			  enemyList.push_back(tmp.GetType());
			  break;
	}

	}
}

Main_Fighting::~Main_Fighting()
{

}

void Main_Fighting::ShowHP(int xHp, int yHp)
{
	for (unsigned int i = 0; i<enemyType.size(); ++i)
	{
		Console::GotoXY(xHp, yHp);

		float temp = (30 * enemyType[i].GetHp()) / enemyType[i].GetMaxHp();

		UI_Color lineC;
		lineC.SetColor(lineC.TEXT_COLOR_RED, lineC.BG_COLOR_WHITE);
		for (int i = 0; i < temp; i++)
		{
			std::cout << "*";
		}
		lineC.SetColor(lineC.TEXT_COLOR_BLACK, lineC.BG_COLOR_WHITE);

		Console::GotoXY(xHp + 32, yHp);


		std::cout << enemyType[i].GetHp() << "/" << enemyType[i].GetMaxHp();
		++yHp;
	}
}
void Main_Fighting::ShowEnemy(int xShowEne, int yShowEne)
{
	for (unsigned int i = 0; i<enemyType.size(); ++i)
	{
		Console::GotoXY(xShowEne, yShowEne);
		std::cout << enemyType[i].GetType();
		++yShowEne;
	}
}

void Main_Fighting::ShowMasHPMP(int xHp, int yHp, Data_ChaMas& masList)
{

	Console::GotoXY(xHp, yHp);
	std::cout << masList.GetChaName();
	Console::GotoXY(xHp, yHp + 1);
	std::cout << "Atk: " << masList.GetDamage();

	Console::GotoXY(xHp, yHp + 2);

	float temp = (20 * masList.GetHp()) / masList.GetMaxHp();

	UI_Color lineC;
	lineC.SetColor(lineC.TEXT_COLOR_RED, lineC.BG_COLOR_RED);
	for (int i = 0; i < temp; i++)
	{
		std::cout << "|";
	}
	lineC.SetColor(lineC.TEXT_COLOR_BLACK, lineC.BG_COLOR_WHITE);

	Console::GotoXY(xHp + 22, yHp + 2);
	std::cout << masList.GetHp() << "/" << masList.GetMaxHp() << "  ";


	Console::GotoXY(xHp, yHp + 3);
	float tempMP = (20 * masList.GetMp()) / masList.GetMaxMp();

	lineC.SetColor(lineC.TEXT_COLOR_LIGHT_BLUE, lineC.BG_COLOR_LIGHT_BLUE);
	for (int i = 0; i < tempMP; i++)
	{
		std::cout << "|";
	}
	lineC.SetColor(lineC.TEXT_COLOR_BLACK, lineC.BG_COLOR_WHITE);

	Console::GotoXY(xHp + 22, yHp + 3);
	std::cout << masList.GetMp() << "/" << masList.GetMaxMp();


}

void Main_Fighting::ShowMasHPMP(int xHp, int yHp, vector<Data_ChaMas>& masList)
{
	for (int i = 0; i<masList.size(); i++)
	{
		Console::GotoXY(xHp, yHp);
		std::cout << masList[i].GetChaName() << " Atk: " << masList[i].GetDamage() << "  ";
		std::cout << masList[i].GetHp() << "/" << masList[i].GetMaxHp() << "  ";
		std::cout << masList[i].GetMp() << "/" << masList[i].GetMaxMp();
	}

}

int Main_Fighting::CheckEnemies()
{
	int i = 0;
	int allDieYN = 0;
	while (enemyType[i].GetHp() <= 0)
	{
		if (i == enemyType.size() - 1)
		{
			allDieYN = 1;
			break;
		}
		++i;
	}
	if (allDieYN == 0)
		return 0; //Keep fighting
	else
		return 1; //Stop fighting
}

void Main_Fighting::FightingTurn(Data_ChaMas& mas, vector<string> skillList, vector<string> skillHint)
{
	/**************************************************************************************************************************************/
	////////////////////////////////////////////       UI(x,y)     /////////////////////////////////////////////////////////////////////////
	/**************************************************************************************************************************************/

	/* Enemy Area */
	unsigned short xShowEnemy = 8;
	unsigned short yShowEnemy = 2;
	unsigned short xHp = 28;
	unsigned short yHp = yShowEnemy;

	/* Master Area */
	unsigned short xShowTurn = 8;
	unsigned short yShowTurn = 7;

	unsigned short xControlMenu_1 = 8; //Main Menu
	unsigned short yControlMenu_1 = 10;
	unsigned short xControlMenu_2 = 28; //2nd Menu
	unsigned short yControlMenu_2 = yControlMenu_1;
	unsigned short xControlMenu_3 = 48; //3rd Menu
	unsigned short yControlMenu_3 = yControlMenu_1;

	/* Hint Area */
	unsigned short xHint_1 = 8;
	unsigned short yHint_1 = 8;
	unsigned short xHint_2 = 8;
	unsigned short yHint_2 = 15;



	/**************************************************************************************************************************************/
	////////////////////////////////////////////     MENU STRING     ///////////////////////////////////////////////////////////////////////
	/**************************************************************************************************************************************/


	unsigned short actionListClear = 10; /* ~= strlen(potionList) */
	unsigned short actionHintClear = 20; /* ~= strlen(potionHint) */
	vector<string> actionList = { "ATTACK", "SKILL", "POTION" };
	vector<string> actionHint = { "Attack", "Cast Skill", "Take the Potion" };

	unsigned short potionListClear = 20; /* ~= strlen(potionList) */
	unsigned short potionHintClear = 15; /* ~= strlen(potionHint) */
	vector<string> potionList = { "Basic HP Potion", "Super HP Potion", "Basic MP Potion", "Super MP Potion", "Attack Bonus Potion" };
	vector<string> potionHint = {
		"Recover 400 HP",
		"Recover 800 HP",
		"Recover 400 MP",
		"Recover 800 MP",
		"Atk * 1.5" };


	/******************************************
	* Member Variable:                       *
	*                                        *
	* int roundEndYN                         *
	* (if roundEndYN == 1, end of the round.)*
	* int roundNumber                        *
	* (if roundEnd, roundNumber++)           *
	******************************************/


	UI_Color turnColor;
	turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

	/******** Show Action Menu ********/


	Console::ClearRect(xShowTurn, yShowTurn, 50, 1);
	Console::GotoXY(xShowTurn, yShowTurn);
	std::cout << mas.GetChaName() << " turn.";

	UI_Menu actionMenu(true, actionList, xControlMenu_1, yControlMenu_1); //vert
	actionMenu.SetFilledColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

	unsigned int actionOption = actionMenu.MenuProcess(actionHint, xHint_1, yHint_1);
	turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);


	/******** Show Enemy ********/

	UI_Menu enemyMenu(true, GetEnemyList(), xShowEnemy, yShowEnemy);
	enemyMenu.SetFilledColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

	ShowEnemy(xShowEnemy, yShowEnemy);
	ShowHP(xHp, yHp);


	switch (actionOption)
	{

	case 0: /* Attack */
	{
				// Show Enemy Menu to choose which you want to attack
				enemyMenu.SetPositon(xControlMenu_2, yControlMenu_2);
				unsigned int target = enemyMenu.MenuProcess();
				turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

				if (enemyType[target].GetHp()>0)
				{
					enemyType[target].SetHp(enemyType[target].GetHp() - mas.GetDamage());
					if (enemyType[target].GetHp()<0)
					{
						enemyType[target].SetHp(0);
					}
					SetRoundEndYN(1);
				}

				// The enemy HP == 0
				else
				{
					enemyType[target].SetHp(0);
					SetRoundEndYN(0);
				}
				Console::ClearRect(xHp, yHp, 10, 4);
				ShowHP(xHp, yHp);
				Console::ClearRect(xControlMenu_2, yControlMenu_2, 50, 4);


				break;
	}
	case 1: /* Skill */
	{
				UI_Menu skillMenu(true, skillList, xControlMenu_2, yControlMenu_2); // vert
				skillMenu.SetFilledColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

				unsigned int skillOption = skillMenu.MenuProcess(skillHint, xHint_2, yHint_2);
				turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

				// call enemy list
				switch (skillOption)
				{
				case 0://Buff 1.5*Atk in following two rounds
				{
						   SetRoundEndYN(mas.UseSkillOne());
						   Console::ClearRect(28, 20, 50, 2);
						   break;
				}
				case 1://Attack an enemy with 1.5*Atk (call enemyType)
				{
						   enemyMenu.SetPositon(xControlMenu_3, yControlMenu_3);
						   unsigned int target = enemyMenu.MenuProcess();
						   turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

						   /**********************
						   CHECK ENEMY's hp <=0
						   **********************/
						   if (enemyType[target].GetHp()>0)
						   {
							   SetRoundEndYN(mas.UseSkillTwo(enemyType, target));
							   //enemyType[target].SetHp(enemyType[target].GetHp()-(SIR87.GetDamage())*1.5);
						   }

						   else
						   {
							   SetRoundEndYN(0);
						   }
						   break;
				}

				case 2://Attack all enemies with 1.2*Atk
				{
						   SetRoundEndYN(mas.UseSkillThr(enemyType, 0));
						   break;
				}
				default:
					break;

				}
				//enemyMenu.SetPositon(58, 10);
				//unsigned int target=enemyMenu.MenuProcess();
				Console::ClearRect(xHp, yHp, 10, 4);
				ShowHP(xHp, yHp);
				Console::ClearRect(28, 10, 80, 4);
				break;
	}
	case 2: /* Potion */
	{
				UI_Menu potionMenu(true, potionList, xControlMenu_2, yControlMenu_2); //vert
				potionMenu.SetFilledColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

				unsigned int potionOption = potionMenu.MenuProcess(potionHint, xHint_2, yHint_2);
				turnColor.SetColor(turnColor.TEXT_COLOR_BLACK, turnColor.BG_COLOR_WHITE);

				int a = mas.UsePotion(potionOption + 1);

				Console::ClearScreen;
				SetRoundEndYN(a);

				Console::ClearRect(28, 20, potionHintClear, 1);
				Console::ClearRect(xHp, yHp, 10, 4);
				ShowHP(xHp, yHp);

				Console::ClearRect(28, 10, potionListClear, potionList.size());


				break;


	}
	default:
		//Console::ClearRect(28, 10, 50, 4);
		break;
	}


}
vector<Data_ChaMas>& Main_Fighting::GetTeamList()
{
	return teamList;
}

vector<Data_ChaEnemy>& Main_Fighting::GetEnemyType()
{
	return enemyType;
}

vector<string>& Main_Fighting::GetEnemyList()
{
	return enemyList;
}

Data_ChaEnemy Main_Fighting::GetEnemyData(int a)
{
	return enemyType[a];
}

#ifndef MAIN_FIGHTING_H
#define MAIN_FIGHTING_H

#include "Data_ChaEnemy.h"
#include "Data_ChaMas.h"
#include "Data_ChaMasDog.h"
#include "Data_ChaMasSor.h"
#include "UI_Console_Global.h"
#include "UI_Color.h"
#include "UI_Menu.h"
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

class Main_Fighting
{
public:
    Main_Fighting();
    Main_Fighting(Data_ChaMas SIR87,int a);
    ~Main_Fighting();

    vector<Data_ChaEnemy>& GetEnemyType();
    vector<string>& GetEnemyList();
    vector<Data_ChaMas>& GetTeamList();
    Data_ChaEnemy GetEnemyData(int a);
    int GetRoundEndYN(){return roundEndYN;};
    int GetRoundNumber(){return roundNumber;};
    void SetRoundEndYN(int a){roundEndYN=a;};
    void SetRoundNumber(int a){roundNumber=a;};


    void FightingTurn(Data_ChaMas& mas,vector<string> skillList, vector<string> skillHint);
    void ShowHP(int xHp, int yHp);
    void ShowEnemy(int xShowEne, int yShowEne);
    void ShowMasHPMP(int xHp, int yHp, Data_ChaMas& masList);
    void ShowMasHPMP(int xHp, int yHp, vector<Data_ChaMas>& masList);
    int  CheckEnemies();
    vector<Data_ChaMas> teamList;

private:
    vector<Data_ChaEnemy> enemyType;
    vector<string> enemyList;
    int roundEndYN;
    int roundNumber;


};




#endif // MAIN_FIGHTING_H

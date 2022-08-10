#include "Data_Random.h"
#include<iostream>
#include <cstdlib>
#include <time.h>
Data_Random::Data_Random()
{
    probability=100;
    meet=34;
    seed=(unsigned)time(NULL);
    srand(seed);
}

Data_Random::~Data_Random()
{
    //dtor
}

int Data_Random::MeetEnemy()
{
     probability=rand()%100;
    if(probability<meet){
        return 1;
    }
    else
        return 0;
}

int Data_Random::Custom(int a)
{
    probability=rand()%a;
    return probability;
}

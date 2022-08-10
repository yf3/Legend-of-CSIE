#ifndef DATA_RANDOM_H
#define DATA_RANDOM_H


class Data_Random
{
    public:
        Data_Random();
        virtual ~Data_Random();
        int MeetEnemy();
        int Custom(int a);  //a用於設定種子需%多少  ex: if a==2, it will be rand()%2
                            //return值為餘數
        inline int GetProbability(){return probability;};
        inline void SetProbability(int a){probability=a;};
        inline void DebugUp(){meet+=2;}
        inline void DebugDown(){meet-=2;}
    protected:
    private:
       int probability;     //隨機值
       int meet;            //遇怪機率
       int seed;            //隨機之種子
};

#endif // DATA_RANDOM_H

#ifndef DATA_RANDOM_H
#define DATA_RANDOM_H


class Data_Random
{
    public:
        Data_Random();
        virtual ~Data_Random();
        int MeetEnemy();
        int Custom(int a);  //a�Ω�]�w�ؤl��%�h��  ex: if a==2, it will be rand()%2
                            //return�Ȭ��l��
        inline int GetProbability(){return probability;};
        inline void SetProbability(int a){probability=a;};
        inline void DebugUp(){meet+=2;}
        inline void DebugDown(){meet-=2;}
    protected:
    private:
       int probability;     //�H����
       int meet;            //�J�Ǿ��v
       int seed;            //�H�����ؤl
};

#endif // DATA_RANDOM_H

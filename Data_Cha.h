#ifndef DATA_CHA_H
#define DATA_CHA_H

class Data_Cha
{
public:
	Data_Cha();
	virtual ~Data_Cha();
	int GetHp(){return hp; };
	int GetMp(){ return mp; };
	int GetAtk(){ return atk ; };
	int GetMaxHp(){ return maxHp; };

	void SetHp(int a){ hp = a; };
	void SetMp(int a){ mp = a; };
	void SetAtk(int a){ atk = a; };
	virtual void SetMaxHp(int a){ maxHp = a; };
private:
	int maxHp;
	int hp;
	int mp;
	int atk;
};

#endif // DATA_CHA_H

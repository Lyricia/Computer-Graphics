#include "Hero.h"


Hero::Hero(char* _name, int _hp, int _mp, int _att)
{
	strcpy(name,_name);
	HP = _hp;
	MP = _mp;
	ATT = _att;
}


Hero::~Hero()
{
}

void Hero::Battle(Hero A, Hero B)
{
	while (A.HP > 0 && B.HP > 0)
	{
		cout << "A Attack" << endl;
		A.HP = A.HP - B.ATT;
		if (A.HP == 0 || A.HP < 0)
		{
			cout << "A Defeat" << endl;
			break;
		}
		else if (B.HP == 0 || B.HP < 0)
		{
			cout << "B Defeat" << endl;
			break;
		}

		cout << "B Attack" << endl;
		B.HP = B.HP - A.ATT;
		if (A.HP == 0 || A.HP < 0)
		{
			cout << "A Defeat" << endl;
			break;
		}
		else if (B.HP == 0 || B.HP < 0)
		{
			cout << "B Defeat" << endl;
			break;
		}

		cout << A.HP << endl;
		cout << B.HP << endl;

	}
}
#include"Hero.h"

/*
ü�� ���� ���� : ISDEAD �Լ�

-> �Լ��� ������ ���� boolean return �� �Ұ��

return (HP<=0); �� ����϶�

or

bool bDead = (hp<=0);

if(bDead)

*/


int main()
{

	Hero *Atype;
	Hero *Btype;

	char name1[10];
	char name2[10];
	int hp;
	int mp;
	int att;

	cout << "NAME : ";
	cin >> name1;
	cout << "HP : ";
	cin >> hp;
	cout << "MP : ";
	cin >> mp;
	cout << "ATT : ";
	cin >> att;

	Atype = new Hero(name1, hp, mp, att);

	cout << "Made A" << endl;

	cout << "NAME : ";
	cin >> name2;
	cout << "HP : ";
	cin >> hp;
	cout << "MP : ";
	cin >> mp;
	cout << "ATT : ";
	cin >> att;

	Btype = new Hero(name2, hp, mp, att);

	cout << "Made B" << endl;

	Atype->Battle(*Atype, *Btype);

	return 0;
}
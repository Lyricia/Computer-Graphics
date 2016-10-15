#include"Hero.h"

/*
체력 관련 물음 : ISDEAD 함수

-> 함수를 만들지 말고 boolean return 을 할경우

return (HP<=0); 을 사용하라

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
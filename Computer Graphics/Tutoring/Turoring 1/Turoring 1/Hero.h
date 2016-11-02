#pragma once
#include<iostream>
#pragma warning(disable :4996)


using namespace std;

class Hero
{
private:
	int HP;
	int MP;
	char name[10];
	int ATT;

public:
	Hero(char *_name, int _hp, int _mp, int _att);
	~Hero();
	void Battle(Hero A, Hero B);
};


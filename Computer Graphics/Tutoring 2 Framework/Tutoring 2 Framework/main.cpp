#include <iostream>
#include <Windows.h>

using namespace std;

class CFramework
{
private:
	int count{ 0 }; // ±’¿œ√ ±‚»≠
	
public: 
	void Draw();
	void Update();
	void Run();

};

namespace //namespace without name can use only in identified cpp file code (sim. static)
{
	CFramework framework;

}

int main()
{
	framework.Run();

	return 0;
}

void CFramework::Update()
{
	Sleep(1000);
}

void CFramework::Draw()
{
	
	system("cls");

	cout << "i m god        " <<count++<< endl;
}


void CFramework::Run()
{
	while (true)
	{
		Update();
		Draw();
	}
}

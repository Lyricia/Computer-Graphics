#include <iostream>
#include <ctime>
#include <gl\glut.h>
#include "GLFramework.h"

using namespace std;

namespace {
	CGLFramework framework;
};

int main(int argc, char* argv[]) 
{
	srand(unsigned(time(NULL)));

	// framework initialize
	framework.Initialize();

	// callback function set
	framework.SetReshapeFunc	([] (int w, int h) {framework.Reshape(w, h); });
	framework.SetDrawFunc		([] () {framework.drawScene(); });
	framework.SetTimerFunc		([] (int val) {framework.Timer(val); });
	framework.SetKeyInputFunc	([](unsigned char key, int x, int y) {framework.KeyInput(key, x, y); });
	framework.SetMouseInputFunc([](int button, int state, int x, int y) {framework.MouseInput(button, state, x, y); });

	// framework run
	framework.Run();

	return 0;
}

#pragma once
#include <iostream>
#include <ctime>
#include <gl\glut.h>

#define W_Width		800
#define W_Height	600
#define CAPTION		"Test"

template <typename Ty>
struct Point2D {
	Ty x, y;
};

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;


class CGLFramework
{
private:
	char			m_szTitle[64] = "";
	Point2i			m_Point_WindowPos	{100,100};
	Point2i			m_Point_WindowSize	{100,100};
	int				m_ulFPS = 16;
	int				counter;

public:
	CGLFramework() = default;
	~CGLFramework() = default;

public:
	GLvoid Init();
	GLvoid Reshape(int w, int h);
	GLvoid drawScene(GLvoid);
	GLvoid Timer(int val);

	GLvoid Run();
	
};


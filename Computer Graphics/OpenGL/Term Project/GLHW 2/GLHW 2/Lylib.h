#pragma once

/*////////////////////////////////////////

generally used in every gl projects.

//////////////////////////////////////////*/

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <ctime>

#include "Vector3D.h"
#include "Spline.h"


#define W_Width		800
#define W_Height	800
#define W_Depth		1000
#define PI			3.141592f

#define RAD(x)		x * PI * 0.005555f
#define DEGREE(x)	x * 57.2958f

float projectionmatrix[16] = {
	1,0,0,0,
	0,0,1,0,
	0,-1,0,0,
	0,0,0,1
};

bool boolswitch(bool chker)
{
	if (chker == true)			return false;
	else if (chker == false)	return true;
	return false;
}
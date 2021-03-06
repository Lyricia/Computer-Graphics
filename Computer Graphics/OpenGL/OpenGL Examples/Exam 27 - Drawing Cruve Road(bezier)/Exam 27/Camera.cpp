#include <cmath>
#include <iostream>
#include "Camera.h"
#include "gl/glut.h"


#define PI			3.14159265359
#define RAD(x)		x * (PI / 180)

CCamera::CCamera()
{
	dist = -300;
}
CCamera::~CCamera()
{}

void CCamera::SetCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, 1.0, 1.0, 10000);
	glTranslatef(0.0, 0.0, dist);
	gluLookAt(
		m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z,
		m_CameraPosition.x + m_LookVector.x, m_CameraPosition.y + m_LookVector.y, m_CameraPosition.z + m_LookVector.z,
		0, 1, 0);
//	gluLookAt(
//		0, 0, 0,
//		m_LookVector.x, m_LookVector.y, m_LookVector.z, 
//		0, 1, 0);
}

/*////////////// Set Camera Look Vector //////////////////
default camera look vector is (0,0,1)
default camera position is Origin (0,0,0)
mouse movement comes to x, y

camera movement pipeline
delta X is mouse horizontal movement value difference to default camera look vector (0,0,1), now call this v_look1
delta Y is mouse vertical movement value difference to vector applied delta X vector, now call this v_look2
after apply all, normalize look vector and reset mousecursor position to center of window

camera look vector is a point on the shpere around CameraVector coordinate
theta is angle after apply x-z movement vector(v_look1)(yaw angle)
alpha is angle after apply z-y movement vector(v_look2)(pitch angle), vertical angle after apply ypos(pitch angle)

angle theta = arccos ( 1 (radius of lookvector coordinate sphere) / delta x (mouse x movement) )
angle alpha = arctan (size of hypotenuse of x-z triangle / delta y (mouse y movement) )
 *alpha CANNOT reach to 90 deg. (tan 90 is infinite)
////////////////////////////////////////////////////////*/

void CCamera::SetLookVector()
{
	float delta_x;
	float delta_y;
	const float ROTATE_SPEED =0.5;

	delta_x = 400 - newMousePostion_x;
	delta_y = 300 - newMousePostion_y;
	//std::cout << delta_x << ' ' << delta_y << std::endl;


	if (delta_x > 0.0f)
 		Angle.yaw += ROTATE_SPEED;
	else if (delta_x < 0.0f)
		Angle.yaw -= ROTATE_SPEED;

	if (delta_y > 0.0f)
		Angle.pitch += ROTATE_SPEED;
	else if (delta_y < 0.0f)
		Angle.pitch -= ROTATE_SPEED;

	if (Angle.pitch > 80.0f)	Angle.pitch = 80.0f; 
	if (Angle.pitch <  -80.0f)	Angle.pitch = -80.0f;

	m_LookVector = { cosf(RAD(Angle.yaw)), tanf(RAD(Angle.pitch)), sinf(RAD(Angle.yaw)) };
//	m_LookVector = { 1.0f, tanf(RAD(Angle.pitch)), 1.0f };
	std::cout << Angle.pitch << std::endl;
	m_LookVector.Normalize();

	oldMousePostion_x = newMousePostion_x;
	oldMousePostion_y = newMousePostion_y;
}


void CCamera::getMouse(int x, int y)
{
	newMousePostion_x = x;
	newMousePostion_y = y;
	std::cout << x << ' ' << y << std::endl; 
}

void CCamera::Move(DIRECTION dir, float speed)
{
	switch (dir)
	{
	case DIRECTION::FRONT:
		dist += speed;
		break;
	case DIRECTION::BACK:
		dist -= speed;
		break;
	case DIRECTION::LEFT:
		break;
	case DIRECTION::RIGHT:
		break;
	}
}



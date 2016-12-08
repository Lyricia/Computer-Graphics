#include <cmath>
#include <iostream>
#include "Camera.h"
#include "gl/glut.h"

#define PI			3.14159265359
#define RAD(x)		x * (PI / 180)
#define DEG(x)		x * (180 / PI)

CCamera::CCamera()
{
	m_dist = 0;
	Position.z = 100;
	Angle.yaw = 90;
	Angle.pitch = 0;
}
CCamera::~CCamera()
{}

void CCamera::SetCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_POV, 1.0, 0.01, 10000);
	glTranslatef(0.0, 0.0, m_dist);
	gluLookAt(
		Position.x , Position.y, Position.z,
		Position.x + m_LookVector.x, Position.y + m_LookVector.y, Position.z + m_LookVector.z,
		0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	//std::cout << Position.x << " " << Position.y << " " << Position.z << std::endl;
}

void CCamera::SetCameraPosition(float x, float y, float z)
{
	Position = { x, y, z };
}

void CCamera::SetCameraPosition(Vec3f _positioninput)
{
	Position = _positioninput;
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
	const float YAW_ROTATE_SPEED = 1.5;
	const float PITCH_ROTATE_SPEED = 1.5;

	delta_x = 400 - newMousePostion_x;
	delta_y = 400 - newMousePostion_y;
	//std::cout << delta_x << ' ' << delta_y << std::endl;

	if (delta_x > 0.0f)
 		Angle.yaw -= YAW_ROTATE_SPEED;
	else if (delta_x < 0.0f)
		Angle.yaw += YAW_ROTATE_SPEED;

	if (delta_y > 1.0f)
		Angle.pitch += PITCH_ROTATE_SPEED;
	else if (delta_y < -1.0f)
		Angle.pitch -= PITCH_ROTATE_SPEED;

	if (Angle.pitch > 80.0f)	Angle.pitch = 80.0f; 
	if (Angle.pitch <  -80.0f)	Angle.pitch = -80.0f;

	m_LookVector = { cosf(RAD(Angle.yaw)), tanf(RAD(Angle.pitch)), sinf(RAD(Angle.yaw)) };

	m_LookVector = Normalize(m_LookVector);
}

void CCamera::SetLookVector(Vec3f _look_vector)
{
	m_LookVector = _look_vector;
	m_LookVector = Normalize(m_LookVector);
}

void CCamera::SetViewpoint(int _dist)	// Set Camera Distance on Z-axis (use (-)value)
{
	m_dist = _dist;
}

void CCamera::getMouse(int x, int y)
{
	newMousePostion_x = x;
	newMousePostion_y = y;
	//std::cout << x << ' ' << y << std::endl; 
}

/*////////////////////////////////////////////////////////////

Movements goes forward, backward along camera lookvector. 
Left, right movements goes along perpendicular vector of lookvector.

/////////////////////////////////////////////////////////////*/

void CCamera::Move(DIRECTION dir, float speed)
{
	Vec3f MoveLR = Normalize(Vec3f({ m_LookVector.z, 0, m_LookVector.x }));
	switch (dir)
	{
	case DIRECTION::FRONT:
		Position = Position + (m_LookVector * speed);
		break;
	case DIRECTION::BACK:
		Position = Position - (m_LookVector * speed);
		break;
	case DIRECTION::LEFT:
		Position.x = Position.x + (MoveLR.x * speed);
		Position.z = Position.z - (MoveLR.z * speed);
		break;
	case DIRECTION::RIGHT:
		Position.x = Position.x - (MoveLR.x * speed);
		Position.z = Position.z + (MoveLR.z * speed);
		break;
	}
}



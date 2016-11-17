#include <cmath>
#include "Camera.h"
#include "gl/glut.h"


CCamera::CCamera()
{}
CCamera::~CCamera()
{}

void CCamera::SetCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, 1.0, 1.0, 10000);
	glTranslatef(0.0, 0.0, -300);
	gluLookAt(
		m_CameraVector.x, m_CameraVector.y, m_CameraVector.z,
		m_LookVector.x, m_LookVector.y, m_LookVector.z,
		0, 1, 0);
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

void CCamera::SetLookVector(int x, int y)
{
	float delta_x = m_CameraVector.x - x;
	float delta_y = m_CameraVector.y - y;
	float hypo_zx;
	float theta;
	float alpha;
	Vec3f Move;

	m_CameraVector.x += x;
	//m_CameraVector.y += y;

	hypo_zx = sqrtf((delta_x * delta_x) + 1);

	theta = acos(delta_x / hypo_zx);
	alpha = atan2f(delta_y, hypo_zx);

	Move.x = cosf(theta);
	Move.y = tanf(alpha);
	Move.z = sinf(theta);
}
#include <cmath>
#include "Camera.h"
#include "gl/glut.h"


CCamera::CCamera()
{}
CCamera::~CCamera()
{}

void CCamera::SetCamera()
{
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
delta X is mouse horizontal movement value differnce between default camera look vector (0,0,1), now call this v_look1
delta Y is mouse vertical movement value differnce between vector applied delta X vector, now call this v_look2
after apply all, reset mousecursor position to center of window

camera look vector is a point on the shpere around cameraVector coordinate
theta is angle after apply x-z movement vector(v_look1)(yaw angle)
alpha is angle after apply z-y movement vector(v_look2)(pitch angle), vertical angle after apply ypos(pitch angle)
angle theta = arccos ( 1 (radius of lookvector coordinate sphere) / delta x (mouse x movement) )
angle alpha = arctan (size of hypotenuse of x-z triangle / delta y (mouse y movement) )
* alpha CANNOT reach to 90 deg. (can be 

////////////////////////////////////////////////////////*/

void CCamera::SetLookVector(int x, int y)
{
	acosf()
}

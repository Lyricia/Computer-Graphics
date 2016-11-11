#include "Ball.h"

CBall::CBall()
{
}

CBall::~CBall()
{
}

void CBall::Render(float scale)
{
	glPushMatrix();
	{
		angle.Rotate();
		Vertex.color.applycolor();
		glutWireSphere(scale, 10, 10);
	}
	glPopMatrix();
}


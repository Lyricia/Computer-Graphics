#include "Box.h"

CBox::CBox()
{
	m_MoveVector = GravityVector;
}

CBox::~CBox()
{
}

void CBox::Render()
{
	glPushMatrix();
	{
		glTranslatef(Position.x, Position.y, Position.z);
		Rotate();
		glutSolidCube(15);
	}
	glPopMatrix();
}


void CBox::Rotate()
{
	glRotatef(-m_angle, 0, 0, 1);
}

void CBox::SetAngle(float speed)
{
	m_angle += speed;
}

void CBox::SetPosition(float y)
{
	Position.y = y;
}

float CBox::GetPosition()
{
	return Position.x;
}

void CBox::Move(float speed, Vec3f externalVector, float ypos)
{
	Position = Position + GravityVector;
	Position = Position + externalVector;
}

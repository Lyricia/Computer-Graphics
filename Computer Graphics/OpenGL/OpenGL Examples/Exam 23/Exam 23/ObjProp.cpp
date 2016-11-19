#include "ObjProp.h"

ObjProp::ObjProp()
{
}


ObjProp::~ObjProp()
{
}

void ObjProp::initBB()
{
	BoundingBox[BBPOS::LEFTTOP].x = Vertex.x - m_scale;
	BoundingBox[BBPOS::LEFTTOP].z = Vertex.z + m_scale;

	BoundingBox[BBPOS::RIGHTTOP].x = Vertex.x + m_scale;
	BoundingBox[BBPOS::RIGHTTOP].z = Vertex.z + m_scale;

	BoundingBox[BBPOS::RIGHTBOTTOM].x = Vertex.x + m_scale;
	BoundingBox[BBPOS::RIGHTBOTTOM].z = Vertex.z - m_scale;

	BoundingBox[BBPOS::LEFTBOTTOM].x = Vertex.x - m_scale;
	BoundingBox[BBPOS::LEFTBOTTOM].z = Vertex.z - m_scale;
}

void ObjProp::DrawBB()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 0);
	for (int i = 0; i < 4; i++) {
		glVertex3f(BoundingBox[i].x, BoundingBox[i].y, BoundingBox[i].z);
	}
	glEnd();
}

CVertex* ObjProp::GetBB()
{
	return BoundingBox;
}



bool ObjProp::isCollide(CVertex *P)
{
	float p_left	= BoundingBox[BBPOS::LEFTTOP].x;
	float p_right	= BoundingBox[BBPOS::RIGHTBOTTOM].x;
	float p_top		= BoundingBox[BBPOS::LEFTTOP].z;
	float p_bottom	= BoundingBox[BBPOS::RIGHTBOTTOM].z;

	float q_left	= P[BBPOS::LEFTTOP].x;
	float q_right	= P[BBPOS::RIGHTBOTTOM].x;
	float q_top		= P[BBPOS::LEFTTOP].z;
	float q_bottom	= P[BBPOS::RIGHTBOTTOM].z;

	if (p_left > q_right)	return false;
	if (p_right < q_left)	return false;
	if (p_top < q_bottom)	return false;
	if (p_bottom > q_top)	return false;

	return true;
}
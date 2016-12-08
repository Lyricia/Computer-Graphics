#include "stdafx.h"

#include "Camera.h"



CCamera::CCamera()
{
	m_ptDelta.x = 90.0f;
}


CCamera::~CCamera()
{
}

Vec3f CCamera::GetLookVector() const
{
	return 	Normalize(Vec3f{ 
		cos(DegreeToRadian(m_ptDelta.x)), 
		tan(DegreeToRadian(m_ptDelta.y)), 
		sin(DegreeToRadian(m_ptDelta.x)) 
	});
}

void CCamera::LookAt()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.f, m_faspect, 1.f, 1000.f);
	auto eye = m_ptPos + GetLookVector() * m_fZoom;
	gluLookAt(
		eye.x, eye.y, eye.z
		, m_ptPos.x, m_ptPos.x, m_ptPos.z
		, 0, 1, 0
	);
	glMatrixMode(GL_MODELVIEW);
}

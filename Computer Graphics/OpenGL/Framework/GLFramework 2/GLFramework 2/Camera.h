#pragma once
class CCamera
{
private:
	Vec3f m_ptPos;
	float m_fZoom = 1.f;
	Point2f m_ptDelta;
	float m_faspect = 1.f;

public:
	CCamera();
	~CCamera();

	void SetAspect(const float aspect) { m_faspect = aspect; LookAt();}
	void Move(const Vec3f& pt) { m_ptPos += pt; LookAt(); }
	void SetPos(const Vec3f& pt) { m_ptPos = pt; LookAt(); }
	const Vec3f& GetPos() const { return m_ptPos; }

	void Rotate(const float x, const float y) { m_ptDelta.x = x; m_ptDelta.y = y; LookAt();	}
	void SetDelta(const float x, const float y) { m_ptDelta.x = x; m_ptDelta.y = y; LookAt(); }

	Vec3f GetLookVector() const;
	void LookAt();

	void Zoom(const bool In, float length = 0.1f) { m_fZoom += (In ? -1 : 1) * length; LookAt(); }
};


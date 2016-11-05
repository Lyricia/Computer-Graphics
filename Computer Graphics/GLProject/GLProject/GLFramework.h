#pragma once

template<typename Ty>
struct Point2D {
	Ty x, y;
};

class CScene;

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;

class CGLFramework
{
private:
	
	char	m_szTile[64]	= "Tutering Sample_2016_2";
	Point2i m_ptWindowPos	{ 100,100 };
	Point2i m_ptWindowSize	{ 800,600 };
	int		m_iFPS			= 16;

	void	(*m_pfReshape)(int w, int h)						 { nullptr } ;
	void	(*m_pfDrawScene)()									 { nullptr } ;
	void	(*m_pfTimer)(int val)								 { nullptr } ;
	void	(*m_pfKeyInput)(unsigned char key, int x, int y)	 { nullptr } ;

	CScene* m_pCurrentScene;

public:

	CGLFramework() = default;
	~CGLFramework() = default;
	
public:

	GLvoid Initialize(GLvoid);

	GLvoid Reshape(int w, int h);
	GLvoid drawScene(GLvoid);
	GLvoid Timer(int val);
	GLvoid KeyInput(unsigned char key, int x, int y);
	GLvoid MouseInput(int button, int state, int x, int y);
	
	GLvoid Run();

	void SetReshapeFunc	(void(*func)(int, int))		{ m_pfReshape = func; }
	void SetDrawFunc	(void(*func)())				{ m_pfDrawScene = func; }
	void SetTimerFunc	(void(*func)(int))			{ m_pfTimer = func; }
	void SetKeyInputFunc(void(*func)(unsigned char, int, int)) { m_pfKeyInput = func; }
	
};


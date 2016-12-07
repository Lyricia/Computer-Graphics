#include "Lylib.h"

#include "Camera.h"

GLvoid RegesterCallBack();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid Timer(int);
GLvoid Keydown(unsigned char, int, int);
GLvoid MouseMove(int, int);
GLvoid MouseEvent(int, int, int, int);
GLvoid init(GLvoid);

GLvoid DrawLines();
GLvoid DrawSpace();
void DrawRail();
void DrawTrain();
void DrawTunnel();
void DrawTree();
void EnLighten();
void ChangeView();

void camerawalk();

void InitBlizzard();
void FallingBlizzard();
void RenderBlizzard();

void RenderShots();
void MoveShots();


CCamera Camera;

float camdist;
float ambiantlevel1 = 0.3f;
float diffuselevel1 = 0.6f;
float specularlevel1 = 0.8f;

bool light1on;
bool IsPerspective = false;
bool IsTrainRunning = false;
bool IsFPSView = true;
bool IsFlatConnected = false;
bool IsRailCompleted = false;
bool IsWeatherSnow = false;
bool IsMouseLock = true;

Vec3f CurveCtrlPt[50];
int pointcounter;
float RailHeight;

Vec3f CurrentPosition;
Vec3f PrevPosition;
Vec3f NextPosition;

Vec3f Treepos[10];

CCrane Train;

Vec3f snowposition[500];
float snowspeed[500];

Vec3f shotspos[100];
Vec3f shotsdir[100];
int shotcounter;

float innercounter;
int outercounter;

void main(int, char *)
{
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_Width, W_Height);
	glutCreateWindow("Test");

	RegesterCallBack();

	glutMainLoop();
}

GLvoid init(GLvoid)
{
	srand(unsigned(time(NULL)));
	camdist = -400;

	ambiantlevel1 = 0.3f;
	diffuselevel1 = 0.6f;
	specularlevel1 = 0.8f;

	memset(CurveCtrlPt, 0, 50);
	memset(shotspos, 0, 100);
	memset(shotsdir, 0, 100);
	memset(Treepos, 0, 10);

	pointcounter = 0;
	shotcounter = 0;
	light1on = true;
	IsPerspective = false;
	IsTrainRunning = false;
	IsFPSView = true;
	IsFlatConnected = false;
	IsRailCompleted = false;
	IsWeatherSnow = false;
	IsMouseLock = true;

	innercounter = 0;
	outercounter = 0;

	for (int i = 0; i < 10; i++)
	{
		Treepos[i] = { -800.f + rand() % 1600, 0.f, -800.f + rand() % 1600 };
		if (Length(Treepos[i]) < 150) {
			while (Length(Treepos[i]) < 150) {
				Treepos[i] = { -800.f + rand() % 1600, 0.f, -800.f + rand() % 1600 };
			}
		}
	}

	InitBlizzard();
	Camera.SetCameraPosition(0, 400, -800);
}

GLvoid RegesterCallBack()
{
	glutMouseFunc(MouseEvent);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keydown);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, Timer, 1);
}

void EnLighten()
{
	auto lightvec = NextPosition - CurrentPosition;
	glEnable(GL_NORMALIZE);

	GLfloat mat_AmbientLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat mat_SpecularLight1[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat mat_DiffuseLight1[] = { 1.f, 1.f, 1.f, 1.0f };

	GLfloat AmbientLight1[] = { ambiantlevel1, ambiantlevel1, ambiantlevel1, 1.0f };
	GLfloat SpecularLight1[] = { specularlevel1, specularlevel1, specularlevel1, 1.0f };
	GLfloat DiffuseLight1[] = { diffuselevel1, diffuselevel1, diffuselevel1, 1.0f };
	GLfloat spotlightDirection[] = { lightvec.x, lightvec.y, lightvec.z };

	GLfloat light1_position[] = { 0, 600, 0 };

	GLfloat mat_shininess[] = { 8 };
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_AmbientLight1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_DiffuseLight1);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_SpecularLight1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 0.1f);                  // 80도 원뿔
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);                 // 초점 설정
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);

	glEnable(GL_LIGHTING);

	if (light1on)		glEnable(GL_LIGHT0);
	else				glDisable(GL_LIGHT0);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	ChangeView();

	glPushMatrix();
	EnLighten();
	DrawSpace();
	glPopMatrix();

	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		{
			glTranslatef(Treepos[i].x, 0, Treepos[i].z);
			DrawTree();
		}
		glPopMatrix();
	}
	
	if (IsPerspective && IsWeatherSnow) {
		glColor3f(1, 1, 1);
		RenderBlizzard();
	}

	if (pointcounter > 1)
	{
		DrawRail();

		if (IsTrainRunning) {
			RenderShots();
			DrawTrain();
		}

		DrawTunnel();
	}

	glutSwapBuffers();
}

void DrawTrain()
{
	glPushMatrix();
	{
		glColor3f(1, 1, 0);
		glTranslatef(NextPosition.x, NextPosition.y, NextPosition.z);
		glutSolidSphere(10, 50, 50);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1, 0, 0);
		glTranslatef(CurrentPosition.x, CurrentPosition.y, CurrentPosition.z);
		glRotatef(-DEGREE(atan2f((NextPosition.z - CurrentPosition.z), (NextPosition.x - CurrentPosition.x))), 0, 1, 0);
		glScalef(0.5f, 0.1f, 0.1f);
		Train.Render();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1, 0, 0);
		glTranslatef(PrevPosition.x, PrevPosition.y, PrevPosition.z);
		glRotatef(-DEGREE(atan2f((CurrentPosition.z - PrevPosition.z), (CurrentPosition.x - PrevPosition.x))), 0, 1, 0);
		glScalef(0.5f, 0.1f, 0.1f);
		Train.Render();
	}
	glPopMatrix();
}

void DrawTunnel()
{
	glPushMatrix();
	{
		for (float f = 0.3f; f < 0.8f; f += 0.01)
		{
			glPushMatrix();
			{
				auto current = CCardinalSpline::CalcCardinal(f, 0.1f, CurveCtrlPt[0], CurveCtrlPt[1], CurveCtrlPt[0], CurveCtrlPt[1]);
				float t = f - 0.05f;
				auto prev = CCardinalSpline::CalcCardinal(t, 0.1f, CurveCtrlPt[0], CurveCtrlPt[1], CurveCtrlPt[0], CurveCtrlPt[1]);
				glTranslatef(current.x, current.y, current.z);
				glRotatef(90, 0, 1, 0);
				glRotatef(-DEGREE(atan2f((current.z - prev.z), (current.x - prev.x))), 0, 1, 0);
				glutWireTorus(15, 80, 50, 50);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void DrawTree()
{
	glPushMatrix();
	{
		glColor3f(0, 1, 0);
		glTranslatef(0, 15, 0);
		glScalef(1, 2, 1);
		glutSolidCube(30);
		glTranslatef(0, 15, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(50, 50, 4, 4);
		glTranslatef(0, 0, 20);
		glScalef(0.8, 0.8, 0.8);
		glutSolidCone(50, 50, 4, 4);
	}
	glPopMatrix();
}

void DrawRail()
{
	glPushMatrix();
	{
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < pointcounter - 3; i++)
		{
			if (i == 0) {
				for (float f = 0.0f; f < 1.05f; f += 0.05)
				{
					glVertex3fv(CCardinalSpline::CalcCardinal(
						f, 0.1f,
						CurveCtrlPt[0],
						CurveCtrlPt[1],
						CurveCtrlPt[0],
						CurveCtrlPt[1]
					).arr);
				}
			}

			for (float f = 0.0f; f < 1.05f; f += 0.05)
			{
				glVertex3fv(CCardinalSpline::CalcCardinal(
					f, 0.1f,
					CurveCtrlPt[i],
					CurveCtrlPt[i + 1],
					CurveCtrlPt[i + 2],
					CurveCtrlPt[i + 3]
				).arr);
			}
		}
		glEnd();

		glPointSize(20);
		if(IsFlatConnected)
			glColor3f(1, 1, 0);
		else
			glColor3f(1, 0, 1);
		glBegin(GL_POINTS);
		{
			for (int i = 0; i < pointcounter; i++)
			{
				if (i == 0)
				{
					if (IsFlatConnected)
						glColor3f(1, 1, 0);
					else
						glColor3f(0, 0, 0);
					for (float f = 0.0f; f < 1.05f; f += 0.05)
					{
						glVertex3fv(CCardinalSpline::CalcCardinal(
							f, 0.1f,
							CurveCtrlPt[0],
							CurveCtrlPt[1],
							CurveCtrlPt[0],
							CurveCtrlPt[1]
						).arr);
					}
				}
				if (IsRailCompleted)
				{
					if (i < pointcounter - 3)
					{
						glColor3f(1, 0, 1);
						for (float f = 0.0f; f < 1.05f; f += 0.05)
						{
							glVertex3fv(CCardinalSpline::CalcCardinal(
								f, 0.1f,
								CurveCtrlPt[i],
								CurveCtrlPt[i + 1],
								CurveCtrlPt[i + 2],
								CurveCtrlPt[i + 3]
							).arr);
						}
					}
				}
				
				else if (!IsRailCompleted && i < pointcounter - 2)
				{
					glColor3f(1, 0, 1);
					for (float f = 0.0f; f < 1.05f; f += 0.05)
					{
						glVertex3fv(CCardinalSpline::CalcCardinal(
							f, 0.1f,
							CurveCtrlPt[i],
							CurveCtrlPt[i + 1],
							CurveCtrlPt[i + 2],
							CurveCtrlPt[i + 3]
						).arr);
					}
				}
				glVertex3fv(CurveCtrlPt[i].arr);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

GLvoid DrawLines()
{
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	glVertex3f(-W_Width, 0.0, 0.0);
	glVertex3f(W_Width, 0.0, 0.0);

	glVertex3f(0.0, -W_Height, 0.0);
	glVertex3f(0.0, W_Height, 0.0);

	glVertex3f(0.0, 0.0, -W_Depth);
	glVertex3f(0.0, 0.0, W_Depth);
	glEnd();
}

GLvoid DrawSpace()
{
	glPushMatrix();
	{
		glScalef(200, 1, 200);
		glPushMatrix();
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_NORMALIZE);

			GLfloat ctrlpoints[3][3][3] = {
				{ { -4.0f, -10.0f, +4.0f },		{ 0.0f, -10.0f, +4.0f },	{ 4.0f, -10.0f, +4.0f } },
				{ { -4.0f, -10.0f, +0.0f },		{ 0.0f, -10.0f, +0.0f },	{ 4.0f, -10.0f, +0.0f } },
				{ { -4.0f, -10.0f, -4.0f },		{ 0.0f, -10.0f, -4.0f },	{ 4.0f, -10.0f, -4.0f } }
			};

			glMap2f(GL_MAP2_VERTEX_3,
				0.0, 1.0, 3, 3,
				0.0, 1.0, 9, 3,
				&ctrlpoints[0][0][0]);

			glEnable(GL_MAP2_VERTEX_3);
			glNormal3f(0, 1, 0);
			glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
			glEvalMesh2(GL_FILL, 0, 50, 0, 50);
			glDisable(GL_MAP2_VERTEX_3);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -500);

	gluLookAt(
		0.0, 1, 0,			// eye
		0.0, 0, 1,			// center
		0.0, 1.0, 0.0);			// up
}

GLvoid Keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break; 

	case 'i':
		system("cls");
		std::cout << "Restarted" << std::endl;
		init();
		break;
		
	case '`':
		IsPerspective = boolswitch(IsPerspective);
		if(IsPerspective)
			std::cout << "Current View Type is Perspective" << std::endl;
		else if (!IsPerspective)
			std::cout << "Current View Type is Orthogonal" << std::endl;
		break;

	case '1':
		light1on = boolswitch(light1on);
		break;
	
	case 'w':
		if (IsPerspective)		Camera.Move(DIRECTION::FRONT, 10);
		break;
	case 's':
		if (IsPerspective)		Camera.Move(DIRECTION::BACK, 10);
		break;
	case 'a':
		if (IsPerspective)		Camera.Move(DIRECTION::LEFT, 10);
		break;
	case 'd':
		if (IsPerspective)		Camera.Move(DIRECTION::RIGHT, 10);
		break;

	case 'j':
		if(IsRailCompleted)
			IsTrainRunning = boolswitch(IsTrainRunning);
		break;

	case 'p':
		IsFPSView = boolswitch(IsFPSView);
		if (IsFPSView) { Camera.SetViewpoint(0); std::cout << "Current View Type is FPS" << std::endl; }
		else if (!IsFPSView) { Camera.SetViewpoint(-100); std::cout << "Current View Type is TPS" << std::endl; }
		
		break;

	case 'z':
		ambiantlevel1 += 0.1;
		std::cout << "Current Ambiant Level is " << ambiantlevel1 << std::endl;
		break;
	case 'Z':
		ambiantlevel1 -= 0.1;
		std::cout << "Current Ambiant Level is " << ambiantlevel1 << std::endl;
		break;
	case 'x':
		diffuselevel1 += 0.1;
		std::cout << "Current Diffuse Level is " << diffuselevel1 << std::endl;
		break;
	case 'X':
		diffuselevel1 -= 0.1;
		std::cout << "Current Diffuse Level is " << diffuselevel1 << std::endl;
		break;
	case 'c':
		specularlevel1 += 0.1;
		std::cout << "Current Specular Level is " << specularlevel1 << std::endl;
		break;
	case 'C':
		specularlevel1 -= 0.1;
		std::cout << "Current Specular Level is " << specularlevel1 << std::endl;
		break;

	case 'e':
		if (IsTrainRunning) {
			shotspos[shotcounter] = NextPosition;
			shotsdir[shotcounter] = NextPosition - CurrentPosition;
			shotcounter++;
			if (shotcounter > 100)
				shotcounter = 0;
		}
		break;

	case 'v':
		IsWeatherSnow = boolswitch(IsWeatherSnow);
		InitBlizzard();
		break;

	case 't':
		RailHeight += 50;
		std::cout << "Current Rail Height is " << RailHeight << std::endl;
		break;

	case 'g':
		if(RailHeight > 0)
			RailHeight -= 50;
		std::cout << "Current Rail Height is " << RailHeight << std::endl;
		break;

	case 'm':
		IsMouseLock = boolswitch(IsMouseLock);
		if(IsMouseLock)					std::cout << "Mouse Locked" << std::endl;
		else if (!IsMouseLock)			std::cout << "Mouse UnLocked" << std::endl;
		break;
	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y)
{
	Camera.getMouse(x, y);
	if(!IsTrainRunning)
		Camera.SetLookVector();

	if (Length(Vec3f(2 * (400 - x), RailHeight, 2 * (y - 400)) - CurveCtrlPt[0]) < 20)
		IsFlatConnected = true;
	
	else
		IsFlatConnected = false;

}

GLvoid MouseEvent(int button, int state, int x, int y) 
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN && !IsPerspective && !IsRailCompleted)
		{
			CurveCtrlPt[pointcounter][0] = 2 * (400 - x);
			CurveCtrlPt[pointcounter][1] = RailHeight;
			CurveCtrlPt[pointcounter][2] = 2 * (y - 400);
			
			if (IsFlatConnected) {
				CurveCtrlPt[pointcounter] = CurveCtrlPt[0];
				CurveCtrlPt[pointcounter + 1] = CurveCtrlPt[1];
				//CurveCtrlPt[pointcounter + 2] = CurveCtrlPt[2];
				pointcounter += 2;
				IsRailCompleted = true;
				break;
			}

			for (float f = 0.0f; f < 1.05f; f += 0.05)
			{
				Vec3f tmp = CCardinalSpline::CalcCardinal(
					f, 0.1f,
					CurveCtrlPt[pointcounter - 2],
					CurveCtrlPt[pointcounter - 1],
					CurveCtrlPt[pointcounter],
					CurveCtrlPt[pointcounter + 1]
				);

				for (int i = 0; i < 10; i++) {
					if (Length(tmp - Treepos[i]) < 50) {
						std::cout << "Rail Collide! Select other point." << std::endl;
						return;
					}
				}
			}

			if (pointcounter<30)
				pointcounter++;
			
			for (int i = pointcounter; i < 30; i++)
			{
				CurveCtrlPt[i][0] = 2 * (400 - x);
				CurveCtrlPt[i][1] = RailHeight;
				CurveCtrlPt[i][2] = 2 * (y - 400);
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}

	glutPostRedisplay();
}

GLvoid Timer(int val)
{
 	if (IsPerspective && !IsTrainRunning && IsMouseLock)			
		glutWarpPointer(400, 400);

	if (IsTrainRunning)			
		camerawalk();

	MoveShots();

	FallingBlizzard();

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

void ChangeView()
{
	if (IsPerspective) {
		//if(!IsTrainRunning)
			//Camera.SetLookVector();
		Camera.SetCamera();
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(W_Width, -W_Width, -W_Height, W_Height, -W_Depth, W_Depth);
		glMultMatrixf(projectionmatrix);
	}
}  

void camerawalk()
{
	

	CurrentPosition = Vec3f(
		CCardinalSpline::CalcCardinal(
			innercounter, 0.1f,
			CurveCtrlPt[outercounter-1],
			CurveCtrlPt[outercounter + 0],
			CurveCtrlPt[outercounter + 1],
			CurveCtrlPt[outercounter + 2]
		));
	
	PrevPosition = Vec3f(
		CCardinalSpline::CalcCardinal(
			innercounter - 0.1, 0.1f,
			CurveCtrlPt[outercounter - 1],
			CurveCtrlPt[outercounter + 0],
			CurveCtrlPt[outercounter + 1],
			CurveCtrlPt[outercounter + 2]
		));

	NextPosition = Vec3f(
		CCardinalSpline::CalcCardinal(
			innercounter + 0.1, 0.1f,
			CurveCtrlPt[outercounter - 1],
			CurveCtrlPt[outercounter + 0],
			CurveCtrlPt[outercounter + 1],
			CurveCtrlPt[outercounter + 2]
		));

	if (outercounter == 0)
	{
		CurrentPosition = Vec3f(
			CCardinalSpline::CalcCardinal(
				innercounter, 0.1f,
				CurveCtrlPt[1],
				CurveCtrlPt[0],
				CurveCtrlPt[1],
				CurveCtrlPt[0]
			));

		PrevPosition = Vec3f(
			CCardinalSpline::CalcCardinal(
				innercounter - 0.1, 0.1f,
				CurveCtrlPt[1],
				CurveCtrlPt[0],
				CurveCtrlPt[1],
				CurveCtrlPt[0]
			));

		NextPosition = Vec3f(
			CCardinalSpline::CalcCardinal(
				innercounter + 0.1, 0.1f,
				CurveCtrlPt[1],
				CurveCtrlPt[0],
				CurveCtrlPt[1],
				CurveCtrlPt[0]
			));
	}

	if (IsFPSView) {
		Camera.SetCameraPosition(
			NextPosition.x,
			NextPosition.y + 20,
			NextPosition.z
		);
	}
	else {
		Camera.SetCameraPosition(
			NextPosition.x,
			NextPosition.y + 50,
			NextPosition.z
		);

	}
	Camera.SetLookVector(NextPosition - CurrentPosition);

	innercounter += 0.01f;
	if (innercounter >= 0.98f) {
		outercounter++;
		innercounter = 0.01f;
	}

	if (outercounter > pointcounter - 3) {
		outercounter = 0;
		innercounter = 0.01f;
	}
}

void InitBlizzard()
{
	for (int i = 0; i < 500; i++)
	{
		snowposition[i].x = -600 + (rand() % 1200);
		snowposition[i].y = rand() % 800;
		snowposition[i].z = -600 + (rand() % 1200);
		snowspeed[i] = 1 + (rand() % 5) * 0.1;
	}
}

void FallingBlizzard()
{
	for (int i = 0; i < 500; i++) {
		snowposition[i].y -= snowspeed[i];
		if (snowposition[i].y < 0)
			snowposition[i].y = 800;
	}
}

void RenderBlizzard()
{
	glPushMatrix();
	{
		for (int i = 0; i < 500; i++)
		{
			glPushMatrix();
			glTranslatef(snowposition[i].x, snowposition[i].y, snowposition[i].z);
			glutSolidSphere(5, 10, 10);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void RenderShots()
{
	for (int i = 0; i < shotcounter; i++) 
	{
		glPushMatrix();
		{
			glTranslatef(shotspos[i].x, shotspos[i].y, shotspos[i].z);
			glutSolidSphere(15, 30, 30);
		}
		glPopMatrix();
	}
}

void MoveShots()
{
	for (int i = 0; i < shotcounter; i++)
	{
		shotspos[i] += shotsdir[i];
	}
}
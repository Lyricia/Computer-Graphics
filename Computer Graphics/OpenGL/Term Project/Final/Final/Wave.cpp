#pragma once
#include "Wave.h"
#include "Tools.h"

CWave::CWave()
{
}


CWave::~CWave()
{
}

void CWave::Set_Wavepos(float x, float y, float z)
{
	const float heliheight = 500;

	Position.x = x;
	Position.y = y + heliheight;
	Position.z = z;

	Position.x -= quad_dis * quad_count / 2;
	Position.z -= 8 * quad_dis * quad_count / 2;			//속지마! 사실상 매직넘버 ㅎ
}

void CWave::init_Wave()
{
	if (init_onoff)				//최적화를 위하여
	{
		for (int i = 0; i < 20; i++)
		{
			if (i == 0 || i == 9)
				wave_h_value = -200;
			else if (i == 2 || i == 5)
				wave_h_value = -250;
			else if (i == 1 || i == 3 || i == 7)
				wave_h_value = 100;

			for (int j = 0; j < 10; j++)
			{
				ctrlpoints[i][j][0] = (quad_dis * quad_count / 10 * j);
				ctrlpoints[i][j][1] = wave_h_value;
				ctrlpoints[i][j][2] = (quad_dis * quad_count / 10 * i);

				if (j == 3 || j == 6) {
					ctrlpoints[i][j][1] += 150;
				}
				else if (j == 0 || j == 9) {
					ctrlpoints[i][j][1] -= 200;
				}
			}
		}
		init_onoff = false;
	}
}

void CWave::Update_Wave()
{
	if (height_type == 0) {
		all_height += 2;

		if (all_height == 10) {
			height_type = 1;
		}
	}
	else if (height_type == 1) {
		all_height -= 2;

		if (all_height == -8) {
			height_type = 0;
		}
	}
}

void CWave::Render_Wave()
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y + all_height, Position.z);


	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 10, 0.0, 1.0, 30, 10, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 100, 0, 100);

	glPointSize(2.0);

	SetColor(103, 203, 255);
	glPopMatrix();
}
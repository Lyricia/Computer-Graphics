#include "Flow.h"



CFlow::CFlow()
{
}


CFlow::~CFlow()
{
}

void CFlow::get_helixyz(float x, float y, float z)
{
	Position.x = x;
	Position.y = 10;
	Position.z = z;

	Position.x -= quad_dis * quad_count / 2;
	Position.z -= 8 * quad_dis * quad_count / 2;			//속지마! 사실상 매직넘버 ㅎ
}

void CFlow::init_flow()
{
	if (init_onoff)				//최적화를 위하여
	{
		for (int i = 0; i < 20; i++)
		{
			if (i == 0 || i == 9)
				flow_h_value = -200;
			else if (i == 2 || i == 5)
				flow_h_value = -250;
			else if (i == 1 || i == 3 || i == 7)
				flow_h_value = 100;

			for (int j = 0; j < 10; j++)
			{
				ctrlpoints[i][j][0] = (quad_dis * quad_count / 10 * j);
				ctrlpoints[i][j][1] = flow_h_value;
				ctrlpoints[i][j][2] = (quad_dis * quad_count / 10 * i);

				if (j == 3 || j == 6) {
					ctrlpoints[i][j][1] += 150;
				}
				else if (j == 0 || j == 9) {
					ctrlpoints[i][j][1] -= 200;
				}
			}
		}
		init_onoff = 0;
	}
}

void CFlow::update_flow()
{
	//물결을 위아래로 흔들어주는 함수입니다!

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

void CFlow::draw_flow()
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y + all_height, Position.z);
	
	glColor3f(1, 1, 1);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 10, 0.0, 1.0, 30, 10, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 100, 0, 100);

	glPointSize(2.0);

	SetColor(103, 203, 255);

	glPopMatrix();

}

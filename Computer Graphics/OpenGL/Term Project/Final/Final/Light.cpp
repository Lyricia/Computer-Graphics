#include "Light.h"
#include "stdafx.h"

CLight::CLight()
{
}


CLight::~CLight()
{
}

void CLight::insert_light(unsigned char key)
{
}

void CLight::Make_Light(float x, float y, float z)
{
	{
		GLfloat AmbientLight_0[] = { 1.0 , 1.0f , 1.0f , 1.0f };
		GLfloat DiffuseLight_0[] = { 0.0f , 0.0f , 0.0f  , 0.5f };
		GLfloat SpecularLight_0[] = { 0.0, 0.0 , 0.0 , 0.5 };
		GLfloat lightPos_0[] = { x , y + 3000 ,  z, 1.0 };
		// 조명을 사용하도록 설정
		glEnable(GL_LIGHTING);

		// 조명 설정
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight_0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight_0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight_0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos_0);
		glEnable(GL_LIGHT0);
	}
	{
		GLfloat AmbientLight_1[] = { 0.1f, 0.1f, 0.2f, 0.3f };
		GLfloat DiffuseLight_1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//GLfloat DiffuseLight_1[] = { 10.0f, 10.0f, 10.0f, 0.1f };

		GLfloat SpecularLight_1[] = { 1.0, 0.0, 0.0, 0.1f };
		//GLfloat lightPos_1[] = { heli.point.x , heli.point.y + 1000,  heli.point.z - 2600, 1.0 };		//진짜설정하고픈 위치
		//GLfloat Spot_dir_1[] = { 0, -1, 1};
		GLfloat lightPos_1[] = { x , y + 10,  z-3000, 1.0 };		//사기침

		GLfloat Spot_dir_1[] = { 0, -1, 0 };

		GLfloat SPOT_CUTOFF_1[] = { 60 };
		GLfloat SPOT_EXPONENT_1[] = { 0, 0 };
		GLfloat CONSTANT_ATTENUATION_1[] = { 1, 0, 0 };


		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight_1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight_1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight_1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos_1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Spot_dir_1);
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, SPOT_CUTOFF_1);
		glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, SPOT_EXPONENT_1);
		glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, CONSTANT_ATTENUATION_1);
		glEnable(GL_LIGHT1);

		/*
		glPushMatrix();																//태양그리는거 나중에 어따가 뺴버리기
		SetColor(250, 250, 250);
		glTranslatef(heli.point.x, heli.point.y + 1000, heli.point.z - 2600);
		glutSolidSphere(200, 100, 100);
		glPopMatrix();
		*/
	}

	{
		GLfloat AmbientLight_2[] = { 0.0f, 0.0f, 1.0f, 0.5f };
		GLfloat DiffuseLight_2[] = { 1.0f, 0.0f, 0.0f, 0.5f };
		GLfloat SpecularLight_2[] = { 1.0, 1.0, 1.0, 0.5 };
		GLfloat lightPos_2[] = { -600, 600, -600, 1.0 };

		glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight_2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight_2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight_2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos_2);

		glEnable(GL_LIGHT2);
	}

	{
		GLfloat AmbientLight_3[] = { 0.0f, 0.0f, 1.0f, 0.5f };
		GLfloat DiffuseLight_3[] = { 1.0f, 0.0f, 0.0f, 0.5f };
		GLfloat SpecularLight_3[] = { 1.0, 1.0, 1.0, 0.5 };
		GLfloat lightPos_3[] = { 600, 600, -600, 1.0 };

		glLightfv(GL_LIGHT3, GL_AMBIENT, AmbientLight_3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, DiffuseLight_3);
		glLightfv(GL_LIGHT3, GL_SPECULAR, SpecularLight_3);
		glLightfv(GL_LIGHT3, GL_POSITION, lightPos_3);
		glEnable(GL_LIGHT3);
	}

	if (onoff_light_0 == 0)
		glDisable(GL_LIGHT0);

	if (onoff_light_1 == 0)
		glDisable(GL_LIGHT1);

	if (onoff_light_2 == 0)
		glDisable(GL_LIGHT2);

	if (onoff_light_3 == 0)
		glDisable(GL_LIGHT3);

	//색은 glcolor 또는 setcolor으로 설정합니다.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//이거 되려나 몰라
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

}
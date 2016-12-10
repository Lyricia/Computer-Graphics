#pragma once

#include "stdafx.h"
#include "Tools.h"

inline int Function_ONOFF(int onoff_)
{
	if (!onoff_)
		return 1;
	else if (onoff_ == 1)
		return 2;
	else if (onoff_)
		return 0;
}

inline int Function_ONOFF_SIMPLE(int onoff_)
{
	if (!onoff_)
		return 1;
	else if (onoff_)
		return 0;
}

typedef class BITMAP_Class_Robot {
public:
	typedef struct tagRGBQUAD { // rgbq
		BYTE rgbBlue;
		BYTE rgbGreen;
		BYTE rgbRed;
		BYTE rgbReserved;
	} RGBQUAD;
	typedef struct tagBITMAPINFO { // bmi
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD bmiColors[1];
	} BITMAPINFO;
	GLubyte * LoadDIBitMap(const char *filename, BITMAPINFO **info)
	{
		FILE *fp;
		GLubyte *bits;
		int bitsize, infosize;
		BITMAPFILEHEADER header;
		// 바이너리 읽기 모드로 파일을 연다
		if ((fp = fopen(filename, "rb")) == NULL)
			return NULL;
		// 비트맵 파일 헤더를 읽는다.
		if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
			fclose(fp);
			return NULL;
		}
		// 파일이 BMP 파일인지 확인한다.
		if (header.bfType != 'MB') {
			fclose(fp);
			return NULL;
		}
		// BITMAPINFOHEADER 위치로 간다.
		infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
		// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
		if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
			fclose(fp);
			exit(0);
			return NULL;
		}
		// 비트맵 인포 헤더를 읽는다.
		if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
			free(*info);
			fclose(fp);
			return NULL;
		}
		// 비트맵의 크기 설정
		if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
			bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.0 *
			abs((*info)->bmiHeader.biHeight);
		// 비트맵의 크기만큼 메모리를 할당한다.
		if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
			free(*info);
			fclose(fp);
			return NULL;
		}
		// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
		if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
			free(*info); free(bits);
			fclose(fp);
			return NULL;
		}
		fclose(fp);
		return bits;
	}
	GLubyte * TexBits_robot[10];
	BITMAPINFO *texture_robot[10];
	int onoff[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	void load_bitmap(const char *filename, int num, float w, float h)
	{
		if (onoff[num]) {
			TexBits_robot[num] = LoadDIBitMap(filename, &texture_robot[num]);
			onoff[num] = 0;
		}
	}
	void draw_bitmap(const char *filename, int num, float w, float h) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits_robot[num]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}
MAKE_BITMAP_Robot;

MAKE_BITMAP_Robot robot_bit;

typedef class Robot_class {
public:
	int robot_head_timer = 0;
	int robot_arm_timer = 0;
	int robot_leg_timer = 0;
	int robot_head_status = 0; // 1일때는 머리왓다
	int robot_arm_status = 0; // 1일때는 팔왓다
	int robot_leg_status = 0;	//1일떄는 다리 왔다
								//int robot_sit_status = 0;	// 1일떄는 앉기

	int robot_shot_status = 1;	// 로봇이 조준상태일때

	int robot_shot_timer = 0;	// 로봇이 조준상태일떄 하나씩올라감! 10이 될때 마다 총을쏨! 13까지 robot_shot_status를 2로 바꾸고 13에서 다시 timer가 0이 되면서 

	int RunOrWalk = 2;		//1일때 달리고 2일때 걷기
	void Robot_timer() {
		//cout << robot_head_timer << "   " << robot_head_status << endl;

		if (robot_head_status == 1)
		{
			robot_head_timer += 1;
			if (robot_head_timer == 15)
				robot_head_status = 2;
		}
		else if (robot_head_status == 2)
		{
			robot_head_timer -= 1;
			if (robot_head_timer == -15)
				robot_head_status = 1;
		}

		if (robot_arm_status == 1)
		{
			robot_arm_timer += 1;

			if (robot_arm_timer == 12)
				robot_arm_status = 2;
		}
		else if (robot_arm_status == 2)
		{
			robot_arm_timer -= 1;
			if (robot_arm_timer == -12)
				robot_arm_status = 1;
		}

		if (robot_leg_status == 1)
		{
			robot_leg_timer += 1;

			if (robot_leg_timer == 12)
				robot_leg_status = 2;
		}
		else if (robot_leg_status == 2)
		{
			robot_leg_timer -= 1;
			if (robot_leg_timer == -12)
				robot_leg_status = 1;
		}

		if (robot_shot_status)
		{
			robot_shot_timer++;

			if (robot_shot_timer >= 10)
			{
				robot_shot_status = 2;

				if (robot_shot_timer == 14) {
					robot_shot_status = 1;
					robot_shot_timer = 0;
				}
			}
		}
	}
	void control_robot(unsigned char key) {
		if (key == 's' || key == 'S')
		{
			robot_head_status = Function_ONOFF(robot_head_status);
		}
		if (key == 'a' || key == 'A')
		{
			robot_arm_status = Function_ONOFF(robot_arm_status);
		}
		if (key == 'd' || key == 'D')
		{
			robot_leg_status = Function_ONOFF(robot_leg_status);
		}
		if (key == 'f' || key == 'F')
			RunOrWalk = Function_ONOFF(RunOrWalk);
		else if (key == 'g' || key == 'G') {
			robot_shot_status = Function_ONOFF_SIMPLE(robot_shot_status);
		}
	}
	void Make_Robot(GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
		int h = size;
		glTranslatef(x, y, z); //x,y,z로 이동시킬겁니다.

		glPushMatrix(); {
			glutSolidCube(10);
			glEnable(GL_TEXTURE_2D);
			//얼굴을 그립니다.
			glPushMatrix(); {
				glTranslatef(0, 650, 0);

				SetColor(255, 255, 255);

				//glScalef((float)4 / (float)5, (float)3 / (float)5, (float)4 / (float)5);
				Rotate_XYZ(0, 3 * robot_head_timer, 0);

				//얼굴정면
				{
					//SetColor(150, 150, 150);
					//glutSolidCube(200);
					//glutWireCube(201);

					robot_bit.load_bitmap("robot_face_real.bmp", 1, 251, 503);
					robot_bit.draw_bitmap("robot_face_real.bmp", 1, 251, 503);

					glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-40, 50, 40);

					/*//	glTexCoord2f(0.36f, 0.2f);
					//	glVertex3f(-29.5, -40, 0);*/
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-40, -50, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -50, 60);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 50, 60);


					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 50, 60);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -50, 60);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(40, -50, 40);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(40, 50, 40);

					glEnd();
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
				}

				//얼굴 측면 두군데
				{
					robot_bit.load_bitmap("robot_face_side.bmp", 2, 321, 490);
					robot_bit.draw_bitmap("robot_face_side.bmp", 2, 321, 490);

					glPushMatrix(); {
						Rotate_XYZ(0, -90, 0);

						glBegin(GL_QUADS);

						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-40, 50, 40);

						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-40, -50, 40);

						glTexCoord2f(0.5f, 0.0f);
						glVertex3f(0, -50, 50);

						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);


						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);

						glTexCoord2f(0.5f, 0.0f);
						glVertex3f(0, -50, 50);

						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(40, -50, 40);

						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(40, 50, 40);

						glEnd();

						Rotate_XYZ(0, 180, 0);

						glBegin(GL_QUADS);

						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(-40, 50, 40);

						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(-40, -50, 40);

						glTexCoord2f(0.5f, 0.0f);
						glVertex3f(0, -50, 50);

						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);


						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);

						glTexCoord2f(0.5f, 0.0f);
						glVertex3f(0, -50, 50);

						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(40, -50, 40);

						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(40, 50, 40);

						glEnd();

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
					}
					glPopMatrix();
				}

				//얼굴 후면 한군데
				{
					robot_bit.load_bitmap("robot_face_back.bmp", 3, 279, 443);
					robot_bit.draw_bitmap("robot_face_back.bmp", 3, 279, 443);

					glPushMatrix(); {
						Rotate_XYZ(0, -180, 0);

						glBegin(GL_QUADS);

						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-40, 50, 40);

						glTexCoord2f(0.0f, 0.5f);
						glVertex3f(-40, 0, 40);

						glTexCoord2f(0.5f, 0.5f);
						glVertex3f(0, 0, 50);

						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);


						glTexCoord2f(0.5f, 1.0f);
						glVertex3f(0, 50, 50);

						glTexCoord2f(0.5f, 0.5f);
						glVertex3f(0, 0, 50);

						glTexCoord2f(1.0f, 0.5f);
						glVertex3f(40, 0, 40);

						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(40, 50, 40);

						glEnd();

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						glPopMatrix();
					}
				}
				glPopMatrix();
			}
			
			//목을 그립니다.
			glPushMatrix(); {
				glTranslatef(0, 640, 0);
				//SetColor(0, 255, 0);
				//Rotate_XYZ(90, 0, 0);

				robot_bit.load_bitmap("robot_neck.bmp", 9, 140, 161);
				robot_bit.draw_bitmap("robot_neck.bmp", 9, 140, 161);
				//glEnable(GL_TEXTURE_GEN_S);
				//glEnable(GL_TEXTURE_GEN_T);

				//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				//SetColor(255, 255, 255);
				//MakeCylinder(0, 0, 0, 15, 50);
				//glutSolidSphere(15, 10, 10);

				glBegin(GL_QUADS); {
					//SetColor(255, 255, 255);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-10, 50, 0);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-10, -100, 0);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(10, -100, 0);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(10, 50, 0);

					glEnd();
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
				}
				//glDisable(GL_TEXTURE_GEN_S);
				//glDisable(GL_TEXTURE_GEN_T);

				//glutWireCube(51);
				glPopMatrix();
			}

			//몸을 그립니다.// 몸 내부에는 팔과 다리 총이 포함됩니다.
			glPushMatrix(); {
				glTranslatef(0, 400, 0);
				SetColor(150, 150, 150);
				//glutSolidCube(200);
				//SetColor(0, 0, 0);
				//glutWireCube(201);
				robot_bit.load_bitmap("robot_body_up.bmp", 4, 300, 423);
				robot_bit.draw_bitmap("robot_body_up.bmp", 4, 300, 423);

				glPushMatrix(); {
					//Rotate_XYZ(0, -180, 0);
					glBegin(GL_QUADS);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(-110, 200, 0);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(-110, -200, 0);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);


					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);


					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(100, -200, 40);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(100, 200, 40);


					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(100, 200, 40);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(110, -200, 0);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(110, 200, 0);


					glEnd();

					Rotate_XYZ(0, -180, 0);
					glBegin(GL_QUADS);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(-110, 200, 0);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(-110, -200, 0);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);


					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-100, 200, 40);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);


					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(0, 200, 50);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(0, -200, 50);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(100, -200, 40);

					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(100, 200, 40);


					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(100, 200, 40);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(100, -200, 40);

					glTexCoord2f(0.5f, 0.0f);
					glVertex3f(110, -200, 0);

					glTexCoord2f(0.5f, 1.0f);
					glVertex3f(110, 200, 0);


					glEnd();


					glPopMatrix();
				}
				glScalef((float)1, 1, (float)4 / (float)5);
				glScalef((float)4 / 3, 1, (float)5 / (float)4);

				//오른쪽 팔을 그립니다.(로봇의 시점에서) 팔뿌리입니다.
				glPushMatrix(); {
					glTranslatef(-80, 140, 0);
					Rotate_XYZ(0, 45, 30);		//얼마나 몸 앞쪽으로 굽히고 몸아래로 내리는가
					glPushMatrix(); {
						//glScalef((float)1 / 3, 1, 1);
						robot_bit.load_bitmap("robot_shoulder.bmp", 5, 200, 116);
						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						//glEnable(GL_TEXTURE_GEN_MODE);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						//SetColor(0, 255, 255);
						SetColor(150, 150, 150);

						glutSolidSphere(25, 10, 10);
						//SetColor(0, 0, 0);
						//glutWireSphere(25, 10, 10);
						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						//glDisable(GL_TEXTURE_GEN_MODE);
						glPopMatrix();
					}

					//오른쪽 첫번째 팔 부위를 그립니다.
					glPushMatrix(); {
						if (robot_arm_timer < 0)				//팔 올라갈때!!
							Rotate_XYZ((float)robot_arm_timer / 2, 0, 0);
						else if (robot_arm_timer > 0)		//팔 내려갈때!!
							Rotate_XYZ((float)robot_arm_timer / 2, 0, 0);

						glPushMatrix(); {
							glTranslatef(0, 0, 0);
							Rotate_XYZ(0, 270, 0);

							if (robot_shot_status) {
								Rotate_XYZ(45, 0, 0);
							}
							robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
							//glEnable(GL_TEXTURE_GEN_MODE);
							glEnable(GL_TEXTURE_GEN_S);
							glEnable(GL_TEXTURE_GEN_T);

							glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							//SetColor(0, 255, 255);
							SetColor(150, 150, 150);

							MakeCylinder(0, 0, 0, 12, 100);
							//glutSolidSphere(15, 10, 10);
							//SetColor(0, 0, 0);
							//glutWireSphere(25, 10, 10);
							glDisable(GL_TEXTURE_GEN_S);
							glDisable(GL_TEXTURE_GEN_T);
							//glDisable(GL_TEXTURE_GEN_MODE);
							//glPopMatrix();

							if (robot_shot_status) {
								glPushMatrix(); {

									glTranslatef(0, 0, 100);

									Rotate_XYZ(30, 140, 0);			// 여기서 push안하고 팔 뻇습니다!!

									if (robot_shot_status == 2)
										Rotate_XYZ(10, 15, 0);			// 여기서 push안하고 팔 뻇습니다!!

									robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
									glEnable(GL_TEXTURE_GEN_S);
									glEnable(GL_TEXTURE_GEN_T);

									glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									SetColor(150, 150, 150);
									glutSolidSphere(15, 10, 10);

									glDisable(GL_TEXTURE_GEN_S);
									glDisable(GL_TEXTURE_GEN_T);

									//오른쪽 팔 가장 긴 부분 손목에서 팔목까지
									glPushMatrix(); {
										glTranslatef(0, 0, 0);

										robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
										glEnable(GL_TEXTURE_GEN_S);
										glEnable(GL_TEXTURE_GEN_T);

										glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
										glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
										SetColor(150, 150, 150);
										MakeCylinder(0, 0, 0, 12, 150);

										glDisable(GL_TEXTURE_GEN_S);
										glDisable(GL_TEXTURE_GEN_T);

										//팔 가장 긴 부분 손목작업
										glPushMatrix(); {

											glTranslatef(0, 0, 120);
											robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
											//glEnable(GL_TEXTURE_GEN_MODE);
											glEnable(GL_TEXTURE_GEN_S);
											glEnable(GL_TEXTURE_GEN_T);

											glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											//SetColor(0, 255, 255);
											SetColor(150, 150, 150);

											glutSolidSphere(15, 10, 10);
											//SetColor(0, 0, 0);
											//glutWireSphere(25, 10, 10);
											glDisable(GL_TEXTURE_GEN_S);
											glDisable(GL_TEXTURE_GEN_T);
											//glDisable(GL_TEXTURE_GEN_MODE);
											//glPopMatrix();

											glPopMatrix();
										}
										// 총 대충 모양 그려줍시다
										glPushMatrix(); {

											glTranslatef(20, 30, 175);		//   가로세로, 높이! ,깊이값!										
											Rotate_XYZ(70, 140, 30);
											//새로운총이다!!
											glTranslatef(0, -10, -30);
											//glTranslatef(0, 0, 300);	// gunhand
											glPushMatrix(); {

												glScalef(1, 3, 1);
												//	SetColor(0, 0, 255);
												//	SetColor(0, 0, 0);
												//	glutWireCube(21);

												robot_bit.load_bitmap("gun_hand.bmp", 7, 64, 87);
												robot_bit.draw_bitmap("gun_hand.bmp", 7, 64, 87);

												glEnable(GL_TEXTURE_GEN_S);
												glEnable(GL_TEXTURE_GEN_T);

												glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
												glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
												SetColor(255, 0, 0);
												glutSolidCube(19);

												glDisable(GL_TEXTURE_GEN_S);
												glDisable(GL_TEXTURE_GEN_T);
												glPopMatrix();
											}

											glPushMatrix(); {
												glTranslatef(70, 50, 0);
												Rotate_XYZ(0, 0, 20);
												glScalef(12, 2, 1);

												robot_bit.draw_bitmap("gun_hand.bmp", 7, 64, 87);

												glEnable(GL_TEXTURE_GEN_S);
												glEnable(GL_TEXTURE_GEN_T);

												glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
												glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
												SetColor(0, 0, 0);
												glutSolidCube(20);

												glDisable(GL_TEXTURE_GEN_S);
												glDisable(GL_TEXTURE_GEN_T);
												glPopMatrix();
											}
											/*
											//총 방아틀 뭉치
											glPushMatrix();
											{
											Rotate_XYZ(90, -40, 30);
											glScalef(1, 1, 5);				// 이젠 제트가 높이!
											SetColor(0, 0, 255);
											glutSolidCube(15);
											SetColor(0, 0, 0);
											glutWireCube(16);
											glPopMatrix();
											}

											// 총 몸뚱아리
											glPushMatrix();
											{
											glTranslatef(80, 50,25);
											Rotate_XYZ(-10, 70, 0);	//x축 회전 //y축 회전 // z축회전

											glScalef(1, 3, 18);

											SetColor(0, 0, 200);
											glutSolidCube(15);
											SetColor(0, 0, 0);
											glutWireCube(16);

											glPopMatrix();
											}
											*/
											glPopMatrix();
										}

										glPopMatrix();
									}
									glPopMatrix();
								}
								glPopMatrix();

							}
							glPopMatrix();
							//glPopMatrix();
						}
						//오른쪽 팔중간부분 /  부분을 그립니다.
						if (!robot_shot_status) {
							glPushMatrix(); {

								glTranslatef(-100, 0, 0);
								Rotate_XYZ(10, 0, 0);			// 여기서 push안하고 팔 뻇습니다!!

								robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
								glEnable(GL_TEXTURE_GEN_S);
								glEnable(GL_TEXTURE_GEN_T);

								glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								SetColor(150, 150, 150);
								glutSolidSphere(15, 10, 10);

								glDisable(GL_TEXTURE_GEN_S);
								glDisable(GL_TEXTURE_GEN_T);

								//오른쪽 팔 가장 긴 부분 손목에서 팔목까지
								glPushMatrix(); {
									glTranslatef(0, 0, 0);

									robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
									glEnable(GL_TEXTURE_GEN_S);
									glEnable(GL_TEXTURE_GEN_T);

									glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									SetColor(150, 150, 150);
									MakeCylinder(0, 0, 0, 12, 150);

									glDisable(GL_TEXTURE_GEN_S);
									glDisable(GL_TEXTURE_GEN_T);

									//팔 가장 긴 부분 손목작업
									glPushMatrix(); {

										glTranslatef(0, 0, 120);
										robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
										//glEnable(GL_TEXTURE_GEN_MODE);
										glEnable(GL_TEXTURE_GEN_S);
										glEnable(GL_TEXTURE_GEN_T);

										glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
										glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
										//SetColor(0, 255, 255);
										SetColor(150, 150, 150);

										glutSolidSphere(15, 10, 10);
										//SetColor(0, 0, 0);
										//glutWireSphere(25, 10, 10);
										glDisable(GL_TEXTURE_GEN_S);
										glDisable(GL_TEXTURE_GEN_T);
										//glDisable(GL_TEXTURE_GEN_MODE);
										//glPopMatrix();

										glPopMatrix();
									}
									// 총 대충 모양 그려줍시다
									glPushMatrix(); {

										glTranslatef(20, 30, 145);		//   가로세로, 높이! ,깊이값!										
										Rotate_XYZ(0, 330, -20);
										//새로운총이다!!

										//glTranslatef(0, 0, 300);	// gunhand
										glPushMatrix(); {

											glScalef(1, 3, 1);
											//	SetColor(0, 0, 255);
											//	SetColor(0, 0, 0);
											//	glutWireCube(21);

											robot_bit.load_bitmap("gun_hand.bmp", 7, 64, 87);
											robot_bit.draw_bitmap("gun_hand.bmp", 7, 64, 87);

											glEnable(GL_TEXTURE_GEN_S);
											glEnable(GL_TEXTURE_GEN_T);

											glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											SetColor(0, 0, 0);
											glutSolidCube(19);

											glDisable(GL_TEXTURE_GEN_S);
											glDisable(GL_TEXTURE_GEN_T);
											glPopMatrix();
										}

										glPushMatrix(); {
											glTranslatef(70, 50, 0);
											Rotate_XYZ(0, 0, 20);
											glScalef(12, 2, 1);

											robot_bit.draw_bitmap("gun_hand.bmp", 7, 64, 87);

											glEnable(GL_TEXTURE_GEN_S);
											glEnable(GL_TEXTURE_GEN_T);

											glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
											SetColor(0, 0, 0);
											glutSolidCube(20);

											glDisable(GL_TEXTURE_GEN_S);
											glDisable(GL_TEXTURE_GEN_T);
											glPopMatrix();
										}
										/*
										//총 방아틀 뭉치
										glPushMatrix();
										{
										Rotate_XYZ(90, -40, 30);
										glScalef(1, 1, 5);				// 이젠 제트가 높이!
										SetColor(0, 0, 255);
										glutSolidCube(15);
										SetColor(0, 0, 0);
										glutWireCube(16);
										glPopMatrix();
										}

										// 총 몸뚱아리
										glPushMatrix();
										{
										glTranslatef(80, 50,25);
										Rotate_XYZ(-10, 70, 0);	//x축 회전 //y축 회전 // z축회전

										glScalef(1, 3, 18);

										SetColor(0, 0, 200);
										glutSolidCube(15);
										SetColor(0, 0, 0);
										glutWireCube(16);

										glPopMatrix();
										}
										*/
										glPopMatrix();
									}

									glPopMatrix();
								}
								glPopMatrix();
							}
							glPopMatrix();
						}
					}
					glPopMatrix();
				}

				//왼쪽 팔을 그립니다.(로봇의 시점에서) 팔뿌리입니다.
				glPushMatrix(); {
					glTranslatef(80, 140, 0);
					Rotate_XYZ(30, 195, 0);		//얼마나 몸 앞쪽으로 굽히고 몸아래로 내리는가
					glPushMatrix(); {
						//glScalef((float)1 / 3, 1, 1);
						//robot_bit.load_bitmap("robot_shoulder_2.bmp", 6, 80, 92);
						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						SetColor(150, 150, 150);
						glutSolidSphere(25, 10, 10);

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						glPopMatrix();
					}

					//왼쪽 첫번째 팔 부위를 그립니다.
					glPushMatrix(); {
						if (robot_arm_timer < 0)				//팔 올라갈때!!
							Rotate_XYZ((float)-robot_arm_timer / 2, 0, 0);
						else if (robot_arm_timer > 0)		//팔 내려갈때!!
							Rotate_XYZ((float)-robot_arm_timer / 2, 0, 0);

						glPushMatrix(); {
							glTranslatef(0, 0, 0);
							Rotate_XYZ(0, 170, 0);
							robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
							glEnable(GL_TEXTURE_GEN_S);
							glEnable(GL_TEXTURE_GEN_T);

							glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							SetColor(150, 150, 150);
							MakeCylinder(0, 0, 0, 12, 100);


							glDisable(GL_TEXTURE_GEN_S);
							glDisable(GL_TEXTURE_GEN_T);
							glPopMatrix();
						}
						//왼쪽 팔중간부분 /  부분을 그립니다.
						glPushMatrix(); {
							glTranslatef(15, 0, -90);
							Rotate_XYZ(60, 150, 0);			// 여기서 push안하고 팔 뻇습니다!!
							if (robot_shot_status)
							{
								Rotate_XYZ(0, -30, 0);
							}
							if (robot_shot_status == 2)
								Rotate_XYZ(-20, 0, 0);			// 여기서 push안하고 팔 뻇습니다!!
							robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
							glEnable(GL_TEXTURE_GEN_S);
							glEnable(GL_TEXTURE_GEN_T);

							glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							SetColor(150, 150, 150);
							glutSolidSphere(15, 10, 10);

							glDisable(GL_TEXTURE_GEN_S);
							glDisable(GL_TEXTURE_GEN_T);

							//왼쪽 팔 가장 긴 부분 손목에서 팔목까지
							glPushMatrix(); {
								glTranslatef(0, 0, 0);

								robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
								glEnable(GL_TEXTURE_GEN_S);
								glEnable(GL_TEXTURE_GEN_T);

								glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								SetColor(150, 150, 150);

								MakeCylinder(0, 0, 0, 12, 150);

								glDisable(GL_TEXTURE_GEN_S);
								glDisable(GL_TEXTURE_GEN_T);
								//팔 가장 긴 부분 손목작업
								glPushMatrix(); {

									glTranslatef(0, 0, 120);
									robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
									//glEnable(GL_TEXTURE_GEN_MODE);
									glEnable(GL_TEXTURE_GEN_S);
									glEnable(GL_TEXTURE_GEN_T);

									glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									//SetColor(0, 255, 255);
									SetColor(150, 150, 150);

									glutSolidSphere(15, 10, 10);
									//SetColor(0, 0, 0);
									//glutWireSphere(25, 10, 10);
									glDisable(GL_TEXTURE_GEN_S);
									glDisable(GL_TEXTURE_GEN_T);
									//glDisable(GL_TEXTURE_GEN_MODE);
									//glPopMatrix();

									//glPopMatrix();

									glPopMatrix();
								}
								glPopMatrix();
							}
							glPopMatrix();
						}
						glPopMatrix();
					}
					glPopMatrix();
				}

				//오른쪽 다리를 그립니다.
				glPushMatrix(); {
					glTranslatef(-50, -200, 0);

					//오른쪽 다리 뿌리를 그립니다.
					glPushMatrix(); {
						//glScalef((float)1 / 3, 1, 1);

						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						SetColor(150, 150, 150);
						glutSolidSphere(25, 10, 10);

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);


						glPopMatrix();
					}

					//오른쪽 다리 시작 기둥을 그립니다.
					glPushMatrix(); {
						glTranslatef(0, 0, 0);
						if (RunOrWalk == 1) {
							if (robot_leg_timer < 0)
								Rotate_XYZ(robot_leg_timer * 4, 0, 0);
							else if (robot_leg_timer > 0)
								Rotate_XYZ(robot_leg_timer * 3, 0, 0);
						}
						else if (RunOrWalk == 2) {
							if (robot_leg_timer < 0)
								Rotate_XYZ(robot_leg_timer * 2, 0, 0);
							else if (robot_leg_timer > 0)
								Rotate_XYZ(robot_leg_timer * (float)3 / 2, 0, 0);
						}
						Rotate_XYZ(90, 0, 0);
						SetColor(0, 255, 0);
						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						SetColor(150, 150, 150);
						MakeCylinder(0, 0, 0, 25, 230);
						//glutSolidSphere(15, 10, 10);

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);

						//오른쪽 무릎을 그린다.
						glPushMatrix(); {
							glTranslatef(0, 0, 230);

							robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
							glEnable(GL_TEXTURE_GEN_S);
							glEnable(GL_TEXTURE_GEN_T);

							glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							SetColor(150, 150, 150);
							glutSolidSphere(15, 10, 10);

							glDisable(GL_TEXTURE_GEN_S);
							glDisable(GL_TEXTURE_GEN_T);


							//오른쪽 나머지 종강이를 그린다.
							glPushMatrix();
							{
								glTranslatef(0, 0, 0);

								//그냥 하드코딩할랍니다!
								if (RunOrWalk == 1) {
									//오른쪽 다리가 뒤로 갈떄에!
									if (robot_leg_status == 1)
									{


										if (robot_leg_timer == -12)
											Rotate_XYZ(25, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(20, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(15, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(3, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(2, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 12)
											Rotate_XYZ(0, 0, 0);
									}
									//오른쪽다리가 앞으로 나오는 경우에!!!
									if (robot_leg_status == 2)
									{
										if (robot_leg_timer == 12)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(20, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(40, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(50, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(60, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(60, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(52, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(44, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(36, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(28, 0, 0);
										if (robot_leg_timer == -12)
											Rotate_XYZ(20, 0, 0);
									}
								}
								else if (RunOrWalk == 2) {
									//오른쪽 다리가 뒤로 갈떄에!
									if (robot_leg_status == 1)
									{
										if (robot_leg_timer == -12)
											Rotate_XYZ(8, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(3, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(2, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 12)
											Rotate_XYZ(0, 0, 0);
									}
									//오른쪽다리가 앞으로 나오는 경우에!!!
									if (robot_leg_status == 2)
									{
										if (robot_leg_timer == 12)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(15, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(20, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(25, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(35, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(38, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(34, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(24, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(22, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(16, 0, 0);
										if (robot_leg_timer == -12)
											Rotate_XYZ(12, 0, 0);
									}
								}
								SetColor(0, 255, 0);
								robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
								glEnable(GL_TEXTURE_GEN_S);
								glEnable(GL_TEXTURE_GEN_T);

								glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								SetColor(150, 150, 150);
								//glutSolidSphere(15, 10, 10);
								MakeCylinder(0, 0, 0, 10, 300);

								glDisable(GL_TEXTURE_GEN_S);
								glDisable(GL_TEXTURE_GEN_T);
								//신발을 그려줍니다.
								//glPushMatrix(); {
								//	glTranslatef(0, 40, 270);		// z값 , y값임
								//	glScalef((float)1 / 2, 1, (float)1 / 2);

								//	robot_bit.load_bitmap("robot_foot.bmp", 6, 60, 59);
								//	robot_bit.draw_bitmap("robot_foot.bmp", 6, 60, 59);

								//	glEnable(GL_TEXTURE_GEN_S);
								//	glEnable(GL_TEXTURE_GEN_T);

								//	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								//	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								//	SetColor(150, 150, 150);
								//	//glutSolidSphere(15, 10, 10);
								//	glutSolidCube(100);

								//	glDisable(GL_TEXTURE_GEN_S);
								//	glDisable(GL_TEXTURE_GEN_T);

								//	//SetColor(150, 150, 150);
								//	//SetColor(0, 0, 0);
								//	//glutWireCube(101);
								//	glPopMatrix();
								//}
								glPopMatrix();
							}
							glPopMatrix();
						}
						glPopMatrix();
					}
					glPopMatrix();
				}

				//왼쪽 다리를 그립니다.
				glPushMatrix(); {
					glTranslatef(50, -200, 0);

					// 왼쪽 다리 뿌리를 그립니다.
					glPushMatrix(); {
						//glScalef((float)1 / 3, 1, 1);


						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						SetColor(150, 150, 150);
						//glutSolidSphere(15, 10, 10);
						glutSolidSphere(25, 10, 10);

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);

						glPopMatrix();
					}

					// 왼쪽 다리 시작 기둥을 그립니다.
					glPushMatrix(); {
						glTranslatef(0, 0, 0);
						if (RunOrWalk == 1) {
							if (robot_leg_timer > 0)
								Rotate_XYZ(-robot_leg_timer * 4, 0, 0);
							else if (robot_leg_timer < 0)
								Rotate_XYZ(-robot_leg_timer * 3, 0, 0);
						}
						else if (RunOrWalk == 2) {
							if (robot_leg_timer > 0)
								Rotate_XYZ(-robot_leg_timer * 2, 0, 0);
							else if (robot_leg_timer < 0)
								Rotate_XYZ(-robot_leg_timer * (float)3 / 2, 0, 0);
						}
						Rotate_XYZ(90, 0, 0);


						robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
						glEnable(GL_TEXTURE_GEN_S);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
						SetColor(150, 150, 150);
						MakeCylinder(0, 0, 0, 25, 230);
						//glutSolidSphere(15, 10, 10);

						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);

						//왼쪽 무릎을 그린다.
						glPushMatrix(); {
							glTranslatef(0, 0, 230);

							robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
							glEnable(GL_TEXTURE_GEN_S);
							glEnable(GL_TEXTURE_GEN_T);

							glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
							SetColor(150, 150, 150);
							glutSolidSphere(15, 10, 10);

							glDisable(GL_TEXTURE_GEN_S);
							glDisable(GL_TEXTURE_GEN_T);

							//왼쪽 나머지 종강이를 그린다.
							glPushMatrix();
							{
								glTranslatef(0, 0, 0);

								if (RunOrWalk == 1) {
									//왼쪽 다리가 뒤로 갈떄에!
									if (robot_leg_status == 2)
									{

										if (robot_leg_timer == -12)
											Rotate_XYZ(25, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(20, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(15, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(3, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(2, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 12)
											Rotate_XYZ(0, 0, 0);
									}
									//왼쪽다리가 앞으로 나오는 경우에!!!
									else if (robot_leg_status == 1)
									{
										if (robot_leg_timer == 12)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(20, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(40, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(50, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(60, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(70, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(60, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(52, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(44, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(36, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(28, 0, 0);
										if (robot_leg_timer == -12)
											Rotate_XYZ(20, 0, 0);
									}
								}
								else if (RunOrWalk == 2) {
									//왼쪽 다리가 뒤로 갈떄에!
									if (robot_leg_status == 2)
									{

										if (robot_leg_timer == -12)
											Rotate_XYZ(8, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(3, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(2, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(0, 0, 0);
										if (robot_leg_timer == 12)
											Rotate_XYZ(0, 0, 0);
									}
									//왼쪽다리가 앞으로 나오는 경우에!!!
									else if (robot_leg_status == 1)
									{
										if (robot_leg_timer == 12)
											Rotate_XYZ(5, 0, 0);
										if (robot_leg_timer == 11)
											Rotate_XYZ(10, 0, 0);
										if (robot_leg_timer == 10)
											Rotate_XYZ(15, 0, 0);
										if (robot_leg_timer == 9)
											Rotate_XYZ(25, 0, 0);
										if (robot_leg_timer == 8)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == 7)
											Rotate_XYZ(35, 0, 0);
										if (robot_leg_timer == 6)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 5)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 4)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 3)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 2)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 1)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == 0)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -1)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -2)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -3)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -4)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -5)
											Rotate_XYZ(41, 0, 0);
										if (robot_leg_timer == -6)
											Rotate_XYZ(38, 0, 0);
										if (robot_leg_timer == -7)
											Rotate_XYZ(34, 0, 0);
										if (robot_leg_timer == -8)
											Rotate_XYZ(30, 0, 0);
										if (robot_leg_timer == -9)
											Rotate_XYZ(24, 0, 0);
										if (robot_leg_timer == -10)
											Rotate_XYZ(22, 0, 0);
										if (robot_leg_timer == -11)
											Rotate_XYZ(16, 0, 0);
										if (robot_leg_timer == -12)
											Rotate_XYZ(12, 0, 0);
									}
								}
								robot_bit.draw_bitmap("robot_shoulder.bmp", 5, 200, 116);
								glEnable(GL_TEXTURE_GEN_S);
								glEnable(GL_TEXTURE_GEN_T);

								glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
								SetColor(150, 150, 150);
								//glutSolidSphere(15, 10, 10);
								MakeCylinder(0, 0, 0, 10, 300);

								glDisable(GL_TEXTURE_GEN_S);
								glDisable(GL_TEXTURE_GEN_T);

								//신발을 그려줍니다.
								glPushMatrix(); {
									glTranslatef(0, 40, 270);		// z값 , y값임
									glScalef((float)1 / 2, 1, (float)1 / 2);
									//SetColor(150, 150, 150);

									robot_bit.draw_bitmap("robot_.bmp", 6, 60, 59);
									glEnable(GL_TEXTURE_GEN_S);
									glEnable(GL_TEXTURE_GEN_T);

									glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
									SetColor(150, 150, 150);
									glutSolidCube(100);
									//glutSolidSphere(15, 10, 10);

									glDisable(GL_TEXTURE_GEN_S);
									glDisable(GL_TEXTURE_GEN_T);
									//SetColor(0, 0, 0);
									//glutWireCube(101);
									glPopMatrix();
								}
								glPopMatrix();
							}
							glPopMatrix();
						}
						glPopMatrix();
					}
					glPopMatrix();
				}

				glPopMatrix();
			}
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
	}
}ROBOT;
ROBOT BOT;

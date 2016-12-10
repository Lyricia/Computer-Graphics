#pragma once
#include "Helicopter.h"
#include "stdafx.h"
#include "Tools.h"

CHelicopter::CHelicopter()
{
	wing_angle = 0;
}


CHelicopter::~CHelicopter()
{
}

void CHelicopter::Render()
{
	glPushMatrix(); 
	{
		glEnable(GL_DEPTH_TEST);
		glScalef(0.01, 0.01, 0.01);
		glTranslatef(Position.x, Position.y, Position.z);
		//������ ����ž�
		glPushMatrix();
		{
			//������ �밡��		//������ �׸��ϱ� ��������... // -> Quads�� �مf�� ���߿� �ѹ� �� �տ� ������!! -> �Ⱥ��ϰŰ�����
			glPushMatrix(); 
			{
				glTranslatef(0, 0, -z_size);

				SetColor(170, 170, 170);

				//glutSolidSphere(y_size, 10, 10);

				glBegin(GL_QUADS); {

					glVertex3f(-x_size + 10, y_size - 10, -30);
					glVertex3f(-x_size, y_size, 0);
					glVertex3f(x_size, y_size, 0);
					glVertex3f(x_size - 10, y_size - 10, -30);


					glEnd();
				}

			}
			glPopMatrix();

			if (wing_style == 1) {
				//���� �߾�!!!
				
				
				glPushMatrix();
				{
					SetColor(255, 255, 255);
					
					//glTranslatef(-3 * x_size, 0, -10);
					//wing_angle = 0;

					//�����Ѹ�!!!!
					glPushMatrix(); 
					{
						glTranslatef(0, y_size + y_size / 2, 0);
						glScalef(1, (float)1 / 5, 1);
						glutSolidSphere(10, 10, 10);						
					}
					glPopMatrix();
					//��������!!
					glPushMatrix(); 
					{
						Rotate_XYZ(0, wing_angle, 0);
						glTranslatef(0, y_size + y_size / 2 - 5, 0);

						SetColor(110, 110, 110);

						glBegin(GL_QUADS); {


							glVertex3f(0, 3, 6);
							glVertex3f(5 * x_size, 3, 6);
							glVertex3f(5 * x_size, -3, -6);
							glVertex3f(0, -3, -6);

							glVertex3f(0, -3, 6);
							glVertex3f(-5 * x_size, -3, 6);
							glVertex3f(-5 * x_size, 3, -6);
							glVertex3f(0, 3, -6);

							glVertex3f(6, -3, 0);
							glVertex3f(6, -3, 5 * x_size);
							glVertex3f(-6, 3, 5 * x_size);
							glVertex3f(-6, 3, 0);

							glVertex3f(6, 3, 0);
							glVertex3f(6, 3, -5 * x_size);
							glVertex3f(-6, -3, -5 * x_size);
							glVertex3f(-6, -3, 0);

							glEnd();
						}

						
					}
					glPopMatrix();
					//���� ���׶��!!
				}
				glPopMatrix();
			}

			/*else if (wing_style == 2) {
				//���� ����!!!
				glPushMatrix();
				{
					SetColor(255, 255, 0);

					glTranslatef(-3 * x_size, 0, -10);
					//wing_angle = 0;
					Rotate_XYZ(0, wing_angle, 0);

					//�����Ѹ�!!!!
					glPushMatrix(); 
					{
						glTranslatef(0, y_size + y_size / 2, 0);

						glScalef(1, (float)1 / 5, 1);
						glutSolidSphere(10, 10, 10);
					}
					glPopMatrix();
					//��������!!
					glPushMatrix(); {
						glTranslatef(0, y_size + y_size / 2 - 5, 0);

						SetColor(100, 200, 0);

						glBegin(GL_QUADS); {


							glVertex3f(0, 3, 6);
							glVertex3f(2 * x_size, 3, 6);
							glVertex3f(2 * x_size, -3, -6);
							glVertex3f(0, -3, -6);

							glVertex3f(0, -3, 6);
							glVertex3f(-2 * x_size, -3, 6);
							glVertex3f(-2 * x_size, 3, -6);
							glVertex3f(0, 3, -6);

							glVertex3f(6, -3, 0);
							glVertex3f(6, -3, 2 * x_size);
							glVertex3f(-6, 3, 2 * x_size);
							glVertex3f(-6, 3, 0);

							glVertex3f(6, 3, 0);
							glVertex3f(6, 3, -2 * x_size);
							glVertex3f(-6, -3, -2 * x_size);
							glVertex3f(-6, -3, 0);

							glEnd();
						}

						glPopMatrix();
					}

					//���� ���׶��!!
					glPushMatrix(); {
						glTranslatef(0, y_size + y_size / 2 - 5, 0);

						SetColor(255, 0, 255);

						glBegin(GL_LINE_LOOP); {
							for (int j = 0; j < 20; j++) {
								for (float i = 0; i < 6.28; i += 0.01) {
									glVertex3d(2 * x_size * cos(i), j - 10, 2 * x_size * sin(i));
									glVertex3d(2 * x_size * cos(i + 1), j - 10, 2 * x_size * sin(i + 1));
								}
							}
							glEnd();
						}
						glPopMatrix();
					}

					glPopMatrix();
				}

				//���� ������!!
				glPushMatrix();
				{
					SetColor(255, 255, 0);

					glTranslatef(3 * x_size, 0, 0);

					Rotate_XYZ(0, wing_angle, 0);

					//�����Ѹ�!!!!
					glPushMatrix(); {
						glTranslatef(0, y_size + y_size / 2, 0);

						glScalef(1, (float)1 / 5, 1);
						glutSolidSphere(12, 10, 10);

						glPopMatrix();
					}

					//��������!!

					glPushMatrix(); {
						glTranslatef(0, y_size + y_size / 2 - 10, 0);

						SetColor(100, 200, 0);

						glBegin(GL_QUADS); {

							glVertex3f(0, 0, 6);
							glVertex3f(2 * x_size, 0, 6);
							glVertex3f(2 * x_size, 0, -6);
							glVertex3f(0, 0, -6);

							glVertex3f(0, 0, 6);
							glVertex3f(-2 * x_size, 0, 6);
							glVertex3f(-2 * x_size, 0, -6);
							glVertex3f(0, 0, -6);

							glVertex3f(6, 0, 0);
							glVertex3f(6, 0, 2 * x_size);
							glVertex3f(-6, 0, 2 * x_size);
							glVertex3f(-6, 0, 0);

							glVertex3f(6, 0, 0);
							glVertex3f(6, 0, -2 * x_size);
							glVertex3f(-6, 0, -2 * x_size);
							glVertex3f(-6, 0, 0);

							glEnd();
						}

						glPopMatrix();
					}

					//���� ���׶��!!
					glPushMatrix(); 
					{
						glTranslatef(0, y_size + y_size / 2 - 5, 0);

						SetColor(255, 0, 255);

						glBegin(GL_LINE_LOOP); {
							for (int j = 0; j < 20; j++) {
								for (float i = 0; i < 6.28; i += 0.01) {
									glVertex3d(2 * x_size * cos(i), j - 10, 2 * x_size * sin(i));
									glVertex3d(2 * x_size * cos(i + 1), j - 10, 2 * x_size * sin(i + 1));
								}
							}
							glEnd();
						}
						glPopMatrix();
					}
					

					glPopMatrix();
				}

				//���뿡�� ���� ��ġ�� ����

				glPushMatrix(); {
					glBegin(GL_QUADS); {

						glVertex3f(-2 * x_size, 0, -z_size + 10);
						glVertex3f(-3 * x_size, 0, z_size - 20);
						glVertex3f(-1 * x_size, 0, z_size - 20);
						glVertex3f(-1 * x_size, 0, -z_size + 10);


						glEnd();
					}
					glPopMatrix();
				}
			}*/
			
			SetColor(140, 140, 140);

			glPushMatrix();
			{
				//����
				glBegin(GL_QUADS); {
					//����
					{
						// ��
						glVertex3f(-x_size, y_size, z_size);
						glVertex3f(-x_size, y_size, -z_size);
						glVertex3f(x_size, y_size, -z_size);
						glVertex3f(x_size, y_size, z_size);
						
						
						//�Ʒ�
						glVertex3f(-x_size, -y_size, z_size);
						glVertex3f(-x_size, -y_size, -z_size);
						glVertex3f(x_size, -y_size, -z_size);
						glVertex3f(x_size, -y_size, z_size);
						
						// ��
						glVertex3f(-x_size, y_size, -z_size);
						glVertex3f(-x_size, -y_size, -z_size);
						glVertex3f(-x_size, -y_size, z_size);
						glVertex3f(-x_size, y_size, z_size);
						
						// ����
						glVertex3f(x_size, y_size, -z_size);
						glVertex3f(x_size, -y_size, -z_size);
						glVertex3f(x_size, -y_size, z_size);
						glVertex3f(x_size, y_size, z_size);

						//back
						glVertex3f(x_size, y_size, -z_size);
						glVertex3f(-x_size, y_size, -z_size);
						glVertex3f(-x_size, 0, z_size);
						glVertex3f(x_size, 0, z_size);
					}
					glEnd();
				}
			}
			glPopMatrix();

			//���� !!
			glPushMatrix();
			{
				glBegin(GL_QUADS); {

					{

						// ���� �Ʒ� ū ����

						SetColor(53, 53, 53);

						glVertex3f(-x_size * 2 / 3, 0,/*y_size,			  */	z_size);
						glVertex3f(-x_size * 2 / 3 + 12, -y_size / 2,/*y_size - 3/2*y_size,*/z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3 - 12, -y_size / 2,/*y_size - 3/2*y_size,*/z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3, 0,/*y_size,				*/	z_size);

						glVertex3f(-x_size * 2 / 3, -y_size, z_size);
						glVertex3f(-x_size * 2 / 3 + 12, -y_size, z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3 - 12, -y_size, z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3, -y_size, z_size);

						glVertex3f(-x_size * 2 / 3, -y_size, z_size);
						glVertex3f(-x_size * 2 / 3 + 12, -y_size, z_size + z_size * 2);
						glVertex3f(-x_size * 2 / 3 + 12, -y_size / 2 /*y_size - 3/2*y_size*/, z_size + z_size * 2);
						glVertex3f(-x_size * 2 / 3, 0 /*y_size*/, z_size);

						glVertex3f(x_size * 2 / 3, -y_size, z_size);
						glVertex3f(x_size * 2 / 3 - 12, -y_size, z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3 - 12, -y_size / 2/*y_size - 3/2*y_size*/, z_size + z_size * 2);
						glVertex3f(x_size * 2 / 3, 0/*y_size*/, z_size);

						// �߰� ���� ����
						SetColor(70, 70, 70);

						glVertex3f(-x_size * 1 / 2, y_size / 2,/*y_size,			  */	z_size);
						glVertex3f(-x_size * 1 / 2 + 12, 0,/*y_size - 3/2*y_size,*/z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2 - 12, 0,/*y_size - 3/2*y_size,*/z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2, y_size / 2,/*y_size,				*/	z_size);

						glVertex3f(-x_size * 1 / 2, y_size / 2 - y_size, z_size);
						glVertex3f(-x_size * 1 / 2 + 12, y_size / 2 - y_size, z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2 - 12, y_size / 2 - y_size, z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2, y_size / 2 - y_size, z_size);

						glVertex3f(-x_size * 1 / 2, y_size / 2 - y_size, z_size);
						glVertex3f(-x_size * 1 / 2 + 12, y_size / 2 - y_size, z_size + z_size * 3 / 2);
						glVertex3f(-x_size * 1 / 2 + 12, 0/*y_size - 3/2*y_size*/, z_size + z_size * 3 / 2);
						glVertex3f(-x_size * 1 / 2, y_size / 2/*y_size*/, z_size);

						glVertex3f(x_size * 1 / 2, y_size / 2 - y_size, z_size);
						glVertex3f(x_size * 1 / 2 - 12, y_size / 2 - y_size, z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2 - 12, 0/*y_size - 3/2*y_size*/, z_size + z_size * 3 / 2);
						glVertex3f(x_size * 1 / 2, y_size / 2/*y_size*/, z_size);
						//���� �ٱ�!
						//glVertex3f(-x_size + 25, y_size - 25, z_size + 20);
						//glVertex3f(-x_size + 25, y_size - 25, z_size + 70);
						//glVertex3f(x_size - 25, y_size - 25, z_size + 70);
						//glVertex3f(x_size - 25, y_size - 25, z_size + 20);

						//���� ��

						SetColor(35, 35, 35);

						glVertex3f(-x_size * 1, -y_size / 2 + 6, z_size + z_size * 7 / 4);
						glVertex3f(-x_size * 3 / 2, -y_size / 2 + 6, z_size + z_size * 8 / 4);
						glVertex3f(x_size * 3 / 2, -y_size / 2 + 6, z_size + z_size * 8 / 4);
						glVertex3f(x_size * 1, -y_size / 2 + 6, z_size + z_size * 7 / 4);

						glVertex3f(-x_size * 1, -y_size / 2, z_size + z_size * 7 / 4);
						glVertex3f(-x_size * 3 / 2, -y_size / 2, z_size + z_size * 8 / 4);
						glVertex3f(x_size * 3 / 2, -y_size / 2, z_size + z_size * 8 / 4);
						glVertex3f(x_size * 1, -y_size / 2, z_size + z_size * 7 / 4);

					}

					glEnd();
				}
			}
			glPopMatrix();


			
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

void CHelicopter::MovePosition(float x, float y, float z)
{
	Position = { x, y, z };
}

void CHelicopter::RotateWing(float speed)
{
	wing_angle += speed;
	if (wing_angle > 90)
		wing_angle -= 90;
}


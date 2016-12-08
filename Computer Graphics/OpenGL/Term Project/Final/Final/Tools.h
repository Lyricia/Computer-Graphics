#pragma once
#include <gl\glut.h>


void Rotate_XYZ(float x, float y, float z) {
	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 1, 0);
	glRotatef(z, 0, 0, 1);
}

void SetColor(float x, float y, float z) {
	glColor3f((float)(x / 255), (float)(y / 255), (float)(z / 255));
}
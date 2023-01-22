/*
 * Description: SimpleView - Camera.cpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"
#include <math.h>

bool DEBUG = false;

Matrix::Camera()
{
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Matrix::reset(void)
{
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Matrix::set(Point Eye, Point Look, Vector Up)
{
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Matrix::setViewNorm()
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat sr;
	x = ref.x - eye.x;
	y = ref.y - eye.y;
	z = ref.z - eye.z;
	sr = (x * x + y * y + z * z) ^ (1 / 2);
	x = x / sr;
	y = y / sr;
	z = z / sr;
	viewNorm.set(x, y, z);
}

void Matrix::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle)
{
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);

	GLfloat vector[4];
	vector[0] = eye.x;
	vector[1] = eye.y;
	vector[2] = eye.z;
	vector[3] = 1.0;
	m.multiplyVector(vector);
	eye.set(vector[0], vector[1], vector[2]);
}

void Matrix::translate(GLfloat tx, GLfloat ty, GLfloat tz)
{
	eye.set(eye.x + tx, eye.y + ty, eye.z + tz);
}

void Matrix::setProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, aspect, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x, viewup.y, viewup.z);
}

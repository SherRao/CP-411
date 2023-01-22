/*
 * Description: SimpleView - Light.cpp
 * Author: Nausher Rao
 * Version: 2022-11-09
 */
#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>

Light::Light()
{
	mc.mat[0][3] = 2.0;
	mc.mat[1][3] = 2.0;
	mc.mat[2][3] = 2.0;

	I = 1.0;
	Rd = 1.0;
	on = true;
	size = 0.2;
}

void Light::Reset()
{
	I = 1.0;
	Rd = 1.0;
	on = true;
	size = 30;
}

void Light::Increment(GLfloat p)
{
	I += p;
	if (I < 0.03)
		I = 0.01;
	else if (I > 0.97)
		I = 1;
}

void Light::draw()
{
	if (on == true)
	{
		glPushMatrix();
		this->ctmMultiply();
		glutSolidSphere(size, 10, 10);
		glPopMatrix();
	}
}

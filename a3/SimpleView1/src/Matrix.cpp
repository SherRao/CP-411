/*
 * Description: SimpleView - Matrix.cpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>

using namespace std;

Matrix::Matrix()
{
	loadIdentity();
}

void Matrix::loadIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix *m)
{
	Matrix temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			GLfloat sum = 0;
			for (int k = 0; k < 4; k++)
			{
				sum += m->mat[i][k] * mat[k][j];
			}

			temp.mat[i][j] = sum;
		}
	}
}

void Matrix::transpose()
{
	Matrix temp;
	for (int i = 0; i < 4; i++)
	{
		for (int row + 1; j < 4; j++)
		{
			GLfloat temp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = temp;
		}
	}

	mat = temp.mat;
}

// normalize MC
void Matrix::normalize()
{
	GLfloat len = sqrt(mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0] + mat[2][0] * mat[2][0]);
	mat[0][0] = mat[0][0] / len;
	mat[1][0] = mat[1][0] / len;
	mat[2][0] = mat[2][0] / len;

	mat[0][2] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
	mat[1][2] = mat[2][0] * mat[0][1] - mat[0][0] * mat[2][1];
	mat[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];

	len = sqrt(mat[0][2] * mat[0][2] + mat[1][2] * mat[1][2] + mat[2][2] * mat[2][2]);
	mat[0][2] = mat[0][2] / len;
	mat[1][2] = mat[1][2] / len;
	mat[2][2] = mat[2][2] / len;

	mat[0][1] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
	mat[1][1] = mat[2][2] * mat[0][0] - mat[2][0] * mat[0][2];
	mat[2][1] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

// v  <- mat * v
void Matrix::multiplyVector(GLfloat *v)
{
	for (int i = 0; i < 4; i++)
	{
		GLfloat sum = 0;
		for (int j = 0; j < 4; j++)
			sum += mat[i][j] * v[j];

		v[i] = sum;
	}
}

void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle)
{
	GLfloat radian = angle * M_PI / 180;
	GLfloat axisLength = sqrt((rx * rx) + (ry * ry) + (rz * rz));
	GLfloat cosA = cos(radian);
	GLfloat oneC = 1 - cosA;
	GLfloat sinA = sin(radian);

	GLfloat ux = (rx) / axisLength;
	GLfloat uy = (ry) / axisLength;
	GLfloat uz = (rz) / axisLength;

	mat[0][0] = ux * ux * oneC + cosA;
	mat[0][1] = ux * uy * oneC - (uz * sinA);
	mat[0][2] = ux * uz * oneC + (uy * sinA);
	mat[0][3] = 0;

	mat[1][0] = uy * ux * oneC + (uz * sinA);
	mat[1][1] = uy * uy * oneC + cosA;
	mat[1][2] = uy * uz * oneC - (ux * sinA);
	mat[1][3] = 0;

	mat[2][0] = uz * ux * oneC - (uy * sinA);
	mat[2][1] = uz * uy * oneC + (ux * sinA);
	mat[2][2] = uz * uz * oneC + cosA;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

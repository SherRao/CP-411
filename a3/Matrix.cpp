
#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>

using namespace std;

class Matrix
{
public:
	Matrix::Matrix()
	{
		loadIdentity();
	}

	void loadIdentity()
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
	void matrixPreMultiply(Matrix *m)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mul[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					mul[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}

	void transpose()
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
	void normalize()
	{
		// add code here
	}

	// v  <- mat * v
	void multiplyVector(GLfloat *v)
	{
		// add code here
	}

	void rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle)
	{
		// add code here
	}
};

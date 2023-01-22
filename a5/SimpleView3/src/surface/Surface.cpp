#include "Surface.hpp"

extern RenderMode renderMode;

Surface::Surface()
{
	reset();
}

void Surface::reset()
{
	row = 0;
	col = 0;
}

void Surface::drawSurface()
{

	switch (renderMode)
	{
	case WIRE:
		for (int j = 0; j < col - 1; j++)
		{
			for (int i = 0; i < row - 1; i++)
			{
				glBegin(GL_LINE_LOOP);
				glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z);
				glVertex3f(Pts[i + 1][j].x, Pts[i + 1][j].y, Pts[i + 1][j].z);
				glVertex3f(Pts[i + 1][j + 1].x, Pts[i + 1][j + 1].y, Pts[i + 1][j + 1].z);
				glVertex3f(Pts[i][j + 1].x, Pts[i][j + 1].y, Pts[i][j + 1].z);
				glEnd();
			}
		}
		break;

	case CONSTANT:
	case FLAT:
	case SMOOTH:
	case PHONE:
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);

		for (int i = 0; i < row - 1; i++)
		{
			glBegin(GL_QUAD_STRIP);
			for (int j = 0; j < col; j++)
			{
				glNormal3f(Normal[i][j].x, Normal[i][j].y, Normal[i][j].z);
				glVertex3f(Pts[i][j].x, Pts[i][j].y, Pts[i][j].z);
				glNormal3f(Normal[i + 1][j].x, Normal[i + 1][j].y, Normal[i + 1][j].z);
				glVertex3f(Pts[i + 1][j].x, Pts[i + 1][j].y, Pts[i + 1][j].z);
			}
			glEnd();
		}

		break;

	case TEXTURE:
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		glColor3f(0.5, 0, 0.5);

		for (int r = 0; r < row - 1; r++)
		{
			glBegin(GL_QUAD_STRIP);
			for (int c = 0; c < col; c++)
			{
				glNormal3f(Normal[r][c].x, Normal[r][c].y, Normal[r][c].z);
				glVertex3f(Pts[r][c].x, Pts[r][c].y, Pts[r][c].z);
				glNormal3f(Normal[r + 1][c].x, Normal[r + 1][c].y, Normal[r + 1][c].z);
				glVertex3f(Pts[r + 1][c].x, Pts[r + 1][c].y, Pts[r + 1][c].z);
			}
			glEnd();
		}
		break;
	}
}

void Surface::draw()
{
	glPushMatrix();
	ctmMultiply();
	glScalef(s * 0.01, s * 0.01, s * 0.01); // to shrink the object to size of viewable
	drawSurface();
	glPopMatrix();
}

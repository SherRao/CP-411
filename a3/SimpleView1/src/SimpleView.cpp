/*
 * Description: SimpleView - SimpleView.cpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"

GLint winWidth = 800;
GLint winHeight = 800;
GLint isInMove = 0;
GLint xbegin = 0;
GLint csType = 1;
GLint transType = 4;

Shape *selectObj = NULL;
World myWorld;
Camera myCamera;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();

	myWorld.draw();
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isInMove = 1;
		xbegin = xMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isInMove = 0;
	}
}

void mouseMotionFcn(GLint xMouse, GLint yMouse)
{
	if (isInMove)
	{
		if (csType == 1)
		{ //  Model transformations
			MCSTransform(xMouse);
		}
		else if (csType == 2)
		{ // WCS transformations
			WCSTransform(xMouse);
		}
		else if (csType == 3)
		{ // VCS transformations
			VCSTransform(xMouse);
		}
		glutPostRedisplay();
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleView1 (Your name)");
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

/*
 * Description: SimpleView - Pyramid.cpp
 * Author: Nausher Rao
 * Version: 2022-11-23
 */
#include "Pyramid.hpp"
#include "Vector.hpp"

extern Camera myCamera;
extern Light myLight;
extern bool isShading;
extern CullMode cullMode;
extern RenderMode renderMode;

Pyramid::Pyramid()
{

	vertex[0][0] = -1;
	vertex[0][1] = -1;
	vertex[0][2] = 0;
	vertex[1][0] = 1;
	vertex[1][1] = -1;
	vertex[1][2] = 0;
	vertex[2][0] = 1;
	vertex[2][1] = 1;
	vertex[2][2] = 0;
	vertex[3][0] = -1;
	vertex[3][1] = 1;
	vertex[3][2] = 0;
	vertex[4][0] = 0;
	vertex[4][1] = 0.0;
	vertex[4][2] = 1.5;

	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 4;
	face[1][0] = 1;
	face[1][1] = 2;
	face[1][2] = 4;
	face[2][0] = 2;
	face[2][1] = 3;
	face[2][2] = 4;
	face[3][0] = 3;
	face[3][1] = 0;
	face[3][2] = 4;

	faceColor[0][0] = 0.0;
	faceColor[0][1] = 1.0;
	faceColor[0][2] = 1.0;
	faceColor[1][0] = 0.0;
	faceColor[1][1] = 1.0;
	faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0;
	faceColor[2][1] = 0.0;
	faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0;
	faceColor[3][1] = 1.0;
	faceColor[3][2] = 0.0;

	for (int i = 0; i < 4; i++)
	{
		Vector V1 = Vector(vertex[face[i][1]][0] - vertex[face[i][0]][0], vertex[face[i][1]][1] - vertex[face[i][0]][1], vertex[face[i][1]][2] - vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0] - vertex[face[i][1]][0], vertex[face[i][2]][1] - vertex[face[i][1]][1], vertex[face[i][2]][2] - vertex[face[i][1]][2]);
		faceNormal[i] = V1.cross(V2);
		faceNormal[i].normalize();
	}

	vertexColor[0][0] = 1.0, vertexColor[0][1] = 0.0;
	vertexColor[0][2] = 0.0;
	vertexColor[1][0] = 0.0, vertexColor[1][1] = 1.0;
	vertexColor[1][2] = 0.0;
	vertexColor[2][0] = 0.0, vertexColor[2][1] = 0.0;
	vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0;
	vertexColor[3][2] = 0.0;
	vertexColor[4][0] = 1.0, vertexColor[4][1] = 0.0;
	vertexColor[4][2] = 1.0;

	vertexNormal[0][0] = -1;
	vertexNormal[0][1] = -1;
	vertexNormal[0][2] = 0;
	vertexNormal[1][0] = 1;
	vertexNormal[1][1] = -1;
	vertexNormal[1][2] = 0;
	vertexNormal[2][0] = 1;
	vertexNormal[2][1] = 1;
	vertexNormal[2][2] = 0;
	vertexNormal[3][0] = -1;
	vertexNormal[3][1] = 1;
	vertexNormal[3][2] = 0;
	vertexNormal[4][0] = 0;
	vertexNormal[4][1] = 0;
	vertexNormal[4][2] = 1.5;

	r = 1.0;
	g = 1.0;
	b = 0;
}

void Pyramid::drawFace(GLint i)
{
	GLfloat shade = 1;
	switch (renderMode)
	{
	case WIRE:
		glColor3f(r, g, b);
		glBegin(GL_LINE_LOOP);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glEnd();
		break;
	case CONSTANT:
		if (myLight.on == true)
			shade = getFaceShade(i, myLight);
		glColor3f(faceColor[i][0] * shade, faceColor[i][1] * shade, faceColor[i][2] * shade);
		glBegin(GL_POLYGON);
		glVertex3fv(vertex[face[i][0]]);
		glVertex3fv(vertex[face[i][1]]);
		glVertex3fv(vertex[face[i][2]]);
		glEnd();
		break;
	case FLAT:
	case SMOOTH:
	case TEXTURE:
		break;
	}
}

void Pyramid::draw()
{
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	for (int i = 0; i < 4; i++)
	{
		if (cullMode == BACKFACE)
		{
			if (isFrontface(i, myCamera))
			{
				drawFace(i);
			}
		}
		else
		{
			drawFace(i);
		}
	}
	glPopMatrix();
}

bool Pyramid::isFrontface(int faceindex, Camera camera)
{
	GLfloat v[4];
	v[0] = faceNormal[faceindex].x;
	v[1] = faceNormal[faceindex].y;
	v[2] = faceNormal[faceindex].z;
	v[3] = 0.0;
	mc.multiplyVector(v);
	if (pmc != NULL)
	{
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0] + (pmc->mat[1][3] - camera.eye.y) * v[1] + (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	}
	else
	{
		return (mc.mat[0][3] - camera.eye.x) * v[0] + (mc.mat[1][3] - camera.eye.y) * v[1] + (mc.mat[2][3] - camera.eye.z) * v[2] < 0;
	}
}

GLfloat Pyramid::getFaceShade(int faceindex, Light light)
{
	GLfloat shade = 1;
	return shade;
}

GLfloat Pyramid::getVertexShade(int i, Light light)
{
	GLfloat shade = 1;
	return shade;
}

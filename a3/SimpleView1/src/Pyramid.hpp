/*
 * Description: SimpleView - Pyramid.hpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid : public Shape
{

protected:
	GLfloat vertex[5][3]; /* 2D array to store cube vertices */
	GLint face[5][4];	  /* 2D array to store faces */
	GLfloat r, g, b;	  /* colour of pyramid */

public:
	Pyramid();
	void draw();
	void drawFace(int);
};

#endif

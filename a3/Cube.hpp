/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];  /* 2D array to store cube vertices */
	GLint face[6][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */
public:
	Cube();
	void draw();
	void drawFace(int);
};

#endif

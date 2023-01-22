/*
 * Description: SimpleView - Pyramid.hpp
 * Author: Nausher Rao
 * Version: 2022-11-09
 */
#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Pyramid : public Shape
{
protected:
	GLfloat vertex[5][3];
	GLint face[4][4];
	GLfloat r, g, b;

public:
	Pyramid();
	void draw();
	void drawMC();

private:
	void drawFace(GLint i);
};

#endif /* PYRAMID_HPP_ */

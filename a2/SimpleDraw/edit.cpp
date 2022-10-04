#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "object.hpp"

extern List objects;

GLint min(GLint x, GLint y)
{
	return x < y ? x : y;
}

GLint max(GLint x, GLint y)
{
	if (x < y)
		return y;
	else
		return x;
}

Node *select(GLint x, GLint y)
{
	// your implementation
	// search the object that cover the clicking point staring

	return NULL;
}

void remove(Node **pp)
{
	// your implementation
}

void moveFront(Node *p)
{
	// your implementation
}

void moveBack(Node *p)
{
	// your implementation
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"

void insert(List *list, Shape *object)
{
	// ...
}

void deleteNode(List *list, Node **selectp)
{
	// ...
}

void clearList(List *list)
{
	// ...
}

void drawShape(Shape *object)
{
	if (object->type == RECTANGLE)
	{ // rectangle
	  // draw filled rectangle
	  // draw outline
	}
	else if (object->type == CIRCLE)
	{ // circle
	  // draw filled circle
	  // draw outline
	}
}

void drawShapeHighLight(Shape *object)
{
	// draw outline with high light color
}

void drawList(List *list)
{
	Node *p = list->start;
	while (p)
	{
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y)
{
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint &xc, const GLint &yc, const GLint &x,
					  const GLint &y)
{
	// ...
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2)
{
	// ...
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y)
{
	// ...
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2)
{
	// ...
}

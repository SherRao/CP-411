#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"

void insert(List *list, Shape *object)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->object = object;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (list->start == NULL)
	{
		list->start = newNode;
		list->end = newNode;
	}
	else
	{
		list->end->next = newNode;
		newNode->prev = list->end;
		list->end = newNode;
	}
}

void deleteNode(List *list, Node **selectp)
{
	Node *temp = *selectp;
	if (temp == NULL)
	{
		return;
	}
	if (temp->prev == NULL && temp->next == NULL)
	{
		list->start = NULL;
		list->end = NULL;
	}
	else if (temp->prev == NULL)
	{
		list->start = temp->next;
		temp->next->prev = NULL;
	}
	else if (temp->next == NULL)
	{
		list->end = temp->prev;
		temp->prev->next = NULL;
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	*selectp = NULL;
	free(temp);
}

void clearList(List *list)
{
	Node *temp = list->start;
	while (temp != NULL)
	{
		Node *next = temp->next;
		free(temp);
		temp = next;
	}
	list->start = NULL;
	list->end = NULL;
}

void drawShape(Shape *object)
{
	if (object->type == RECTANGLE)
	{
		glBegin(GL_QUADS);
		glColor3f(object->fillR, object->fillG, object->fillB);
		glVertex2f(object->x1, object->y1);
		glVertex2f(object->x2, object->y2);
		glVertex2f(object->x2, object->y2);
		glVertex2f(object->x1, object->y2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(object->strokeR, object->strokeG, object->strokeB);
		glLineWidth(object->strokeW);
		glVertex2f(object->x1, object->y1);
		glVertex2f(object->x2, object->y1);
		glVertex2f(object->x2, object->y2);
		glVertex2f(object->x1, object->y2);
		glEnd();
	}
	else if (object->type == CIRCLE)
	{
		glColor3f(object->fillR, object->fillG, object->fillB);
		circleMidpointFill(object->x1, object->y1, object->x2, object->y2);
		glColor3f(object->strokeR, object->strokeG, object->strokeB);
		circleMidpoint(object->x1, object->y1, object->x2, object->y2);
	}
}

void drawShapeHighLight(Shape *object)
{
	if (object->type == RECTANGLE)
	{
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(object->x1, object->y1);
		glVertex2f(object->x2, object->y1);
		glVertex2f(object->x2, object->y2);
		glVertex2f(object->x1, object->y2);
		glEnd();
	}

	else if (object->type == CIRCLE)
	{
		glColor3f(1.0, 1.0, 0.0);
		circleMidpoint(object->x1, object->y1, object->x2, object->y2);
	}
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

void circlePlotPoints(const GLint &xc, const GLint &yc, const GLint &x,
					  const GLint &y)
{
	setPixel(xc + x, yc + y);
	setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc - x);
}

void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2)
{
	GLint xc = x1;
	GLint yc = y1;
	GLint r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	GLint p = 1 - r;
	GLint x = 0;
	GLint y = r;
	circlePlotPoints(xc, yc, x, y);
	while (x < y)
	{
		x++;
		if (p < 0)
			p += 2 * x + 1;

		else
		{
			y--;
			p += 2 * (x - y) + 1;
		}

		circlePlotPoints(xc, yc, x, y);
	}
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y)
{
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(x1 + x, y1 + y);
	glVertex2i(x1 - x, y1 + y);
	glVertex2i(x1 + x, y1 - y);
	glVertex2i(x1 - x, y1 - y);
	glVertex2i(x1 + y, y1 + x);
	glVertex2i(x1 - y, y1 + x);
	glVertex2i(x1 + y, y1 - x);
	glVertex2i(x1 - y, y1 - x);
	glEnd();
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2)
{
	GLint xc = x1;
	GLint yc = y1;
	GLint r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	GLint p = 1 - r;
	GLint x = 0;
	GLint y = r;
	circlePlotPointsFill(xc, yc, x, y);
	while (x < y)
	{
		x++;
		if (p < 0)
			p += 2 * x + 1;

		else
		{
			y--;
			p += 2 * (x - y) + 1;
		}

		circlePlotPointsFill(xc, yc, x, y);
	}
}

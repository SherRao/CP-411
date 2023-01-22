#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
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
	Node *curr = objects.end;
	GLboolean found = GL_FALSE;
	while (curr && found == GL_FALSE)
	{
		if (curr->object->type == 1 && min(curr->object->x1, curr->object->x2) < x &&
			min(curr->object->y1, curr->object->y2) < y && max(curr->object->x1, curr->object->x2) > x &&
			max(curr->object->y1, curr->object->y2) > y)
		{
			found = GL_TRUE;
		}
		else if (curr->object->type == 2)
		{
			GLint rx = (GLint)pow(curr->object->x2 - curr->object->x1, 2);
			GLint ry = (GLint)pow(curr->object->y2 - curr->object->y1, 2);
			GLint r = rx + ry;
			if (r > pow(x - curr->object->x1, 2) + pow(y - curr->object->y1, 2))
			{
				found = GL_TRUE;
			}
		}

		if (found == GL_TRUE)
		{
			curr = curr->prev;
		}
	}

	return curr;
}

void remove(Node **pp)
{
	deleteNode(&objects, pp);
}

void moveFront(Node *pointer)
{
	if (pointer == NULL)
		return;

	if (objects.end == NULL)
		return;

	Node *prev = NULL;
	Node *curr = pointer;
	Node *next = NULL;
	if (objects.start == curr)
	{
		next = pointer->next;
		next->prev = NULL;
		objects.start = next;
	}
	else
	{
		prev = curr->prev;
		prev->next = curr->next;
		next = curr->next;
		next->prev = prev;
	}

	curr->prev = objects.end;
	curr->next = NULL;
	objects.end->next = curr;
	objects.end = curr;
}

void moveBack(Node *pointer)
{
	if (pointer == NULL)
		return;

	if (objects.end == NULL)
		return;

	Node *prev = NULL;
	Node *curr = pointer;
	Node *next = NULL;
	if (objects.start == curr)
	{
		return;
	}
	else if (objects.end == curr)
	{
		prev = curr->prev;
		prev->next = NULL;
		objects.end = prev;
	}
	else
	{
		prev = curr->prev;
		prev->next = curr->next;
		next = curr->next;
		next->prev = prev;
	}

	curr->next = objects.start;
	curr->prev = NULL;
	objects.start->prev = curr;
	objects.start = curr;
}

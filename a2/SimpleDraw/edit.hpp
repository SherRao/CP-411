#ifndef EDIT_HPP_
#define EDIT_HPP_

#include <GL/glut.h>

extern int selected;
extern int selection;

GLint min(GLint x, GLint y);

GLint max(GLint x, GLint y);

Node *select(GLint x, GLint y);

void remove(Node **pp);

void moveFront(Node *p);

void moveBack(Node *p);

void moveAround(Node *p);

#endif /* EDIT_HPP_ */

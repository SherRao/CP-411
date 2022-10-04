#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <GL/gl.h>

typedef enum shapeType
{
	RECTANGLE = 1,
	CIRCLE
} ShapeType;

/**
 * Represents a shape on screen, with a type, fill color, stroke color, stroke
 * width, and coordinates.
 */
typedef struct shape
{
	ShapeType type;
	int x1;
	int y1;
	int x2; // Used as radius for circles.
	int y2; // Unused for circles.

	GLfloat fillR;
	GLfloat fillG;
	GLfloat fillB;

	GLfloat strokeR;
	GLfloat strokeG;
	GLfloat strokeB;
	GLint strokeW;
} Shape;

/**
 * Represents a Node within a doubly-linked list. Each node contains a pointer to
 * the next node in the list, a pointer to the previous node in the list, and a
 * pointer to the data contained within the node.
 */
typedef struct node
{
	Shape *object;
	Node *prev;
	Node *next;
} Node;

/**
 * Represents a doubly-linked list. Each list contains a pointer to the first
 * node in the lis and a pointer to the last node in the list.
 */
typedef struct list
{
	Node *start;
	Node *end;
} List;

/**
 * Inserts a new node into the list, containing the given data.
 *
 * @param list The list to insert the node into.
 * @param data The data to insert into the list.
 */
void insert(List *list, Shape *object);

/**
 * Removes the given node from the list.
 *
 * @param list The list to remove the node from.
 * @param node The node to remove from the list.
 */
void deleteNode(List *list, Node **selectp);

/**
 * Removes all nodes from the list.
 *
 * @param list The list to clear.
 */
void clearList(List *list);

void drawShape(Shape *object);
void drawShapeHighLight(Shape *object);
void drawList(List *list);

void setPixel(GLint x, GLint y);
void circlePlotPoints(const GLint &xc, const GLint &yc, const GLint &x, const GLint &y);
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2);
void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y);
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2);
void plotObject(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat r1, GLfloat g1, GLfloat b1, GLint t1, GLint s1);

#endif

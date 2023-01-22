#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <GL/gl.h>

typedef enum shapeType
{
	RECTANGLE = 1,
	CIRCLE = 2
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
	node *prev;
	node *next;
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

/**
 * Draws the given shape to the screen.
 *
 * @param object The shape to draw.
 */
void drawShape(Shape *object);

/**
 * Draws all shapes in the given list to the screen.
 *
 * @param list The list of shapes to draw.
 */
void drawShapeHighLight(Shape *object);

/**
 * Draws all shapes in the given list to the screen.
 *
 * @param list The list of shapes to draw.
 */
void drawList(List *list);

/**
 * Sets the pixel at the given coordinates to the given color.
 */
void setPixel(GLint x, GLint y);

/**
 * Draws the important points of the given circle to the screen.
 *
 * @param xc The x-coordinate of the center of the circle.
 * @param yc The y-coordinate of the center of the circle.
 * @param x The x-coordinate of the point to draw.
 * @param y The y-coordinate of the point to draw.
 */
void circlePlotPoints(const GLint &xc, const GLint &yc, const GLint &x, const GLint &y);

/**
 * Draws a circle to the screen using the midpoint circle algorithm.
 *
 * @param x1 The x-coordinate of a point on the circle.
 * @param y1 The y-coordinate of a point on the circle.
 * @param x2 The x-coordinate of another point on the circle.
 * @param y2 The y-coordinate of another point on the circle.
 */
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2);

/**
 * Draws the important points of the given circle to the screen with fill.
 *
 * @param xc The x-coordinate of the center of the circle.
 * @param yc The y-coordinate of the center of the circle.
 * @param x The x-coordinate of the point to draw.
 * @param y The y-coordinate of the point to draw.
 */
void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y);

/**
 * Draws a circle to the screen using the midpoint circle algorithm with fill.
 *
 * @param x1 The x-coordinate of a point on the circle.
 * @param y1 The y-coordinate of a point on the circle.
 * @param x2 The x-coordinate of another point on the circle.
 * @param y2 The y-coordinate of another point on the circle.
 */
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2);
#endif

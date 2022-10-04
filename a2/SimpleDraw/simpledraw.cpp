#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "object.hpp"
#include "menu.hpp"
#include "edit.hpp"
#include "file.hpp"

GLsizei width = 800;
GLsizei height = 600;

// State data
GLint operationMode;
GLboolean inDrawMode;
GLboolean isMenuOpen;
GLboolean inMoveMode;
GLint xbegin; // Beginning x coordinate point of translate vector for moving
GLint ybegin; // Beginning y coordinate point of translate vector for moving

// Object data
ShapeType shapeType = RECTANGLE;
GLfloat fillR = 1.0;
GLfloat fillG = 0.0;
GLfloat fillB = 0.0;
GLfloat strokeR = 1.0;
GLfloat strokeG = 0.0;
GLfloat strokeB = 0.0;
GLint strokeW = 1;

List objects = {0};	 // object list and initialization
Node *selectedShape; // pointing to selected node
Shape tempShape;	 // variable to store temp object data when drawing.

/**
 * Called when the program is being created - initializes the state and sets up
 * the window.
 */
void init(void)
{
	glutInitDisplayMode(GLUT_DOUBLE); // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("SimpleDraw (Nausher Rao)");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, width, height, 0.0); // Set top left as origin
}

/**
 * Called everytime the list of objects is changed - redraws the screen.
 */
void drawObjectList()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (objects.start != NULL)
		drawList(&objects);

	// Draw temp object when dragging an object
	if (operationMode == 0 && inDrawMode == GL_TRUE)
		drawShape(&tempShape);

	// Draw the highlight of selected object in edit mode
	if (operationMode == 1 && inMoveMode == GL_FALSE && selectedShape != NULL)
		drawShapeHighLight(selectedShape->object);

	glFlush();
	glutSwapBuffers();
}

/**
 * Called by OpenGL when the mouse has an action occur, such as a click or release.
 */
void onMouseAction(GLint button, GLint action, GLint xMouse, GLint yMouse)
{

	if (operationMode == 0 && isMenuOpen == GL_FALSE)
	{
		if (button == GLUT_LEFT_BUTTON)
		{

			// Drawing mode
			if (action == GLUT_DOWN)
			{
				tempShape.type = shapeType;
				tempShape.fillR = fillR;
				tempShape.fillG = fillG;
				tempShape.fillB = fillB;
				tempShape.strokeR = strokeR;
				tempShape.strokeG = strokeG;
				tempShape.strokeB = strokeB;
				tempShape.strokeW = strokeW;

				tempShape.x1 = xMouse;
				tempShape.y1 = yMouse;

				inDrawMode = GL_TRUE; // start dragging
				if (shapeType == RECTANGLE)
				{
					tempShape.x2 = xMouse;
					tempShape.y2 = yMouse;
				}
				else if (shapeType == CIRCLE)
				{
					tempShape.x2 = abs(xMouse - tempShape.x1);
				}
			}
			else if (action == GLUT_UP && inDrawMode == GL_TRUE)
			{

				inDrawMode = GL_FALSE; // end of dragging
				if (shapeType == RECTANGLE)
				{
					tempShape.x2 = xMouse;
					tempShape.y2 = yMouse;
				}
				else if (shapeType == CIRCLE)
				{
					tempShape.x2 = abs(xMouse - tempShape.x1);
				}

				// create a new shape object, copy the tempObj values to the new object,
				// and the new object to the object list
				Shape *newShape = (Shape *)malloc(sizeof(Shape));
				*newShape = tempShape;
				insert(&objects, newShape);
			}
		}
	}

	// Select mode
	else if (inMoveMode == GL_FALSE)
	{
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		{
			selectedShape = select(xMouse, yMouse);
		}
	}

	// Edit move mode
	else if (inMoveMode == GL_TRUE)
	{
		if (button == GLUT_LEFT_BUTTON)
		{

			if (action == GLUT_DOWN)
			{
				// select node and copy the select node data to temp node for drawing
				// set mouse postion to xbegin, and ybegin
				selectedShape = select(xMouse, yMouse);
				if (selectedShape != NULL)
				{
					xbegin = xMouse;
					ybegin = yMouse;
				}
			}
			else if (action == GLUT_UP)
			{
				// get the vector from (xbegin, ybegin) to the new mouse position
				// use the vector to update the properties of moving object.
			}
		}
	}

	glutPostRedisplay();
	glFlush();
}

/**
 * Called by OpenGL when the mouse is moved.
 */
void onMouseMove(GLint xMouse, GLint yMouse)
{
	// in drawing mode, use xMouse and yMouse value to update the tempObj
	// in edit move mode, use (xbegin, ybegin) and (xMouse, yMouse) to update the selected object

	glutPostRedisplay();
	glFlush();
}

/**
 * Called by OpenGL when the window is resized. Updates the viewport and project matrix.
 */
void onResize(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);

	width = newWidth;
	height = newHeight;

	drawObjectList();
}

/**
 * Main entry function that sets up the OpenGL context, registers callbacks, and starts the main loop.
 */
int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging
	setvbuf(stderr, NULL, _IONBF, 0);

	glutInit(&argc, argv);
	addMenu();
	init();
	glutDisplayFunc(drawObjectList);
	glutReshapeFunc(onResize);
	glutMouseFunc(onMouseAction);
	glutMotionFunc(onMouseMove);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

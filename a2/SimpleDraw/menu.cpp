#include <GL/glut.h>
#include "menu.hpp"
#include "object.hpp"
#include "edit.hpp"
#include "file.hpp"

extern List objects;
extern GLsizei height, width;

extern GLint operationMode;
extern GLboolean inDrawMode;
extern GLboolean isMenuOpen;
extern GLboolean inMoveMode;
extern ShapeType shapeType;

extern Node *selectedShape;
extern GLint strokeW;
extern GLfloat fillR;
extern GLfloat fillG;
extern GLfloat fillB;
extern GLfloat strokeR;
extern GLfloat strokeG;
extern GLfloat strokeB;

void createContextMenu()
{
	// Menu -> Draw
	GLint drawSubMenuId = glutCreateMenu(processDrawSubMenu);
	glutAddMenuEntry("Rectangle", 0);
	glutAddMenuEntry("Circle", 1);

	// Menu -> Style -> Fill Color
	GLint styleFillColorSubMenuId = glutCreateMenu(processStyleFillColorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("Cyan", 7);

	// Menu -> Style -> Stroke Color
	GLint styleStrokeColorSubMenuId = glutCreateMenu(processStyleStrokeColorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("Cyan", 7);

	// Menu -> Style -> Stroke Width
	GLint styleStrokeWidthSubMenuId = glutCreateMenu(processStyleStrokeWidthSubMenu);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);

	// Menu -> Style
	GLint styleSubMenuId = glutCreateMenu(processStyleSubMenu);
	glutAddSubMenu("Fill Color", styleFillColorSubMenuId);
	glutAddSubMenu("Stroke Color", styleStrokeColorSubMenuId);
	glutAddSubMenu("Stroke Width", styleStrokeWidthSubMenuId);

	// Menu -> Edit
	GLint editSubMenuId = glutCreateMenu(processEditSubMenu);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Delete", 2);
	glutAddMenuEntry("Move front", 3);
	glutAddMenuEntry("Move back", 4);
	glutAddMenuEntry("Move around", 5);

	// Menu -> File
	GLint fileSubMenuId = glutCreateMenu(processFileSubMenu);
	glutAddMenuEntry("Save SVG", 1);
	glutAddMenuEntry("Open SVG", 2);
	glutAddMenuEntry("Export Bitmap", 3);

	// Menu
	GLint menuId = glutCreateMenu(processMenu);
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawSubMenuId);
	glutAddSubMenu("Style", styleSubMenuId);
	glutAddSubMenu("Edit", editSubMenuId);
	glutAddSubMenu("File", fileSubMenuId);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void clear()
{
	// ...
}

void processMenu(GLint menuOption)
{
	isMenuOpen = GL_TRUE;
	switch (menuOption)
	{
	case 1:
		clear();
		break;

	case 2:
		exit(0);
	}

	isMenuOpen = GL_FALSE;
	glutPostRedisplay();
}

void processDrawSubMenu(GLint typeOption)
{
	operationMode = 0;
	inMoveMode = GL_FALSE;
	//
}

void processFileSubMenu(GLint fileOption)
{
	// ..
}

void processEditSubMenu(GLint editOption)
{
	operationMode = 1;
	inMoveMode = 0;
	// ...
	glutPostRedisplay();
}

void processStyleSubMenu(GLint styleOption)
{
}

void processStyleFillColorSubMenu(GLint colorOption)
{
	// ...
}

void processStyleStrokeColorSubMenu(GLint colorOption)
{
	// ...
}

void processStyleStrokeWidthSubMenu(GLint width)
{
	// ....
}

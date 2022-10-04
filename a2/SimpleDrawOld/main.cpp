/*
 * Description: Example from textbook chapter 20, GUI menu
 * Compile: g++ opengl_menu.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
 */
#include <stdio.h>
#include <GL/glut.h>
#include "shape.cpp"
#include "list.cpp"

GLsizei width = 800;
GLsizei height = 600;
ShapeType type;
GLint fillR;
GLint fillG;
GLint fillB;
GLint strokeR;
GLint strokeG;
GLint strokeB;
GLint strokeW;

// FL_FALSE for circle
List<Shape> shapes;
Shape *activeShape;

void printState()
{
    printf("====================================\n");
    if (activeShape == NULL)
    {
        printf("No shape in the list\n");
        printf("====================================\n\n");
        return;
    }

    printf("shapetype: %s\n", activeShape->type == RECTANGLE ? "rect" : "circ");
    printf("fill: (%d, %d, %d)\n", activeShape->fillR, activeShape->fillG, activeShape->fillB);
    printf("stroke: (%d, %d, %d)\n", activeShape->strokeR, activeShape->strokeG, activeShape->strokeB);
    printf("strokeW: %d\n", activeShape->strokeW);
    printf("====================================\n\n");
}

void init(void)
{
    glClearColor(0.6, 0.6, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);

    shapes = List<Shape>();
    activeShape = NULL;

    type = RECTANGLE;
    fillR = 0;
    fillG = 0;
    fillB = 0;
    strokeR = 0;
    strokeG = 0;
    strokeB = 0;
    strokeW = 0;
}

void resizeWindow(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, newWidth, 0.0, newHeight);
    glFlush();
}

void onMouseAction(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if (button != GLUT_LEFT_BUTTON)
        return;

    if (action == GLUT_DOWN)
    {
    }
    ekse if (action == GLUT_UP)
    {
    }

    if (action == GLUT_DOWN && button != GLUT_RIGHT_BUTTON && numObj < MaxNumObj - 1)
    {
        list[numObj].x1 = xMouse;
        list[numObj].y1 = yMouse;
        list[numObj].x2 = xMouse;
        list[numObj].y2 = yMouse;
        list[numObj].t = type;
        list[numObj].s = 2;
        list[numObj].r = red;
        list[numObj].g = green;
        list[numObj].b = blue;
        glutPostRedisplay();
    }
    else if (action == GLUT_UP && button != GLUT_RIGHT_BUTTON)
    {
        list[numObj].x2 = xMouse;
        list[numObj].y2 = yMouse;
        list[numObj].s = style;
        numObj++;
        glutPostRedisplay();
    }
}

void processMenu(GLint option)
{
    if (option == 0)
    {
        init();
    }
    else
        exit(0);
}

void processDrawSubMenu(GLint option)
{
    if (activeShape == NULL)
        return;

    activeShape->type = (option == 0) ? RECTANGLE : CIRCLE;
    printState();
}

void processStyleFillColorSubMenu(GLint option)
{
    if (activeShape == NULL)
        return;

    switch (option)
    {
    case 0:
        activeShape->fillR = 255;
        activeShape->fillG = 0;
        activeShape->fillB = 0;
        break;

    case 1:
        activeShape->fillR = 0;
        activeShape->fillG = 255;
        activeShape->fillB = 0;
        break;

    case 2:
        activeShape->fillR = 0;
        activeShape->fillG = 0;
        activeShape->fillB = 255;
        break;

    case 3:
        activeShape->fillR = 255;
        activeShape->fillG = 255;
        activeShape->fillB = 0;
        break;

    case 4:
        activeShape->fillR = 255;
        activeShape->fillG = 0;
        activeShape->fillB = 255;
        break;

    case 5:
        activeShape->fillR = 0;
        activeShape->fillG = 255;
        activeShape->fillB = 255;
        break;

    case 6:
        activeShape->fillR = 255;
        activeShape->fillG = 255;
        activeShape->fillB = 255;
        break;
    }

    printState();
}

void processStyleStrokeColorSubMenu(GLint option)
{
    if (activeShape == NULL)
        return;

    switch (option)
    {
    case 0:
        activeShape->strokeR = 255;
        activeShape->strokeG = 0;
        activeShape->strokeB = 0;
        break;

    case 1:
        activeShape->strokeR = 0;
        activeShape->strokeG = 255;
        activeShape->strokeB = 0;
        break;

    case 2:
        activeShape->strokeR = 0;
        activeShape->strokeG = 0;
        activeShape->strokeB = 255;
        break;

    case 3:
        activeShape->strokeR = 255;
        activeShape->strokeG = 255;
        activeShape->strokeB = 0;
        break;

    case 4:
        activeShape->strokeR = 255;
        activeShape->strokeG = 0;
        activeShape->strokeB = 255;
        break;

    case 5:
        activeShape->strokeR = 0;
        activeShape->strokeG = 255;
        activeShape->strokeB = 255;
        break;

    case 6:
        activeShape->strokeR = 255;
        activeShape->strokeG = 255;
        activeShape->strokeB = 255;
        break;
    }

    printState();
}

void processStyleStrokeWidthSubMenu(GLint option)
{
    if (activeShape == NULL)
        return;

    activeShape->strokeW = option + 1;
    printState();
}

void processStyleSubMenu(GLint option) {}

void processEditSubMenu(GLint option) {}

void processFileSubMenu(GLint option) {}

void createContextMenu()
{
    // Menu -> Draw
    GLint drawSubMenu = glutCreateMenu(processDrawSubMenu);
    glutAddMenuEntry("Rectangle", 0);
    glutAddMenuEntry("Circle", 1);

    // Menu -> Style -> Fill Color
    GLint styleFillColorSubMenu = glutCreateMenu(processStyleFillColorSubMenu);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Black", 3);
    glutAddMenuEntry("White", 4);
    glutAddMenuEntry("Yellow", 5);
    glutAddMenuEntry("Cyan", 6);

    // Menu -> Style -> Stroke Color
    GLint styleStrokeColorSubMenu = glutCreateMenu(processStyleStrokeColorSubMenu);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Black", 3);
    glutAddMenuEntry("White", 4);
    glutAddMenuEntry("Yellow", 5);
    glutAddMenuEntry("Cyan", 6);

    // Menu -> Style -> Stroke Width
    GLint styleStrokeWidthSubMenu = glutCreateMenu(processStyleStrokeWidthSubMenu);
    glutAddMenuEntry("1", 0);
    glutAddMenuEntry("2", 1);
    glutAddMenuEntry("3", 2);
    glutAddMenuEntry("4", 3);
    glutAddMenuEntry("5", 4);

    // Menu -> Style
    GLint styleSubMenu = glutCreateMenu(processStyleSubMenu);
    glutAddSubMenu("Fill Color", styleFillColorSubMenu);
    glutAddSubMenu("Stroke Color", styleStrokeColorSubMenu);
    glutAddSubMenu("Stroke Width", styleStrokeWidthSubMenu);

    // Menu -> Edit
    GLint editSubMenu = glutCreateMenu(processEditSubMenu);
    glutAddMenuEntry("Select", 0);
    glutAddMenuEntry("Delete", 1);
    glutAddMenuEntry("Move front", 2);
    glutAddMenuEntry("Move back", 3);
    glutAddMenuEntry("Move around", 4);

    // Menu -> File
    GLint fileSubMenu = glutCreateMenu(processFileSubMenu);
    glutAddMenuEntry("Save SVG", 0);
    glutAddMenuEntry("Open SVG", 1);
    glutAddMenuEntry("Export Bitmap", 2);

    // Menu
    GLint menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("New", 0);
    glutAddSubMenu("Draw", drawSubMenu);
    glutAddSubMenu("Style", styleSubMenu);
    glutAddSubMenu("Edit", editSubMenu);
    glutAddSubMenu("File", fileSubMenu);
    glutAddMenuEntry("Quit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging
    setvbuf(stderr, NULL, _IONBF, 0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(width, height);
    glutCreateWindow("SimpleDraw (Nausher Rao)");

    init();
    createContextMenu();

    glutReshapeFunc(resizeWindow);
    glutMainLoop();
}

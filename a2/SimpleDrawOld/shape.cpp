#include <stdio.h>
#include <GL/glut.h>

enum ShapeType
{
    RECTANGLE,
    CIRCLE
};

class Shape
{
public:
    ShapeType type;
    GLint fillR;
    GLint fillG;
    GLint fillB;
    GLint strokeR;
    GLint strokeG;
    GLint strokeB;
    GLint strokeW;

    Shape(ShapeType type, GLint fillR, GLint fillG, GLint fillB, GLint strokeR, GLint strokeG, GLint strokeB, GLint strokeW)
    {
        this->type = type;
        this->fillR = fillR;
        this->fillG = fillG;
        this->fillB = fillB;
        this->strokeR = strokeR;
        this->strokeG = strokeG;
        this->strokeB = strokeB;
        this->strokeW = strokeW;
    }
};

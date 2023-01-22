/*
 * Description: SimpleView - House.hpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#ifndef CHOUSE_H
#define CHOUSE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Pyramid.hpp"
#include "Cube.hpp"

class House : public Shape
{

public:
    Pyramid roof;
    Cube frame;
    House();
    void draw();
};

#endif

/*
 * Description: SimpleView - House.cpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#include "House.hpp"

House::House()
{
}

void House::draw()
{

    glPushMatrix();
    this->ctmMultiply();

    glScalef(s, s, s);
    glTranslatef(0, 0, 1);
    roof.draw();
    glPopMatrix();

    glPushMatrix();
    this->ctmMultiply();

    glScalef(s, s, s);
    frame.draw();
    glPopMatrix();
}

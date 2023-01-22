/*
 * Description: SimpleView - Pyramid.cpp
 * Author: Nausher Rao
 * Version: 2022-11-09
 */
#include "Pyramid.hpp"
#include "Vector.hpp"

Pyramid::Pyramid()
{
    vertex[0][0] = -1;
    vertex[0][1] = -1;
    vertex[0][2] = 0;
    vertex[1][0] = 1;
    vertex[1][1] = -1;
    vertex[1][2] = 0;
    vertex[2][0] = 1;
    vertex[2][1] = 1;
    vertex[2][2] = 0;
    vertex[3][0] = -1;
    vertex[3][1] = 1;
    vertex[3][2] = 0;
    vertex[4][0] = 0;
    vertex[4][1] = 0.0;
    vertex[4][2] = 1.5;

    face[0][0] = 0;
    face[0][1] = 1;
    face[0][2] = 4;
    face[1][0] = 1;
    face[1][1] = 2;
    face[1][2] = 4;
    face[2][0] = 2;
    face[2][1] = 3;
    face[2][2] = 4;
    face[3][0] = 3;
    face[3][1] = 0;
    face[3][2] = 4;

    r = 1.0;
    g = 1.0;
    b = 0;
}

void Pyramid::drawFace(GLint i)
{
    GLfloat shade = 1;
    switch (renderMode)
    {
    case WIRE:
        glColor3f(r, g, b);
        glBegin(GL_LINE_LOOP);
        glVertex3fv(vertex[face[i][0]]);
        glVertex3fv(vertex[face[i][1]]);
        glVertex3fv(vertex[face[i][2]]);
        glEnd();
        break;
    case CONSTANT:
        if (myLight.on == true)
            shade = getFaceShade(i, myLight);
        glColor3f(faceColor[i][0] * shade, faceColor[i][1] * shade, faceColor[i][2] * shade);
        glBegin(GL_POLYGON);
        glVertex3fv(vertex[face[i][0]]);
        glVertex3fv(vertex[face[i][1]]);
        glVertex3fv(vertex[face[i][2]]);
        glEnd();
        break;
    case FLAT:
        break;
    case SMOOTH:
        break;
    case PHONE:
        break;
    case TEXTURE:
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBegin(GL_TRIANGLES);

        glTexCoord2f(0.0, 0.0);
        glVertex3fv(&vertex[face[i][0]][0]);
        glTexCoord2f(1.0, 0.0);
        glVertex3fv(&vertex[face[i][1]][0]);
        glTexCoord2f(1.0, 1.0);
        glVertex3fv(&vertex[face[i][2]][0]);

        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
    }
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
    for (int i = 0; i < 4; i++)
    {
        if (cullMode == BACKFACE)
        {
            if (isFrontface(i, myCamera))
                drawFace(i);

        }
        else
            drawFace(i);

    }
    glPopMatrix();
}

bool Pyramid::isFrontface(int faceindex, Camera camera)
{
    GLfloat vector[4];
    vector[0] = faceNormal[faceindex].x;
    vector[1] = faceNormal[faceindex].y;
    vector[2] = faceNormal[faceindex].z;
    vector[3] = 0.0;
    mc.multiplyVector(vector);
    if (pmc != NULL)
    {
        pmc->multiplyVector(vector);
        return (pmc->mat[0][3] - camera.eye.x) * vector[0] + (pmc->mat[1][3] - camera.eye.y) * vector[1] + (pmc->mat[2][3] - camera.eye.z) * vector[2] < 0;
    }
    else
        return (mc.mat[0][3] - camera.eye.x) * vector[0] + (mc.mat[1][3] - camera.eye.y) * vector[1] + (mc.mat[2][3] - camera.eye.z) * vector[2] < 0;
}

GLfloat Pyramid::getFaceShade(int faceindex, Light light)
{
    GLfloat shade = 1;
    return shade;
}

GLfloat Pyramid::getVertexShade(int i, Light light)
{
    GLfloat shade = 1;
    return shade;
}

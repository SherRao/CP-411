#include "Sphere.hpp"

extern RenderMode renderMode;

Sphere::Sphere(GLdouble size)
{
	radius = size;
	splices = 50;
	stacks = 50;
	textureID = 0;
	r = 1;
	g = 1;
	b = 1;
	quad = gluNewQuadric();
}

void Sphere::setTextureID(GLuint id)
{
	textureID = id;
}

void Sphere::draw()
{
	glPushMatrix();
	ctmMultiply();

	switch (renderMode)
	{
	case WIRE:
	case CONSTANT:
	case FLAT:
	case SMOOTH:
		glColor3f(r, g, b);
		glutSolidSphere(radius, splices, stacks);
		break;

	case TEXTURE:
		gluQuadricOrientation(this->quad, GLU_OUTSIDE);
		gluQuadricNormals(this->quad, GLU_SMOOTH);
		gluQuadricTexture(this->quad, GL_TRUE);

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, textureID);
		gluSphere(quad, radius, splices, stacks);
		glDisable(GL_TEXTURE_2D);
		break;

	case PHONE:
		break;
	}

	glPopMatrix();
}

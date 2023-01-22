/*
 * Description: SimpleView - Point.cpp
 * Author: Nausher Rao
 * Version: 2022-10-27
 */
#include "Point.hpp"
#include <math.h>
#include <stdio.h>

Point::Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

void Point::set(GLfloat x1, GLfloat y1, GLfloat z1)
{
	x = x1;
	y = y1;
	z = z1;
}

void Point::set(Point p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

void Point::Normalize()
{
	GLdouble length = (x * x + y * y + z * z) ^ (1 / 2);
	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
	}
}

Point Point::CalcNormal(Point p1, Point p2)
{
	Point n, pa, pb;

	pa.x = p1.x - this->x;
	pa.y = p1.y - this->y;
	pa.z = p1.z - this->z;
	pb.x = p2.x - this->x;
	pb.y = p2.y - this->y;
	pb.z = p2.z - this->z;
	pa.Normalize();
	pb.Normalize();

	n.x = pa.y * pb.z - pa.z * pb.y;
	n.y = pa.z * pb.x - pa.x * pb.z;
	n.z = pa.x * pb.y - pa.y * pb.x;
	n.Normalize();

	return (n);
}

void Point::CrossProduct(Point p1, Point p2)
{
	this->x = p1.y * p2.z - p1.z * p2.y;
	this->y = p1.z * p2.x - p1.x * p2.z;
	this->z = p1.x * p2.y - p1.y * p2.x;
}

void Point::printPoint()
{
	printf("(%f, %f, %f)\n", x, y, z);
}

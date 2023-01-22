#include "Bezier.hpp"

extern GLint winWidth, winHeight;

Bezier::Bezier()
{
	reset();
}

void Bezier::reset()
{
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute binomial coefficients C[n] for given value of n, output in GLint C[] */
void Bezier::binomialCoeffs(GLint n, GLint C[])
{
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
{
	int n = nCtrlPts - 1;
	double b[nCtrlPts], x = 0, y = 0, z = 0, r = 0;
	double MIN = 0.00001, MAX = 0.99999;
	if (u < MIN)
	{
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;
	}
	else if (u > MAX)
	{
		bezPt->x = ctrlPts[n].x;
		bezPt->y = ctrlPts[n].y;
		bezPt->z = ctrlPts[n].z;
	}
	else
	{
		r = u / (1.0 - u);
		b[0] = pow(1.0 - u, n);
		for (int i = 1; i <= n; ++i)
			b[i] = b[i - 1] * (n - i + 1) / i * r;

		for (int i = 0; i <= n; ++i)
		{
			x = x + b[i] * ctrlPts[i].x;
			y = y + b[i] * ctrlPts[i].y;
			z = z + b[i] * ctrlPts[i].z;
		}

		bezPt->x = x;
		bezPt->y = y;
		bezPt->z = z;
	}
}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt, Vector *bezTan)
{
	int n = nCtrlPts - 1, n1 = nCtrlPts - 2;
	double b[n], x1 = 0, y1 = 0, z1 = 0, r = 0;
	double x2 = 0, y2 = 0, z2 = 0;
	double MIN = 0.00001, MAX = 0.99999;
	if (u < MIN)
	{
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;
		bezTan->x = ctrlPts[1].x - ctrlPts[0].x;
	}
	else if (u > MAX)
	{
		bezPt->x = ctrlPts[n].x;
		bezPt->y = ctrlPts[n].y;
		bezPt->z = ctrlPts[n].z;
		bezTan->x = ctrlPts[nCtrlPts].x - ctrlPts[nCtrlPts - 1].x;
	}
	else
	{
		r = u / (1.0 - u);
		b[0] = pow(1.0 - u, n);
		for (int i = 1; i < n; i++)
			b[i] = b[i - 1] * (n - i) / i * r;

		for (int i = 0; i <= n; i++)
		{
			x1 = x1 + b[i] * ctrlPts[i].x;
			y1 = y1 + b[i] * ctrlPts[i].y;
			z1 = z1 + b[i] * ctrlPts[i].z;
		}

		bezPt->x = x1;
		bezPt->y = y1;
		bezPt->z = z1;
		r = u / (1.0 - u);
		b[0] = pow(1.0 - u, n1);
		for (int i = 1; i < n; ++i)
			b[i] = b[i - 1] * (n - i) / i * r;

		for (int i = 0; i < n; ++i)
		{
			x2 = x2 + b[i] * (ctrlPts[i + 1].x - ctrlPts[i].x);
			y2 = y2 + b[i] * (ctrlPts[i + 1].y - ctrlPts[i].y);
			z2 = z2 + b[i] * (ctrlPts[i + 1].z - ctrlPts[i].z);
		}

		bezTan->x = n * x2;
		bezTan->y = n * y2;
		bezTan->z = n * z2;
	}
}

/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts()
{
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts - 1, C);
	for (int k = 0; k < nPts; k++)
	{
		u = GLfloat(k) / GLfloat(nPts - 1);
		computeBezPt(u, nCtrlPts, ctrlPts, C, &Pts[k]);
	}
}

/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtsTan(GLint npts, Point pts[], Vector tangents[])
{
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts - 1, C);
	for (int k = 0; k < npts; k++)
	{
		u = GLfloat(k) / GLfloat(npts - 1);
		computeBezPtTan(u, nCtrlPts, ctrlPts, C, &pts[k], &tangents[k]);
	}
}

void Bezier::drawCPts()
{
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++)
	{
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts()
{
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display()
{
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}

/* 
 * Description: testing on 2D transformations
 * compile: g++ opengl_curves.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  right clicking to bring up menu for drawing different curves
 * HBF
 */
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX 100
GLint m = MAX;  // number of points on curve,

GLsizei winWidth = 800, winHeight = 800;
GLsizei cwleft = -2, cwright = 2, cwbottom = -2, cwtop = 2;
GLfloat boxleft = -1.5, boxright = 1.5, boxbottom = -1.5, boxtop = 1.5;
GLint curveType = 1;

// data structure to store curve point
struct POINT2 {
	GLfloat x, y;
};


void lineSegment(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void message(char str[], GLfloat x, GLfloat y) {
	glRasterPos2f(x, y);
	int i = 0;
	while (str[i]) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		i++;
	}
}

void line_messae(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	char line[20];
	lineSegment(x1, y1, 0, x2, y2, 0);
	sprintf(line, "(%.1f,%.1f)", x1, y1);
	message(line, x1, y1);
	sprintf(line, "(%.1f,%.1f)", x2, y2);
	message(line, x2, y2);
}

void drawBox() {
	glColor3f(1.0, 1.0, 1.0);
	line_messae(boxleft, 0, boxright, 0);  // x-axis
	line_messae(0, boxbottom, 0, boxtop);  // y-axis
	line_messae(boxleft, boxbottom, boxright, boxbottom);  // bottom
	line_messae(boxleft, boxtop, boxright, boxtop);        // top
	line_messae(boxleft, boxbottom, boxleft, boxtop);      // left
	line_messae(boxright, boxbottom, boxright, boxtop);    // right
}

void drawAxis() {
	glColor3f(1.0, 0.0, 0.0);
	lineSegment(boxleft, 0, 0, boxright, 0, 0);  // x-axis
	glColor3f(0.0, 1.0, 0.0);
	lineSegment(0, boxbottom, 0, 0, boxtop, 0);  // y-axis
	glColor3f(0.0, 0.0, 1.0);
	lineSegment(0, 0, boxbottom, 0, 0, boxtop);  // z-axis
}


// polynomial: p[0]*x^(n-1) + ...+ p[n-2]*x + p[n-1]
int n=3;
GLfloat p[] = {1, 1, -1}; // x^2 + x -1

// Horner's algorithn to evaluate polynomial
GLfloat horner(int n, GLfloat p[], GLfloat x) {
	GLfloat r=0;
	for (int i=0; i<n; i++)
		r = r * x + p[i];
	return r;
}

// compute curve points when drawing
void drawPolynormial(int n, GLfloat p[]) {
	GLfloat a = -1.5, b=1.5;
	GLfloat s = (b-a)/m;
	GLfloat x, y;
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<m; i++) {
		x = a+s*i;
		y = horner(n, p, x);
		//printf("%f, %f\n", x, y);
		glVertex2f(x, y);
	}
	glEnd();
}


// compute and store polynomial curve points
POINT2 polynomialPoints[MAX];
void computePolynormial(int n, GLfloat p[], POINT2 points[], int m) {
	GLfloat a = -1, b=1;
	GLfloat s = (b-a)/m;
	GLfloat x, y;
	for (int i=0; i<m; i++) {
		x = a+s*i;
		y = horner(n, p, x);
		points[i].x = x;
		points[i].y = y;
	}
}


// compute and store circle points
#define Pi 3.1415
POINT2 circlePoints[MAX];
void computeCircle(GLfloat r, POINT2 points[], int m) {
	GLfloat a = 2*Pi, b=0;
	GLfloat s = (b-a)/m;
	GLfloat t;
	for (int i=0; i<m; i++) {
		t = a+s*i;
		points[i].x = r*cos(t);
		points[i].y = r*sin(t);
	}
}


// compute curve point at rendering
void drawCurveByPoints(POINT2 points[], int m, int isLoop) {
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<m; i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();

	if (isLoop == 1) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(points[m-1].x, points[m-1].y);
		glVertex2f(points[0].x, points[0].y);
		glEnd();
	}

}


void drawHelix() {
	int angle = 0, spcount = 2;
	GLfloat x, y, z=0;
	GLfloat r = 1,  b = 0.002;
	GLfloat radia= Pi/180, theta = 0;
	glBegin(GL_LINE_STRIP);
		for(angle = 0; angle < 360*spcount; angle += 1)
		{
			theta = angle*radia;
			x = r * cos(theta);
			y = r * sin(theta);
			glVertex3f(x,y,z);
			z+= b;
		}
	 glEnd();
}


// data structure to store 3D curve point
struct POINT3 {
	GLfloat x, y, z;
};


void computeHelix(POINT3 points[], int m) {
	int i = 0;
	GLfloat x, y, z=0;
	GLfloat r = 1, b = 0.002;
	GLfloat radia= Pi/180, theta = 0;
	for(i = 0; i < m; ++i)
	{
		theta = i*radia;
		x = r * cos(theta);
		y = r * sin(theta);
		points[i].x = x;
		points[i].y = y;
		points[i].z = z;
		z+= b;
	}
}

// compute curve point at rendering
void draw3DCurveByPoints(POINT3 points[], int m, int isLoop) {
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<m; i++) {
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();

	if (isLoop == 1) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(points[m-1].x, points[m-1].y, points[m-1].z);
		glVertex3f(points[0].x, points[0].y, points[m-1].z);
		glEnd();
	}

}

POINT3 helixPoints[720];

void init(void) {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(cwleft,  cwright, cwbottom, cwtop);
	computePolynormial(n, p, polynomialPoints, 100);   // compute polynomial curve data
	computeCircle(1.0, circlePoints, 100);
	computeHelix(helixPoints, 720);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.0, 0.0, 0.0, 1.0);

    switch (curveType) {
      case 1:
    	 drawBox();
    	 glColor3f(1.0, 0.0, 0.0);
    	 drawPolynormial(n, p);
    	 break;
      case 2:
    	  drawBox();
    	  glColor3f(0.0, 1.0, 0.0);
    	  drawCurveByPoints(polynomialPoints, m, 0);
    	 break;
      case 3:
    	 drawBox();
    	 glColor3f(0.0, 0.0, 1.0);
    	 drawCurveByPoints(circlePoints, m, 1);
    	 break;

      case 4:
    	drawAxis();
    	glColor3f(1.0, 1.0, 0.0);
    	drawHelix();
    	break;

      case 5:
    	drawAxis();
    	glColor3f(0.0, 1.0, 1.0);
    	draw3DCurveByPoints(helixPoints, 720, 0);
    	break;
    }
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void mainMenuFcn(GLint option) {
	curveType = option;
	switch (option) {
	case 1: case 2: case 3:
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(cwleft,  cwright, cwbottom, cwtop);
		break;

	case 4: case 5:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(
		 40.0,  /* field of view in degree */
		 1.0,   /* aspect ratio */
		 1.0,   /* Z near */
		 30.0   /* Z far */
		);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(3.0, 3.0, 6.0, /* eye is at (0,0,5) */
		          0.0, 0.0, 0.0,  /* center is at (0,0,0) */
		          0.0, 0.0, 1.0   /* up is in positive Y direction */
	    );
		break;
	}

	display();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//setbuf(stdout, NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);    
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("hand-on OpenGL curves");
    init();
	glutDisplayFunc(display);
	glutCreateMenu(mainMenuFcn);
	glutAddMenuEntry("Compute and draw polynomial curve", 1);
	glutAddMenuEntry("Draw stored polynomial curve", 2);
	glutAddMenuEntry("Draw stored circle", 3);
	glutAddMenuEntry("Draw 3D helix", 4);
	glutAddMenuEntry("Draw stored helix", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

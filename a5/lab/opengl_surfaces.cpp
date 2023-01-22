/*
 * Description: testing on 3D surface
 * compile: g++ opengl_surfaces.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
 * HBF
 */

#include <GL/glut.h>
#include <math.h>

GLfloat rotation = 0;
GLfloat Pi = 3.1415926;

char str[100];

struct POINT3 {
	GLfloat x, y, z;
};


POINT3 surfacePoints1[100][100];
POINT3 surfacePoints2[100][100];

GLint M=20;
GLint N=20;

enum SurfaceType {
  function = 0,
  parametric,
  cylinder,
  torus,
  double_helix,
  mobuis_strip,
  glut_sphere,
  glut_cone,
  glut_torus
} surfaceType;

class Vector {
 public:
	GLfloat x,y,z; 			// the coordinates
	Vector() {x=0;y=0;z=0;};               // constructor
	Vector(GLfloat dx, GLfloat dy, GLfloat dz) {x=dx; y=dy; z=dz;};
	void normalize() {
		GLdouble sqs = x * x + y * y + z * z;
		if(sqs < 0.0000001) return;
		GLfloat scaleFactor = 1.0/(GLfloat)sqrt(sqs);
		x *= scaleFactor;
		y *= scaleFactor;
		z *= scaleFactor;
	}
};

void computeFunction(int m, int n, POINT3 points[][100]);
void computeParametric(int m, int n, POINT3 points[][100]);
void drawMeshByPoints(int m, int n, POINT3 points[][100], int isLoop);

void myCylinder();
void myDoubleHelix();
void myTorus();
void myMobuis();


void drawObject(void) {
	switch (surfaceType) {
	case function:
		drawMeshByPoints(M, N, surfacePoints1, 0);
		break;
	case parametric:
		drawMeshByPoints(M, N, surfacePoints2, 1);  // rounded
		break;
	case cylinder:
		myCylinder();
		break;
	case torus:
		myTorus();
		break;
	case double_helix:
		myDoubleHelix();
		break;
	case mobuis_strip:
		myMobuis();
		break;
	case glut_sphere:
		glutWireSphere(1,16,16);
		break;
	case glut_cone:
		glutWireCone(1,1,16,16);
		break;
	case glut_torus:
		glutWireTorus(0.2,0.8,16,16);
		break;
	}
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void message(char str[], GLint x, GLint y) {
	glRasterPos2i(x, y);
	int i = 0;
	while (str[i]) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		i++;
	}
}

Vector p( float u, float v ) {
	float r_maj = 5.0; // distance from origin to center of a meridian
	float r_min = 2.0; // radius of a meridian
	return( Vector(cos(u)*(r_maj+r_min*cos(v)), sin(u)*(r_maj+r_min*cos(v)), r_min*sin(v) ) );
}

Vector n( float u, float v ) {
	Vector N;
	N.x = cos(v)*cos(u);
	N.y = cos(v)*sin(u);
	N.z = sin(v);
	N.normalize();
	return( N );
}

//char str[] = "Press key r or l to rotate";

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	message("Press key r or l to rotate", 4, 1);

	// draw WCS axis
	glColor3f(1.0, 0.0, 0.0);
	lineSegment(-4, 0, 0, 4, 0, 0); /* x-axis in red */
 	glColor3f(0.0, 1.0, 0.0);
	lineSegment(0, -4, 0, 0, 4, 0); /* y-axis in green */
	glColor3f(0.0, 0.0, 1.0);
	lineSegment(0, 0, -4, 0, 0, 4); /* z-axis in blue */

	glColor3f(1.0, 1.0, 0.0);

	glPushMatrix();

    glRotatef(rotation, 0.0, 1.0, 1.0);
    if (surfaceType == torus) glScalef(0.5, 0.5, 0.5);
    if (surfaceType == glut_torus) glScalef(2, 2, 2);

	drawObject();

	glPopMatrix();

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void init(void) {
	/* Setup 3D view */
	glMatrixMode(GL_PROJECTION);
	gluPerspective(
	 40.0,  /* field of view in degree */
	 1.0,   /* aspect ratio */
	 1.0,   /* Z near */
	 30.0   /* Z far */
	);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(6.0, 6.0, 12.0, /* eye is at (0,0,5) */
	          0.0, 0.0, 0.0,  /* center is at (0,0,0) */
	          0.0, 0.0, 1.0   /* up is in positive Y direction */
    );

	//glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_FRONT, GL_LINE);
	glPolygonMode( GL_BACK, GL_LINE);

	computeFunction(M, N, surfacePoints1);
	computeParametric(M, N, surfacePoints2);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'L':
	case 'l':
		rotation += 20;
		break;
	case 'R':
	case 'r':
		rotation -= 20;
		break;
	default:
		break;
	}
}

void mainMenu(GLint option) {
	if (option == 20) exit(0);
	surfaceType = (SurfaceType) option;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("3D surface");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("function", function);
	glutAddMenuEntry("parametric", parametric);
	glutAddMenuEntry("cylinder", cylinder);
	glutAddMenuEntry("torus", torus);
	glutAddMenuEntry("double_helix", double_helix);
	glutAddMenuEntry("mobuis_strip", mobuis_strip);
	glutAddMenuEntry("glut_sphere", glut_sphere);
	glutAddMenuEntry("glut_cone", glut_cone);
	glutAddMenuEntry("glut_torus", glut_torus);
	glutAddMenuEntry("Quit", 20);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

#define Pi 3.1415

void computeFunction(int m, int n, POINT3 points[][100]) {
	GLfloat a = -2, b =2, c=-2, d = 2;
	GLfloat xs = (b-a)/m, ys=(d-c)/n, x, y, z;
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			x = a+i*xs;
			y = c+j*ys;
		    z = -0.5*(x*x + y*y);
			// z = sin(x) + cos(y);
			// z = 1;
			points[i][j].x = x;
			points[i][j].y = y;
			points[i][j].z = z;
		}
	}
}

void computeParametric(int m, int n, POINT3 points[][100]) {
	GLfloat r = 1.5, a = 0, b = Pi, c=0, d = 2*Pi;
	GLfloat xs = (b-a)/m, ys=(d-c)/n, u, v, x, y, z;
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			u = a+i*xs;
			v = c+j*ys;
			x = r * cos(u) * cos(v);
			y = r * cos(u) * sin(v);
		    z = r * sin(u);
			points[i][j].x = x;
			points[i][j].y = y;
			points[i][j].z = z;
		}
	}
}


void drawMeshByPoints(int m, int n, POINT3 points[][100], int isLoop) {
	for (int i=0; i<m-1; i++) {
		glBegin( GL_QUAD_STRIP);
		for (int j=0; j<n; j++) {
			glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
			glVertex3f(points[i+1][j].x, points[i+1][j].y, points[i+1][j].z);
		}
		glEnd();
	}

	if (isLoop == 1) {
		glBegin( GL_QUAD_STRIP);
		for (int i=0; i<1; i++) {
			glVertex3f(points[i][n-1].x, points[i][n-1].y, points[i][n-1].z);
			glVertex3f(points[i+1][n-1].x, points[i+1][n-1].y, points[i+1][n-1].z);
			glVertex3f(points[i][0].x, points[i][0].y, points[i][0].z);
			glVertex3f(points[i+1][0].x, points[i+1][0].y, points[i+1][0].z);
		}
		glEnd();
	}
}

void myCylinder() {
	int nslice = 36;
	glBegin( GL_QUAD_STRIP);
	GLfloat t = 0.;
	GLfloat dt = (360. / nslice) * 3.1416 / 180.;
	for  (int j = 0; j <= nslice; ++j) {
		 glNormal3f( cos(t), 0., sin(t));
		 glVertex3f( cos( t), 0., sin( t));
		 glVertex3f( cos( t), 2., sin( t));
		 t = t + dt;
	}
	glEnd();
}

void myDoubleHelix() {
	//double helix surface
	int angle = 0, spcount = 1;
	GLfloat x, y, z, x1, y1, z1=0;
	GLfloat r = 2,  b = 0.02;
	GLfloat pi = 3.1415926;
	GLfloat radia= pi/180, theta = 0;

	glBegin(GL_QUAD_STRIP);
		for(angle = 0; angle < 180*spcount; angle += 1)
		{
			theta = angle*radia;
			x = r * cos(theta);
			y = r * sin(theta);
			glVertex3f(x,y,z);
			z+= b;

			x1 = r * cos(theta+pi);
			y1 = r * sin(theta+pi);
			glVertex3f(x1,y1,z1);
			z1+= b;
		}
	  glEnd();

}

void myTorus() {
	// torus
	// return a point on the torus for u,v both on [0, 2pi]
	// where v = radians around a meridian
	// u = radians "swept" around the axis
	int num_steps_u = 30;
	int num_steps_v = 15;
	const float PI = 3.14159265359;

	float step_u = (2*PI)/(float)num_steps_u;
	float step_v = (2*PI)/(float)num_steps_v;

	glBegin( GL_QUADS );

	for( float u = 0; u < 2 * PI; u += step_u ) {
		for( float v = 0; v < 2 * PI; v += step_v ) {
			Vector P[4], N[4];
			P[0] = p( u, v );
			P[1] = p( u+step_u, v );
			P[2] = p( u+step_u, v+step_v );
			P[3] = p( u, v+step_v );

			N[0] = n( u, v );
			N[1] = n( u+step_u, v );
			N[2] = n( u+step_u, v+step_v );
			N[3] = n( u, v+step_v );

			for( int c = 0; c < 4; c++ ) {
				glNormal3f( N[c].x, N[c].y, N[c].z );
				glVertex3f( P[c].x, P[c].y, P[c].z );
			}
		}
	}
	glEnd();

}

void myMobuis() {
	 //Mobuis strip wired mesh
	int angle = 0, spcount = 1;
	GLfloat x, y, z, x1, y1, z1=0;
	GLfloat r = 2,  l = 1;
	GLfloat pi = 3.1415926;
	GLfloat radia= pi/180, theta = 0;
	glBegin(GL_QUAD_STRIP);
		for(angle = 0; angle <= 360; angle += 5)
		{
			theta = angle*radia;
			x1 = l*sin(theta/2)*cos(theta);
			y1 = l*sin(theta/2)*sin(theta);
			z1 = l*cos(theta/2);
			glVertex3f(r*cos(theta)+x1, r*sin(theta)+y1,  z1);
			glVertex3f(r*cos(theta)-x1, r*sin(theta)-y1,  -z1);

		}
	glEnd();
}

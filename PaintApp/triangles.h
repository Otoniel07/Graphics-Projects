#include "glut.h"
#include <math.h> 
#include <tuple>
using namespace std;


void triangleH(GLfloat x, GLfloat y, GLfloat radius) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2i(x, y + radius);
	glColor3f(0, 0, 0);
	glVertex2i(x - radius, y - radius);
	glColor3f(0, 0, 0);
	glVertex2i(x + radius, y - radius);
	glEnd();
}

void triangleF(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> colors) {
	glBegin(GL_POLYGON);
	glColor3f(get<0>(colors), get<1>(colors), get<2>(colors));
	glVertex2i(x, y + radius);
	glVertex2i(x - radius, y - radius);
	glVertex2i(x + radius, y - radius);
	glEnd();
}

class Triangle {
public:
	GLfloat t_x;
	GLfloat t_y;
	GLfloat t_radius;
	tuple<double, double, double> t_color;
	bool t_fill;
	Triangle(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> color, bool fill) {
		t_x = x;
		t_y = y;
		t_radius = radius;
		t_color = color;
		t_fill = fill;
	}
	void draw() {
		if (t_fill) {
			glBegin(GL_POLYGON);
			glColor3f(get<0>(t_color), get<1>(t_color), get<2>(t_color));
			glVertex2i(t_x, t_y + t_radius);
			glVertex2i(t_x - t_radius, t_y - t_radius);
			glVertex2i(t_x + t_radius, t_y - t_radius);
			glEnd();
			glColor3f(0, 0, 0);
		}
		else {
			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			glVertex2i(t_x, t_y + t_radius);
			glColor3f(0, 0, 0);
			glVertex2i(t_x - t_radius, t_y - t_radius);
			glColor3f(0, 0, 0);
			glVertex2i(t_x + t_radius, t_y - t_radius);
			glEnd();
		}
	}
};
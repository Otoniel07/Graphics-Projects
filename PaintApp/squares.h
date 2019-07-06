#include "glut.h"
#include <math.h> 
#include <tuple>
using namespace std;


void squareH(GLfloat x, GLfloat y, GLfloat radius) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2i(x - radius, y - radius);
	glColor3f(0, 0, 0);
	glVertex2i(x - radius, y + radius);
	glColor3f(0, 0, 0);
	glVertex2i(x + radius, y + radius);
	glColor3f(0, 0, 0);
	glVertex2i(x + radius, y - radius);
	glEnd();
}

void squareF(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> colors) {
	glBegin(GL_POLYGON);
	glColor3f(get<0>(colors), get<1>(colors), get<2>(colors));
	glVertex2i(x - radius, y - radius);
	glVertex2i(x - radius, y + radius);
	glVertex2i(x + radius, y + radius);
	glVertex2i(x + radius, y - radius);
	glEnd();
}

class Square {
public:
	GLfloat s_x;
	GLfloat s_y;
	GLfloat s_radius;
	tuple<double, double, double> s_color;
	bool s_fill;;
	Square(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> color, bool fill) {
		s_x = x;
		s_y = y;
		s_radius = radius;
		s_color = color;
		s_fill = fill;
	}
	void draw() {
		if (s_fill) {
			glBegin(GL_POLYGON);
			glColor3f(get<0>(s_color), get<1>(s_color), get<2>(s_color));
			glVertex2i(s_x - s_radius, s_y - s_radius);
			glVertex2i(s_x - s_radius, s_y + s_radius);
			glVertex2i(s_x + s_radius, s_y + s_radius);
			glVertex2i(s_x + s_radius, s_y - s_radius);
			glEnd();
			glColor3f(0, 0, 0);
		}
		else {
			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			glVertex2i(s_x - s_radius, s_y - s_radius);
			glColor3f(0, 0, 0);
			glVertex2i(s_x - s_radius, s_y + s_radius);
			glColor3f(0, 0, 0);
			glVertex2i(s_x + s_radius, s_y + s_radius);
			glColor3f(0, 0, 0);
			glVertex2i(s_x + s_radius, s_y - s_radius);
			glEnd();
		}
	}
};
#include "glut.h"
#include <math.h>
#include <tuple>
using namespace std;

float PI = 3.1415926;

void circleH(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f( x + (radius * cos(i * twicePi / lineAmount)),
			        y + (radius * sin(i * twicePi / lineAmount)));
	}
	glEnd();
}

void circleF(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> colors) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(get<0>(colors), get<1>(colors), get<2>(colors));
	glVertex2f(x, y); // center of circle

	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f( x + (radius * cos(i * twicePi / triangleAmount)),
					y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

class Circle {
public:
	GLfloat c_x;
	GLfloat c_y;
	GLfloat c_radius;
	tuple<double, double, double> c_color;
	bool c_fill;
	Circle(GLfloat x, GLfloat y, GLfloat radius, tuple<double, double, double> color, bool fill) {
		c_x = x;
		c_y = y;
		c_radius = radius;
		c_color = color;
		c_fill = fill;
	}

	void draw() {
		if (c_fill){
			int i;
			int triangleAmount = 20; //# of triangles used to draw circle
			GLfloat twicePi = 2.0f * PI;

			glBegin(GL_TRIANGLE_FAN);
			glColor3f(get<0>(c_color), get<1>(c_color), get<2>(c_color));
			glVertex2f(c_x, c_y); // center of circle
			for (i = 0; i <= triangleAmount; i++) {
				glVertex2f( c_x + (c_radius * cos(i * twicePi / triangleAmount)),
							c_y + (c_radius * sin(i * twicePi / triangleAmount)));
			}
			glEnd();
			glColor3f(0, 0, 0);
		}
		else
		{
			int i;
			int lineAmount = 100; //# of triangles used to draw circle
			GLfloat twicePi = 2.0f * PI;

			glBegin(GL_LINE_LOOP);
			for (i = 0; i <= lineAmount; i++) {
				glVertex2f( c_x + (c_radius * cos(i * twicePi / lineAmount)),
							c_y + (c_radius * sin(i * twicePi / lineAmount)));
			}
			glEnd();
		}
	}
};
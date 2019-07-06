#include "glut.h"
#include <math.h> 
#include <tuple>
#include <vector>
using namespace std;

int st = 0;
int bt = 0;


class Line {
public:
	GLfloat cx;
	GLfloat cy;
	GLfloat cthickness;
	tuple<double, double, double> ccolors;
	vector<pair<int, int>> ppoints;

	Line(vector<pair<int, int>> points, GLfloat thickness, tuple<double, double, double> colors) {
		ppoints = points;
		cthickness = thickness;
		ccolors = colors;
	}

	void addpoint(int x, int y) {
		ppoints.push_back(make_pair(x, y));
	}

	void draw() {
		glLineWidth(cthickness);

		glBegin(GL_LINE_STRIP);
		
		glColor3f(get<0>(ccolors), get<1>(ccolors), get<2>(ccolors));
		for(pair<int, int> point : ppoints)
		glVertex2i(point.first, point.second);
		glEnd();
		glColor3f(0, 0, 0);
	}
};
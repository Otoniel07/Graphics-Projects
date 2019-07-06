#include <iostream>
#include "glut.h"
#include "line.h"
#include "circles.h"
#include "squares.h"
#include "triangles.h"
#include "mouse.h"

using namespace std;

//double height = 500.0;
//double width = 700.0;
//int shape = 1, scale = 1, rad = 15;
//tuple<double, double, double> color;
//tuple<double, double, double> red = make_tuple(1.0, 0.0, 0.0);
//tuple<double, double, double> blue = make_tuple(0.0, 0.0, 1.0);
//tuple<double, double, double> green = make_tuple(0.5, 1.0, 0.5);

void drawToolbar()
{
	glColor3f(0.85, 0.85, 1);
	glRectf(0, height, 120, height - 600);
	glColor3f(0, 0, 0);    // Draw lines of width 2 around and across the menu.
	glLineWidth(2);
	glBegin(GL_LINES);

	glVertex2f(0, height-1);    // Line at the top.
	glVertex2f(119, height-1);

	glVertex2f(1, height - 600);        // Line at the left.
	glVertex2f(1, height);

	glVertex2f(119, height - 600);       // Line at the right.
	glVertex2f(119, height);

	glVertex2f(0, height - 300);     // Line at the bottom.
	glVertex2f(119, height - 300);

	glVertex2f(0, 1);     // Line at the bottom.
	glVertex2f(119, 1);

	glEnd();

	triangleH(30, 425, 15);

	glBegin(GL_LINES);
	glVertex2f(0, height - 100); 
	glVertex2f(119, height - 100);
	glEnd();

	squareH(80, 425, 15);

	glBegin(GL_LINES);
	glVertex2f(0, height - 200);
	glVertex2f(119, height - 200);
	glEnd();

	circleH(30, 470, 15);

	glBegin(GL_LINES);
	glVertex2f(65, height - 45);
	glVertex2f(95, height - 15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2i(35, 368);
	glVertex2i(35, 378);
	glVertex2i(85, 378);
	glVertex2i(85, 368);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2i(55, 350);
	glVertex2i(55, 395);
	glVertex2i(65, 395);
	glVertex2i(65, 350);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2i(35, 318);
	glVertex2i(35, 328);
	glVertex2i(85, 328);
	glVertex2i(85, 318);
	glEnd();

	squareF(30, 250, 14, red);
	squareF(60, 250, 14, blue);
	squareF(90, 250, 14, green);

	squareF(60, 100, 40, white);

	glLineWidth(1);
}

void drawCanvas()
{

	glBegin(GL_POLYGON);
	glColor3f(1,1,1);
	glVertex2i(120, 0);
	glVertex2i(120, height);
	glVertex2i(width, height);
	glVertex2i(width, 0);
	glEnd();

	vector<Circle>::iterator circle_it = circlesV.begin();
	vector<Line>::iterator line_it = linesV.begin();
	vector<Triangle>::iterator triangle_it = trianglesV.begin();
	vector<Square>::iterator square_it = squaresV.begin();

	for (int order_it : order)
	{
		switch (order_it)
		{
		case 1:
			circle_it->draw();
			circle_it++;
			break;
		case 2:
			line_it->draw();
			line_it++;
			break;
		case 3:
			triangle_it->draw();
			triangle_it++;
			break;
		case 4:
			square_it->draw();
			square_it++;
			break;
		case 5:
			square_it->draw();
			square_it++;
			break;
		}

	}
	drawToolbar();
}

//void initTransformation(double x1, double x2, double y1, double y2) {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(x1, x2, y1, y2);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
//	glViewport(120, 0, width - 120, height);
//	initTransformation(0, 1, 0, 1);
//	drawCanvas();

	glViewport(0, 0, width, height);
//	initTransformation(0, 120, 0, height);
	drawToolbar();
	drawCanvas();


	glFlush();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
}

int main(int argc, char *argv[])
{
	printf("Left-Click to select a tool from the toolbar! \n");
	printf("Left-Click again to draw on the canvas! \n");
	printf("With Pen-tool selected, Right-Click to erase! \n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple Paint");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutMainLoop();

	return 0;
}

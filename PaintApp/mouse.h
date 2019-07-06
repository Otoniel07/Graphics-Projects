#include "glut.h"
#include <vector> 
#include <utility> 

double height = 500.0;
double width = 620.0;
int shape = 1, scale = 1, rad = 15, thickness = 2, btn = 0, sta = 0;
bool drawing = false;
tuple<double, double, double> color;
tuple<double, double, double> red = make_tuple(1.0, 0.0, 0.0);
tuple<double, double, double> blue = make_tuple(0.0, 0.0, 1.0);
tuple<double, double, double> green = make_tuple(0.5, 1.0, 0.5);
tuple<double, double, double> white = make_tuple(1.0, 1.0, 1.0);
vector<Circle> circlesV;
vector<Line> linesV;
vector<Triangle> trianglesV;
vector<Square> squaresV;
vector<int> order;


void menuMouse(int x, int y) {
	// This method is called when the user clicks the menu.
	if (y > height - 50 && x < 60)
	{
		shape = 1;
		printf("Circle\n");
	}
	else if (y > height - 50 && (x < 120 && x > 60))
	{
		shape = 2;
		printf("Line\n");
	}
	else if (y > height - 100 && x < 60)
	{
		shape = 3;
		printf("Triangle\n");
	}
	else if (y > height - 100 && (x < 120 && x > 60))
	{
		shape = 4;
		printf("Square\n");
	}
	else if (y > height - 150 && y < height -  100)
	{
		if (scale < 10)
		{
			scale = scale + 1;
			printf("Scale up\n");
		}
		else
		{
			printf("Scale Upper Limit Reached");
		}
	}
	else if (y > height - 200 && y < height - 150)
	{
		if (scale > 1)
		{
			scale = scale - 1;
			printf("Scale down\n");
		}
		else
		{
			printf("Scale Lower Limit Reached");
		}
	}
	else if ((y < height - 230 && y > height - 270) && x < 40)
	{
		color = red;
		printf("Red\n");
	}
	else if ((y < height - 230 && y > height - 270) && (x < 80 && x > 40))
	{
		color = blue;
		printf("Blue\n");
	}
	else if ((y < height - 230 && y > height - 270) && (x < 120 && x > 80))
	{
		color = green;
		printf("Green\n");
	}
	else if ((y < 140 && y > 60) && (x < 100 && x > 20))
	{
		order.push_back(5);
		squaresV.push_back(Square(350, 250, 280, white, true));
		printf("Blank\n");
	}
}

void myMouse(int button, int state, int x, int y) {
	int ny = height - y;
	btn = button;
	sta = state;
	if ((x < 120) && state == GLUT_DOWN) {  // Mouse is in the menu area
		menuMouse(x, height - y);
	}
	else if (button == GLUT_LEFT_BUTTON) {
		double dx, dy;  // mouse position in drawing coordinates
		dx = (double)(x - 120) / (width - 120);
		dy = (double)(height - y) / height;
		if (state == GLUT_DOWN && x > 120)
		{
			if(shape == 1)
			{
				order.push_back(1);
				circlesV.push_back(Circle(x, ny, rad*scale, color, true));
			}
			else if (shape == 2)
			{
				if (drawing == false)
				{
					order.push_back(2);
					linesV.push_back(Line({ make_pair(x,ny) }, thickness * scale, color));
					drawing = true;
				}
			}
			else if (shape == 3)
			{
				order.push_back(3);
				trianglesV.push_back(Triangle(x, ny, rad*scale, color, true));
			}
			else if (shape == 4)
			{
				order.push_back(4);
				squaresV.push_back(Square(x, ny, rad*scale, color, true));
			}
		}
		else if(state == GLUT_UP && x > 120)
		{
			if (shape == 2)
			{
				if (drawing == true)
				{
					linesV.back().addpoint(x, ny);
					drawing = false;
				}
			}
		}
	} 
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN && x > 120)
		{
			if (drawing == false)
			{
				order.push_back(2);
				linesV.push_back(Line({ make_pair(x,ny) }, thickness * 10 * scale, white));
				drawing = true;
			}
		}
		else if (state == GLUT_UP && x > 120)
		{
			if (shape == 2)
			{
				if (drawing == true)
				{
					linesV.back().addpoint(x, ny);
					drawing = false;
				}
			}

		}
	}
	glutPostRedisplay();
}

void myMotion(int x, int y)
{
	int ny = height - y;
	if (btn == GLUT_LEFT_BUTTON)
	{
		if (sta == GLUT_DOWN && x > 120)
		{
			if (shape == 2 && drawing == true)
			{
				linesV.back().addpoint(x, ny);
			}
		}
	}
	else if (btn == GLUT_RIGHT_BUTTON)
	{
		if (sta == GLUT_DOWN && x > 120)
		{
			if (shape == 2 && drawing == true)
			{
				linesV.back().addpoint(x, ny);
			}
		}
	}
	glutPostRedisplay();
}
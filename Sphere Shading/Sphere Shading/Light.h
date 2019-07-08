#include <cmath>
#include <utility>
#include <iostream>
//#include <tuple>
#include "tuple.h"

using namespace std;

class Light {
public:
	float x, y, z, r, b, g, a, shininess, angle, expo;
	tuple<float, float, float> position, direction;
	tuple<float, float, float, float> ambient, diffuse, specular;
	
	Light(tuple<float, float, float> pos, tuple<float, float, float, float> col, int type) {
		ambient = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		specular = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		position = make_tuple(0.0f, 0.0f, 0.0f);

		setPosition(pos);

		switch (type)
		{
		case 0:
			setAmbient(col);
			break;
		case 1:
			setDiffuse(col);
			break;
		case 2:
			setSpecular(col);
			break;
		default:
			break;
		}
	}

	Light(tuple<float, float, float> pos, tuple<float, float, float, float> col, tuple<float, float, float> dir, float angl, float exp, int type) {
		ambient = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		specular = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		position = make_tuple(0.0f, 0.0f, 0.0f);

		setPosition(pos);
		direction = dir;
		angle = angl;
		expo = exp;

		switch (type)
		{
		case 0:
			setAmbient(col);
		case 1:
			setDiffuse(col);
		case 2:
			setSpecular(col);
		default:
			break;
		}
	}

	Light(tuple<float, float, float> pos, tuple<float, float, float, float> col, tuple<float, float, float> dir, int type) {
		ambient = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		specular = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
		position = make_tuple(0.0f, 0.0f, 0.0f);

		setPosition(pos);
		direction = dir;

		switch (type)
		{
		case 0:
			setAmbient(col);
		case 1:
			setDiffuse(col);
		case 2:
			setSpecular(col);
		default:
			break;
		}
	}

	void setPosition(tuple<float, float, float> pos) {
		x = get<0>(pos);
		y = get<1>(pos);
		z = get<2>(pos);
		position = pos;
	}

	void setDirection(tuple<float, float, float> dir) {
		direction = make_tuple(get<0>(dir), get<1>(dir), get<2>(dir));
	}

	void setAngle(float ang) {
		angle = ang;
	}

	void setExpo(float ex) {
		expo = ex;
	}


	void setShine(float sh) {
		shininess = sh;
	}

	void setAmbient(tuple<float, float, float, float> light) {
		ambient = make_tuple(get<0>(light), get<1>(light), get<2>(light), get<3>(light));
		r = get<0>(light);
		g = get<1>(light);
		b = get<2>(light);
		a = get<3>(light);
	}

	void setDiffuse(tuple<float, float, float, float> light) {
		diffuse = make_tuple(get<0>(light), get<1>(light), get<2>(light), get<3>(light));
		r = get<0>(light);
		g = get<1>(light);
		b = get<2>(light);
		a = get<3>(light);
	}

	void setSpecular(tuple<float, float, float, float> light) {
		specular = make_tuple(get<0>(light), get<1>(light), get<2>(light), get<3>(light));
		r = get<0>(light);
		g = get<1>(light);
		b = get<2>(light);
		a = get<3>(light);
	}

};
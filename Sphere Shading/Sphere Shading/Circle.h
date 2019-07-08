#include <tuple>
#include <cmath>
#include "tuple.h"

using namespace std;



class Circle {
public:
	float r, x, y, z;
	tuple<float, float, float> color, position;
	int inRange = 0;
	tuple<float, float, float, float> mat_ambient;
	tuple<float, float, float, float> mat_diffuse;
	tuple<float, float, float, float> mat_specular;
	float mat_shininess;

	Circle(float rad, tuple<float, float, float> pos, tuple<float, float, float> col, tuple<float, float, float, float> ambient, tuple<float, float, float, float> diffuse, tuple<float, float, float, float> specular, float shininess) {
		r = rad;
		x = get<0>(pos);
		y = get<1>(pos);
		z = get<2>(pos);
		color = col;
		mat_ambient = make_tuple(get<0>(ambient), get<1>(ambient), get<2>(ambient), get<3>(ambient));
		mat_diffuse = make_tuple(get<0>(diffuse), get<1>(diffuse), get<2>(diffuse), get<3>(diffuse));
		mat_specular = make_tuple(get<0>(specular), get<1>(specular), get<2>(specular), get<3>(specular));
		mat_shininess = shininess;
	}
	
	tuple<float, float, float> newVec(tuple<float, float, float> vec, float num) {
		float newx = (1 / r)*get<0>(vec) + 0 * get<1>(vec) + 0 * get<2>(vec) + (-x / r)*num;
		float newy = 0* get<0>(vec) + (1 / r) * get<1>(vec) + 0 * get<2>(vec) + (-y / r)*num;
		float newz = 0* get<0>(vec) + 0 * get<1>(vec) + (1 / r) * get<2>(vec) + (-z / r)*num;
		return make_tuple(newx, newy, newz);
	}

	int rangeCalc(tuple<float, float, float> p) {
		if ((get<0>(p) <= abs(x + r) && get<0>(p) >= abs(x - r)) || (get<0>(p) >= abs(x + r) && get<0>(p) <= abs(x - r))) {
			if ((get<1>(p) <= abs(y + r) && get<0>(p) >= abs(y - r)) || (get<1>(p) >= abs(y + r) && get<0>(p) <= abs(y - r))) {
				if ((get<2>(p) <= abs(z + r) && get<2>(p) >= abs(z - r)) || (get<2>(p) >= abs(z + r) && get<2>(p) <= abs(z - r))) {
					if (sqrt(pow(get<0>(p) - (get<0>(p) - x), 2) + pow(get<1>(p) - (get<1>(p) - y), 2) + pow(get<2>(p) - (get<2>(p) - z), 2)) <= r) {
						return 1;
					}
				}
			}
		}
		return 0;
	}

	tuple<float, float> intersection(tuple<float, float, float> S, tuple<float, float, float> D) {
		float a = dot(D, D);
		float b = dot(S, D);
		float c = dot(S, S) - 1;

		float delta = pow(b, 2) - (a)*(c);

		if (delta == 0) {
			return make_tuple((-b)/a, (-b)/a);
		}
		else if (delta > 0){
			return make_tuple((-b - sqrt(pow(b,2) - (a*c)))/a, (-b + sqrt(pow(b, 2) - (a*c))) / a);
		}

		return make_tuple(0,0);
	}

};
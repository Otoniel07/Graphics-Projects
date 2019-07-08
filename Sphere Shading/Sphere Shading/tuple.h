#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <tuple>
#include <cmath>
using namespace std;

tuple<float, float, float> cross(tuple<float, float, float> a, tuple<float, float, float> b) {
	tuple<float, float, float> result = make_tuple(get<1>(a)*get<2>(b) - get<2>(a)*get<1>(b), get<2>(a)*get<0>(b) - get<0>(a)*get<2>(b), get<0>(a)*get<1>(b) - get<1>(a)*get<0>(b));
	return result;
}

float dot(tuple<float, float, float> a, tuple<float, float, float> b) {
	float result = get<0>(a)*get<0>(b) + get<1>(a)*get<1>(b) + get<2>(a)*get<2>(b);
	return result;
}

tuple<float, float, float> sub(tuple<float, float, float> a, tuple<float, float, float> b) {
	tuple<float, float, float> result = make_tuple(get<0>(a) - get<0>(b), get<1>(a) - get<1>(b), get<2>(a) - get<2>(b));
	return result;
}

tuple<float, float, float> add(tuple<float, float, float> a, tuple<float, float, float> b) {
	tuple<float, float, float> result = make_tuple(get<0>(a) + get<0>(b), get<1>(a) + get<1>(b), get<2>(a) + get<2>(b));
	return result;
}

tuple<float, float, float, float> add(tuple<float, float, float, float> a, tuple<float, float, float, float> b) {

	float r = get<0>(a) + get<0>(b), g = get<1>(a) + get<1>(b), bl = get<2>(a) + get<2>(b), aa = get<3>(a) + get<3>(b);

	if (r > 1) {
		r = 1;
	}
	if (g > 1) {
		g = 1;
	}
	if (bl > 1) {
		bl = 1;
	}
	if (aa > 1) {
		aa = 1;
	}

	tuple<float, float, float, float> result = make_tuple(r, g, bl, aa);

	return result;
}

tuple<float, float, float, float> cap(tuple<float, float, float, float> a) {

	float r = get<0>(a), g = get<1>(a), bl = get<2>(a), aa = get<3>(a);

	if (r > 1) {
		r = 1;
	}
	if (g > 1) {
		g = 1;
	}
	if (bl > 1) {
		bl = 1;
	}
	if (aa > 1) {
		aa = 1;
	}

	tuple<float, float, float, float> result = make_tuple(r, g, bl, aa);

	return result;
}

float cap(float a) {

	float result = a;

	if (a > 1) {
		result = 1;
	}
	return result;
}

tuple<float, float, float> cMult(float c, tuple<float, float, float> a) {
	tuple<float, float, float> result = make_tuple(get<0>(a) * c, get<1>(a) * c, get<2>(a) * c);
	return result;
}

tuple<float, float, float, float> cMult(float c, tuple<float, float, float, float> a) {
	tuple<float, float, float, float> result = make_tuple(get<0>(a) * c, get<1>(a) * c, get<2>(a) * c, get<3>(a) * c);
	return result;
}

tuple<float, float, float> normalize(tuple<float, float, float> vec) {
	if (dot(vec, vec) < .0000001)
		return vec;
	else
		return cMult(1 / (sqrt(dot(vec, vec))), vec);
}

tuple<float, float, float> calcN(tuple<float, float, float> eye, tuple<float, float, float> lookAt) {
	tuple<float, float, float> s = sub(eye, lookAt);
	s = normalize(s);
	return s;
}

tuple<float, float, float> calcU(tuple<float, float, float> up, tuple<float, float, float> nVec) {
	tuple<float, float, float> c = cross(up, nVec);
	c = normalize(c);
	return c;
}

tuple<float, float, float> calcV(tuple<float, float, float> nVec, tuple<float, float, float> uVec) {
	tuple<float, float, float> c = cross(nVec, uVec);
	c = normalize(c);
	return c;
}

tuple<float, float, float, float> operator &(tuple<float, float, float, float> t, tuple<float, float, float, float> u) {
	return tuple<float, float, float, float>(get<0>(t) * get<0>(u), get<0>(t) * get<1>(u), get<2>(t) * get<2>(u), get<3>(t) * get<3>(u));
}

tuple<float, float, float, float> operator *(tuple<float, float, float, float> t, float s) {
	return tuple<float, float, float, float>(get<0>(t) * s, get<0>(t) * s, get<2>(t) * s, get<3>(t) * s);
}

bool operator ==(tuple<float, float, float> tup, float compare) {
	return (get<0>(tup) == compare && get<1>(tup) == compare && get<2>(tup) == compare);
}

#endif
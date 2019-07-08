#include "tuple.h"
#include <cmath>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include "glut.h"
#include "Circle.h"
#include "Light.h"

using namespace std;

tuple<float, float, float> red = make_tuple(1.0, 0.0, 0.0);
tuple<float, float, float> blue = make_tuple(0.0, 1.0, 0.0);
tuple<float, float, float> green = make_tuple(0.0, 0.0, 1.0);

tuple<float, float, float> eye = make_tuple(0.0, 0.0, 1.0);

tuple<float, float, float> pos1 = make_tuple(.125f, -.25f, -1.0f);
tuple<float, float, float> pos2 = make_tuple(.5f, .5f, -1.75f);
tuple<float, float, float> pos3 = make_tuple(-.5f, 0.0f, -2.5f);

tuple<float, float, float, float> global_lt = make_tuple( .25f, .05f, .05f, 1.0f );
tuple<float, float, float, float> point_lt = make_tuple( .65f, .65f, .65f, 1.0f );
tuple<float, float, float, float> spot_lt = make_tuple( 0.4f, 0.4f, 0.7f, 1.0f );
tuple<float, float, float, float> dir_lt = make_tuple( 0.8f, 0.8f, 0.6f, 1.0f );

//inbetween small sphere
tuple<float, float, float, float> mat_ambient1 = make_tuple( 0.5f, 0.5f, 0.5f, 1.0f );
tuple<float, float, float, float> mat_diffuse1 = make_tuple( 0.7f, 0.7f, 0.7f, 1.0f );
tuple<float, float, float, float> mat_specular1 = make_tuple( 0.9f, 0.9f, 0.9f, 1.0f );
float mat_shininess1 = 3.0f;

//matte medium sphere
tuple<float, float, float, float> mat_ambient2 = make_tuple( 0.5f, 0.5f, 0.5f, 1.0f );
tuple<float, float, float, float> mat_diffuse2 = make_tuple( 0.4f, 0.4f, 0.4f, 1.0f );
tuple<float, float, float, float> mat_specular2 = make_tuple( 0.001f, 0.001f, 0.001f, 1.0f );
float mat_shininess2 = 1.0f;

//shiny large sphere
tuple<float, float, float, float> mat_ambient3 = make_tuple( 0.23125f, 0.23125f, 0.23125f, 1.0f );
tuple<float, float, float, float> mat_diffuse3 = make_tuple( 0.2775f, 0.2775f, 0.2775f, 1.0f );
tuple<float, float, float, float> mat_specular3 = make_tuple( 0.6f, 0.6f, 0.6f, 1.0f );
float mat_shininess3 = 89.6f;

Light global_light(make_tuple(0.0f, 0.0f, 0.0f), global_lt, 0);
Light point_light(make_tuple(200.0f, 100.0f, 50.0f), point_lt, 0);
Light spot_light(make_tuple(-1.0f, 0.0f, 1.0f), spot_lt, make_tuple(0.0f, 0.0f, -1.0f), 0.3f, 0.5f, 2);
Light dir_light(make_tuple(0.0f, 0.0f, 0.0f), dir_lt, make_tuple(-400.0f, 692.0f, 0.0f), 1);

Circle circle1(.125, pos1, red, mat_ambient1, mat_diffuse1, mat_specular1, mat_shininess1);
Circle circle2(.375, pos2, blue, mat_ambient2, mat_diffuse2, mat_specular2, mat_shininess2);
Circle circle3(.75, pos3, green, mat_ambient3, mat_diffuse3, mat_specular3, mat_shininess3);

vector<Circle> circles = { circle1, circle2, circle3 };
vector<Light> lights = { point_light, spot_light, dir_light };

tuple<float, float, float> n = calcN(make_tuple(0, 0, 1), make_tuple(0, 0, 0));
tuple<float, float, float> u = calcU(make_tuple(0, 1, 0), n);
tuple<float, float, float> v = calcV(n, u);

float N = 1.4;
float W = 0.5;
float H = 0.4;

tuple<float, float, float> dir(float r, float c, float nRow, float nCol) {
	tuple<float, float, float> nPart = cMult(-N, n);
	float uc = W*(((2 * c) / nCol) - 1);
	tuple<float, float, float> uPart = cMult(uc, u);
	float vr = H*(((2 * r) / nRow) - 1);
	tuple<float, float, float> vPart = cMult(vr, v);
	tuple<float, float, float> result = add(nPart, add(uPart, vPart));
	return result;
}

tuple<float, float, float, float> calcAmbient(tuple<float, float, float, float> mat_ambient, Light light) {
	float red = get<0>(mat_ambient) * light.r;
	float green = get<1>(mat_ambient) * light.g;
	float blue = get<2>(mat_ambient) * light.b;
	float a = get<3>(mat_ambient) * light.a;
	return make_tuple(red, green, blue, a);
}

tuple<float, float, float, float> calcDiffuse(tuple<float, float, float, float> mat_diffuse, Light light, float LdotN) {
	float red = get<0>(mat_diffuse) * light.r * max(0.0f,LdotN);
	float green = get<1>(mat_diffuse) * light.g *  max(0.0f, LdotN);
	float blue = get<2>(mat_diffuse) * light.b *  max(0.0f, LdotN);
	float a = get<3>(mat_diffuse) * light.a *  max(0.0f, LdotN);
	return make_tuple(red, green, blue, a);
}

tuple<float, float, float, float> calcSpecular(tuple<float, float, float, float> mat_specular, Light light, float HdotN, float shininess) {
	float red = get<0>(mat_specular) * light.r * pow(max(0.0f,HdotN),shininess);
	float green = get<1>(mat_specular) * light.g * pow(max(0.0f, HdotN), shininess);
	float blue = get<2>(mat_specular) * light.b * pow(max(0.0f, HdotN), shininess);
	float a = get<3>(mat_specular) * light.a * pow(max(0.0f, HdotN), shininess);
	return make_tuple(red, green, blue, a);
}

tuple<float, float, float> calcL(Light light, tuple<float, float, float> hitpoint) {
	if (light.angle != 0 && light.expo != 0) { 
		return normalize(sub(add(light.position, light.direction), hitpoint)); 
	}
	else if (light.position == 0) { 
		return normalize(light.direction); 
	}
	else if (light.direction == 0) { 
		return normalize(sub(light.position, hitpoint)); 
	}
}

//tuple<float, float, float> calcLPD(Light light, tuple<float, float, float> hitpoint) {
//	return normalize(sub(add(light.position,light.direction), hitpoint));
//}

tuple<float, float, float> calcN(tuple<float, float, float> hitpoint, Circle circle) {
	return normalize(sub(hitpoint, circle.position));
}

tuple<float, float, float> calcVv(tuple<float, float, float> hitpoint, tuple<float, float, float> eye) {
	return normalize(sub(eye, hitpoint));
}

tuple<float, float, float> calcH(tuple<float, float, float> V, tuple<float, float, float> L) {
	return normalize(cMult(0.5f, add(V, L)));
}

struct RGBApixel{ //struct from CG book by Hill
  unsigned char r, g, b, a;
};

int Width, Height;
RGBApixel **pixmap2d;

// drawing callback routine. Uncomment the line to draw the pixmap you want
void drawScreen()
{
 	glRasterPos2i(0, 0);

	glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);
    
	glFlush();
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int width, int height){
  
  // open window and establish coordinate system on it
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutCreateWindow("Pixmap Example");
  
  glMatrixMode(GL_PROJECTION); //set projection to 2D
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
}




int main(int argc, char *argv[]){
   Width = 600;
   Height = 480;
   
  pixmap2d = new RGBApixel*[Height];
  pixmap2d[0] = new RGBApixel[Width * Height];
  for(int row = 1; row < Height; row++)
    pixmap2d[row] = pixmap2d[row - 1] + Width;


  dir_light.direction = make_tuple(-400, 692, 0);

  spot_light.direction = make_tuple(0, 0, -1);
  spot_light.angle = 0.3f;
  spot_light.expo = 0.5f;

  vector<tuple<int, int, int, float>> hits;
  vector<float> reds;
  vector<float> greens;
  vector<float> blues;
  tuple<float, float, float, float> total;

  for (int row = 0; row < Height; row++){
	  for (int col = 0; col < Width; col++){

		  tuple<float, float, float> direction = dir(row, col, Height, Width);
		  float mintime = numeric_limits<float>::max();

		  for (int i = 0; i < 3; i++) {

			  tuple<float, float, float> nDirection = circles.at(i).newVec(direction, 0);
			  tuple<float, float, float> nEye = circles.at(i).newVec(eye, 1);
			  tuple<float, float> intersect = circles.at(i).intersection(nEye, nDirection);
			  int sph = 3;

			  if (get<0>(intersect) > 0) {
				  if (get<0>(intersect) < mintime) {
					  mintime = get<0>(intersect);
					  sph = i;
				  }
			  }

			  if (get<1>(intersect) > 0) {
				  if (get<1>(intersect) < mintime) {
					  mintime = get<1>(intersect);
					  sph = i;
				  }
			  }

			  if (get<0>(intersect) != 0 || get<1>(intersect) != 0) {
				  tuple<float, float, float> hitpoint = normalize(add(nEye, cMult(mintime, nDirection)));
				  tuple<float, float, float, float> color_Mult;

				  tuple<float, float, float, float> ambient;// = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
				  tuple<float, float, float, float> diffuse;// = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
				  tuple<float, float, float, float> specular;// = make_tuple(0.0f, 0.0f, 0.0f, 0.0f);

				  for (int k = 0; k < 3; k++) {
					  tuple<float, float, float> pos = lights.at(k).position;
					  tuple<float, float, float> dir = lights.at(k).direction;
					  tuple<float, float, float, float> amb = lights.at(k).ambient;
					  tuple<float, float, float> L = calcL(lights.at(k), hitpoint);
					  tuple<float, float, float> N = calcN(hitpoint, circles.at(i));
					  tuple<float, float, float> V = calcVv(hitpoint, nEye);
					  tuple<float, float, float> H = calcH(V, L);

					  float LdotN = dot(L, N);
					  float HdotN = dot(H, N);

					  ambient = add(ambient, circles.at(i).mat_ambient & lights.at(k).ambient );
					  diffuse = add(diffuse, (circles.at(i).mat_diffuse & lights.at(k).diffuse) * max(0.0f, LdotN));
					  specular = add(specular, ((circles.at(i).mat_specular & lights.at(k).specular) * pow(max(0.0f, HdotN), circles.at(i).mat_shininess)) * (pow(cos(spot_light.angle), spot_light.expo)));
				  }

				  ambient = add(ambient, circles.at(i).mat_ambient & global_light.ambient);

				  reds.push_back(cap(get<0>(ambient) + get<0>(diffuse) + get<0>(specular)*.1));
				  greens.push_back(cap(get<1>(ambient) + get<1>(diffuse) + get<1>(specular)*.1));
				  blues.push_back(cap(get<2>(ambient) + get<2>(diffuse) + get<2>(specular)));
				  total = add(add(ambient, diffuse), specular);

				  tuple<int, int, int, float> tup = make_tuple(row, col, sph, mintime);
				  hits.push_back(tup);
			  }
		  }
		  pixmap2d[row][col].r = 255 * get<0>(global_lt)*.5; pixmap2d[row][col].g = 255 * get<1>(global_lt)*.5;
		  pixmap2d[row][col].b = 255 * get<2>(global_lt)*.5; pixmap2d[row][col].a = 1 * get<3>(global_lt);
	  }
	      
  }


  int vsize = hits.size();
  for (int i = 0; i < vsize; i++) {
	  tuple<int, int, int, float> pixelP = hits.at(i);
	  pair<int, int> pixel = make_pair(get<0>(pixelP), get<1>(pixelP));
	  int sphereI = get<2>(pixelP);
	  if (sphereI == 0) {
		  pixmap2d[pixel.first][pixel.second].r = 255 * reds.at(i); pixmap2d[pixel.first][pixel.second].g = 255 * greens.at(i);
		  pixmap2d[pixel.first][pixel.second].b = 255 * blues.at(i); pixmap2d[pixel.first][pixel.second].a = 1;
	  }
	  else if (sphereI == 1) {
		  pixmap2d[pixel.first][pixel.second].r = 255 * reds.at(i); pixmap2d[pixel.first][pixel.second].g = 255 * greens.at(i);
		  pixmap2d[pixel.first][pixel.second].b = 255 * blues.at(i); pixmap2d[pixel.first][pixel.second].a = 1;
	  }
	  else if (sphereI == 2) {
		  pixmap2d[pixel.first][pixel.second].r = 255 * reds.at(i); pixmap2d[pixel.first][pixel.second].g = 255 * greens.at(i);
		  pixmap2d[pixel.first][pixel.second].b = 255 * blues.at(i); pixmap2d[pixel.first][pixel.second].a = 1;
	  }
  }

	 

  // open window and establish coordinate system on it
  startgraphics(Width, Height);

  // register display callback routine
  glutDisplayFunc(drawScreen);
  glutMainLoop();
  
  return 0;
}
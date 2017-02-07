#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <armadillo>
#include <cmath>
#include <stdlib.h>
#include "light.hpp"

using namespace std;
using namespace arma;

class Renderable{
	public:
		virtual bool colision(vec, vec, double *, vec&) = 0;
		virtual vec shading(Light light , vec , vec , vec) = 0;
		virtual vec getDifuseColor() = 0;
		virtual vec getEspecColor() = 0;
};

class Sphere : public Renderable {
	private:
		double ray;
		vec center;
		vec difuseColor;
		vec especColor;
		double p;
	public:

	Sphere(double, vec, vec, vec);

	bool colision(vec, vec, double *, vec& normal);
	vec getDifuseColor();
	vec getEspecColor();
	vec shading(Light light, vec intersect, vec v, vec normal);
};

class Triangle : public Renderable {
	private:
		vec normal;
		vec difuseColor;
		vec especColor;
	public:
		vec a;
		vec b;
		vec c;
		vec nA;
		vec nB;
		vec nC;

		double alpha, beta, gama,p;

		Triangle(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc);
		Triangle(vec pA, vec pB , vec pC);
		bool colision(vec origin, vec coordImg, double *distance, vec& normal);
		vec calcNormal();
		void setColors(vec pDifuseColor, vec pEspecColor);
		vec shading(Light light, vec intersect, vec v, vec normal);
		vec getDifuseColor();
		vec getEspecColor();
};

class Object{
	private:
		vector <vec> vertices;
		vector <vec> normais;
		vector <Triangle*> triangs; 
	
	public:
		void addVertices(vec);
		void addNormais(vec);
		void addTriang(Triangle *);
		vec getVertice(int);
		vec getNormal(int);
		vector <Triangle *> getTriangs();
		Object(){}
};

#endif
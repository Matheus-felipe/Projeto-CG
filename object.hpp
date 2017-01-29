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

class Triangle {
	private:
		vec difuseColor;
		vec especColor;

	public:
		vec a;
		vec b;
		vec c;
		vec nA;
		vec nB;
		vec nC;

		double alpha, beta, gama, p;

		Triangle(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc);
		bool colision(vec origin, vec coordImg, double *distance, vec& normal);
		vec calcNormal();
		void setColors(vec pDifuseColor, vec pEspecColor);
		vec shading(vector <Light> lights, vec intersect, vec v, vec normal);
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
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

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

		double alpha, beta, gama;

		Triangle(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc);
		bool colision(vec origin, vec coordImg, double *distance, vec& normal);
		vec calcNormal();
		void setColors(vec pDifuseColor, vec pEspecColor);
		vec getDifuseColor();
		vec getEspecColor();
};

#endif
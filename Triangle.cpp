#include "Triangle.cpp"

Triangle::Triangle(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc){
			this->a = pA;
			this->b = pB;
			this->c = pC;
			this->nA = pNa;
			this->nB = pNb;
			this->nC = pNc;
};

Triangle::bool colision(vec origin, vec coordImg, double *distance, vec& normal){

			mat A, B, G, T;
			double mata, beta, gama, t;

			A << a[0]-b[0] << a[0]-c[0] << coordImg[0] << endr
			  << a[1]-b[1] << a[1]-c[1] << coordImg[1] << endr
			  << a[2]-b[2] << a[2]-c[2] << coordImg[2];

			B << a[0]-coordImg[0] << a[0]-c[0] << coordImg[0] << endr
			  << a[1]-coordImg[1] << a[1]-c[1] << coordImg[1] << endr
			  << a[2]-coordImg[2] << a[2]-c[2] << coordImg[2];

			G << a[0]-b[0] << a[0]-coordImg[0] << coordImg[0] << endr
			  << a[1]-b[1] << a[1]-coordImg[1] << coordImg[1] << endr
			  << a[2]-b[2] << a[2]-coordImg[2] << coordImg[2];

			T << a[0]-b[0] << a[0]-c[0] << a[0]-coordImg[0] << endr
		      << a[1]-b[1] << a[1]-c[1] << a[1]-coordImg[1] << endr
			  << a[2]-b[2] << a[2]-c[2] << a[2]-coordImg[2];

			mata = det(A);
			this->beta = det(B)/mata;
			this->gama = det(G)/mata;
			this->alpha = 1.0 - (this->beta + this->gama);
			t = det(T)/mata;

			(*distance) = t;
			if (t < 0) {
				return false;
			}
			else if(this->gama < 0 || this->gama > 1){
				return false;
			}
			else if(this->beta < 0 || (this->beta + this->gama) > 1 ){
				return false;
			}else{
				
				//vec v = (origin + (t * coordImg));
				//normalise(v);
				normal = calcNormal();
				/*
				double cosTetha = dot(-v, normal);
				if(cosTetha >= 0.0 && cosTetha < 1.0)
					normal = -normal;
				*/
				return true;
			}
}

Triangle::vec calcNormal(){
			/*
			vec AB;
			vec AC;
			vec n;
			
			AB = this->b - this->a;
			AC = this->c - this->a;

			n = normalise(cross(AB, AC));
			*/
			vec n;

			n = ((this->alpha)*(this->nA)) + ((this->beta)*(this->nB)) + ((this->gama)*(this->nC));
			normalise(n);
			return n;
}

Triangle::void setColors(vec pDifuseColor, vec pEspecColor){
	this->difuseColor = pDifuseColor;
	this->especColor = pEspecColor;
}

Triangle::vec getDifuseColor(){
	return this->difuseColor;
}

Triangle::vec getEspecColor(){
	return this->especColor;
}
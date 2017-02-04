#include "object.hpp"

Sphere::Sphere(double pRay, vec pCenter, vec pDifuseColor, vec pEspecColor){
		this->ray = pRay;
		this->center = pCenter;
		this->difuseColor = pDifuseColor;
		this->especColor = pEspecColor;
};

vec Sphere::getDifuseColor(){
	return this->difuseColor;
};

vec Sphere::getEspecColor(){
	return this->difuseColor;
};

bool Sphere::colision(vec origin, vec coordImg, double *distance, vec& normal){
		double a,b,c;
		double delta = 0.0;
		double t1,t2;

		vec distOrgia;
		distOrgia = origin - this->center;

		a = cdot(coordImg, coordImg);
		b = cdot((2*coordImg), distOrgia);
		c = cdot(distOrgia, distOrgia) - (this->ray * this->ray);

		delta = (b*b) - 4*a*c;

		normal = (coordImg - this->center) / this->ray;

		t1 = (-b + sqrt(delta)) / a*a;
		t2 = (-b - sqrt(delta)) / a*a;

		(*distance) = (t1 < t2) ? t1 : t2;  

		if(delta < 0){
			return false;
		}else{
			return true;
		}
};	

Triangle::Triangle(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc){
			this->a = pA;
			this->b = pB;
			this->c = pC;
			this->nA = pNa;
			this->nB = pNb;
			this->nC = pNc;
};

bool Triangle::colision(vec origin, vec coordImg, double *distance, vec& normal){

			mat A, B, G, T;
			double mata, beta, gama, t;

			A << a[0]-b[0] << a[0]-c[0] << coordImg[0] << endr
			  << a[1]-b[1] << a[1]-c[1] << coordImg[1] << endr
			  << a[2]-b[2] << a[2]-c[2] << coordImg[2];

			B << a[0]-origin[0] << a[0]-c[0] << coordImg[0] << endr
			  << a[1]-origin[1] << a[1]-c[1] << coordImg[1] << endr
			  << a[2]-origin[2] << a[2]-c[2] << coordImg[2];

			G << a[0]-b[0] << a[0]-origin[0] << coordImg[0] << endr
			  << a[1]-b[1] << a[1]-origin[1] << coordImg[1] << endr
			  << a[2]-b[2] << a[2]-origin[2] << coordImg[2];

			T << a[0]-b[0] << a[0]-c[0] << a[0]-origin[0] << endr
		      << a[1]-b[1] << a[1]-c[1] << a[1]-origin[1] << endr
			  << a[2]-b[2] << a[2]-c[2] << a[2]-origin[2];

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
				//cout << "colidiu" << endl;
				return true;
			}
}

vec Triangle::calcNormal(){
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

void Triangle::setColors(vec pDifuseColor, vec pEspecColor){
	this->difuseColor = pDifuseColor;
	this->especColor = pEspecColor;
}

vec Triangle::shading(vector <Light> lights, vec intersect, vec v, vec normal){
	vec L;
	L << 0.0 << 0.0 << 0.0;
	vec h;
	vec Li;
	vec nLi;
	vec nH;
	double max1, max2;
	normalise(v);

	for(int i = 0; i < lights.size(); i++){
		Li = (lights[i].getOrigin() - intersect);
		h = v + Li;
		normalise(h);
		normalise(Li);
		max1 = (dot(normal,Li) > 0.0) ? dot(normal,Li) : 0.0;
		max2 = (dot(normal,h) > 0.0) ? dot(normal,h) : 0.0; 
		L += (((this->difuseColor%lights[i].getIntensity()) * max1) + ((this->especColor%lights[i].getIntensity())) * pow(max2,this->p));
	}

	for(int j = 0; j < 3; j++) {
		if(L[j] > 255.0){
			L[j] = 255.0;
		}
		if(L[j] < 0.0) {
			L[j] = 0.0;
		}
	}

	return L;
};

vec Triangle::getDifuseColor(){
	return this->difuseColor;
}

vec Triangle::getEspecColor(){
	return this->especColor;
}


void Object::addVertices(vec v){
	this->vertices.push_back(v);
}

void Object::addNormais(vec n){
	this->normais.push_back(n);
}

void Object::addTriang(Triangle *triang){
	this->triangs.push_back(triang);
}

vec Object::getVertice(int position){
	return this->vertices[position -1];
}

vec Object::getNormal(int position){
	return this->normais[position - 1];
}

vector <Triangle *> Object::getTriangs(){
	return this->triangs;
}



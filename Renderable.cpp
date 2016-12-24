#include "Renderable.hpp"

public Renderable::vec shading(vec difuseColor, vec especColor, vector <Light> lights, vec intersect, vec v, vec normal, double p){
	vec L;
	L << 0.0 << 0.0 << 0.0;
	vec h;
	vec Li;
	vec nLi;
	vec nH;
	double max1, max2;
	normalise(v);

	for(int i = 0; i < lights.size(); i++){
		Li = (lights[i].origin - intersect);
		h = v + Li;
		normalise(h);
		normalise(Li);
		max1 = (dot(normal,Li) > 0.0) ? dot(normal,Li) : 0.0;
		max2 = (dot(normal,h) > 0.0) ? dot(normal,h) : 0.0; 
		L += (((difuseColor%lights[i].intensity) * max1) + ((especColor%lights[i].intensity)) * pow(max2,p));
	}

	for(int j = 0; j < 3; j++){
		if(L[j] > 255.0){
			L[j] = 255.0;
		}
	}

	return L;
};

void printIMG(vec origin, vector <Renderable *> objects, int w, int h, vector <Light> lights){
		FILE *arq = NULL;

	int p;

	double fx, fy;

	double distance;

	bool colidiu;

	vec matrizPixel;
	vec normal;

	fx = mdc(h, w);

	fy = fx;

	vec director;

	mat k(3, 3);

	k << 1/fx << 0 << ((-w)/(2*fx)) << endr 
	  << 0 << ((-1)/fy) << (h/(2*fy)) << endr
	  << 0 << 0 << 1;

	arq = fopen("img.ppm", "w");
	fprintf(arq,"P3 \n%d %d", w, h);
	fprintf(arq,"\n255\n");	

	vec menorNormal;
	for(int j = 0; j < h; j++){
		fprintf(arq, "\n");
		for(int  i = 0; i < w; i++){
			double distanceMenor = 100000000000000000;
			matrizPixel << i << j << 1;

			director = k * matrizPixel;

			colidiu = false;
 			
			for(int l = 0; l < objects[0]->coordFace.size(); l++){
				

				if(objects[0]->coordFace[l]->colision(origin, director, &distance,normal)){
				
					colidiu = true;
					if(distance < distanceMenor){
						distanceMenor = distance;
						p = l;
						menorNormal = normal;
					}
				}
			}
			if(colidiu) {

				vec intersect;
				intersect = director + (director*distanceMenor);
				vec v;
				v = -director;
				vec tempColor;
				tempColor = shading(objects[0]->coordFace[p]->getDifuseColor(), objects[0]->coordFace[p]->getEspecColor(),lights,intersect, v, menorNormal, 5.0);
				fprintf(arq, "%d %d %d ",(int)tempColor[0], (int)tempColor[1], (int)tempColor[2]);
			}else {
				fprintf(arq, "255 255 255 ");
			}
		}
	}

};
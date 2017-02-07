#include "cena.hpp"


void Cena::addObjects(Renderable* rend) {
	this->objects.push_back(rend);
}

vector <Object*>Cena::readObjects(FILE *arqObjects) {

	char linha[256], tipo[16], nomeMaterial[32];
	int qtdVertices = 0;
	int qtdVetoresNormais = 0;
	int vert1, vert2, vert3;
	int norm1, norm2, norm3;
	int rolinha;
	int quant_obj = -1;
	vector <Object*> objects;
	
	vector <Object *> objs;
	vec vertice(3);
	vec norm(3);
	vec dColor(3);
	vec eColor(3);
	vector <vec> colorFace;

	//default
	dColor << 51.0 << 51.0 << 51.0;
	eColor << 51.0 << 51.0 << 51.0;

	Object *objt = NULL;

	while (fgets(linha, sizeof(linha), arqObjects)) {

		sscanf(linha, "%s ", tipo);

		if (!strcmp(tipo, "o")) {
			++quant_obj;
				
			objt = new Object();
			objs.push_back(objt);
			//cout << "obj" << endl;
		}
		else if (!strcmp(tipo, "v")) {
			sscanf(linha, "%*s %lf %lf %lf", &vertice[0], &vertice[1], &vertice[2]);
			objt->addVertices(vertice);
		}
		else if (!strcmp(tipo, "vn")) {
			sscanf(linha, "%*s %lf %lf %lf", &norm[0], &norm[1], &norm[2]);
			objt->addNormais(norm);
		}
		else if (!strcmp(tipo, "f")) {
			sscanf(linha, "%*s %d//%d %d//%d %d//%d", &vert1, &norm1, &vert2, &norm2, &vert3, &norm3);

			Triangle *triang = new Triangle(objt->getVertice(vert1),
											objt->getVertice(vert2), 
											objt->getVertice(vert3),
											objt->getNormal(norm1),
											objt->getNormal(norm2),
											objt->getNormal(norm3));
			triang->setColors(dColor, eColor);
			objt->addTriang(triang);
		}
		else if (strcmp(tipo, "mtllib") == 0) {
			//char nomeArquivoMateriais[32];
			//sscanf(linha, "%s %s", tipo,  nomeArquivoMateriais);
			//FILE *arquivoMateriais = fopen(nomeArquivoMateriais, "r");
		}
		else if (strcmp(tipo, "usemtl") == 0) {
			sscanf(linha, "%s %s", tipo, nomeMaterial);
		}
		else if (strcmp(tipo, "dColor") == 0) {
			cout << "color" << endl;
			sscanf(linha, "%*s %lf %lf %lf", &dColor[0], &dColor[1], &dColor[2]);
		}
		else if (strcmp(tipo, "eColor") == 0) {
			sscanf(linha, "%*s %lf %lf %lf", &eColor[0], &eColor[1], &eColor[2]);
		}
	}

	return objs;
}

double mdc(int h, int w){
return (w == 0) ? h : mdc(w, h%w);
}

void Cena::renderizar(vec origin, int w, int h, vector <Light> lights, char *nomeArq){
	FILE *arq = NULL;
	cout << "renderizando..." << endl;
	int p;

	vector <Triangle *> allTriangles;

	double fx, fy;

	double distance;

	bool colidiu;

	vec matrizPixel;
	vec normal; 
	normal << 0.0 << 0.0 << 1.0;

	fx = mdc(h, w);

	fy = fx;

	vec director;

	mat k(3, 3);

	k << 1/fx << 0 << ((-w)/(2*fx)) << endr 
	  << 0 << ((-1)/fy) << (h/(2*fy)) << endr
	  << 0 << 0 << 1;

	arq = fopen(nomeArq, "w");
	fprintf(arq,"P3 \n%d %d", w, h);
	fprintf(arq,"\n255\n");	

	vec menorNormal;
	//cout << this->objects[0]->getTriangs().size() << endl;
	

	for(int j = 0; j < h; j++){
		fprintf(arq, "\n");
		for(int  i = 0; i < w; i++){
			double distanceMenor = 100000000000000000;
			matrizPixel << i << j << 1;

			director = k * matrizPixel;

			colidiu = false;
			Renderable *objtAtual = NULL;
 			
			for(int l = 0; l < this->objects.size(); l++){
				//cout << "Entrou dentro desse" << endl;				
				if(this->objects[l]->colision(origin, director, &distance,normal)){
				
					colidiu = true;

					if(distance < distanceMenor){
						distanceMenor = distance;
						p = l;
						menorNormal = normal;
						objtAtual = objects[l];
					}
				}	
			}

			if(colidiu){ 
				bool sombra = false;
				vec intersect;
				vec directorToLight;
				int quantObjects = 0;
				vec tempColor;
				tempColor << 0.0 << 0.0 << 0.0;

				for (int j = 0; j < lights.size(); j++) { //verificando todas as luzes

					intersect = origin + director * distanceMenor;
					directorToLight = lights[j].getOrigin() - intersect;
					normalise(directorToLight);
					normalise(intersect);
					sombra = false;

					for (int i = 0; i < this->objects.size(); i++) { // verificando todos os objetos
						
						if (this->objects[i]->colision(intersect, directorToLight, &distance, normal)) { // verifica se o raio de interseção
							
							if (objtAtual == objects[i]) continue;

							sombra = true;
							break;
						}
					}

					if(sombra == false){
						//cout << "sou uma luzinha!" << endl;
						vec v;
						v = -directorToLight;
						normalise(v);
						tempColor += objtAtual->shading(lights[j], intersect, v, menorNormal);	
					}
				}

				if (sombra) {
					//cout << "Oi sou uma sombra!" << endl;
					fprintf(arq, "%d %d %d ",(int)tempColor[0], (int)tempColor[1], (int)tempColor[2]);
				}

				else {
					fprintf(arq, "%d %d %d ",(int)tempColor[0], (int)tempColor[1], (int)tempColor[2]);
				}

			}
			else {
				//cout << "nao colidiu" << endl;
				fprintf(arq, "30 30 30 ");
			}
		}
	}	
}

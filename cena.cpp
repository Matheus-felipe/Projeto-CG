#include "cena.hpp"


void Cena::addObjects(Object *obj){
	this->objects.push_back(obj);
}

void Cena ::readObjects(FILE *arqObjects) {

	char linha[256], tipo[16], nomeMaterial[32];;
	int qtdVertices = 0;
	int qtdVetoresNormais = 0;
	int vert1, vert2, vert3;
	int norm1, norm2, norm3;
	int rolinha;
	int quant_obj = -1;
	
	vector <Object *> objects;
	//vector <Material*> materiais;
	vec vertice(3);
	vec norm(3);
	vec dColor;
	vec eColor;

	dColor << 255.0 << 0.0 << 0.0;
	eColor << 255.0 << 0.0 << 0.0;

	Object *objt = NULL;

	while (fgets(linha, sizeof(linha), arqObjects)) {

		sscanf(linha, "%s ", tipo);

		if (!strcmp(tipo, "o")) {
			++quant_obj;
			objt = new Object();
			addObjects(objt);
			//cout << "Objeto" << endl;
			//objects.push_back(objeto);
		}
		else if (!strcmp(tipo, "v")) {
			sscanf(linha, "%*s %lf %lf %lf", &vertice[0], &vertice[1], &vertice[2]);
			//cout << "alow" << endl;
			objt->addVertices(vertice);
			//qtdVertices++;
			//cout << vertice[0] << "  " << vertice[1] << "  " << vertice[2] << endl;
			//return objects;
		}
		else if (!strcmp(tipo, "vn")) {
			sscanf(linha, "%*s %lf %lf %lf", &norm[0], &norm[1], &norm[2]);
			//cout << "Entrei" << endl;
			objt->addNormais(norm);
			//qtdVetoresNormais++;
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

			char nomeArquivoMateriais[32];

			sscanf(linha, "%s %s", tipo,  nomeArquivoMateriais);
			FILE *arquivoMateriais = fopen(nomeArquivoMateriais, "r");

			//materiais = lerMateriais(arquivoMateriais);
		}
		else if (strcmp(tipo, "usemtl") == 0) {
			sscanf(linha, "%s %s", tipo, nomeMaterial);
		}
	}
}

void Cena::printIMG(vec origin, int w, int h, vector <Light> lights){
	FILE *arq = NULL;

	int p;

	int quantObjects = this->objects.size();

	int positionObject;

	double fx, fy;

	double distance;

	bool colidiu;

	vec matrizPixel;
	vec normal; 
	normal << 0.0 << 0.0 << 0.0;

	//fx = mdc(h, w);

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
	cout << this->objects[0]->getTriangs().size() << endl;
	for(int j = 0; j < h; j++){
		fprintf(arq, "\n");
		for(int  i = 0; i < w; i++){
			double distanceMenor = 100000000000000000;
			matrizPixel << i << j << 1;

			director = k * matrizPixel;

			colidiu = false;
 			
			for(int l = 0; l < this->objects[0]->getTriangs().size(); l++){
				//cout << "Entrou dentro desse" << endl;				
				if(this->objects[0]->getTriangs()[l]->colision(origin, director, &distance,normal)){
				
					colidiu = true;
					if(distance < distanceMenor){
						distanceMenor = distance;
						p = l;
						menorNormal = normal;
					}
				}	
			}

			if(colidiu) {
				//cout << "colidiu" << endl;
				vec intersect;
				intersect = director + (director*distanceMenor);
				vec v;
				v = -director;
				vec tempColor;
				tempColor = this->objects[0]->getTriangs()[p]->shading(lights, intersect, v, menorNormal);
				fprintf(arq, "%d %d %d ",(int)tempColor[0], (int)tempColor[1], (int)tempColor[2]);
			}else {
				//cout << "nao colidiu" << endl;
				fprintf(arq, "255 255 255 ");
			}
		}
	}
}
/*
vector <Material*> lerMateriais(FILE *arquivoMateriais) {
	char linha[256], tipo[16], nomeMaterial[32];
	vec cor(3);

	vector <Material*> mate;
	Material *material;

	while (fgets(linha, sizeof(linha), arquivoMateriais)) {

		sscanf(linha, "%s ", tipo);

		if (strcmp(tipo, "newmtl") == 0) {
			
			sscanf(linha, "%s %s", tipo, nomeMaterial);
			material = new Material();
			strcpy(material->nome_,nomeMaterial);
		
		}
		else if (strcmp(tipo, "Kd") == 0) {
			sscanf(linha, "%*s %lf %lf %lf", &cor[0], &cor[1], &cor[2]);
			material->difuseColor << cor[0] << cor[1] << cor[2];
			mate.push_back(material);
		}
			return mate;

	}
	*/
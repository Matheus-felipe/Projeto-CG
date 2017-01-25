#include "leitor_de_obj.hpp"

//essa class FACE seria a triang nossa, foi aquilo que eu havia comentado antes, ai mudamos de Face pra triang gg

Face :: Face(vec pA, vec pB , vec pC, vec pNa, vec pNb, vec pNc) : a(pA), b(pB), c(pC), nA(pNa), nB(pNb), nC(pNc) {
	
}

void Face :: setColors(vec pDifuseColor, vec pEspecularColor) {
	difuseColor = pDifuseColor;
	especularColor = pEspecularColor;
}

vec Face :: getDifuseColor() {
	return this->difuseColor;
}

vec Face :: getEspecularColor() {
	return this->especularColor;
}

vec Face :: getVecA() {
	return this->a;
}

vec Face :: getVecB() {
	return this->b;
}

vec Face :: getVecC() {
	return this->c;
}

Object :: Object() {

}

//no lugar de retornar vector <Object *> retornamos a Cena, ficaria mais organizado. Deixei uma Class da Cena já *.*

vector <Object *> readObjects(FILE *arqObjects) {

	char linha[256], tipo[16], nomeMaterial[32];;
	int qtdVertices = 0;
	int qtdVetoresNormais = 0;
	int vert1, vert2, vert3;
	int norm1, norm2, norm3;
	int rolinha;
	int quant_obj = -1;
	
	vector <Object *> objects;
	vector <Material*> materiais;
	vector <vec> vVercices;
	vector <vec> faces;
	vector <vec> normals;

	vec vertice(3);
	vec norm(3);
	vec dColor;
	vec eColor;

	dColor << 255.0 << 0.0 << 0.0;
	eColor << 255.0 << 0.0 << 0.0;

	Object *objeto = NULL;
	Face *face = NULL;

	while (fgets(linha, sizeof(linha), arqObjects)) {

		sscanf(linha, "%s ", tipo);

		if (!strcmp(tipo, "o")) {
			++quant_obj;
			objeto = new Object();
			cout << "Objeto" << endl;
			objects.push_back(objeto);
		}
		else if (!strcmp(tipo, "v")) {
			sscanf(linha, "%*s %lf %lf %lf", &vertice[0], &vertice[1], &vertice[2]);
			vVercices.push_back(vertice);
			qtdVertices++;
			cout << vertice[0] << "  " << vertice[1] << "  " << vertice[2] << endl;
			//return objects;
		}
		else if (!strcmp(tipo, "vn")) {
			sscanf(linha, "%*s %lf %lf %lf", &norm[0], &norm[1], &norm[2]);
			normals.push_back(norm);
			qtdVetoresNormais++;
		}
		else if (!strcmp(tipo, "f")) {
			sscanf(linha, "%*s %d//%d %d//%d %d//%d", &vert1, &norm1, &vert2, &norm2, &vert3, &norm3);
			face = new Face(vVercices[vert1 - 1], vVercices[vert2 - 1], vVercices[vert3 - 1], normals[norm1 -1], normals[norm2 -1], normals[norm3 -1]);
			//cout << vVercices[vert1 - 1] << endl;
			face->setColors(dColor, eColor);
			objects[quant_obj]->vertices_face.push_back(face);
			qtdVertices = 0;
			qtdVetoresNormais = 0;
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
	return objects;
}
//caso venha a usar os materiais do blender
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
	}

	return mate;
}

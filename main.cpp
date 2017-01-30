#include "cena.hpp"
#include "light.hpp"

int main(int argc, char **argv) {
	Cena *cena = new Cena();
	FILE *arq = NULL;
	vec originCam;
	vec intens;
	vec origin;
	vector <Light> lights;
	intens << 0.8 << 0.8 << 0.8;
	origin << 1.0 << 3.0 << 1.0;
	originCam << 0.0 << 0.0 << 0.0;
	Light light(origin, intens);
	lights.push_back(light);
	arq = fopen(argv[1], "r");

	if(argc < 2){
		cout << "Parametros necessarios : Programa + Nome do arquivo" << endl;
		return 1;
	}

	if (arq == NULL) {
		cout << "Arquivo nao existe!" << endl;
		return 2;
	}

	
	cena->readObjects(arq);
	cena->printIMG(originCam, 800, 600,lights);


	return 0;
}
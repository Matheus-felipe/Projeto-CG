#include "cena.hpp"
#include "light.hpp"

int main(int argc, char **argv) {
	char type;
	char nomeArqObj[32];
	char nomeArqSaida[32];
	Cena *cena = new Cena();
	vector <Light> lights;
	vec originCam(3);
	vec originLight(3);
	vec intensLight(3);
	int sizeX, sizeY; 
	FILE *arqConfig = NULL;
	FILE *arq = NULL;

	if (argc < 2) {
		cout << "Passe como parâmetro o arquivo de configurações!" << endl;
		return 1;
	}

	arqConfig = fopen(argv[1], "r");

	if (arqConfig == NULL) {
		cout << argv[1] << " Nao existe!" << endl;
		return 2;
	}

	//default
	originCam << 0.0 << 0.0 << 0.0;
	originLight << 0.0 << 0.0 << 0.1;
	intensLight << 0.5 << 0.5 << 0.5;
	sizeX = 800;
	sizeY = 600;

	while (!feof(arqConfig)) {

		fscanf(arqConfig, "%c", &type);

		if (type == 'c') {
			fscanf(arqConfig, "%lf %lf %lf\n", &originCam[0], &originCam[1], &originCam[2]);
			//cout << originCam << endl;
		}

		if (type == 'l') {
			fscanf(arqConfig, " %lf %lf %lf %lf %lf %lf\n", &originLight[0], &originLight[1], &originLight[2], &intensLight[0], &intensLight[1], &intensLight[2]);
			Light light(originLight, intensLight);
			lights.push_back(light);
			//cout << originLight << endl;
		}

		if (type == 's') {
			fscanf(arqConfig, "%i %i\n", &sizeX, &sizeY);
			//cout << sizeX << "  " << sizeY << endl;
		}

		if (type == 'o') {
			fscanf(arqConfig, "%s\n", nomeArqObj);
			//cout << nomeArqObj << endl;
		}

		if (type == 'a') {
			//botar o nome do arq de saida;
			fscanf(arqConfig, "%s\n", nomeArqSaida);
			//cout << nomeArqSaida << endl;
		}

	}

	if (lights.size() == 0) {
		Light light(originLight, intensLight);
		lights.push_back(light);
	}

	arq = fopen(nomeArqObj, "r");
	cena->readObjects(arq);
	cena->renderizar(originCam, sizeX, sizeY, lights, nomeArqSaida);

	return 0;
}

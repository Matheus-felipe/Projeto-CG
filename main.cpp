#include "cena.hpp"
#include "light.hpp"

int main(int argc, char **argv) {
	char type;
	char nomeArqObj[32];
	char nomeArqSaida[32];
	double sphereRay = 0.0;
	double p = 0.0; //Expoente de Phong
	Cena *cena = new Cena();
	vector <Light> lights;
	vector <Object*> objects;
	vec originCam(3);
	vec originLight(3);
	vec intensLight(3);
	vec sphereCenter(3);
	vec vertA(3);
	vec vertB(3);
	vec vertC(3);
	int sizeX, sizeY; 
	FILE *arqConfig = NULL;
	FILE *arq = NULL;
	vec d;
	vec au;

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
	d << 51.0 << 51.0 << 51.0;
	au << 51.0 << 51.0 << 51.0;
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
			fscanf(arqConfig, "%s %lf\n", nomeArqObj, &p);
			arq = fopen(nomeArqObj, "r");
			objects = cena->readObjects(arq,p);

			for(int i = 0; i < objects.size(); i++){
				for(int j = 0; j < objects[i]->getTriangs().size(); j++){
					cena->addObjects(objects[i]->getTriangs()[j]);
				}
			}

			//cout << nomeArqObj << endl;
		}

		if (type == 'a') {
			//botar o nome do arq de saida;
			fscanf(arqConfig, "%s\n", nomeArqSaida);
			//cout << nomeArqSaida << endl;
		}

		if(type == 'e'){
			fscanf(arqConfig, " %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &sphereCenter[0], &sphereCenter[1], &sphereCenter[2], &sphereRay, &d[0], &d[1], &d[2], &au[0], &au[1], &au[3], &p);
			Sphere* sphere = new Sphere(sphereRay,sphereCenter, d, au, p);
			cena->addObjects(sphere);
		}
		/*
		if(type == 't'){
			fscanf(arqConfig, " %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &vertA[0], &vertA[1], &vertA[2], &vertB[0], &vertB[1], &vertB[2], &vertC[0], &vertC[1], &vertC[2]);		
			Triangle* triangle = new Triangle(vertA, vertB, vertC);
			triangle->setColors(d, au);
			cena->addObjects(triangle);
		}
		*/



	}

	//default
	if (lights.size() == 0) {
		Light light(originLight, intensLight);
		lights.push_back(light);
	}

	cena->renderizar(originCam, sizeX, sizeY, lights, nomeArqSaida);

	return 0;
}

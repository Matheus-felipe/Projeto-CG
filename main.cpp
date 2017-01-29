#include "cena.hpp"
#include "light.hpp"

int main(int argc, char **argv){
	Cena *cena = new Cena();
	FILE *arq = NULL;
	vec au;
	vec intens;
	vec origin;
	vector <Light> lights;
	intens << 1 << 1 << 1;
	origin << 2.0 << 3.0 << 5.0;
	au << 0.0 << 0.0 << 0.0;
	Light light(origin, intens);
	lights.push_back(light);
	arq = fopen(argv[1], "r");


	
	cena->readObjects(arq);
	cena->printIMG(au, 400, 300,lights);


	return 0;
}
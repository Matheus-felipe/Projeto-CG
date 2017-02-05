#ifndef CENA_HPP
#define CENA_HPP

#include "object.hpp"

class Cena {
	private:
		vector <Object *> objects;
	public:
		//vector getObjects();
		//void addObjects(Object *);
		void readObjects(FILE *arq);
		void renderizar(vec, int, int , vector <Light>, char *);	
};

#endif	
#ifndef CENA_HPP
#define CENA_HPP

#include "object.hpp"

class Cena {
	private:
		vector <Renderable *> objects;
		
	public:
		//vector getObjects();
		void addObjects(Renderable *);
		vector <Object*>readObjects(FILE *arq);
		void renderizar(vec, int, int , vector <Light>, char *);	
};

#endif	
#ifndef CENA_HPP
#define CENA_HPP

#include "object.hpp"

class Cena{
	private:
		vector <Object *> objects;
	public:
		//vector getObjects();
		void addObjects(Object *);
		void readObjects(FILE *arq);	
		void printIMG(vec, int, int , vector <Light>);	
};

#endif	
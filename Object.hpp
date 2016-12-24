#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object : public Renderable {
	private:
		vector <vec> vertices;
		vector <vec> normais;
		vector <Triang> triangs; 
	
	public:
		vector <Triang *> coordFace;
		Object(){}
};

#endif
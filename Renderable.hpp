#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

class Renderable {
	public vec shading(vec difuseColor, vec especColor, vector <Light> lights, vec intersect, vec v, vec normal, double p);
	void printIMG(vec origin, vector <Renderable *> objects, int w, int h, vector <Light> lights);
};

#endif
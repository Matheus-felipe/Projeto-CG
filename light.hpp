#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <armadillo>

using namespace arma;

class Light {
	private:
		vec origin;
		vec intensity;

	public:
		Light(vec pOrigin, vec pIntensity);
		vec getOrigin();
		vec getIntensity();
};

#endif
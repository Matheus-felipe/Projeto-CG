#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light {
	private:
		vec origin;
		vec intensity;

	public:
		Light(vec pOrigin, vec pIntensity);
};

#endif
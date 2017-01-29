#include "light.hpp"

Light::Light(vec pOrigin, vec pIntensity){
			this->origin = pOrigin;
			this->intensity = pIntensity;
		};
vec Light::getOrigin(){
	return this->origin;
}		

vec Light::getIntensity(){
	return this->intensity;
}
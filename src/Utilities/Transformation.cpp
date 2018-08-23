#include "Transformation.h"
#include <cmath>

namespace utils{

Transformation::Transformation() : baseLengthUnit(100.0f){}

std::pair<float, float> Transformation::coordinatesToPixels(float x, float y) const{

	//1.0 coordinate movement == baseLengthUnit pixels (by default ) movement
	//Split the logic of coordinates in 4 cases
	float temp1 = 0;
	float xPixels;
	float yPixels;

	//All the cases for calculating xPixel
	if(true){
		//In the left half of the screen
		if(x <= 0.0f){
			temp1 = x + 4.0f;
			xPixels = temp1 * baseLengthUnit;
		}

		//In or outside the right half of the screen
		else {
			temp1 = x + 4.0f;
			xPixels = temp1 * baseLengthUnit;;
		}
	}

	//All cases for calculating yPixel
	if(true){
		//In or outside the bottom half of the screen
		if(y <= 0.0f){
			temp1 = 3.0f + std::fabs(y);
			yPixels = temp1 * baseLengthUnit;;
		}
		else {
			temp1 = 3.0f - y;
			yPixels = temp1 * baseLengthUnit;;
		}
	}

	return {xPixels, yPixels};

}

float Transformation::getLengthUnit() const{
	return baseLengthUnit;
}

void Transformation::setLengthUnit(float unit){
	this->baseLengthUnit = unit;
}

template class Singleton<Transformation>;


}

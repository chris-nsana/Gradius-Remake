#include "Transformation.h"
#include <cmath>

namespace utils{


std::pair<float, float> Transformation::coordinatesToPixels(float x, float y) const{

	//1.0 coordinate movement == 140.0 pixel movement
	//Split the logic of coordinates in 4 cases
	float temp1 = 0;
	float xPixels;
	float yPixels;

	//All the cases for calculating xPixel
	if(true){
		//In the left half of the screen
		if(x <= 0.0f){
			temp1 = x + 4.0f;
			xPixels = temp1 * 140.0f;
		}

		//In or outside the right half of the screen
		else {
			temp1 = x + 4.0f;
			xPixels = temp1 * 140.0f;
		}
	}

	//All cases for calculating yPixel
	if(true){
		//In or outside the bottom half of the screen
		if(y <= 0.0f){
			temp1 = 3.0f + std::abs(y);
			yPixels = temp1 * 140.0;
		}
		else {
			temp1 = 3.0f - y;
			yPixels = temp1 * 140.0f;
		}
	}

	return {xPixels, yPixels};

}

template class Singleton<Transformation>;


}






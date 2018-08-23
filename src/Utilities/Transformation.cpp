#include "Transformation.h"
#include <cmath>
#include <SFML/Graphics.hpp>

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

void Transformation::resizeWindow(const std::shared_ptr<sf::RenderWindow>& window, sf::Event& resizeEvent){
	int baseWidth  = static_cast<int>(8.0f * this->baseLengthUnit);
	int baseHeight = static_cast<int>(6.0f * this->baseLengthUnit);
	sf::View newView;
	newView.reset(sf::FloatRect(0, 0, baseWidth, baseHeight));

	//This means we're going from smallscreen to fullscreen
	if(resizeEvent.size.height > baseHeight){
		float width      = (float) resizeEvent.size.width;
		float height     = (float) resizeEvent.size.height;
		float wFactor    = 1.0f;
		float hFactor    = 1.0f;
		float sideBars   = 0.0f;
		float topBars    = 0.0f;
		//This means we need to add bars to the side to enforce 4:3 aspect ratio
		if((width/height) > 1.333f){
			//Factor to determine how small the width should be to achieve 4:3 aspect ratio
			float factor   = (1.333f * height) / width;
			float newWidth = factor * width;
			wFactor        = newWidth / width;
			sideBars       = (1 - wFactor) / 2.0f;

		}
		//This means we need to add bars to the top and the bottom to enforce 4:3 aspect ratio
		else if((width/height) < 1.333f){
			//Factor to determine how small the width should be to achieve 4:3 aspect ratio
			float factor    = 1.0f / (1.333f / width * height);
			float newHeight = factor * height;
			hFactor         = newHeight / height;
			topBars         = (1 - hFactor) / 2.0f;

		}
		//This means that the screen already has a 4:3 aspect ratio, so nothing has to be done.
		else{}

		newView.setViewport(sf::FloatRect(sideBars, topBars, wFactor, hFactor));
		window->setView(newView);
	}
	//Else we're going from fullscreen back to smallscreen
	else{
		window->setView(window->getDefaultView());
	}
}

template class Singleton<Transformation>;


}

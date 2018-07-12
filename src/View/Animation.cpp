//////////////////////////////////////////////////////////
//
// This class design was provided by Hilze Vonck in a video tutorial.
// All credits for the main design and implementation go to Hilze Vonck.
// The code was shared under a Creative Commons licence, meaning that the
// code can be freely used and altered aslong as the creator is credited for their work
// source: https://www.youtube.com/watch?v=Aa8bXSq5LDE
//
//////////////////////////////////////////////////////////

#include "Animation.h"
#include <iostream>

namespace View{

Animation::Animation(){}

Animation::Animation(const std::unique_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float switchTime)
 : row(0), staticTexture(false){

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width  = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::Animation(float pixelsX, float pixelsY)
 : row(0), staticTexture(true){
	 totalTime = 0.0f;
	 currentImage.x = 0;
	 uvRect.width  = pixelsX;
	 uvRect.height = pixelsY;

}

Animation::~Animation(){}

void Animation::changeRow(int newRow){
	if(newRow >= imageCount.y ) throw std::invalid_argument("Error: trying to set Animation row higher than imageCount");
	currentImage.x = 0;
	row = newRow;
}

void Animation::update( float deltaTime){

	currentImage.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime){
		totalTime = 0;
		currentImage.x++;

		if(currentImage.x >= imageCount.x){
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top  = currentImage.y * uvRect.height;
}
}

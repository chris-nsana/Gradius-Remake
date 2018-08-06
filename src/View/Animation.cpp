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
 : row(0), death(false){
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width  = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation(){}

const sf::IntRect& Animation::getTextureRect() const{
  return this->uvRect;
}

int Animation::getNumberOfFrames() const{
  return this->imageCount.x;
}

int Animation::getNumberOfRows() const{
  return this->imageCount.y;
}

float Animation::getSwitchTime() const{
  return this->switchTime;
}

void Animation::startDeathAnimation(){
  //Use the next row, which should be the frames for the death animation.
  row++;
	//Restart from the leftmost frame
	currentImage.x = 0;
  //Set the death flag
  death = true;
}

void Animation::update( float deltaTime){
	currentImage.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime){
		totalTime = 0;
		currentImage.x++;

		if(currentImage.x >= imageCount.x){
      if(!death){
        currentImage.x = 0;
      }
      //The death animation should only be played once, going through all
      //the frames is enough. Render the uvRect empty to prevent any other imaging.
      else{
        uvRect.width  = 0;
        uvRect.height = 0;
        return void();
      }
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top  = currentImage.y * uvRect.height;
}
}

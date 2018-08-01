#include <iostream>
#include <fstream>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Utilities/Transformation.h"
#include "Utilities/Stopwatch.h"
#include "View.h"

namespace View{

View::View(std::shared_ptr<sf::RenderWindow> window, std::string texturesFile) : window(window){
	nlohmann::json textures;
	std::ifstream file{texturesFile};
	file >> textures;
	this->texturesJson = textures;

	for(auto it = textures.begin(); it != textures.end(); ++it ){
		auto textureName = it.key();
		auto file_path   = it.value()["image_path"];
		this->textures[textureName] = std::make_unique<sf::Texture>();
		this->textures[textureName]->loadFromFile(file_path);
		this->textures[textureName]->setRepeated(true);
	}
	this->baseLengthUnit = (window->getSize()).x / 8.0f;
}

View::~View(){}

void View::displayGame(){
	window->clear();
	for(auto& s : sprites){
		auto it = this->animations.find(s.first);
		if(it != this->animations.end()){
			//There is an animation for this sprite and
			//set the correct frame of the animation
			s.second.setTextureRect(it->second.uvRect);
		}
		window->draw(s.second);
	}
	window->display();
}

bool View::isOpen() const{
	return window->isOpen();
}

void View::addSprite(int id, std::string texture){
	sf::Sprite spriteObj;
	//Get a reference to the Texture, since the constructor of sf::Sprite only takes that as argument.
	const sf::Texture& t = *((this->textures[texture]).get());
	spriteObj.setTexture(t);
	sprites[id] = spriteObj;
}

void View::scaleSprite(int id, float width, float height, bool sheet){
	sf::Sprite& curSprite = sprites[id];
	float realWidth       = width * this->baseLengthUnit;
	float realHeight      = height * this->baseLengthUnit;

	if (sheet){
		auto animation    = animations[id];
		float startWidth  = animation.uvRect.width;
		float startHeight = animation.uvRect.height;
		float scaleX      = realWidth / startWidth;
		float scaleY      = realHeight / startHeight;
		curSprite.scale(scaleX, scaleY);
		curSprite.setTextureRect(animation.uvRect);
	}

	//If it's not a sprite sheet and a normal texture, we just set it to repeat.
	else{
		curSprite.setTextureRect(sf::IntRect(0, 0, realWidth, realHeight));
	}
}

void View::addAnimation(int id, std::string texture){
	//Get the information of this texture's animation from the json file.
	auto animationInfo = this->texturesJson[texture];
	int frames    = animationInfo["frames"];
	int rows      = animationInfo["rows"];
	float switchT = animationInfo["switch_time"];

	Animation a{this->textures[texture], sf::Vector2u(frames, rows), switchT};
	animations.insert(std::pair<int, Animation>(id, a));
}

void View::informCreation(int id, float width, float height, std::string texture){
	//Create the sprite that matches with this object.
	addSprite(id, texture);
	sf::Sprite& curSprite = sprites[id];
	//Find out out if the provided texture element is a sprite sheet or just a normal texture.
	bool sheet = this->texturesJson[texture]["sprite_sheet"];
	//If it's a sprite sheet we can generate an animation.
	if(sheet){
		//Create the animation object with the texture.
		addAnimation(id, texture);
	}
	//Scale the sprite using the entities width and height.
	scaleSprite(id, width, height, sheet);
	//Center the origin of the sprite before we us it.
	sf::FloatRect bound_rect = curSprite.getLocalBounds();
	curSprite.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);
	curSprite.setPosition(-800.0f, 0.0f);
	}

void View::inform(int id, float x, float y){
	//Get the existing sprite
	try{
	sf::Sprite& curSprite = sprites.at(id);
	}
	catch(std::out_of_range& e){
		throw std::logic_error("pop");
	}
	float xPixels, yPixels;
	//Unpacking the pixel values that the Transformation object returned in the variables xPixels and yPixels.
	std::tie(xPixels, yPixels) = utils::Transformation::getInstance().coordinatesToPixels(x, y);
	sf::Sprite& sprite = sprites[id];
	sprite.setPosition(xPixels, yPixels);
	}

void View::informDeath(int id){
	return void();
}

void View::updateAnimations(){
	float elapsed = utils::Stopwatch::getInstance().getElapsedTime();
	for(auto& a : animations){
		a.second.update(elapsed);
	}
}

void View::deleteEntity(int ID){
	auto it = sprites.find(ID);
	if(it != sprites.end()){
		sprites.erase(it);
		auto it2 = animations.find(ID);
		if(it2 != animations.end()){
			animations.erase(it2);
		}
	}
}


}

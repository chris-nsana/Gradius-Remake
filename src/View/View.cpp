#include <iostream>
#include <fstream>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Utilities/Transformation.h"
#include "Utilities/Stopwatch.h"
#include "View.h"
#include "GameGlobals.h"

namespace View{

View::View(std::shared_ptr<sf::RenderWindow>& w, std::string texturesFile) : window(w){
	nlohmann::json textures;
	std::ifstream file{texturesFile};
	file >> textures;
	this->texturesJson = textures;

	for(auto it = textures.begin(); it != textures.end(); ++it ){
		auto textureName = it.key();
		auto file_path   = it.value()["image_path"];
		this->textures[textureName] = std::make_unique<sf::Texture>();
		this->textures[textureName]->loadFromFile(file_path);
	}
}

View::~View(){}

void View::displayGame(){
	window->clear();
	for(auto& s : sprites){
		(s.second).setTextureRect((animations[s.first]).uvRect);
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

/*
void View::addTexture(int typeOfEntity){
	std::shared_ptr<sf::Texture> sp = std::make_shared<sf::Texture>();

	switch(typeOfEntity){

	case 0:
		{sp->loadFromFile("./../resources/images/PlayerSprite.png");
		textures[typeOfEntity] = sp;
		break;}

	case 1:
		{sp->loadFromFile("./../resources/images/PlayerBullet.png");
		textures[typeOfEntity] = sp;
		break;}

	case 3:
		{
		if(level == 1) sp->loadFromFile("./../resources/images/BackgroundLevel1.png");
		else if(level == 2) sp->loadFromFile("./../resources/images/BackgroundLevel2.png");
		else if(level == 3) sp->loadFromFile("./../resources/images/BackgroundLevel3.jpg");
		textures[typeOfEntity] = sp;
		break;
		}

	case 4:
		{
		sp->setRepeated(true);
		if(level == 1) sp->loadFromFile("./../resources/images/BorderLevel1.png");
		else if(level == 2) sp->loadFromFile("./../resources/images/BorderLevel2.png");
		else if(level == 3) sp->loadFromFile("./../resources/images/BorderLevel3.png");
		textures[typeOfEntity] = sp;
		break;
		}



	default:
		throw std::invalid_argument("There is no texture found for this type of entity! Texture files might be missing from the project folder.");
	}
}*/

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
	//Create the animation object with the texture.
	addAnimation(id, texture);
	//Set the sprite to the starting animation frame.
	curSprite.setTextureRect(animations[id].uvRect);
	//Center the origin of the sprite before we us it.
	sf::FloatRect bound_rect = curSprite.getLocalBounds();
	curSprite.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);
	}


void View::inform(int id, float x, float y){
	//Get the existing sprite
	sf::Sprite& curSprite = sprites[id];
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
		animations.erase(it2);
	}
}


}

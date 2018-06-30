#include "View.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <tuple>
#include "Utilities/Transformation.h"
#include "Utilities/Stopwatch.h"
#include <iostream>
#include "GameGlobals.h"

namespace View{

View::View(std::shared_ptr<sf::RenderWindow>& w) : window(w){}

View::~View(){}

void View::displayGame(){
	window->clear();
	for(auto& sS : staticSprites){
		window->draw(sS.second);
	}
	for(auto& aS : animatedSprites){
		(aS.second).setTextureRect((animations[aS.first]).uvRect);
		window->draw(aS.second);
	}
	window->display();
}

bool View::isOpen() const{
	return window->isOpen();
}

void View::addSprite(int id, int typeOfEntity, bool animated){

	sf::Sprite s;
	//Get a reference to the Texture, since the constructor of sf::Sprite only takes that as argument.
	const sf::Texture& t = *(textures[typeOfEntity].get());
	s.setTexture(t);
	switch(typeOfEntity){

	case 0:
	{
		s.scale(sf::Vector2f(0.5f, 0.5f));
		break;
	}

	case 1:
	{
		s.scale(sf::Vector2f(0.25f, 0.25f));
		break;
	}

	case 3:
	{
		if(level == 1)s.scale(sf::Vector2f(0.7f, 0.7f));
		else if(level == 2) s.scale(sf::Vector2f(1.2444444f, 1.2444444f));
		else if(level == 3) s.scale(sf::Vector2f(0.7f, 0.7f));
		break;
	}

	case 4:
		//scaling is not needed for this type
		break;




	default:
		throw std::invalid_argument("Can't create sprite of this type!");
	}

	if(animated) animatedSprites[id] = s;
	else staticSprites[id] = s;
}

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
}

void View::addAnimation(int id, int typeOfEntity){
	Animation a{textures[typeOfEntity], sf::Vector2u(5, 2), 0.1f};
	animations.insert(std::pair<int, Animation>(id, a));
}

bool View::isAnimated(int type){
	 switch(type){
	 case 0:
		 return true;

	 default:
		 return false;

	 }
}

void View::inform(float x, float y, int id, int type){

	bool animated = isAnimated(type);
	std::map<int, sf::Sprite>::iterator aIterator = animatedSprites.find(id);
	std::map<int, sf::Sprite>::iterator sIterator = staticSprites.find(id);


	//Check whether View already knows of this object's existence
	if((aIterator == animatedSprites.end()) and (sIterator == staticSprites.end())){
		//New objects without sprites don't have animations either, but we need the Texture before we can make Animation objects.
		//Check if the texture is there, we use count() instead of find() because we don't need the iterator.
		if(!(textures.count(type)> 0)){
			//Create the texture for the given type.
			addTexture(type);
		}
		//Create the sprite that matches with this object.
		addSprite(id, type, animated);
		if(animated){
		sf::Sprite& curSprite = animatedSprites[id];
		//Create the animation object with the texture.
		addAnimation(id, type);
		//Set the sprite to the starting animation frame.
		curSprite.setTextureRect(animations[id].uvRect);
		//Center the origin of the sprite before we us it.
		sf::FloatRect bound_rect = curSprite.getLocalBounds();
		curSprite.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);
		}
		else{
			sf::Sprite& curSprite = staticSprites[id];
			sf::Texture& tx = *(textures[type].get());
			curSprite.setTexture(tx);
			//Center the origin of the sprite before we us it.
			sf::FloatRect bound_rect = curSprite.getLocalBounds();
			curSprite.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);
			//Special case for the border sprites
			if(type == 4){
				curSprite.setTextureRect(sf::IntRect(0, 0, 1120, 60));
				sf::FloatRect bound_rect = curSprite.getLocalBounds();
				curSprite.setOrigin(bound_rect.left + bound_rect.width/2.0f, bound_rect.top  + bound_rect.height/2.0f);
			}
		}


	}

	//The object either exist or is created now. We can move the object according to the changes now.
	float xPixels, yPixels;
	//Unpacking the pixel values that the Transformation object returned in the variables xPixels and yPixels.
	std::tie(xPixels, yPixels) = utils::Transformation::getInstance().coordinatesToPixels(x, y);
	if(animated){
		sf::Sprite& sprite = animatedSprites[id];
		sprite.setPosition(xPixels, yPixels);
	}
	else{
		//std::cout << id << " op locatie " << xPixels << " en " << yPixels << std::endl;
		sf::Sprite& sprite = staticSprites[id];
		sprite.setPosition(xPixels, yPixels);
	}


}

void View::updateAnimations(){

	float elapsed = utils::Stopwatch::getInstance().getElapsedTime();
	for(auto& a : animations){
		a.second.update(elapsed);
	}
}

void View::deleteEntity(int ID){
	auto it = animatedSprites.find(ID);
	if(it != animatedSprites.end()){
		animatedSprites.erase(it);
		auto it2 = animations.find(ID);
		animations.erase(it2);
	}
	else{
		auto it3 = staticSprites.find(ID);
		staticSprites.erase(it3);
	}
}


}

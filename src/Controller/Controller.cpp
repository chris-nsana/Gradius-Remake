#include "Controller.h"
#include "Model/Model.h"
#include "Utilities/Stopwatch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameGlobals.h"

namespace Controller{
Controller::Controller(std::shared_ptr<Model::Model>& m, std::shared_ptr<sf::RenderWindow>& w) : model(m), window(w),
		pTime(0.0125f), movementPattern(0), gunJammed(0){
	//This is an important setting to correctly handle keyboard input.
	//This basically means that holding a key won't fill the Event queue with multiple events of that key.
	window->setKeyRepeatEnabled(false);
}

Controller::~Controller(){}

void Controller::processInput(){

	float xMovement = 0;
	float yMovement = 0;
	//Did the player fire a bullet in this tick?
	bool fired = false;
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) resulting += 5;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) resulting +=3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) resulting -=3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) resulting -= 5;*/


	sf::Event event;

	switch(this->movementPattern){

	case 5:
		xMovement += 0.0375f;
		break;

	case 3:
		yMovement += 0.025f;
		break;

	case -3:
		yMovement -= 0.025f;
		break;

	case -5:
		xMovement -= 0.025f;
		break;

	case 0:
		//do nothing because there was no movement or the movement cancelled eachother out
		//std::cout << "wtf bro" << std::endl;
		break;

	case 8:
		//Diagonal up + right
		xMovement += 0.025;
		yMovement += 0.025f;
		break;

	case 2:
		//Diagonal right + down;
		xMovement += 0.025f;
		yMovement -= 0.025f;
		break;

	case -2:
		//Diagonal left + up
		xMovement -= 0.025f;
		yMovement += 0.025f;
		break;

	case -8:
		//Diagonal left + down
		xMovement -= 0.025f;
		yMovement -= 0.025f;
		break;

	}

	while(window->pollEvent(event)){

		//The combination of pressed keys determines how we should move, so to always have a valid state of movement
		//the Controller class keeps a movementPattern that changes when keys are pressed or keys are not pressed.
		//This is how the movementPatten should change when a new key gets pressed.
		if(event.type == sf::Event::KeyPressed){
			switch(event.key.code){

			case sf::Keyboard::Key::Right :
				movementPattern += 5;
				break;

			case sf::Keyboard::Key::Up :
				movementPattern += 3;
				break;

			case sf::Keyboard::Key::Down :
				movementPattern -= 3;
				break;

			case sf::Keyboard::Key::Left :
				movementPattern -= 5;
				break;

			case sf::Keyboard::Key::Space :
			{//The gun is not jammed so player can fire. But it will be jammed for the next frame.
				if(gunJammed == 0){
					gunJammed += 15;
					fired = true;
					model->playerFire();
					break;
					}
				}


			default:
				break;


			}

		}
		//This is how the movementPattern should change when a key gets released.
		else if(event.type == sf::Event::KeyReleased){
			switch(event.key.code){

			case sf::Keyboard::Key::Right :
				movementPattern -= 5;
				break;

			case sf::Keyboard::Key::Up :
				movementPattern -= 3;
				break;

			case sf::Keyboard::Key::Down :
				movementPattern += 3;
				break;

			case sf::Keyboard::Key::Left :
				movementPattern += 5;
				break;

			default:
				break;


			}

		}




		else if (event.type == sf::Event::Closed) window->close();

	}
	//Release the jam because the player couldn't fire this frame
	if((!fired) and (gunJammed > 0)) gunJammed -= 1;
	model->movePlayer(xMovement, yMovement);


}

}

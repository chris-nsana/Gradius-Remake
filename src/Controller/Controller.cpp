#include "Controller.h"
#include "Model/Model.h"
#include "Model/Entities/Player.h"
#include "Utilities/Stopwatch.h"
#include "Utilities/Transformation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Controller{
Controller::Controller(std::shared_ptr<Model::Model> model, std::shared_ptr<sf::RenderWindow> window, bool co_op)
 : model(model), window(window), co_op(co_op), paused(false){}

Controller::~Controller(){}

void Controller::processInput(){
	//Process the keyboard events / window events
	sf::Event event;
	while(window->pollEvent(event)){
		//The combination of pressed keys determines how we should move, so to always have a valid state of movement
		//the Controller class keeps track of the changes when keys are pressed or keys are not pressed.

		//This is how the movementPatten should change when a new key gets pressed.
		if(event.type == sf::Event::KeyPressed){
      //This key pauses the game and should also pause the control of other keys.
      if(event.key.code == sf::Keyboard::Key::P){
        pauseControl();
      }
      else{
        processKeyPressed(event);
      }
		}
		//This is how the movement should change when a key gets released.
    //and the Controller is not paused.
		else if(event.type == sf::Event::KeyReleased){
			processKeyReleased(event);
		}

    else if(event.type == sf::Event::Resized){
      utils::Transformation::getInstance().resizeWindow(this->window, event);
    }

    //This case should be handled regardless if the Controller is paused.
		else if(event.type == sf::Event::Closed){
			window->close();
		}
	}

  if(!paused){
    //Control the players with the state of the current pressed keys.
    controlPlayer1();
    controlPlayer2();
  }
}

void Controller::processKeyPressed(sf::Event& event){
	switch(event.key.code){
		case sf::Keyboard::Key::Right :
			p1Movement.right = true;
			break;

		case sf::Keyboard::Key::D :
			p2Movement.right  = true;
			break;

		case sf::Keyboard::Key::Up :
			p1Movement.up = true;
			break;

		case sf::Keyboard::Key::W :
		case sf::Keyboard::Key::Z :
			p2Movement.up = true;
			break;

		case sf::Keyboard::Key::Down :
			p1Movement.down = true;
			break;

		case sf::Keyboard::Key::S :
			p2Movement.down = true;
			break;

		case sf::Keyboard::Key::Left :
			p1Movement.left = true;
			break;

		case sf::Keyboard::Key::A :
		case sf::Keyboard::Key::Q :
			p2Movement.left = true;
			break;

		case sf::Keyboard::Key::Space :
		{ if(paused) break;
      try{
        auto& p1 = model->getPlayer1();
			  p1.fire();
      }
      catch(std::out_of_range& e){}
			break;
		}

		case sf::Keyboard::Key::J :
		{
		  if(!co_op or paused) break;
      try{
  			auto& p2 = model->getPlayer2();
  			p2.fire();
      }
      catch(std::out_of_range& e){}
			break;
			}
		}
}

void Controller::processKeyReleased(sf::Event& event){
	switch(event.key.code){
		case sf::Keyboard::Key::Right :
			p1Movement.right = false;
			break;

		case sf::Keyboard::Key::D :
			p2Movement.right  = false;
			break;

		case sf::Keyboard::Key::Up :
			p1Movement.up = false;
			break;

		case sf::Keyboard::Key::W :
		case sf::Keyboard::Key::Z :
			p2Movement.up = false;
			break;

		case sf::Keyboard::Key::Down :
			p1Movement.down = false;
			break;

		case sf::Keyboard::Key::S :
			p2Movement.down = false;
			break;

		case sf::Keyboard::Key::Left :
			p1Movement.left = false;
			break;

		case sf::Keyboard::Key::A :
		case sf::Keyboard::Key::Q :
			p2Movement.left = false;
			break;
    }
}

void Controller::pauseControl(){
  if(!paused){
    paused = true;
    model->freeze();
  }
  else if(paused){
    paused = false;
    model->unfreeze();
  }
}

void Controller::controlPlayer(Model::Player& player, bool p1){
	playerMovement curPlayer;
	if(p1) curPlayer = p1Movement;
	else   curPlayer = p2Movement;
	//Pressing opposing bullets cancels out the movement
	if(curPlayer.left and !curPlayer.right) player.moveLeft();

	if(curPlayer.right and !curPlayer.left) player.moveRight();

	if(curPlayer.up and !curPlayer.down) player.moveUp();

	if(curPlayer.down and !curPlayer.up)player.moveDown();

}

void Controller::controlPlayer1(){
  try{
    Model::Player& p1 = model->getPlayer1();
    controlPlayer(p1, true);
  }
  catch(std::out_of_range& e){return void();}
}

void Controller::controlPlayer2(){
	//There is no need to control player 2 if we're not in co-op mode.
	if(!co_op) return void();
  try{
    Model::Player& p2 = model->getPlayer2();
    controlPlayer(p2, false);
  }
  catch(std::out_of_range& e){return void();}
}

}

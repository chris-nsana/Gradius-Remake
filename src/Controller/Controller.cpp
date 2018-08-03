#include "Controller.h"
#include "Model/Model.h"
#include "Model/Entities/Player.h"
#include "Utilities/Stopwatch.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Controller{
Controller::Controller(std::shared_ptr<Model::Model> model, std::shared_ptr<sf::RenderWindow> window, bool co_op)
 : model(model), window(window), p1Movement(0), p2Movement(0), co_op(co_op), paused(false){
	//This is an important setting to correctly handle keyboard input.
	//This basically means that holding a key won't fill the Window Event queue with multiple events of that key.
	window->setKeyRepeatEnabled(false);
}

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
      if(event.key.code == sf::Keyboard::Key::Escape){
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
			p1Movement += 5;
			break;

		case sf::Keyboard::Key::D :
			p2Movement += 5;
			break;

		case sf::Keyboard::Key::Up :
			p1Movement += 3;
			break;

		case sf::Keyboard::Key::W :
		case sf::Keyboard::Key::Z :
			p2Movement += 3;
			break;

		case sf::Keyboard::Key::Down :
			p1Movement -= 3;
			break;

		case sf::Keyboard::Key::S :
			p2Movement -= 3;
			break;

		case sf::Keyboard::Key::Left :
			p1Movement -= 5;
			break;

		case sf::Keyboard::Key::A :
		case sf::Keyboard::Key::Q :
			p2Movement -= 5;
			break;

		case sf::Keyboard::Key::Space :
		{ if(paused) break;
      auto& p1 = model->getPlayer1();
			p1.fire();
			break;
		}

		case sf::Keyboard::Key::J :
		{
		  if(!co_op or paused) break;
			auto& p2 = model->getPlayer2();
			p2.fire();
			break;
			}
		}
}

void Controller::processKeyReleased(sf::Event& event){
	switch(event.key.code){
		case sf::Keyboard::Key::Right :
      //In some cases the Controller can detect KeyReleased events without the accompanying KeyPressed event.
      //We only want let the released key to have have effect if there was an effect of KeyPressed, we can check
      //this using the movementPatterns which has deterministic values.
      p1Movement -= 5;
			break;

		case sf::Keyboard::Key::D :
      p1Movement -= 5;
			break;

		case sf::Keyboard::Key::Up :
			p1Movement -= 3;
			break;

		case sf::Keyboard::Key::W :
		case sf::Keyboard::Key::Z :
			p2Movement -= 3;
			break;

		case sf::Keyboard::Key::Down :
			p1Movement += 3;
			break;

		case sf::Keyboard::Key::S :
			p2Movement += 3;
			break;

		case sf::Keyboard::Key::Left :
			p1Movement += 5;
			break;

		case sf::Keyboard::Key::A :
		case sf::Keyboard::Key::Q :
			p2Movement += 5;
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

void Controller::controlPlayer(Model::Player& player, int pattern){
	switch(pattern){

		case 5:
			player.moveRight();
			break;

		case 3:
			player.moveUp();
			break;

		case -3:
			player.moveDown();
			break;

		case -5:
			player.moveLeft();
			break;

		case 0:
			//Do nothing because there was no movement or the keys cancelled eachother out.
			break;

		case 8:
			//Diagonal (up + right)
			player.moveRight();
			player.moveUp();
			break;

		case 2:
			//Diagonal (right + down)
			player.moveRight();
			player.moveDown();
			break;

		case -2:
			//Diagonal (left + up)
			player.moveLeft();
			player.moveUp();
			break;

		case -8:
			//Diagonal (left + down)
			player.moveLeft();
			player.moveDown();
			break;

		}
}

void Controller::controlPlayer1(){
  try{
    Model::Player& p1 = model->getPlayer1();
    controlPlayer(p1, p1Movement);
  }
  catch(std::out_of_range& e){return void();}
}

void Controller::controlPlayer2(){
	//There is no need to control player 2 if we're not in co-op mode.
	if(!co_op) return void();
  try{
    Model::Player& p2 = model->getPlayer2();
    controlPlayer(p2, p2Movement);
  }
  catch(std::out_of_range& e){return void();}
}

}

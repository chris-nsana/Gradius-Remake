#include "Controller.h"
#include "Model/Model.h"
#include "Model/Entities/Player.h"
#include "Utilities/Stopwatch.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Controller{
Controller::Controller(std::shared_ptr<Model::Model> model, std::shared_ptr<sf::RenderWindow> window, bool co_op)
 : model(model), window(window), p1Movement(0), p2Movement(0), co_op(co_op), paused(false){}

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

    else if(event.type == sf::Event::Resized){
      resizeWindow(event);
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
      //In some cases the Controller can detect KeyReleased events without the accompanying KeyPressed event.
      //We only want let the released key to have have effect if there was an effect of KeyPressed, we can check
      //this using the movementPatterns which has deterministic values.
      p1Movement -= 5;
			break;

		case sf::Keyboard::Key::D :
      p2Movement -= 5;
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

void Controller::resizeWindow(sf::Event& resizeEvent){
  sf::View newView;
  newView.reset(sf::FloatRect(0, 0, 800, 600));

  //This means we're going from smallscreen to fullscreen
  if(resizeEvent.size.height > 600){
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

}

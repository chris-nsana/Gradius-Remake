#include "Game.h"
#include "Model/Model.h"
#include "Controller/Controller.h"
#include "View/View.h"
#include "Model/Entities/Entity.h"
#include "Utilities/Stopwatch.h"
#include "Model/Entities/Player.h"
#include "GameGlobals.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>


int tickNumber = 0;
int level = 0;
int lives = 5;

using nlohmann::json;

Game::Game() : initialized(false){}

void Game::init(){

	json config;
	std::ifstream file("./../resources/config.json");
	file >> config;
	std::vector<std::string> allLevels = config["levels"];
	levels = allLevels;
	level = config["startingLevel"];
	std::string beginLevel = "./../resources/levels/" + allLevels[level-1];
	std::ifstream currentLevel(beginLevel);
	json levelInfo;
	currentLevel >> levelInfo;
	std::vector<json> elements = levelInfo["Elements"];
	this->levelElements = std::move(elements);
	elementPtr = levelElements.begin();
	initialized = true;

}

void Game::readLevel(){

	for(auto it = elementPtr; it != levelElements.end(); ++it){
		//If it's time to process this element
		if(tickNumber == (*it)["timeframe"]){
			bool dynamic = (*it)["dynamic"];
			int type = (*it)["type"];
			float x = (*it)["posX"];
			float y = (*it)["posY"];
			gameModel->createEntity(x, y, type, dynamic);

		}
		//Else it's too early and we wait. All events after this one also have to wait so we break out of the method.
		else{
			//Store this location in the vector to resume at later ticks.
			elementPtr = it;
			return void();
		}
	}
	//If all elements are already read
	elementPtr = levelElements.end();

}

void Game::Run(){
	//The game runs at 60 ticks per second, tick takes 1.0/60.0 seconds.
	if(!initialized) throw std::runtime_error("Game::Init() has not been called before running the game!");
	float tick = 1.0f / 60.0f;
	std::shared_ptr<sf::RenderWindow> window  = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600),
	"Gradius", sf::Style::Close);
	gameView    = std::make_shared<View::View>(window, "./../resources/textures.json");
	Model::Entity::Attach(gameView);
	gameModel   = std::make_shared<Model::Model>("./../resources/entities.json", false);
	gameControl = std::make_shared<Controller::Controller>(gameModel, window);


	gameModel->setLevel();




	while(gameView->isOpen()){
		utils::Stopwatch::getInstance().reset();
		//Process what the keyboard and view get as input
		gameControl->processInput();
		//Let the entities do their behaviour for this tick
		gameModel->update();
		//Read the next thing to do / create in the levelfile
		readLevel();
		//Notify the observer of all the changes that happened in this tick
		gameModel->massNotify();
		//Display these changes
		gameView->displayGame();
		//Wait for tick to finish if necessary
		while(utils::Stopwatch::getInstance().getElapsedTime() < tick){}
		//consistently update the animation frames after a tick
		gameView->updateAnimations();
		//increase the ammount of ticks that happened in this game by 1
		tickNumber += 1;

    }
}

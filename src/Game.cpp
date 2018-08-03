#include "Game.h"
#include "Model/Model.h"
#include "Model/Entities/Entity.h"
#include "Model/Events.h"
#include "Controller/Controller.h"
#include "View/View.h"
#include "Utilities/Stopwatch.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>


Game::Game(){}

void Game::init(bool co_op){
	nlohmann::json config;
	std::ifstream file("./../resources/config.json");
	file >> config;
	std::string entitiesFile        = config["entitiesFile"];
	std::string texturesFile        = config["texturesFile"];
	std::vector<std::string> levels = config["levels"];
	int startingLevel               = config["startingLevel"];
	int lives                       = config["playerLives"];

	std::shared_ptr<sf::RenderWindow> window  = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Gradius", sf::Style::Close);
	gameView         = std::make_shared<View::View>(window, texturesFile);
	Model::Entity::attach(gameView);
	gameModel        = std::make_shared<Model::Model>(entitiesFile, std::move(levels), startingLevel, lives, co_op);
	gameModel->attach(gameView);
	Model::Event::setModel(gameModel);
	gameControl      = std::make_shared<Controller::Controller>(gameModel, window, co_op);
}

void Game::run(){
	init();
	float tick     = 1.0f / 60.0f;
	int tickNumber = 0;
	gameModel->startLevel();

	while(gameModel->isActive()){
		utils::Stopwatch::getInstance().reset();
		//Process what the keyboard and view get as input
		gameControl->processInput();
		//Let the entities do their behaviour for this tick
		gameModel->update();
		//Wait for tick to finish if necessary
		while(utils::Stopwatch::getInstance().getElapsedTime() < tick){}
		//Consistently update the animation frames after a tick
		gameView->updateAnimations();
		//Display these changes
		gameView->displayGame();
		//Increase the ammount of ticks that happened in this game by 1
		tickNumber += 1;
		//Also update this in the Model
		gameModel->tick();
    }

}

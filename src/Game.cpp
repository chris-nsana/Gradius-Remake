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

void Game::init(){}

void Game::Run(){
	float tick = 1.0f / 60.0f;
	std::shared_ptr<sf::RenderWindow> window  = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600),
	"Gradius", sf::Style::Close);
	gameView    = std::make_shared<View::View>(window, "./../resources/textures.json");
	Model::Entity::Attach(gameView);
	gameModel   = std::make_shared<Model::Model>("./../resources/entities.json", true);
	gameControl = std::make_shared<Controller::Controller>(gameModel, window);
	gameModel->startLevel();

	while(gameView->isOpen()){
		utils::Stopwatch::getInstance().reset();
		//Process what the keyboard and view get as input
		gameControl->processInput();
		//Let the entities do their behaviour for this tick
		gameModel->update();
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

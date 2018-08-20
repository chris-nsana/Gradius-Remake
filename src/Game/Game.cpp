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


Game::Game() : gameMenu(*this){}

void Game::init(bool co_op){
	nlohmann::json config;
	std::ifstream file("./../resources/config.json");
	file >> config;
	std::string entitiesFile        = config["entitiesFile"];
	std::string texturesFile        = config["texturesFile"];
	std::string mainFont            = config["mainFont"];
	std::vector<std::string> levels = config["levels"];
	int startingLevel               = config["startingLevel"];
	int lives                       = config["playerLives"];

	window           = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Gradius", sf::Style::Close);
	gameView         = std::make_shared<View::View>(window, texturesFile, mainFont, co_op);
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
    }

		std::cout << "Model Ended" << std::endl;
}

Game::Menu::Menu(Game& game) : game(game){}

void Game::Menu::presentMainOptions(){
	int totalOptions  = 3;
	int currentOption = 1;
	int entered       = 0;
	auto width        = game.window->getSize().x;
	auto height       = game.window->getSize().y;

	sf::Text play;
	play.setColor(sf::Color::Red);
	play.setString("PLAY");
	play.setPosition(sf::Vector2f(width/2, (0.5 * height)));

	sf::Text levelSelect;
	levelSelect.setColor(sf::Color::White);
	levelSelect.setString("LEVEL SELECT");
	levelSelect.setPosition(sf::Vector2f(width/2, (0.5 * height) + ((0.5 * height)/3.0)));

	sf::Text score;
	score.setColor(sf::Color::White);
	score.setString("SCOREBOARD");
	score.setPosition(sf::Vector2f(width/2, (0.5 * height) + ((0.5 * height)/3.0) * 2));

	while(true){
		sf::Event event;
		if(game.window->pollEvent(event)){
			if(event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Key::Down){
					currentOption += 1;
					if(currentOption > totalOptions) currentOption = totalOptions;
				}

			}

		}
	}


}

void Game::Menu::presentLevelOptions(){}

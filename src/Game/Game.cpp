#include "Game.h"
#include "Model/Model.h"
#include "Model/Entities/Entity.h"
#include "Model/Events.h"
#include "View/View.h"
#include "Controller/Controller.h"
#include "Utilities/Stopwatch.h"
#include <fstream>
#include <iostream>
#include <utility>



Game::Game() : gameMenu(*this), startingLevel(1){
	std::ifstream file("./../resources/config.json");
	file >> this->configuration;
	window  = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Gradius", sf::Style::Close);
	this->gameFont.loadFromFile(configuration["gameFont"]);
	this->errorFont.loadFromFile(configuration["errorFont"]);

}

void Game::start(){
	this->gameMenu.presentMainOptions();
}

void Game::init(bool co_op){
	std::string entitiesFile        = configuration["entitiesFile"];
	std::string texturesFile        = configuration["texturesFile"];
	std::string gameFont            = configuration["gameFont"];
	std::vector<std::string> levels = configuration["levels"];
	int lives                       = configuration["playerLives"];


	gameView         = std::make_shared<View::View>(window, texturesFile, gameFont, co_op);
	Model::Entity::attach(gameView);
	gameModel        = std::make_shared<Model::Model>(entitiesFile, std::move(levels), startingLevel, lives, co_op);
	gameModel->attach(gameView);
	Model::Event::setModel(gameModel);
	gameControl      = std::make_shared<Controller::Controller>(gameModel, window, co_op);
}

void Game::run(){
	float tick     = 1.0f / 60.0f;
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
    }
		std::cout << "Model Ended" << std::endl;

}

Game::Menu::Menu(Game& game) : game(game){}

void Game::Menu::presentMainOptions(){
	int totalOptions  = 3;
	int currentOption = 1;
	auto width        = game.window->getSize().x;
	auto height       = game.window->getSize().y;
	std::map<int, sf::Text> textMap;

	sf::Text play("PLAY", game.gameFont);
	play.setColor(sf::Color::Red);
	play.setPosition(sf::Vector2f(0.10 * width, (0.5 * height)));
	textMap[currentOption] = play;

	sf::Text levelSelect("LEVEL SELECT", game.gameFont);
	levelSelect.setColor(sf::Color::White);
	levelSelect.setPosition(sf::Vector2f(0.10 * width, (0.5 * height) + ((0.5 * height)/3.0)));
	textMap[currentOption+1] = levelSelect;

	sf::Text score("SCOREBOARD", game.gameFont);
	score.setColor(sf::Color::White);
	score.setPosition(sf::Vector2f(0.10 * width, (0.5 * height) + ((0.5 * height)/3.0) * 2));
	textMap[currentOption+2] = score;

	while(true){
		sf::Event event;
		if(game.window->pollEvent(event)){
			if(event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Key::Down){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption += 1;
					if(currentOption > totalOptions) currentOption = totalOptions;
					textMap[currentOption].setColor(sf::Color::Red);
				}
				else if(event.key.code == sf::Keyboard::Key::Up){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption -= 1;
					if(currentOption < 1) currentOption = 1;
					textMap[currentOption].setColor(sf::Color::Red);
				}

				else if(event.key.code == sf::Keyboard::Key::Return){
					if(currentOption == 1) return modeSelection();
					else if(currentOption == 2) return levelSelection();
					else if (currentOption == 3) return void();
				}
			}
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->display();
	}
}

void Game::Menu::modeSelection(){
	int totalOptions  = 2;
	int currentOption = 1;
	auto width        = game.window->getSize().x;
	auto height       = game.window->getSize().y;
	std::map<int, sf::Text> textMap;

	sf::Text single("SINGLE-PLAYER MODE", game.gameFont);
	single.setColor(sf::Color::Red);
	single.setPosition(sf::Vector2f(0.10 * width, (0.5 * height)));
	textMap[currentOption] = single;

	sf::Text coop("CO-OP MODE", game.gameFont);
	coop.setColor(sf::Color::White);
	coop.setPosition(sf::Vector2f(0.10 * width, (0.5 * height) + ((0.5 * height)/3.0)));
	textMap[currentOption+1] = coop;

	while(true){
		sf::Event event;
		if(game.window->pollEvent(event)){
			if(event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Key::Down){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption += 1;
					if(currentOption > totalOptions) currentOption = totalOptions;
					textMap[currentOption].setColor(sf::Color::Red);
				}
				else if(event.key.code == sf::Keyboard::Key::Up){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption -= 1;
					if(currentOption < 1) currentOption = 1;
					textMap[currentOption].setColor(sf::Color::Red);
				}
				else if(event.key.code == sf::Keyboard::Key::Return){
					if(currentOption == 1) game.init(false);
					else if(currentOption == 2) game.init(true);
					return game.run();
				}

			}
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->display();
	}
}

void Game::Menu::levelSelection(){
	int totalOptions;
	int currentOption = 1;
	auto width        = game.window->getSize().x;
	auto height       = game.window->getSize().y;
	std::map<int, sf::Text> textMap;

	int totalLevels   = game.configuration["levels"].size();
	totalOptions      = totalLevels;
	for(int i = 0; i < totalLevels; i += 1){
		std::string title = "LEVEL " + std::to_string(i+1);
		sf::Text temp(title, game.gameFont);
		float yPosition =  (0.5 * height) + (i * ((0.5 * height) / (float)totalLevels));
		temp.setPosition(sf::Vector2f(0.10 * width, yPosition));
		temp.setColor (sf::Color::White);
		textMap[i+1] = temp;
	}
	//Make the first choice red as usual.
	textMap.begin()->second.setColor(sf::Color::Red);

	while(true){
		sf::Event event;
		if(game.window->pollEvent(event)){
			if(event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Key::Down){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption += 1;
					if(currentOption > totalOptions) currentOption = totalOptions;
					textMap[currentOption].setColor(sf::Color::Red);
				}
				else if(event.key.code == sf::Keyboard::Key::Up){
					textMap[currentOption].setColor(sf::Color::White);
					currentOption -= 1;
					if(currentOption < 1) currentOption = 1;
					textMap[currentOption].setColor(sf::Color::Red);
				}
				else if(event.key.code == sf::Keyboard::Key::Return){
					game.startingLevel = currentOption;
					return modeSelection();
				}

			}
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->display();
	}

}

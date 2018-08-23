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
	window  = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Gradius", sf::Style::Close | sf::Style::Resize);
	//This is an important setting to correctly handle keyboard input.
	//This basically means that holding a key won't fill the Window Event queue with multiple events of that key.
	window->setKeyRepeatEnabled(false);
	this->gameFont.loadFromFile(configuration["gameFont"]);
	this->errorFont.loadFromFile(configuration["errorFont"]);
	this->scoreboard = Scoreboard(configuration["scoreFile"], this->gameFont);

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

void Game::resizeWindow(sf::Event& resizeEvent){
  sf::View newView;
  newView.reset(sf::FloatRect(0, 0, 800, 600));

  auto maxVideo    = sf::VideoMode::getDesktopMode();
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

Game::Menu::Menu(Game& game) : game(game){}

void Game::Menu::presentMainOptions(){
	int totalOptions  = 3;
	int currentOption = 1;
	auto width        = game.window->getSize().x;
	auto height       = game.window->getSize().y;
	std::map<int, sf::Text> textMap;

	sf::Sprite logo;
	sf::Texture logoTexture;
	logoTexture.loadFromFile(game.configuration["gameLogo"]);
	logo.setTexture(logoTexture);
	float startWidth  = (float)logo.getTextureRect().width;
	float startHeight = (float)logo.getTextureRect().height;
	float scale       = width / startWidth;
	logo.scale(scale, scale);

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
					else if (currentOption == 3)
						return game.scoreboard.showScoreboard(game.window);
				}
			}
			else if(event.type == sf::Event::Resized){
				game.resizeWindow(event);
			}
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->draw(logo);
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
			else if(event.type == sf::Event::Resized){
				game.resizeWindow(event);
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
			else if(event.type == sf::Event::Resized){
				game.resizeWindow(event);
			}
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->display();
	}

}

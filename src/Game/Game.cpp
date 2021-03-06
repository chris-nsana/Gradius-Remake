#include "Game.h"
#include "Game/GameExceptions.h"
#include "Model/Model.h"
#include "Model/Entities/Entity.h"
#include "Model/Events.h"
#include "View/View.h"
#include "Controller/Controller.h"
#include "Utilities/Stopwatch.h"
#include "Utilities/Transformation.h"
#include <fstream>
#include <iostream>
#include <utility>

namespace Game{

Game::Game() : gameMenu(*this), startingLevel(1) {
	std::ifstream file("./../resources/config.json");
	if(!file.is_open()) throw FileNotFoundError("Configuration file", "./../resources/config.json");
	try{
		file >> this->configuration;
	}
	catch(...){throw InvalidFileError("Configuration file");}
	int resX;
	int resY;
	std::string fontPath1;
	std::string fontPath2;
	std::string scoreFile;
	try{
		resX      = configuration["resolutionX"];
		resY      = configuration["resolutionY"];
		fontPath1 = configuration["gameFont"];
		fontPath2 = configuration["errorFont"];
		scoreFile = configuration["scoreFile"];
	}
	catch(...){
		throw InvalidInputError("Config file", "Invalid input detected.");
	}
	//If the aspect ratio doesn't match the expected value default to 800x600
	if(((float)resX  / (float)resY) !=  (4.0f/3.0f)){
		resX = 800.0f;
		resY = 600.0f;
	}
	//This is how much pixels corresponds to 1.0 in the game's coordinate system.
	float pixelUnit = (float)resX / 8.0f;
	utils::Transformation::getInstance().setLengthUnit(pixelUnit);
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(resX, resY), "Gradius", sf::Style::Close | sf::Style::Resize);
	this->resolution = {resX, resY};
	//This is an important setting to correctly handle keyboard input.
	//This basically means that holding a key won't fill the Window Event queue with multiple events of that key.
	window->setKeyRepeatEnabled(false);
	this->gameFont.loadFromFile(fontPath1);
	this->errorFont.loadFromFile(fontPath2);
	scoreboard = Scoreboard(scoreFile, this->gameFont);

}

void Game::start(){
	try{
		this->gameMenu.presentMainOptions();
	}
	catch(InternalError& e){
	  showErrorMessage("Internal error occured.");
	}
	catch(ExternalError& e){
		showErrorMessage(e.what());
	}
}

void Game::init(bool co_op){

	std::string entitiesFile;
	std::string texturesFile;
	std::string gameFont;
	std::vector<std::string> levels;
	int lives;

	try{
		entitiesFile                = configuration["entitiesFile"];
	  texturesFile                = configuration["texturesFile"];
		gameFont                    = configuration["gameFont"];
		std::vector<std::string> t  = configuration["levels"];
		levels                      = t;
		lives                       = configuration["playerLives"];
	}

	catch(...){
		throw InvalidInputError("Config file", "Invalid input detected.");
	}

	gameView         = std::make_shared<View::View>(window, texturesFile, gameFont, co_op);
	gameModel        = std::make_shared<Model::Model>(entitiesFile, std::move(levels), startingLevel, lives, co_op);
	gameModel->attach(gameView);
	Model::Event::setModel(gameModel);
	gameControl      = std::make_shared<Controller::Controller>(gameModel, window, co_op);
}

void Game::run(){
	float tick     = 1.0f / 60.0f;
	gameModel->startLevel();

	while(gameModel->isActive() and window->isOpen()){
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
	//The Model has ended either because of a loss or because of a win and the window is still open.
	if(window->isOpen()){
		if(gameModel->isWinningState()) showVictoryScreen();
		else showLossScreen();
		int p1Score = gameModel->getPlayerScore(true);
		int p2Score = gameModel->getPlayerScore(false);
		//If this score deserves a place in the highscores;
		if(scoreboard.checkEntry(p1Score)){
			showHighscoreMessage(true);
			std::string playerName = scoreboard.promptName(this->resolution, this->window);
			scoreboard.addEntry(p1Score, playerName);
		}

		if(scoreboard.checkEntry(p2Score)){
			showHighscoreMessage(false);
			std::string playerName = scoreboard.promptName(this->resolution, this->window);
			scoreboard.addEntry(p2Score, playerName);
		}
	}


}

void Game::showVictoryScreen(){
	showSimpleTextOnScreen("VICTORY", sf::Color::Green);
}

void Game::showLossScreen(){
	showSimpleTextOnScreen("GAME OVER", sf::Color::Red);
}

void Game::showHighscoreMessage(bool p1){
	std::string text;
	if(p1) text = "PLAYER 1 REACHED HIGHSCORE!";
	else text = "PLAYER 2 REACHED HIGHSCORE!";
	showSimpleTextOnScreen(text, sf::Color::Blue);
}

void Game::showErrorMessage(std::string message){
	float width       = static_cast<float>(this->resolution.first);
	float height      = static_cast<float>(this->resolution.second);
	std::cout << "An error occured! Details:" << std::endl;
	std::cout << message << std::endl;

	sf::Text t1("An error occured! Details:", this->errorFont);
	t1.setCharacterSize(21);
	t1.setPosition(sf::Vector2f(0.0f, 0.0f));

	sf::Text t2(message, this->errorFont);
	t2.setCharacterSize(21);
	t2.setPosition(sf::Vector2f(0.0f, 0.5 * height));

	while(window->isOpen()){
		sf::Event event;
		if(window->pollEvent(event)){
			if(event.type == sf::Event::Closed) window->close();
		}

		else if(event.type == sf::Event::Resized){
			utils::Transformation::getInstance().resizeWindow(window, event);
		}

		window->clear(sf::Color::Red);
		window->draw(t1);
		window->draw(t2);
		window->display();
	}
}

void Game::showSimpleTextOnScreen(std::string text, sf::Color color){
	float lengthUnit = utils::Transformation::getInstance().getLengthUnit();

	sf::Text victory(text, this->gameFont);
	victory.setCharacterSize(50);
	sf::FloatRect textRect = victory.getLocalBounds();
	victory.setOrigin(textRect.width/2.0f, textRect.height/2.0f);
	victory.setPosition(4 * lengthUnit, 3 * lengthUnit);

	utils::Stopwatch::getInstance().reset();
	while(utils::Stopwatch::getInstance().getElapsedTime() < 3.0f){
		sf::Event event;
		window->pollEvent(event);
		if(event.type == sf::Event::Resized){
			utils::Transformation::getInstance().resizeWindow(window, event);
		}
		window->clear(color);
		window->draw(victory);
		window->display();
	}
}

Game::Menu::Menu(Game& game) : game(game){}

void Game::Menu::presentMainOptions(){
	int totalOptions  = 3;
	int currentOption = 1;
	float width       = static_cast<float>(game.resolution.first);
	float height      = static_cast<float>(game.resolution.second);
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

	while(game.window->isOpen()){
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
					if(currentOption == 1) modeSelection();
					else if(currentOption == 2) levelSelection();
					else if (currentOption == 3)
						game.scoreboard.showScoreboard(game.resolution, game.window);
				}
			}
			else if(event.type == sf::Event::Resized){
				utils::Transformation::getInstance().resizeWindow(game.window, event);
			}

			else if(event.type == sf::Event::Closed) game.window->close();
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
	auto width        = static_cast<float>(game.resolution.first);
	auto height       = static_cast<float>(game.resolution.second);
	std::map<int, sf::Text> textMap;

	sf::Text single("SINGLE-PLAYER MODE", game.gameFont);
	single.setColor(sf::Color::Red);
	single.setPosition(sf::Vector2f(0.10 * width, (0.5 * height)));
	textMap[currentOption] = single;

	sf::Text coop("CO-OP MODE", game.gameFont);
	coop.setColor(sf::Color::White);
	coop.setPosition(sf::Vector2f(0.10 * width, (0.5 * height) + ((0.5 * height)/3.0)));
	textMap[currentOption+1] = coop;

	while(game.window->isOpen()){
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
				else if(event.key.code == sf::Keyboard::Key::Escape) return void();
			}

			else if(event.type == sf::Event::Closed) game.window->close();

			else if(event.type == sf::Event::Resized){
				utils::Transformation::getInstance().resizeWindow(game.window, event);
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
	auto width        = static_cast<float>(game.resolution.first);
	auto height       = static_cast<float>(game.resolution.second);
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

	while(game.window->isOpen()){
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

				else if(event.key.code == sf::Keyboard::Key::Escape) return void();

			}
			else if(event.type == sf::Event::Resized){
				utils::Transformation::getInstance().resizeWindow(game.window, event);
			}

			else if(event.type == sf::Event::Closed) game.window->close();
		}
		game.window->clear();
		for(auto& t : textMap){
			game.window->draw(t.second);
		}
		game.window->display();
	}

}

}

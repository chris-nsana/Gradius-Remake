#ifndef GAME_H_
#define GAME_H_
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utilities/json.hpp"
#include "Game/Scoreboard.h"

namespace Model{class Model;}
namespace Controller{class Controller;}
namespace View{class View;}


class Game{

	class Menu{
	public:

		Menu(Game& game);

		~Menu() = default;

		void presentMainOptions();

	private:

		void modeSelection();

		void levelSelection();

		Game& game;
		int nr_Levels;
	};

public:

	Game();

	/**
	*@brief Method that starts the whole application by presenting the menu options.
	*/
	void start();

	/**
	 * @brief Something something.
	 */
	void init(bool co_op=false);

	/**
	 * @brief Method that initializes the subsystems of the game and starts running it.
	 */
	void run();

	void showVictoryScreen();

	void showLossScreen();

	void showHighscoreMessage(bool p1);


private:

	void showSimpleTextOnScreen(std::string text, sf::Color color);



	nlohmann::json configuration;
	std::pair<int, int> resolution;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<View::View> gameView;
	std::shared_ptr<Model::Model> gameModel;
	std::shared_ptr<Controller::Controller> gameControl;
	sf::Font gameFont;
	sf::Font errorFont;
	Menu gameMenu;
	Scoreboard scoreboard;
	int startingLevel;
};




#endif /* GAME_H_ */

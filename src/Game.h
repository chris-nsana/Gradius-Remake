#ifndef GAME_H_
#define GAME_H_
#include <memory>
#include <vector>
#include "Utilities/json.hpp"

namespace Model{class Model;}
namespace Controller{class Controller;}
namespace View{class View;}


class Game{

public:

	Game();

	/**
	 * @brief Method that reads the configuration of the game. This should be called before running.
	 */
	void init();

	/**
	 * @brief Method that reads the inputfile for the level and handles its data.
	 */
	void readLevel();

	/**
	 * @brief Method that initializes the subsystems of the game and starts running it.
	 */
	void Run();

private:

	std::shared_ptr<Model::Model> gameModel;
	std::shared_ptr<Controller::Controller> gameControl;
	std::shared_ptr<View::View> gameView;
	std::vector<std::string> levels;
	std::vector<nlohmann::json> levelElements; //vector game elements in json format.
	std::vector<nlohmann::json>::iterator elementPtr; //Points to the next level element that has to be processed.
	bool initialized;


};




#endif /* GAME_H_ */

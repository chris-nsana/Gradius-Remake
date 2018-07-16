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
	 * @brief Something something.
	 */
	void init();

	/**
	 * @brief Method that initializes the subsystems of the game and starts running it.
	 */
	void Run();

private:

	std::shared_ptr<Model::Model> gameModel;
	std::shared_ptr<Controller::Controller> gameControl;
	std::shared_ptr<View::View> gameView;
};




#endif /* GAME_H_ */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <memory>


namespace Model{
	class Model;
	class Player;
}

namespace sf{
	class RenderWindow;
	class Event;
}

namespace Controller{

class Controller{

public:

	Controller(std::shared_ptr<Model::Model>& model, std::shared_ptr<sf::RenderWindow>& window, bool co_op);

	~Controller();

	/**
	 * @brief Method that processes the keyboard input.
	 */
	void processInput();

	void processKeyPressed(sf::Event& event);

	void processKeyReleased(sf::Event& event);

	void controlPlayer(Model::Player& player, int pattern);

	void controlPlayer1();

	void controlPlayer2();

private:

	std::shared_ptr<Model::Model> model;
	std::shared_ptr<sf::RenderWindow> window;
	int p1Movement;
	int p2Movement;
	bool co_op;

};
}





#endif /* CONTROLLER_H_ */

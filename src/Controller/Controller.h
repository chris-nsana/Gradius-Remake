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
	
	struct playerMovement{
		bool left{false};
		bool right{false};
		bool up{false};
		bool down{false};
	};

public:

	Controller(std::shared_ptr<Model::Model> model, std::shared_ptr<sf::RenderWindow> window, bool co_op);

	~Controller();

	/**
	 * @brief Method that processes the keyboard input.
	 */
	void processInput();

	void processKeyPressed(sf::Event& event);

	void processKeyReleased(sf::Event& event);

	void pauseControl();

	void controlPlayer(Model::Player& player, bool p1);

	void controlPlayer1();

	void controlPlayer2();

	void resizeWindow(sf::Event& resizeEvent);

private:

	std::shared_ptr<Model::Model> model;
	std::shared_ptr<sf::RenderWindow> window;
	playerMovement p1Movement;
	playerMovement p2Movement;
	bool co_op;
	bool paused;

};
}





#endif /* CONTROLLER_H_ */

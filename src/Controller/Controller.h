#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <memory>


namespace Model{class Model;}

namespace sf{class RenderWindow;}

namespace Controller{

class Controller{

public:

	Controller(std::shared_ptr<Model::Model>& model, std::shared_ptr<sf::RenderWindow>& window);

	~Controller();

	/**
	 * @brief Method that processes the keyboard input.
	 */
	void processInput();

private:

	std::shared_ptr<Model::Model> model;
	std::shared_ptr<sf::RenderWindow> window;
	//A float representing the max ammount of time in seconds the controller will process input before
	//returning logic to the rest of the game loop.
	float pTime;
	int movementPattern;
	int gunJammed; //This bool is used to limit the fire rate, can't fire for 2 frames in a row

};
}





#endif /* CONTROLLER_H_ */

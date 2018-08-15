#ifndef VIEW_H_
#define VIEW_H_
#include <memory>
#include <map>
#include <string>
#include "Utilities/json.hpp"
#include "StatusDisplay.h"

namespace sf{

class RenderWindow;
class Sprite;
class Texture;
}

namespace View{

class Animation;

class View{

public:

	View(std::shared_ptr<sf::RenderWindow> window, std::string texturesFile, std::string fontPath, bool co_op);

	~View();

	/**
	 * @brief Method that displays the given game state provided by the entities.
	 */
	void displayGame();

	/**
	 * @brief Method that creates a new sprite for an object that will be displayed by View.
	 * @param int id to identify which object we're displaying
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void addSprite(int id, std::string texture);

	void scaleSprite(int id, float width, float height, bool sheet);

	void addAnimation(int id, std::string texture);

	/**
	 * @brief Method that creates the animation object for a certain entity that will be displayed
	 * @param int id to identify which object we're animating.
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void informCreation(int id, float width, float height, std::string texture);

	/**
	 * @brief Method that informs the view of a entity's changes.
	 * @param float x the x-coordinate of the entity in the model
	 * @param float y the y-coordinate of the entity in the model
	 * @param integer id the entity ID to identify which entity is changing
	 * @param int type an integer that represents what type of entity is informing the view of its changes.
	 * @param bool animatet that tells the view if the entity is animated or not
	 */
	void inform(int id, float x, float y);

	/**
	 * @brief Method that creates the animation object for a certain entity that will be displayed
	 * @param int id to identify which object we're animating.
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void informHit(int id);

	/**
	 * @brief Method that creates the animation object for a certain entity that will be displayed
	 * @param int id to identify which object we're animating.
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void informDeath(int id);

	/**
	*@brief Method that ...
	*/
	void informPlayerInfo(bool p1, int lives, int score);

	/**
	 * @brief Method that deletes an entity from the view.
	 * @param int ID to identify the entity
	 */
	void deleteEntity(int ID);
	/**
	 * @brief Method that updates all the animations of the view.
	 */
	void updateAnimations();

	void freezeView();

	void unfreezeView();

private:

	//Window to render the visuals.
	std::shared_ptr<sf::RenderWindow> window;
	//Associative container that maps texture names to their respective texture object.
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	//Assiocative container that maps entities to their respective sprites.
	std::map<int, sf::Sprite> sprites;
	//Associative container that maps entities to their respective animation texture.
	std::map<int, Animation> animations;
	//Json object containing all information on entity textures
	nlohmann::json texturesJson;
	//A container keeping track of dying sprites and when to delete them (key = ID, value = time left)
	std::map<int, int> dyingSprites;
	//Object in charge of the representation of the player information
	StatusDisplay playerStatus;
	//Font used in the game
	sf::Font font;
	bool co_op;
	bool paused;

};

}





#endif /* VIEW_H_ */

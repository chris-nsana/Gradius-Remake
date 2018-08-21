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

	std::shared_ptr<sf::RenderWindow> window; //Window to render the visuals.
	std::map<std::string, std::unique_ptr<sf::Texture>> textures; //Textures used throughout the game.
	std::map<int, sf::Sprite> sprites; //Map that holds sprites for non-animated entities, key = entity id, value
	std::map<int, Animation> animations; //Map that holds animations, key = entity id, value = animation object
	nlohmann::json texturesJson; //Json object containing all information on entity textures
	std::map<int, int> dyingSprites; //Map that keeps track of dying sprites, key = id, value = ticks left
	StatusDisplay playerStatus; //Object that visualizes player info (score, lives et cetera)
	sf::Font font; //Font used for the game
	bool co_op; //Boolean indicating whether the game is in co-op mode
	bool paused;

};

}





#endif /* VIEW_H_ */

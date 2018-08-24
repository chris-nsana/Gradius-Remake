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
	 * @param string texture used to make a basic sprite
	 */
	void addSprite(int id, std::string texture);

	/**
	 * @brief Method that scales a sprite using its real width and height in the game
	 * @param int id to identify which object we're displaying
	 * @param float width the real width in the model system
	 * @param float height the real width in the model system
	 * @param bool indicating whether the sprite is a sprite sheet.
	 */
	void scaleSprite(int id, float width, float height, bool sheet);

	/**
	 * @brief Method that creates a new animation object that will be displayed by View.
	 * @param int id to identify which object we're displaying
	 * @param string texture used to make an animation
	 */
	void addAnimation(int id, std::string texture);

	/**
	 * @brief Method that tells the Viewer a new entity has been created and its visual representation should be created.
	 * @param int id to identify which object we're animating.
	 * @param float width the real width in the model system
	 * @param float height the real width in the model system
	 * @param string the texture needed to make the visual representation
	 */
	void informCreation(int id, float width, float height, std::string texture);

	/**
	 * @brief Method that informs the view of a entity's changes.
	 	* @param integer id the entity ID to identify which entity is changing
	 * @param float x the x-coordinate of the entity in the model
	 * @param float y the y-coordinate of the entity in the model
	 */
	void inform(int id, float x, float y);

	/**
	 * @brief Method that informs the view an entity is hit and to visualize it
	 * @param int id to identify which object we're using.
	 */
	void informHit(int id);

	/**
	 * @brief Method that informs that an entity has died
	 * @param int id to identify which object has died
	 */
	void informDeath(int id);

	/**
	*@brief Method that informs the view about the changes in playerInfo (lives, score et cetera)
	* @param bool p1 indicating if it's updating player1, true for player1 and false for player 2
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

	/**
	 * @brief Method that freezes the view.
	 */
	void freezeView();

	/**
	 * @brief Method that unfreezes the view.
	 */
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

#ifndef VIEW_H_
#define VIEW_H_
#include <memory>
#include <map>

namespace sf{

class RenderWindow;
class Sprite;
class Texture;
}

namespace View{

class Animation;

class View{

public:

	View(std::shared_ptr<sf::RenderWindow>& w);

	~View();

	/**
	 * @brief Method that displays the given game state provided by the entities.
	 */
	void displayGame();

	/**
	 * @brief Method to return the isOpen() method of the encapsulated sf::RenderWindow
	 * @return returns true if the window is still open or else it returns false.
	 */
	bool isOpen() const;

	/**
	 * @brief Method that creates a new sprite for an object that will be displayed by View.
	 * @param int id to identify which object we're displaying
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void addSprite(int id, int typeOfEntity, bool animated);

	/**
	 * @brief Method that loads the texture needed for an entity in memory.
	 * @param int id that identifies the entity
	 * @param int typeOfEntity that is an identifier for a specific texture for an entity type.
	 * @param bool animated is a flag that tells us whether we should treat it as an animated sprite or not.
	 */
	void addTexture(int typeOfEntity);

	/**
	 * @brief Method that creates the animation object for a certain entity that will be displayed
	 * @param int id to identify which object we're animating.
	 * @param int typeOfEntity represents the type of the object, since its type determines certain attributes.
	 */
	void addAnimation(int id, int typeOfEntity);

	/**
	 * @brief Method that checks whether a certain type of entity has an animated representation
	 * @param int typeOfEntity that specifies the entity type.
	 */
	bool isAnimated(int typeOfEntity);

	/**
	 * @brief Method that informs the view of a entity's changes.
	 * @param float x the x-coordinate of the entity in the model
	 * @param float y the y-coordinate of the entity in the model
	 * @param integer id the entity ID to identify which entity is changing
	 * @param int type an integer that represents what type of entity is informing the view of its changes.
	 * @param bool animatet that tells the view if the entity is animated or not
	 */
	void inform(float x, float y, int id);

	/**
	 * @brief Method that deletes an entity from the view.
	 * @param int ID to identify the entity
	 */
	void deleteEntity(int ID);
	/**
	 * @brief Method that updates all the animations of the view.
	 */
	void updateAnimations();

private:

	//Window to render the images.
	std::shared_ptr<sf::RenderWindow> window;
	//Assiocative container that maps entities to their respective animated sprites.
	std::map<int, sf::Sprite> animatedSprites;
	//Assiocative container that maps entities to their respective static sprites.
	std::map<int, sf::Sprite> staticSprites;
	//Associative container that maps entities to their respective animations.
	std::map<int, Animation> animations;
	//Associative container that maps entity types to their respective texture.
	std::map<int, std::shared_ptr<sf::Texture>> textures;

};



}





#endif /* VIEW_H_ */

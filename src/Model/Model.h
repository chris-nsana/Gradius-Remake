#ifndef MODEL_H_
#define MODEL_H_
#include <memory>
#include <vector>
#include <string>
#include <Utilities/json.hpp>
namespace Model{

class Entity;
class Player;
class EntityFactory;

class Model{

public:

	Model(std::string entitiesFile, bool co_op);

	~Model();

	/**
	 * @brief Method that creates and stores a certain type of Entity in the model.
	 * @param float x is x-coordinate of the new entity
	 * @param float y is y-coordinate of the new entity
	 * @param int type is the type of the new entity
	 * @param bool dynamic specifies whether it's a dynamic entity or not.
	 */
	void createEntity(float x, float, int type, bool dynamic);

	/**
	 * @brief Method that does some prep work for a level.
	 */
	void startLevel();

	/**
	*
	*
	*/
	void readLevel();

	/**
	 * @brief Method that updates all the entities for the current game tick
	 */
	void update();

	/**
	 * @brief Method that lets all the entities in the model notify their observer of their changes.
	 */
	void massNotify();

	/**
	 * @brief Method that is called when the player fires a bullet. The creation and handling of the bullet entity is handled by Model.
	 */
	void playerFire();

	/**
	 * @brief Method that checks whether this exact entity is colliding with another one.
	 * @param A unique_ptr to the element that we check for.
	 */
	void checkCollision();

	/**
	 * @brief Method that destroys an entity.
	 * @param std::unique_ptr reference to the entity
	 */
	void destroyEntity();

	/**
	 * @brief Return a reference to the player 1 entity.
	 */
	Player& getPlayer1();

	/**
	 * @brief Return a reference to the player 2 entity.
	 */
	Player& getPlayer2();



private:


	using entity_it = std::vector<std::unique_ptr<Entity>>::iterator;

	/**
	*
	*/
	entity_it locateEntity(int eID);


	std::unique_ptr<EntityFactory> factory;
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::string> levels; //All the level names that are playable.
	std::vector<nlohmann::json> levelElements; //Vector of game elements in json format.
	std::vector<nlohmann::json>::iterator elementPtr; //Points to the next level element that has to be processed.
	int player1ID;
	int player2ID;
	bool co_op;
	int playerlives;
	int currentLevel = 1;
	int levelTime;




};

}





#endif /* MODEL_H_ */

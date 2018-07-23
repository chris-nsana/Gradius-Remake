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

	Model(std::string entitiesFile, std::vector<std::string> levels, int level, bool co_op);

	~Model();

	/**
	 * @brief Method that does some prep work for a level.
	 */
	void startLevel();

	/**
	*
	*@brief Reads the level file and creates entities according to that file.
	*/
	void readLevel();

	/**
	 * @brief Method that updates all the entities for the current game tick
	 */
	void update();

	/**
	*@brief Increment the tickCounter of the Model
	*/
	void tick();

	/**
	 * @brief Method that lets all the entities in the model notify their observer of their changes.
	 */
	void massNotify();

	/**
	 * @brief Method that is called when the player fires a bullet. The creation and handling of the bullet entity is handled by Model.
	 */

	void checkCollision();

	/**
	 * @brief Method that destroys an entity.
	 * @param std::unique_ptr reference to the entity
	 */
	void destroyEntity(int ID);

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
	*@brief Internal method used to find specific entities in the entities vector by using their ID.
	*/
	entity_it locateEntity(int eID);


	std::unique_ptr<EntityFactory> factory;
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::string> levels; //All the level names that are playable.
	std::vector<nlohmann::json> levelElements; //Vector of game elements in json format.
	std::vector<nlohmann::json>::iterator elementPtr; //Points to the next level element that has to be processed.
	int player1ID;
	int player2ID;
	int playerlives;
	int currentLevel;
	bool co_op;
	int levelTime;




};

}





#endif /* MODEL_H_ */

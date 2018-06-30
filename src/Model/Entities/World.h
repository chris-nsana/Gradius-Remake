#ifndef WORLD_H_
#define WORLD_H_
#include "Entity.h"
#include <memory>
#include <vector>

using staticPtr = std::unique_ptr<Entity>;
//World contains all the data of staticentities that are part of the world
//like background, border, obstacles,
class World : public Entity{

public:

	World();

	~World();

	/**
	 * @brief Method that updates the position of all the static elements in the side-scrolling world
	 */
	void update();

	/**
	 * @brief Method that creates entities that are world elements.
	 * @param float x that represents the x-coordinate of that entity
	 * @param float y that represents the y-coordinate of that entity
	 * @param int type of entity being created.
	 */
	void createWorldElement(float x, float y, int type);

	/**
	 * Method that generates the bare bones of a world. (Background and borders)
	 */
	void setWorld();

	/**
	 *@brief The world itself has nothing to notify to the observer, but all the elements stored will notify their changes.
	 */
	void virtual notify() const;

private:
	std::vector<staticPtr> worldElements;

};





#endif /* WORLD_H_ */

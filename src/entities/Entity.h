#ifndef ENTITY_H_
#define ENTITY_H_
#include <utility>
#include <memory>
#include <View/View.h>

namespace View{class View;}

class Entity{

protected:

	Entity();

	Entity(float x, float y, float radius, int type);


public:

	virtual ~Entity();


    /**
     * @brief Method that attaches a view to all entities of the game.
     * @param obs is a shared_ptr reference to that view we want to attach.
     */
	static void Attach(const std::shared_ptr<View::View>& obs);

    /**
     * @brief Method that detaches that view from all the entities of the game.
     */
	static void Detach();

	/**
	 * @brief Method that returns whether an observer is attached to an entity or not.
	 * @return bool that is true if attached and false if not attached
	 */
	bool isAttached() const;

    /**
     * @brief Method that lets the entity notify the view of changes in its state.
     */
	void notify() const;

	/**
	 * @brief The model knows of a entities death, but the entity has to notify its observer aswell. This method does just that.
	 */
	void notifyDeath() const;

	/**
	 *@brief Method that sets an entity to a different position.
	 *@param float x that represents the x-coordinate
	 *@param float y that rerpesents the y-coordinate
	 */
	void setPosition(float x , float y);

	/**
	 * @brief A simple getter to the position of an entity.
	 * @return pair<float, float> with the x-coordinate and y-coordinate
	 */
	std::pair<float, float> getPosition() const;

	int getID() const;

	int getType() const;

	float getRadius() const;


private:

	std::pair<float, float> position;
	float radius;
	int type;
	int eID;
	static std::shared_ptr<View::View> observer; //The observer viewing the state of all entities.
	static int entityCount; //Count of all entities in the game.


};

#endif /* ENTITY_H_ */

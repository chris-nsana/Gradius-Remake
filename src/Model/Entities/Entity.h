#ifndef ENTITY_H_
#define ENTITY_H_
#include <utility>
#include <memory>
#include <View/View.h>

namespace View{class View;}

namespace Model{

class Neutral;
class Friendly;
class Enemy;

class Entity{

protected:

	Entity();

	Entity(float x, float y, float health, float damage, float width, float height);

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

	float getHealth() const;

	float getDamage() const;

	float getWidth() const;

	float getHeight() const;

	float getHalfWidth() const;

	float getHalfHeight() const;

	int getID() const;

	void takeDamage(float amount);

	bool isDead() const;

	virtual void update()=0;

	virtual void move()=0;

	virtual void fire()=0;

	virtual bool isNeutral() const=0;

	virtual bool isFriendly() const=0;

	virtual bool isEnemy() const=0;

	virtual void onCollisionReact(const std::unique_ptr<Entity>& otherEntity)=0;


private:

	std::pair<float, float> position;
	float health;
	float damage;
	float width;
	float height;
	int eID;
	static std::shared_ptr<View::View> observer; //The observer viewing the state of all entities.
	static int entityCount; //Count of all entities in the game.


};

}

#endif /* ENTITY_H_ */

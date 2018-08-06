#ifndef ENTITY_H_
#define ENTITY_H_
#include <utility>
#include <memory>
#include <string>
#include <View/View.h>

namespace View{class View;}

using std::string;

namespace Model{

class Entity{

protected:

	Entity();

	Entity(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	Entity(const Entity&)=delete;

	Entity& operator=(const Entity&) = delete;

public:

	virtual ~Entity();

    /**
     * @brief Method that attaches a view to all entities of the game.
     * @param obs is a shared_ptr reference to that view we want to attach.
     */
	static void attach(const std::shared_ptr<View::View>& obs);

    /**
     * @brief Method that detaches that view from all the entities of the game.
     */
	static void detach();

	/**
	 * @brief Method that returns whether an observer is attached to an entity or not.
	 * @return bool that is true if attached and false if not attached
	 */
	bool isAttached() const;

	/**
	 * @brief Method that lets the entity notify its observer of its creation.
	 */
	void notifyCreation() const;

    /**
     * @brief Method that lets the entity notify its observer of its changes.
     */
	void notify() const;

	/**
	 * @brief Method that lets the entity notify its observer of its death.
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

	float getDamage() const;

	float getSpeed() const;

	float getWidth() const;

	float getHeight() const;

	float getHalfWidth() const;

	float getHalfHeight() const;

	float getWorth() const;

	float getCreatorID() const;

	int getID() const;

	std::string getTexture() const;

	void setWorth(int worth);

	void setCreatorID(int id);

	bool isDead() const;

	virtual void takeDamage(float amount, bool enemy);

	virtual void fire();

	virtual void update()=0;

	virtual void move()=0;

	virtual bool isNeutral() const=0;

	virtual bool isFriendly() const=0;

	virtual bool isEnemy() const=0;

	virtual void onCollisionReact(Entity& other)=0;


private:

	std::pair<float, float> position;
	float health;
	float damage;
	float speed;
	float width;
	float height;
	int worth;
	int creatorID;
	string texture;
	int eID;
	static std::weak_ptr<View::View> observer; //The observer viewing the state of all entities.
	static int entityCount; //Count of all entities in the game.


};

}

#endif /* ENTITY_H_ */

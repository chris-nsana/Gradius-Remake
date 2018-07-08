#ifndef ENEMY_H_
#define ENEMY_H_
#include "Entity.h"

namespace Model{

class Enemy : public Entity{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Enemy();

		Enemy(float x, float y, float health, float damage, float width, float height);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Enemy();

		virtual bool isNeutral() const override;

		virtual bool isFriendly() const override;

		virtual bool isEnemy() const override;

		virtual void onCollisionReact(const std::unique_ptr<Entity>& otherEntity) override;

		virtual void setBlocked()=0;

};
}




#endif /* ENEMY_H_ */

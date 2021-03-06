#ifndef NEUTRAL_H_
#define NEUTRAL_H_
#include "Entity.h"

namespace Model{

class Neutral : public Entity{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Neutral();

		Neutral(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Neutral();

		virtual bool isNeutral() const override;

		virtual bool isFriendly() const override;

		virtual bool isEnemy() const override;

		virtual void fire() override;

		virtual void onCollisionReact(Entity& other) override;

};
}



#endif /* NEUTRAL_H_ */

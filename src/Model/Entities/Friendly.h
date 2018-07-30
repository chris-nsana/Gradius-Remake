#ifndef FRIENDLY_H_
#define FRIENDLY_H_
#include "Entity.h"

namespace Model{

class Friendly : public Entity{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Friendly();

		Friendly(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Friendly();

		virtual bool isNeutral() const override;

		virtual bool isFriendly() const override;

		virtual bool isEnemy() const override;

		virtual void onCollisionReact(Entity& other) override;


};
}


#endif /* FRIENDLY_H_ */

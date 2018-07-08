#ifndef NEUTRAL_H_
#define NEUTRAL_H_
#include "Entity.h"

namespace Model{

class Neutral : public Entity{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Neutral();

		Neutral(float x, float y, float health, float damage, float width, float height);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Neutral();

		virtual bool isNeutral() const override;

		virtual bool isFriendly() const override;

		virtual bool isEnemy() const override;

		virtual void onCollisionReact(const std::unique_ptr<Entity>& otherEntity) override;

};
}



#endif /* NEUTRAL_H_ */

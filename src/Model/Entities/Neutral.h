#ifndef NEUTRAL_H_
#define NEUTRAL_H_
#include "Entity.h"

namespace Model{

class Neutral : public Entity{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Neutral();

		Neutral(float x, float y, float health, float damage, float width, float height, int type);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Neutral();

		virtual bool isNeutral() const override;

		virtual void onCollisionReact(Neutral& other) override;

		virtual void onCollisionReact(Friendly& other) override;

		virtual void onCollisionReact(Enemy& other) override;

};
}



#endif /* NEUTRAL_H_ */

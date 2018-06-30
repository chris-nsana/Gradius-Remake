#ifndef DYNAMICENTITY_H_
#define DYNAMICENTITY_H_
#include "Entity.h"
#include <memory>



class DynamicEntity: public Entity{
	
public:
	
	void virtual move()=0;

	//The DynamicEntity destructor can be called by the smart_pointers in polymorphic cases.
	virtual ~DynamicEntity();

//These constructors are not to be called outside the class hierarchy.
protected:

	DynamicEntity();
	
	DynamicEntity(float x, float y, float radius, int type, int health);

	
	

private:
	
	int health;
};

#endif /* DYNAMICENTITY_H_ */

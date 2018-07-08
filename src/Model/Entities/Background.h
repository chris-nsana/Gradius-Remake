#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "Entity.h"
#include "Neutral.h"

namespace Model{

class Background : public Neutral{

public:

	Background(float x, float y, float health, float damage, float width, float height, string texture);

	virtual ~Background();

	virtual void update() override;

	virtual void move() override;
};

}





#endif /* BACKGROUND_H_ */

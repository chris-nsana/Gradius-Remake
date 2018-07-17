#ifndef BORDER_H_
#define BORDER_H_
#include "Entity.h"
#include "Neutral.h"

namespace Model{

class Border : public Neutral{

public:

	Border(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	virtual ~Border();

	virtual void update() override;

	virtual void move() override;
};

}





#endif /* BORDER_H_ */

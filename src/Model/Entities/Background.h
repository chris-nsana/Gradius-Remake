#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "Entity.h"
#include "Neutral.h"

namespace Model{

class Background : public Neutral{

public:

	Background(float x, float y, float health, float damage, float width, float height);

	virtual ~Background();
};

}





#endif /* BACKGROUND_H_ */

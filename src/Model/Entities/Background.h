#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "Entity.h"
#include "Neutral"

namespace Model{

class Background : public Neutral{

public:

	Background(float x, float y);

	virtual ~Background();
};

}





#endif /* BACKGROUND_H_ */

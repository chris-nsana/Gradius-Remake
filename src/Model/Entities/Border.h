#ifndef BORDER_H_
#define BORDER_H_
#include "Entity.h"
#include "Neutral.h"

namespace Model{

class Border : public Neutral{

public:

	Border(float x, float y);

	virtual ~Border();
};

}





#endif /* BORDER_H_ */

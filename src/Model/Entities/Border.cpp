#include "Border.h"

namespace Model{

Border::Border(float x, float y, float health, float damage, float width, float height)
 : Neutral(x, y, health, damage, width, height){}

Border::~Border(){};

}

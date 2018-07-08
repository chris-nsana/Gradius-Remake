#include "Border.h"

namespace Model{

Border::Border(float x, float y, float health, float damage, float width, float height, string texture)
 : Neutral(x, y, health, damage, width, height, texture){}

Border::~Border(){};

void Border::update(){}

void Border::move(){}

}

#include "Background.h"

namespace Model{


Background::Background(float x, float y, float health, float damage, float width, float height, string texture)
 : Neutral(x, y, health, damage, width, height, texture){}

Background::~Background(){}

void Background::update(){};

void Background::move(){};

}

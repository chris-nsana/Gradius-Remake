#include "DynamicEntity.h"

DynamicEntity::DynamicEntity(){}

DynamicEntity::DynamicEntity(float x, float y, float r, int t, int h) : Entity(x, y, r, t), health(h){}

DynamicEntity::~DynamicEntity(){}

void DynamicEntity::move(){}

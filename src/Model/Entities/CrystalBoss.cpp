#include "CrystalBoss.h"
#include "Model/EventQueue.h"

namespace Model{

CrystalBoss::CrystalBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), shootingTime(115){}

 CrystalBoss::~CrystalBoss(){}

void CrystalBoss::update(){
  if(shootingTime == 0){
    shootingTime = 115;
    auto pos = getPosition();
    EventQueue::getInstance().addEnemyFire("EnemyLaser", pos.first - 4.15f, pos.second - 0.03f);
  }
  else{
    shootingTime -= 1;
  }
}

void CrystalBoss::move(){}

}

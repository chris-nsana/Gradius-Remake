#include "PlayerData.h"
#include "View/View.h"

namespace Model{

PlayerData::PlayerData(int id, int lives, int score, bool p1)
: entityID(id), lives(lives), score(score), p1(p1){}

PlayerData::~PlayerData(){}

void PlayerData::attach(const std::shared_ptr<View::View>& obs){
  observer = obs;
}

void PlayerData::notify() const{
  if(auto spt = observer.lock()){
		spt->informPlayerInfo(this->p1, this->lives, this->score);
	}
	else throw std::runtime_error("An entity tried to notify its observer, but no observer was attached to it!");
}

void PlayerData::setID(int id){
  entityID = id;
}

int PlayerData::getID() const{
  return entityID;
}

int PlayerData::getLives() const{
  return lives;
}

int PlayerData::getScore() const{
  return score;
}

void PlayerData::takeLives(int lives){
  this->lives = this->lives - lives;
  if(this->lives < 0) this->lives = 0;
}

void PlayerData::addPoints(int points){
  score += points;
}

std::weak_ptr<View::View> PlayerData::observer = std::weak_ptr<View::View>();

}

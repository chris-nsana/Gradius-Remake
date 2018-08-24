#ifndef EVENTS_H_
#define EVENTS_H_
#include<memory>

namespace Model {

class Model;

class Event{
protected:

  static std::weak_ptr<Model> model;

public:

  /**
   * @brief Abstract base for all Events in the game that will be stored in the EventQueue.
   */
  Event();

  virtual ~Event();

  static void setModel(const std::shared_ptr<Model>& m);

  virtual void execute()=0;
};

class EnemyDeath : public Event{
public:

  //This constructor is handy if the Enemy died without being killed.
  EnemyDeath(int eID);

  ~EnemyDeath();

  virtual void execute() override;

private:
  int eID;
};

class FriendlyDeath : public Event{
public:
  FriendlyDeath(int eID);

  ~FriendlyDeath();

  virtual void execute() override;

private:
  int eID;
};

class PlayerDeath : public Event{
public:

  PlayerDeath(int eID, bool byEnemy);

  ~PlayerDeath();

  virtual void execute() override;

private:
  int eID;
  bool byEnemy;
};

class BossDeath : public Event{
public:

  BossDeath();

  ~BossDeath();

  virtual void execute() override;

};

class PlayerFire : public Event{
public:

  PlayerFire(int shooterID, std::string entity, float x, float y);

  ~PlayerFire();

  virtual void execute() override;

private:
  int shooterID;
  std::string entity;
  float x;
  float y;
};

class EnemyFire : public Event{
public:

  EnemyFire(std::string entity, float x, float y);

  ~EnemyFire();

  virtual void execute() override;

private:
  int shooterID;
  std::string entity;
  float x;
  float y;
};

class PointsGain : public Event{
public:
  PointsGain(int scorerID, int amount);

  ~PointsGain();

  virtual void execute() override;

private:

  int scorerID;
  int amount;

};

class LevelReset : public Event{
public:
  LevelReset();

  ~LevelReset();

  virtual void execute() override;

};

class LevelEnd : public Event{

public:

  LevelEnd();

  ~LevelEnd();

  virtual void execute() override;
};



}


#endif /* EVENTS_H_ */

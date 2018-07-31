#ifndef EVENTS_H_
#define EVENTS_H_
#include<memory>

namespace Model {

class Model;

class Event{
protected:

  static std::weak_ptr<Model> model;

public:

  Event();

  virtual ~Event();

  static void setModel(const std::shared_ptr<Model>& m);

  virtual void execute()=0;
};

class EnemyDeath : public Event{
public:

  EnemyDeath(int eID, int killerID, int worth);

  ~EnemyDeath();

  virtual void execute() override;

private:
  int eID;
  int killerID;
  int worth;
};


class PlayerDeath : public Event{
public:

  PlayerDeath(int eID);

  ~PlayerDeath();

  virtual void execute() override;

private:
  int eID;
};

class BossDeath : public Event{
public:

  BossDeath(int eID, int worth);

  ~BossDeath();

  virtual void execute() override;

private:
  int eID;
  int worth;
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

}


#endif /* EVENTS_H_ */

#ifndef EVENTS_H_
#define EVENTS_H_

class Model;

class Event{
protected:

  static std::weak_ptr<Mpdel> model;

public:

  Event(Event::Type eventType);

  virtual ~Event();

  static void setModel(const std::shared_ptr<Model::Model>& obs);

  virtual void execute()=0;
};

class Death : public Event{
public:

  Death(int eID, int killerID, int worth) : eID(eID), killerID(killerID), worth(worth);

  ~Death();

  virtual void execute() override;

private:
  int eID;
  int killerID;
  int worth;
};


class PlayerDeath : public Event{
public:

  PlayerDeath(int eID) : eID(eID);

  ~PlayerDeath();

  virtual void execute() override;

private:
  int eID;
};

class BossDeath : public Event{
public:

  BossDeath(int eID, int worth) : eID(eID), worth(worth);

  ~BossDeath();

  virtual void execute() override;

private:
  int eID;
  int worth;
};

class PlayerFire : public Event{
public:

  PlayerFire(int shooterID, std::string entity, float x, float y) : shooterID(shooterID), entity(entity), x(x), y(y);

  ~PlayerFire();

  virtual void execute() override;

private:
  int shooterID;
  std::string entity;
  float x;
  float y;
}

class EnemyFire : public Event{
public:

  EnemyFire(std::string entity, float x, float y) : entity(entity), x(x), y(y);

  ~BulletFire();

  virtual void execute() override;

private:
  int shooterID;
  std::string entity;
  float x;
  float y;
}


#endif /* EVENTS_H_ */

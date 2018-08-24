#ifndef PLAYERDATA_H_
#define PLAYERDATA_H_

#include<memory>

namespace View{ class View;}

namespace Model{

  /**
   * @brief PlayerData class
   * Holds crucial information about the Player that should be remembered even past its lifetime
   */
class PlayerData{
public:

  PlayerData(int id, int lives, int score, bool p1);

  ~PlayerData();

  /**
   * @brief Method that attaches a view to all entities of the game.
   * @param obs is a shared_ptr reference to that view we want to attach.
   */
  static void attach(const std::shared_ptr<View::View>& obs);

  void notify() const;

  void setID(int id);

  int getID() const;

  int getLives() const;

  int getScore() const;

  void takeLives(int lives);

  void addPoints(int points);

private:

  int entityID;
  int lives;
  int score;
  bool p1;
  static std::weak_ptr<View::View> observer;
};

}

#endif /* PLAYERDATA_H_ */

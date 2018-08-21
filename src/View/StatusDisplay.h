#ifndef STATUSDISPLAY_H_
#define STATUSDISPLAY_H_
#include <memory>
#include <SFML/Graphics.hpp>

namespace View{

class StatusDisplay{
public:

  StatusDisplay();

  StatusDisplay(const sf::Texture& lifeTexture, sf::Font& font, bool co_op);

  ~StatusDisplay();

  void draw(const std::shared_ptr<sf::RenderWindow>& window);

  std::string stringify_score(int score);

  void updatePlayer1(int lives, int score);

  void updatePlayer2(int lives, int score);

private:
  float baseLengthUnit;
  bool co_op;
  sf::Sprite lifeIcon1;
  sf::Sprite lifeIcon2;
  sf::Text p1;
  sf::Text p2;
  sf::Text lives1;
  sf::Text lives2;
  sf::Text score1;
  sf::Text score2;


};

}







#endif /* STATUSDISPLAY_H_ */

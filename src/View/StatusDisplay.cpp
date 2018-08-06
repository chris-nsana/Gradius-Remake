#include <SFML/Graphics.hpp>
#include "StatusDisplay.h"
#include "View.h"
#include "Utilities/Transformation.h"

namespace View{

StatusDisplay::StatusDisplay(){}

StatusDisplay::StatusDisplay(const sf::Texture& lifeTexture, sf::Font& font, bool co_op){
  baseLengthUnit = utils::Transformation::getInstance().getLengthUnit();

  p1 = sf::Text("P1", font);
  p1.setCharacterSize(21);
  //Get the Text a little bit away from the left edge.
  p1.setPosition(0.050 * baseLengthUnit, 0.0f);
  sf::FloatRect p1Rect = p1.getGlobalBounds();
  float leftEdge       = p1.getPosition().x;

  lifeIcon.setTexture(lifeTexture);
  float desiredWidth  = 0.20f * baseLengthUnit;
  float desiredHeight = 0.20f * baseLengthUnit;
  sf::FloatRect rect  = lifeIcon.getLocalBounds();
  float xScale        = desiredWidth / rect.width;
  float yScale        = desiredHeight / rect.height;
  lifeIcon.scale(sf::Vector2f(xScale, yScale));
  lifeIcon.setPosition(leftEdge + p1Rect.width + 0.1 * baseLengthUnit, 0.025 * baseLengthUnit);

  rect                = lifeIcon.getGlobalBounds();
  leftEdge            = lifeIcon.getPosition().x;
  lives1              = sf::Text("X3", font);
  lives1.setCharacterSize(21);
  lives1.setPosition(leftEdge + rect.width + 0.050 * baseLengthUnit, 0.0f);

  rect                = lives1.getGlobalBounds();
  leftEdge            = lives1.getPosition().x;
  score1              = sf::Text("000000", font);
  score1.setCharacterSize(21);
  score1.setPosition(leftEdge + rect.width + 0.5 * baseLengthUnit, 0.0f);
}

StatusDisplay::~StatusDisplay(){}

void StatusDisplay::draw(const std::shared_ptr<sf::RenderWindow>& window){
  window->draw(p1);
  window->draw(lifeIcon);
  window->draw(lives1);
  window->draw(score1);
}


std::string StatusDisplay::stringify_score(int score){
  std::string stringScore = std::to_string(score);
  if(stringScore.size() < 6){
    int rest = 6 - stringScore.size();
    stringScore = std::string(rest, '0') + stringScore;
  }
  return stringScore;
}

void StatusDisplay::updatePlayer1(int lives, int score){
  std::string livesString = "X" + std::to_string(lives);
  std::string scoreString = stringify_score(score);
  lives1.setString(livesString);
  score1.setString(scoreString);
}

void StatusDisplay::updatePlayer2(int lives, int score){
  /*
  std::string livesString = "X" + std::to_string(lives);
  std::string scoreString = stringify_score(score);
  lives2.setString(livesString);
  score2.setString(scoreString);
  */
}

}

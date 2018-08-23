#include <SFML/Graphics.hpp>
#include "StatusDisplay.h"
#include "View.h"
#include "Utilities/Transformation.h"

namespace View{

StatusDisplay::StatusDisplay(){}

StatusDisplay::StatusDisplay(const sf::Texture& lifeTexture, sf::Font& font, bool co_op){
  baseLengthUnit  = utils::Transformation::getInstance().getLengthUnit();
  //21 is the wanted character size for a screen of 800x600
  //if we have something bigger or smaller, we adjust or character size
  int scaledChar =  static_cast<int>(21.0 * (baseLengthUnit / 100.0f));

  p1 = sf::Text("P1", font);
  //Get the Text a little bit away from the left edge.
  p1.setPosition(0.050 * baseLengthUnit, 0.0f);
  p1.setCharacterSize(scaledChar);
  lifeIcon1.setTexture(lifeTexture);
  float desiredWidth  = 0.20f * baseLengthUnit;
  float desiredHeight = 0.20f * baseLengthUnit;
  sf::FloatRect rect  = lifeIcon1.getLocalBounds();
  float xScale        = desiredWidth / rect.width;
  float yScale        = desiredHeight / rect.height;
  lifeIcon1.scale(sf::Vector2f(xScale, yScale));
  lifeIcon1.setPosition(0.3 * baseLengthUnit, 0.025 * baseLengthUnit);
  lives1 = sf::Text("X3", font);
  lives1.setPosition(0.550 * baseLengthUnit, 0.0f);
  lives1.setCharacterSize(scaledChar);
  score1 = sf::Text("000000", font);
  score1.setPosition(1.0 * baseLengthUnit, 0.0f);
  score1.setCharacterSize(scaledChar);

  if(co_op){
    p2 = sf::Text("P2", font);
    p2.setPosition(4.050 * baseLengthUnit, 0.0f);
    p2.setCharacterSize(scaledChar);
    lifeIcon2 = lifeIcon1;
    lifeIcon2.setPosition(4.350 * baseLengthUnit, 0.025 * baseLengthUnit);
    lives2 = sf::Text("X3", font);
    lives2.setPosition(4.600 * baseLengthUnit, 0.0f);
    lives2.setCharacterSize(21);
    score2 = sf::Text("000000", font);
    score2.setPosition(5.0 * baseLengthUnit, 0.0f);
    score2.setCharacterSize(scaledChar);
  }

}

StatusDisplay::~StatusDisplay(){}

void StatusDisplay::draw(const std::shared_ptr<sf::RenderWindow>& window){
  window->draw(p1);
  window->draw(lifeIcon1);
  window->draw(lives1);
  window->draw(score1);

  window->draw(p2);
  window->draw(lifeIcon2);
  window->draw(lives2);
  window->draw(score2);
}


std::string StatusDisplay::stringify_score(int score){
  std::string stringScore = std::to_string(score);
  if(stringScore.size() < 8){
    int rest    = 8 - stringScore.size();
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
  std::string livesString = "X" + std::to_string(lives);
  std::string scoreString = stringify_score(score);
  lives2.setString(livesString);
  score2.setString(scoreString);
}

}

#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Utilities/json.hpp"

class Scoreboard{

public:

  Scoreboard();

  Scoreboard(std::string scoreFile, sf::Font& font);

   ~Scoreboard();

   bool checkEntry(int score);

   void addEntry(int score, bool p1,  std::string player);

   void showScoreboard(const std::shared_ptr<sf::RenderWindow>& window);

private:
  nlohmann::json entries;
  sf::Font font;
};

#endif /* SCOREBOARD_H_ */
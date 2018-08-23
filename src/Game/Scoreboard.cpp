#include "Scoreboard.h"
#include "Game.h"
#include <utility> //to include std::pair
#include <fstream>
#include <set>
#include <iostream>

Scoreboard::Scoreboard(){}

Scoreboard::Scoreboard(std::string& scoreFile, sf::Font& font) : font(font){
  std::ifstream file;
  try{
    file.open(scoreFile);
    if(!file.is_open()) throw std::invalid_argument("");
  }
  //The file doesn't exist, we create a new blank one then.
  catch(std::invalid_argument&){
    nlohmann::json newFile;
    std::string contents = newFile.dump();
    std::ofstream createdFile(scoreFile);
    createdFile << contents;
    createdFile.close();
    file.open(scoreFile);
  }

  file >> entries;
}

Scoreboard::~Scoreboard(){}

bool Scoreboard::checkEntry(int score){
  if (entries.empty()) return true;
  auto it = --(entries.end());
  int entryScore = (*it)["score"];
  return (entryScore < score);
}

void Scoreboard::addEntry(int score, bool p1,  std::string player){
  auto iterator = entries.end();
  if(!entries.empty()) --iterator;
  //Loop through the entries until the right spot
  for(auto it = iterator; it != entries.begin(); --it){
    int entryScore = (*it)["score"];
    if(score > entryScore) iterator = it;
    else break;
  }

  nlohmann::json val;
  val["score"] = score;
  val["name"]  = player;
  entries.insert(iterator, val);
}

void Scoreboard::showScoreboard(Game& game, const std::shared_ptr<sf::RenderWindow>& window){
  auto width        = static_cast<double>(game.getResolution().first);
  auto height       = static_cast<double>(game.getResolution().second);

  sf::Text name("NAME", this->font);
  name.setPosition(sf::Vector2f(0.60 * (float)width, 0.0f));

  sf::Text score("SCORE", this->font);
  score.setPosition(sf::Vector2f(0.10 * (float)width, 0.0f));

  std::vector<sf::Text> toDraw = {name, score};
  std::set< std::pair<int, std::string> > entrySet;
  for(auto& entry : entries){
    int a         = entry["score"];
    std::string b = entry["name"];
    std::pair<int, std::string> value = {a, b};
    entrySet.insert(value);
  }
  //int existing   = entrySet.size();
  int offset     = 1;
  float spacing  = (0.8f * height) / 10.0f;
  for(auto& e : entrySet){
    std::string scoreString = std::to_string(e.first);
    std::string playerName  = e.second;
    sf::Text temp1(scoreString, this->font);
    sf::Text temp2(playerName, this->font);
    temp1.setPosition(sf::Vector2f(0.10 * (float)width, (float)offset * spacing));
    temp2.setPosition(sf::Vector2f(0.60 * (float)width, (float)offset * spacing));
    toDraw.push_back(temp1); toDraw.push_back(temp2);
    offset += 1;
  }
  while(true){
	sf::Event event;
	if(window->pollEvent(event)){
		if(event.key.code == sf::Keyboard::Key::Escape) return void();
		else if(event.type == sf::Event::Resized) game.resizeWindow(event);
	}
    window->clear(sf::Color(135, 206, 250));
    for(auto& drawable : toDraw){
      window->draw(drawable);
    }
    window->display();
  }

}

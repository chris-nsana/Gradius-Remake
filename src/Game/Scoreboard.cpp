#include "Scoreboard.h"
#include "Game.h"
#include <utility> //to include std::pair
#include <fstream>
#include <set>
#include <iostream>
#include "Utilities/Transformation.h"
#include "Utilities/Stopwatch.h"

namespace Game{

Scoreboard::Scoreboard(){}

Scoreboard::Scoreboard(std::string& scoreFile, sf::Font& font) : scoreFile(scoreFile), font(font){
  std::ifstream file;
  try{
    file.open(scoreFile);
    if(!file.is_open()) throw std::invalid_argument("");
  }
  //The file doesn't exist, we create a new blank one then.
  catch(std::invalid_argument&){
    //Empty array of json objects
    std::string contents = "[]";
    std::ofstream createdFile(scoreFile);
    createdFile << contents;
    createdFile.close();
    file.open(scoreFile);
  }

  file >> entries;
}

Scoreboard::~Scoreboard(){}

bool Scoreboard::checkEntry(int score) const{
  if(score == 0) return false;
  else if (entries.empty()) return true;
  std::set<std::pair<int, std::string>> elements;
  for(auto& entry : entries){
	  int score        = entry["score"];
	  std::string name = entry["name"];
	  std::pair<int, std::string> element = {score, name};
	  elements.insert(element);
  }

  if(score >= elements.rbegin()->first) return true;
  else return false;
}

std::string Scoreboard::promptName(std::pair<int, int> resolution, const std::shared_ptr<sf::RenderWindow>& window){
  float width        = static_cast<float>(resolution.first);
  float height       = static_cast<float>(resolution.second);
  std::string instructionText = "TYPE THE NAME OF THE PLAYER THAT REACHED THE HIGHSCORE"
  "\n\n(MAX 20 CHARACTERS) AND PRESS ENTER TO CONFIRM";
  sf::Text instruction(instructionText, this->font);
  instruction.setPosition(sf::Vector2f(0.035 * width, 0.0f));
  std::string typedString = "";
  sf::Text typed (typedString, this->font);
  typed.setPosition(sf::Vector2f(0.035 * width, 0.5 * height));
  //This string is what is going to be represented in the window.
  std::string visual = "";
  //The amount of time to wait to show or hide the typing underscore
  float flickerTime = 0.25f;
  //Bool indicating if the underscore is visible
  bool visibleChar  = true;
  utils::Stopwatch::getInstance().reset();
  while(true){
  if(utils::Stopwatch::getInstance().getElapsedTime() >= flickerTime){
    utils::Stopwatch::getInstance().reset();
    if(visibleChar)visibleChar = false;
    else visibleChar = true;
  }
  sf::Event event;
  if(window->pollEvent(event)){

    if(event.type == sf::Event::TextEntered){
      int code = static_cast<int>(event.text.unicode);
      //These are the only characters supported for typing
      if((code >= 32) and (code <= 126)){
        //We support lengths of max 20 characters.
        if(typedString.size() <= 20) typedString += event.text.unicode;
      }
      //code == 8 is backspace
      //Backspace is not supported visually, but used to delete characters
      if(code == 8 and typedString.size() > 0) typedString.pop_back();

      //If the key is equal to carriage return (enter), we exit with the string
      if(code == 13) return typedString;
    }

    else if(event.type == sf::Event::Resized){
      utils::Transformation::getInstance().resizeWindow(window, event);
    }
  }
  visual = typedString;
  if(visibleChar) visual += "_";
  typed.setString(visual);
  window->clear(sf::Color(135, 206, 250));
  window->draw(instruction);
  window->draw(typed);
  window->display();
  }
}

void Scoreboard::addEntry(int score, std::string player){
  nlohmann::json val;
  val["score"] = score;
  val["name"]  = player;
  entries.push_back(val);
  if(entries.size() > 10) entries.erase(10);

  std::string contents = entries.dump();
  std::ofstream updatedFile(this->scoreFile);
  updatedFile << contents;
  updatedFile.close();
}

void Scoreboard::showScoreboard(std::pair<int, int> resolution, const std::shared_ptr<sf::RenderWindow>& window){
  float width        = static_cast<float>(resolution.first);
  float height       = static_cast<float>(resolution.second);

  sf::Text name("NAME", this->font);
  name.setPosition(sf::Vector2f(0.60 * width, 0.0f));

  sf::Text score("SCORE", this->font);
  score.setPosition(sf::Vector2f(0.10 * width, 0.0f));

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
  for(auto it = entrySet.rbegin(); it != entrySet.rend(); ++it){
    //If the file contains some bogus entries, only keep the 10 best.
    if(offset > 10) break;
    std::string scoreString = std::to_string(it->first);
    std::string playerName  = it->second;
    sf::Text temp1(scoreString, this->font);
    sf::Text temp2(playerName, this->font);
    temp1.setPosition(sf::Vector2f(0.10 *  width, static_cast<float>(offset) * spacing));
    temp2.setPosition(sf::Vector2f(0.60 *  width, static_cast<float>(offset) * spacing));
    toDraw.push_back(temp1); toDraw.push_back(temp2);
    offset += 1;
  }
  while(window->isOpen()){
	sf::Event event;
	if(window->pollEvent(event)){
		if(event.key.code == sf::Keyboard::Key::Escape) return void();

		else if(event.type == sf::Event::Resized){
			utils::Transformation::getInstance().resizeWindow(window, event);
		}

		else if(event.type == sf::Event::Closed) window->close();
	}
    window->clear(sf::Color(135, 206, 250));
    for(auto& drawable : toDraw){
      window->draw(drawable);
    }
    window->display();
  }

}

}

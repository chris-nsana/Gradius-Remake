//////////////////////////////////////////////////////////
//
// This class design was provided by Hilze Vonck in a video tutorial.
// All credits for the main design and implementation go to Hilze Vonck.
// The code was shared under a Creative Commons licence, meaning that the
// code can be freely used and altered aslong as the creator is credited for their work
// source: https://www.youtube.com/watch?v=Aa8bXSq5LDE
//
//////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <memory>

namespace View{

class View;

class Animation{
	//The View class is the only class that should know the details of animations.
	friend View;
public:

	Animation();

	Animation(std::shared_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float switchTime);

	~Animation();

	/**
	 * @brief Method that updates the state of an animation in function of the elapsed time
	 * @param float deltaTime which is the time since the last update call / game tick.
	 */
	void update(float deltaTime);

	/**
	 * @brief Method that changes the animation sequence to a different one.
	 * @param int nRow that represents is used to choose this new sequence.
	 */
	void changeRow(int nRow);



private:

	sf::IntRect uvRect;

	sf::Vector2u currentImage;
	sf::Vector2u imageCount;

	float totalTime;
	float switchTime;
	int row;
};
}

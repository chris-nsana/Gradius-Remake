//////////////////////////////////////////////////////////
//
// The original class design was provided by Hilze Vonck in a video tutorial.
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
public:

	Animation();

	Animation(const std::unique_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float switchTime);

	~Animation();

	/**
	*@brief Method that returns a sf::IntRect rerpesenting the current animation frame
	*/
	const sf::IntRect& getTextureRect() const;


	int getNumberOfFrames() const;


	int getNumberOfRows() const;

	/**
	*@brief Return the amount of time it takes to move on to the next frame
	*/
	float getSwitchTime() const;

	/**
	 * @brief Method that updates the state of an animation in function of the elapsed time
	 * @param float deltaTime which is the time since the last update call / game tick.
	 */
	void update(float deltaTime);

	/**
	 * @brief Method that changes the animation sequence to the next one, which is the one for death.
	 */
	void startDeathAnimation();



private:

	sf::IntRect uvRect;
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;

	float totalTime;
	float switchTime;
	int row;
	bool death;
};

}

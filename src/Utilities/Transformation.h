#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "Singleton.h"
#include <utility>
#include <memory>

namespace sf{
	class Event;
	class RenderWindow;
}
namespace utils{



class Transformation : public Singleton<Transformation>{
	friend Singleton<Transformation>;

public:

    /**
     * @brief Method that transforms coordinates to pixel values.
     * @return return a pair containing the pixel values
     * @param x a float that represents the x-coordinate
     * @param y a float that represents the y-coordinate
     */
	std::pair<float, float> coordinatesToPixels(float x, float y) const;

		/**
		* @brief Returns how many pixels a distance of 1.0 is in the game coordinates.
		*/
	float getLengthUnit() const;

	/**
	 * @brief Method that changes the scale of the coordinate to pixel mapping
	 * @param unit a float that determines how big a distance of 1.0 in the game coordinates in pixels.
	 */
	 void setLengthUnit(float unit);

	 /**
	 * @brief Resize the window while keeping the 4:3 aspect ratio.
	 */
	 void resizeWindow(const std::shared_ptr<sf::RenderWindow>& window, sf::Event& resizeEvent);




private:

	Transformation();
	Transformation(const Transformation&) = default;
	Transformation& operator=(const Transformation&) = default;

	float baseLengthUnit;


};


}






#endif /* TRANSFORMATION_H_ */

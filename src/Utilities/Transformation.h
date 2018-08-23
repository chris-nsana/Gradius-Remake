#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "Singleton.h"
#include <utility>

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
		* @brief ...
		*/
	float getLengthUnit() const;

	/**
	 * @brief Method that changes the scale of the coordinate to pixel mapping
	 * @param scale, a float that determines how much bigger the new screen is compared to the default.
	 */
	 void setLengthUnit(float unit);




private:

	Transformation();
	Transformation(const Transformation&) = default;
	Transformation& operator=(const Transformation&) = default;

	float baseLengthUnit;


};


}






#endif /* TRANSFORMATION_H_ */

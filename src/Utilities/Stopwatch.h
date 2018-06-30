#ifndef STOPWATCH_H_
#define STOPWATCH_H_
#include "Singleton.h"
#include <chrono>
namespace utils{

class Stopwatch : public Singleton<Stopwatch>{
	friend Singleton<Stopwatch>;

public:


	/**
	 * @brief Method that sets /resets the stopwatch;
	 */
	void reset();


	/**
	 * @brief Method that returns how many seconds passed since the stopwatch has been set
	 * @return a float representing the ammount of time in seconds that has elapsed.
	 */
	float getElapsedTime() const;

private:

	Stopwatch() = default;
	Stopwatch(const Stopwatch&) = default;
	Stopwatch& operator=(const Stopwatch&) = default;

	std::chrono::high_resolution_clock::time_point start;

};

}





#endif /* STOPWATCH_H_ */

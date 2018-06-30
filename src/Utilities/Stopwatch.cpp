#include "Stopwatch.h"

namespace utils{

void Stopwatch::reset(){
	start = std::chrono::high_resolution_clock::now();
}

float Stopwatch::getElapsedTime() const{
	auto time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> fpSeconds = time - start;
	return fpSeconds.count();
}

template class Singleton<Stopwatch>;

}

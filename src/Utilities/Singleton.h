#ifndef SINGLETON_H_
#define SINGLETON_H_
#include<queue>

namespace utils{


template <class C>
class Singleton{
	friend C;

public:

	static C& getInstance(){
		static C Instance;
		return Instance;
	}

private:

	Singleton(){}
	Singleton(const Singleton&){}
	Singleton& operator=(const Singleton&){}
};

}

#endif /* SINGLETON_H_ */

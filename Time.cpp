#include "Time.h"
#include <chrono>

namespace Time
{
	namespace
	{
		double _time;
		double _deltaTime;
	}

	double getTime()
	{
		return _time;
	}

	double getDeltaTime()
	{
		return _deltaTime;
	}

	void updateTime()
	{
		std::chrono::duration<double> t = std::chrono::system_clock::now().time_since_epoch();
		_deltaTime = t.count() - _time;
		_time = t.count();
	}
}

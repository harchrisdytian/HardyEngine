#include "Time.h"

Time::Time()
{
	last = std::chrono::steady_clock::now();
}

float Time::Mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> time = last - old;
	return time.count();	
}

float Time::Peak()
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}




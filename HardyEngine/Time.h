#pragma once
#include <chrono>
class Time
{
public:
	Time();
	float Mark();
	float Peak();
private:
	std::chrono::steady_clock::time_point last;
};


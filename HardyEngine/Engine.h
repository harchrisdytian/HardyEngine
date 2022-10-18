#pragma once
#include "Window.h"
#include "Time.h"
#include <optional>
class Engine
{
public: 
	Engine();
	int Init();
	bool Frame();
private:
	Window window;
	Time timer;
	//std::optional<int> exitCode;
};


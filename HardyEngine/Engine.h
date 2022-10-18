#pragma once
#include "Window.h"
#include <optional>
class Engine
{
public: 
	Engine();
	int Init();
	bool Frame();
private:
	Window window;
	//std::optional<int> exitCode;
};


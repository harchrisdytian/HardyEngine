#pragma once
#include <optional>
#include "Window.h"
#include "Time.h"


class Engine
{
public: 
	Engine();
	~Engine();

	int Init();
	bool Frame();
private:
	Window window;
	Time timer;
	std::vector<std::unique_ptr<class Cube>> cubes;
	//std::optional<int> exitCode;
};


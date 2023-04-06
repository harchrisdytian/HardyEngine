#pragma once
#include <optional>
#include "Window.h"
#include "Time.h"
#include "Camera.h"
#include "PointLight.h"


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
	Camera cam;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 330;
	PointLight light;

};


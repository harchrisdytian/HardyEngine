#include "Engine.h"

#include <memory>
#include "Cube.h"

Engine::Engine():
	window(720,1280 ,"yes")
{
	
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		cubes.push_back(std::make_unique<Cube>(window.GetGraphics(),rng,adist,ddist,odist,rdist));
	}
	window.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f) );
}

Engine::~Engine()
{
}


int Engine::Init()
{
	while (true) {
		Frame();
		if (const auto exitcode = Window::ProcessMessage()) {
			return *exitcode;
		}
		
	}
}

bool Engine::Frame()
{
	auto deltaTime = timer.Mark();
	const std::string name = std::to_string( timer.Peak());
	window.GetGraphics().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& c : cubes) {
		c->Update(deltaTime);
		c->Draw(window.GetGraphics());
	}
	window.GetGraphics().EndFrame();

	return true;
}

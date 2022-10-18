#include "Engine.h"

Engine::Engine():
	window(720,1280 ,"yes")
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
	window.GetGraphics().EndFrame();
	const std::string name = std::to_string( timer.Peak());
	window.ChangeName(name);

	return true;
}

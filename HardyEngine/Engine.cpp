#include "Engine.h"
#include "Pyramid.h"
#include "Cube.h"
#include "Blob.h"
#include "Sheet.h"
#include "MyMath.h"
#include <algorithm>
#include <memory>
#include "ImageWrapper.h"
#include "ResourceManager.h"

#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
ResourceManager resourceManager;

Engine::Engine():
	window(600,800 ,"yes")
{


	

	class Factory
	{

	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<Cube>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 2:
				return std::make_unique<Blob>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			case 3:
				return std::make_unique<Sheet>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,3 };
	};

	Factory f(window.GetGraphics());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);

	window.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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
	window.GetGraphics().ClearBuffer(0.47f, 0.0f, 0.12f);
	for (auto& c : drawables) {
		c->Draw(window.GetGraphics());
		c->Update(deltaTime);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	static bool bowl = true;
	if (bowl) {
		ImGui::ShowDemoWindow(&bowl);

	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	window.GetGraphics().EndFrame();
	
	return true;
}

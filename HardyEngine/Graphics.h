#pragma once


#include <wrl/client.h>
#include <d3d11.h>
#include <memory>

#pragma comment( lib,"d3d11.lib" )

class Graphics
{
	//they did surgery on a grape 
public:
	Graphics(HWND window,int height, int width);

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	~Graphics() = default;
	void EndFrame();
private:
	
	int screenHeight;
	int screenWidth;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

};


#pragma once


#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <DirectXMath.h>
#include <memory>
#include <vector>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


class Graphics
{
	friend class Bindable;
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


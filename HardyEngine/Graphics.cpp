#include "Graphics.h"

Graphics::Graphics(HWND window, int height, int width)
{
	screenHeight = height;
	screenWidth = width;

	DXGI_SWAP_CHAIN_DESC swapChangeDescription = {};
	swapChangeDescription.BufferCount = 1;
	swapChangeDescription.BufferDesc.Width = screenWidth;
	swapChangeDescription.BufferDesc.Height = screenHeight;
	swapChangeDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChangeDescription.BufferDesc.RefreshRate.Numerator = 1;
	swapChangeDescription.BufferDesc.RefreshRate.Denominator = 60;
	swapChangeDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChangeDescription.OutputWindow = window;
	swapChangeDescription.SampleDesc.Count = 1;
	swapChangeDescription.SampleDesc.Quality = 0;
	swapChangeDescription.Windowed = TRUE;
	
	UINT swapCreateFlag = 0u;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, swapCreateFlag, nullptr, 0, D3D11_SDK_VERSION, &swapChangeDescription, &swapchain, &device, nullptr, &deviceContext);

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	//device->CreateRenderTargetView(device.Get(),nullptr,tatget)



}

void Graphics::EndFrame()
{
	swapchain->Present(1u, 0u);
}

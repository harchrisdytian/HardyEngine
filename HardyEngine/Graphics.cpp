#include "Graphics.h"

Graphics::Graphics(HWND window, int height, int width)
{
	screenHeight = height;
	screenWidth = width;

	DXGI_SWAP_CHAIN_DESC swapChangeDescription = {};
	swapChangeDescription.BufferCount = 1;
	swapChangeDescription.BufferDesc.Width = 0;
	swapChangeDescription.BufferDesc.Height = 0;
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
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);

	D3D11_DEPTH_STENCIL_DESC depthStencilDescription = {};
	depthStencilDescription.DepthEnable = TRUE;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState;

	device->CreateDepthStencilState(&depthStencilDescription, &DepthStencilState);

	deviceContext->OMSetDepthStencilState(DepthStencilState.Get(), 1u);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	D3D11_TEXTURE2D_DESC depthTextureDescription = {};
	depthTextureDescription.Width = screenWidth;
	depthTextureDescription.Height = screenHeight;
	depthTextureDescription.MipLevels = 1u;
	depthTextureDescription.ArraySize = 1u;
	depthTextureDescription.Format = DXGI_FORMAT_D32_FLOAT;
	depthTextureDescription.SampleDesc.Count = 1u;
	depthTextureDescription.SampleDesc.Quality = 0u;
	depthTextureDescription.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	device->CreateTexture2D( &depthTextureDescription, nullptr, &depthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0u;
	device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &DepthStencilView);

	D3D11_VIEWPORT viewPort;
	viewPort.Height = height;
	viewPort.Width = width;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	deviceContext->RSSetViewports(1u, &viewPort);


}


void Graphics::EndFrame()
{
	swapchain->Present(1u, 0u);
}

void Graphics::DrawIndexed(UINT count)
{
	deviceContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj)
{
	projection = proj;
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	const float color[] = { r,g,b,1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);
	deviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

DirectX::XMMATRIX Graphics::GetProjection()
{
	return projection;
}

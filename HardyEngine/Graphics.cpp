#include "Graphics.h"
#include <sstream>
#include <d3dcompiler.h>
#include "dxerr.h"
#include <cmath>
#include <DirectXMath.h>
#include "GraphicsThrowMacros.h"

#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


Graphics::Graphics(HWND window, int height, int width)
{
	screenHeight = height;
	screenWidth = width;
	HRESULT hr;


	DXGI_SWAP_CHAIN_DESC swapChangeDescription = {};
	swapChangeDescription.BufferDesc.Width = 0;
	swapChangeDescription.BufferDesc.Height = 0;
	swapChangeDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChangeDescription.BufferDesc.RefreshRate.Numerator = 0;
	swapChangeDescription.BufferDesc.RefreshRate.Denominator = 0;
	swapChangeDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChangeDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChangeDescription.SampleDesc.Count = 1;
	swapChangeDescription.SampleDesc.Quality = 0;
	swapChangeDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChangeDescription.BufferCount = 1;
	swapChangeDescription.OutputWindow = window;
	swapChangeDescription.Windowed = TRUE;
	swapChangeDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChangeDescription.Flags = 0;

	UINT swapCreateFlag =  0 | D3D11_CREATE_DEVICE_DEBUG;

	// create device and front/back buffers, and swap chain and rendering context
	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, swapCreateFlag, nullptr, 0,
		D3D11_SDK_VERSION, &swapChangeDescription,
			&swapchain, &device, nullptr, &deviceContext));

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);

	GFX_THROW_INFO(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView));



	D3D11_DEPTH_STENCIL_DESC depthStencilDescription = {};
	depthStencilDescription.DepthEnable = TRUE;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState;

	device->CreateDepthStencilState(&depthStencilDescription, &DepthStencilState);

	deviceContext->OMSetDepthStencilState(DepthStencilState.Get(), 1u);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
	D3D11_TEXTURE2D_DESC depthTextureDescription = {};
	depthTextureDescription.Width = 784u;
	depthTextureDescription.Height = 561u;
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

	deviceContext->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), DepthStencilView.Get());

	D3D11_VIEWPORT viewPort;
	viewPort.Height = 600.0f; ;
	viewPort.Width = 800.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	deviceContext->RSSetViewports(1u, &viewPort);

	ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
}


void Graphics::EndFrame()
{
	if (imguiEnabled) {
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT hr;
#ifndef NDEBUG
	infoManager.Set();
#endif
	if (FAILED(hr = swapchain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(device->GetDeviceRemovedReason());
		}
		else
		{
			throw GFX_EXCEPT(hr);
		}
	}
}


void Graphics::DrawIndexed(UINT count)
{
	GFX_THROW_INFO_ONLY( deviceContext->DrawIndexed(count, 0u, 0u));
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj)
{
	projection = proj;
}

Graphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}
const char* Graphics::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetStartString();
	errBuffer = oss.str();
	return errBuffer.c_str();
}

const char* Graphics::HrException::GetType() const noexcept
{
	return "My Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string Graphics::HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(hr);
}

std::string Graphics::HrException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return buf;
}

std::string Graphics::HrException::GetErrorInfo() const noexcept
{
	return info;
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "My Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}


const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetStartString();
	errBuffer = oss.str();
	return errBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept
{
	return "My Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	if (imguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	const float color[] = { r,g,b,1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);
	deviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

DirectX::XMMATRIX Graphics::GetProjection()
{
	return projection;
}

DirectX::XMMATRIX Graphics::GetCamera()
{
	return camera;
}

void Graphics::SetCamera(DirectX::XMMATRIX cam)
{
	camera = cam;
}

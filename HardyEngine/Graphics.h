#pragma once

#include <Windows.h>
#include "ExceptionHandler.h"
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include "DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <random>	



#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


class Graphics
{
	friend class Bindable;
	//they did surgery on a grape 
public:
	class Exception : public ExceptionHandler
	{
		using ExceptionHandler::ExceptionHandler;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND window,int height, int width);

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	~Graphics() = default;
	void EndFrame();
	void DrawIndexed(UINT count);
	void SetProjection(DirectX::FXMMATRIX proj);
	
	void ClearBuffer(float r, float g, float b);
	DirectX::XMMATRIX GetProjection();
	DirectX::XMMATRIX GetCamera();
	void SetCamera(DirectX::XMMATRIX cam);
private:
	DirectX::XMMATRIX projection;
	int screenHeight;
	int screenWidth;
	bool imguiEnabled = true;

	DirectX::XMMATRIX camera;
	DxgiInfoManager infoManager;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView;

};


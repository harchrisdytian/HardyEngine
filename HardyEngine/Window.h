#pragma once

//#include "Event.h"
#include "Graphics.h"
#include "ExceptionHandler.h"
#include "Input.h"
#include <Windows.h>
#include <memory>
#include <optional>
#include "ImGui/imgui.h"

class Window
{
public:
	class Exception : public ExceptionHandler
	{
		using ExceptionHandler::ExceptionHandler;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
private:


	class WindowClass
	{
	private:
		WindowClass();
		~WindowClass();
	public:
		static WindowClass windowClass;
		static HINSTANCE GetInstance();
		
	private: 
		HINSTANCE hInstance;

	};
public:
		Input input;

public:
		Window(int heght, int width, const char* name);
		~Window();
		Window(const Window& window) = delete;
		Window& operator=(const Window& window) = delete;
		void ChangeName(std::string name);
		HWND GetHandle();
		static std::optional<int> ProcessMessage();
		static constexpr const char* windowClassName = "Hardy Engine";
		LRESULT CALLBACK MessageHandle(HWND hWindow,UINT uMsg, WPARAM wParameter,LPARAM lParameter );
		static LRESULT CALLBACK MessageStartUp(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter);
		static LRESULT CALLBACK MessageTranslator(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter);
		Graphics& GetGraphics();

private:
	HWND hWindow;
	std::unique_ptr<Graphics> graphics;
	int height;
	int width;
};


#pragma once

#include <Windows.h>


class Window
{
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
		Window(int heght, int width, const char* name);
		~Window();
		Window(const Window& window) = delete;
		Window& operator=(const Window& window) = delete;
		static constexpr const char* windowClassName = "Hardy Engine";
		static LRESULT CALLBACK MessageHangle(HWND hWnd,UINT uMsg, WPARAM wParameter,LPARAM lParameter );
private:
	HWND hWindow;
	int height;
	int width;

};


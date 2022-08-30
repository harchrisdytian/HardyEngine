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
		HINSTANCE hInstance;

	};

public:
		Window(int heght, int width, const char* name);
		~Window();
		Window(const Window& window) = delete;
		Window& operator=(const Window& window) = delete;

		static LRESULT CALLBACK MessageHangle(HWND hWnd,UINT uMsg, WPARAM wParameter,LPARAM lParameter );
private:
	HWND hWnd;
	int height;
	int width;

};


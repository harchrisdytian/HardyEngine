#pragma once

//#include "Event.h"
#include <Windows.h>
#include "Input.h"
#include <memory>


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
		Input input;

public:
		Window(int heght, int width, const char* name);
		~Window();
		Window(const Window& window) = delete;
		Window& operator=(const Window& window) = delete;
		
		static constexpr const char* windowClassName = "Hardy Engine";
		LRESULT CALLBACK MessageHandle(HWND hWindow,UINT uMsg, WPARAM wParameter,LPARAM lParameter );
		static LRESULT CALLBACK MessageStartUp(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter);
		static LRESULT CALLBACK MessageTranslator(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter);
	    

private:
	HWND hWindow;


	int height;
	int width;
};


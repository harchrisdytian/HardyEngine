#include "Window.h"


Window::WindowClass::WindowClass()
{
	WNDCLASSEX wndClass = {};
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = MessageHangle;
	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = nullptr;
	wndClass.hIcon = nullptr;
	wndClass.hIconSm = nullptr;
	wndClass.lpszClassName = windowClassName;

	RegisterClassEx( &wndClass);
 
}
Window::WindowClass::~WindowClass()
{
	UnregisterClass(windowClassName, hInstance);
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return windowClass.hInstance;
}

Window::Window(int heght, int width, const char* name)
	:
	width(width), 
	height(height)
{
	//set the size of window
	RECT rect;
	rect.left = 100;
	rect.right = width + 100;
	rect.top = 100;
	rect.bottom = 100 + height;


	hWindow = CreateWindow( TEXT(windowClassName), TEXT(name),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.top - rect.bottom,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	

	


}

Window::~Window()
{
}
LRESULT CALLBACK Window::MessageHangle(HWND hWnd,UINT uMsg,WPARAM wParameter, LPARAM lParameter) 
{
	return DefWindowProc(hWnd, uMsg, wParameter, lParameter);
}
//singleton
Window::WindowClass Window::WindowClass::windowClass;


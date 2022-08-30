#include "Window.h"


Window::WindowClass::WindowClass()
{
	WNDCLASSEX wndClass = {};
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = MessageHangle;
	wndClass.cbSize = sizeof(wndClass);

 
}
Window::WindowClass::~WindowClass()
{
}

Window::Window(int heght, int width, const char* name)
	:
	width(width), 
	height( height)
{
	RECT rect;
	rect.left = 100;
	rect.right = width + 100;
	rect.top = 100;
	rect.bottom = 100 + height;

	


}

Window::~Window()
{
}
LRESULT CALLBACK Window::MessageHangle(HWND hWnd,UINT uMsg,WPARAM wParameter, LPARAM lParameter) noexcept
{
	return DefWindowProc(hWnd, uMsg, wParameter, lParameter);
}
//singleton
Window::WindowClass Window::WindowClass::windowClass;


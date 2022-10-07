#include "Window.h"

//singleton
Window::WindowClass Window::WindowClass::windowClass;


Window::WindowClass::WindowClass()
{
	WNDCLASSEX wndClass = {};
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = MessageStartUp;
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

Window::Window(int height, int width, const char* name)
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
		rect.bottom - rect.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	
	ShowWindow(hWindow, SW_SHOWDEFAULT);
	


}

Window::~Window()
{
	DestroyWindow(hWindow);
}


LRESULT CALLBACK Window::MessageHandle(HWND hWnd,UINT uMsg,WPARAM wParameter, LPARAM lParameter) 
{
	
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(20);
		return 20;

	//***  ******//
	// Input Handler
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		const Event e = Event(Event::Type::KEY_PRESSED,static_cast<char>(wParameter));
		input.OnKeyPressed(e);
		break;
	
	}
		 //OnKeyPressed(e);
		//Input input;

	case WM_KEYUP:
	{
		{
		 const Event e = Event(Event::Type::KEY_RELEASED, static_cast<char>(wParameter));
		 input.OnKeyRelease(e);
		 break;
		}
	}

	}
	return DefWindowProc(hWnd, uMsg, wParameter, lParameter);
}

LRESULT Window::MessageStartUp(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter)
{
	if (uMsg == WM_CREATE) {
		// translates the creation to use winapi to handle user-data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParameter);
		Window* const pWindow = static_cast<Window*>(pCreate->lpCreateParams); 
		SetWindowLongPtr(hWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		//
		SetWindowLongPtr(hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::MessageTranslator));

		return pWindow->MessageHandle(hWindow,uMsg,wParameter,lParameter);

	}
	return DefWindowProc(hWindow, uMsg, wParameter, lParameter);
}
LRESULT Window::MessageTranslator(HWND hWindow, UINT uMsg, WPARAM wParameter, LPARAM lParameter) 
{
	Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWindow, GWLP_USERDATA));
	// parse threw pointer 
	return pWindow->MessageHandle(hWindow, uMsg, wParameter, lParameter);
}

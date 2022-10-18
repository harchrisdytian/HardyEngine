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
	
	graphics = std::make_unique<Graphics>(hWindow,width,height);
	ShowWindow(hWindow, SW_SHOWDEFAULT);
	


}

Window::~Window()
{
	DestroyWindow(hWindow);
}


HWND Window::GetHandle()
{
	return hWindow;
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}

LRESULT CALLBACK Window::MessageHandle(HWND hWnd,UINT uMsg,WPARAM wParameter, LPARAM lParameter)
{
	
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(67);
		return 20;

	//***  ******//
	// Input Handler
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		const Event e = Event(Event::Type::KEY_PRESSED, static_cast<unsigned char>(wParameter));
		
		input.OnKeyPressed(e);
		break;
	
	}
		 //OnKeyPressed(e);
		//Input input;

	case WM_CHAR:
	{
		input.OnCharPressed(static_cast<unsigned char>(wParameter));
		break;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		{
		 const Event e = Event(Event::Type::KEY_RELEASED, static_cast<unsigned char>(wParameter));
		 input.OnKeyRelease(e);
		 break;
		}
	}
	// Mouse input
	case WM_MOUSEMOVE: 
	{

		const POINTS pt = MAKEPOINTS(lParameter);
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
		{
			input.SetPos(pt.x, pt.y);
		}
		break;
		}

	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_LEFT_PRESSED, pt.x,pt.y,true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonPressed(e);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_LEFT_RELEASED, pt.x, pt.y, true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonRelease(e);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_RIGHT_PRESSED, pt.x, pt.y, true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonPressed(e);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_RIGHT_RELEASED, pt.x, pt.y, true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonRelease(e);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_MIDDLE_PRESSED, pt.x, pt.y, true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonPressed(e);
		break;
	}
	case WM_MBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParameter);
		Event e = Event(Event::Type::MOUSE_MIDDLE_RELEASED, pt.x, pt.y, true, false);
		input.SetPos(pt.y, pt.y);
		input.OnMouseButtonRelease(e);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const int delta  = GET_WHEEL_DELTA_WPARAM(wParameter);
		input.OnWheelDelta(delta);
		break;
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

Graphics& Window::GetGraphics()
{
	if (graphics)
		return *graphics;

}

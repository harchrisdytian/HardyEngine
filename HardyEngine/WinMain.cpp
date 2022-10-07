#include <Windows.h>
#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	Window win = Window(400, 500, "bob");
	MSG gMsg;
	BOOL gMsgRes;
	while (( gMsgRes = GetMessage(&gMsg, nullptr,0,0)) >0)
	{
		//return gMsg.wParam;
		if (win.input.IsKeyPressed('E'))
		{
			return gMsg.wParam;
		}
		TranslateMessage(&gMsg);
		DispatchMessage(&gMsg);
		
	}
	
	return gMsg.wParam;
}
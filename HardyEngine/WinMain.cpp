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
		if (win.keyboard);
		TranslateMessage(&gMsg);
		DispatchMessage(&gMsg);
		
	}
	
	return gMsg.wParam;
}
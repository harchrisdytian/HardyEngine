
#include "ResourceManager.h"
#include <gdiplus.h>


int ResourceManager::refCount = 0;
ULONG_PTR ResourceManager::token = 0;

ResourceManager::ResourceManager()
{
	if (refCount++ == 0) 
	{
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

ResourceManager::~ResourceManager()
{
	if (--refCount == 0) 
	{
		Gdiplus::GdiplusShutdown(token);
	}
}

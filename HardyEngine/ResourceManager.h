#pragma once

#include <Windows.h>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ULONG_PTR token;
	static int refCount;
};


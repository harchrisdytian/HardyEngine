#pragma once
#include "Graphics.h"

class Bindable
{
public:
	virtual void Bind( Graphics& _graphics) = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(Graphics& _graphics);
	static ID3D11Device* GetDevice(Graphics& _graphics);
};


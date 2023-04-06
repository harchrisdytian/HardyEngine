#pragma once
#include <d3d11.h>

#include "Graphics.h"
class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const;
	void SpawnControlWindow();
	void Reset();
private:
	//positional data;
	float r = 20.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
};



#pragma once
#include "Graphics.h"
#include "SolidSphere.h"
#include "ConstantBuffer.h"
class PointLight
{
public:
	PointLight(Graphics& _graphics, float radius = 0.5f);

	void Reset() ;
	void Draw(Graphics& _graphics);
	void Bind(Graphics& _graphics, DirectX::FXMMATRIX view);;
private:
	struct PointLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	PointLightCBuf cbData;
	mutable SolidSphere mesh;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};
#include "PointLight.h"

PointLight::PointLight(Graphics& _graphics, float radius):
	mesh(_graphics,radius),
	cbuf(_graphics)
{
	Reset();
}

void PointLight::Reset()
{
	cbData = {
		{ 1.5f,14.0f,-4.5f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void PointLight::Draw(Graphics& _graphics)
{
	mesh.SetPos(cbData.pos);
	mesh.Draw(_graphics);
}

void PointLight::Bind(Graphics& _graphics, DirectX::FXMMATRIX view)
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(_graphics, dataCopy);
	cbuf.Bind(_graphics);
}

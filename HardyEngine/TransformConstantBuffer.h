#pragma once
#include "ConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>
class TransformConstantBuffer : public Bindable
{
public:
	TransformConstantBuffer(Graphics& _Graphics, const Drawable& parent);
	void Bind(Graphics& _Graphics) override;
private:
	VertexConstantBuffer<DirectX::XMMATRIX> m_VertexMatrixBuffer;
	const Drawable& parent;
};


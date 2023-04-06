#pragma once
#include "ConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>
class TransformConstantBuffer : public Bindable
{
public:
	TransformConstantBuffer(Graphics& _Graphics, const Drawable& parent);
	void Bind(Graphics& _Graphics) override;
	struct ModelTransform
	{
		DirectX::XMMATRIX modelViewTransfrom;
		DirectX::XMMATRIX model;
	};
private:
	static std::unique_ptr<VertexConstantBuffer<ModelTransform>> m_VertexMatrixBuffer;
	const Drawable& parent;
};


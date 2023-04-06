#include "TransformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Graphics& _Graphics, const Drawable& parent):
	parent(parent)
{
	if (!m_VertexMatrixBuffer) {
		m_VertexMatrixBuffer = std::make_unique<VertexConstantBuffer<ModelTransform>> (_Graphics);
	}
}

void TransformConstantBuffer::Bind(Graphics& _Graphics)
{
	const auto model = parent.GetTransformXM();
	const ModelTransform transfrom =
	{
		DirectX::XMMatrixTranspose(model),
		DirectX::XMMatrixTranspose(
		model *
		_Graphics.GetCamera() *
		_Graphics.GetProjection()
		)
	};
	m_VertexMatrixBuffer->Update(_Graphics, transfrom);


	m_VertexMatrixBuffer->Bind(_Graphics);
}

std::unique_ptr<VertexConstantBuffer<TransformConstantBuffer::ModelTransform>> TransformConstantBuffer::m_VertexMatrixBuffer;
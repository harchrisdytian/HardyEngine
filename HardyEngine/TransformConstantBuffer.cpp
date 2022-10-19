#include "TransformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Graphics& _Graphics, const Drawable& parent):
	m_VertexMatrixBuffer(_Graphics),
	parent(parent)
{

}

void TransformConstantBuffer::Bind(Graphics& _Graphics)
{
	m_VertexMatrixBuffer.Update(_Graphics, DirectX::XMMatrixTranspose(parent.GetTransformXM() * _Graphics.GetProjection()));
	m_VertexMatrixBuffer.Bind(_Graphics);
}

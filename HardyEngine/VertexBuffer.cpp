#include "VertexBuffer.h"



void VertexBuffer::Bind(Graphics& _Graphics)
{
	const UINT offset = 0u;
	GetContext(_Graphics)->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
}

#include "VertexBuffer.h"
template<class V>
VertexBuffer::VertexBuffer(Graphics& _Graphics, const std::vector<V>& vertices):
	stride(sizeof(V))

{
	D3D11_BUFFER_DESC VertexBufferDescription = {};
	VertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDescription.CPUAccessFlags = 0u;
	VertexBufferDescription.MiscFlags = 0u;
	VertexBufferDescription.ByteWidth = UINT(sizeof(V) * vertices.size());
	VertexBufferDescription.StructureByteStride = sizeof(V);
	D3D11_SUBRESOURCE_DATA VertexResourceData;
	VertexResourceData.pSysMem = vertices.data();

	GetDevice(_Graphics)->CreateBuffer(VertexBufferDescription, VertexResourceData, m_VertexBuffer);
}


void VertexBuffer::Bind(Graphics& _Graphics)
{
	const UINT offset = 0u;
	GetContext(_Graphics)->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
}

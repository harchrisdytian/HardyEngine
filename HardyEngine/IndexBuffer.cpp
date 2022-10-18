#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& _graphics, std::vector<unsigned short> indices):
	count((UINT) indices.size())

{
	D3D11_BUFFER_DESC IndexBufferDescription = {};
	IndexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDescription.CPUAccessFlags = 0u;
	IndexBufferDescription.MiscFlags = 0u;
	IndexBufferDescription.ByteWidth = UINT(count * sizeof(unsigned short));
	IndexBufferDescription.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA IndexBufferData = {};
	IndexBufferData.pSysMem = indices.data();

	GetDevice(_graphics)->CreateBuffer(&IndexBufferDescription, &IndexBufferData, &indexBuffer);
}

void IndexBuffer::Bind(Graphics& _graphics)
{
	GetContext(_graphics)->IASetIndexBuffer(indexBuffer.Get(),DXGI_FORMAT_R16_UINT, 0u);
}
UINT IndexBuffer::GetCount() const
{
	return count;
}

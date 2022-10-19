#pragma once
#include "Bindable.h"

class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics& _Graphics, const std::vector<V>& vertices):
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

		GetDevice(_Graphics)->CreateBuffer(&VertexBufferDescription, &VertexResourceData, &m_VertexBuffer);
	};
	void Bind(Graphics& _Graphics) override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};


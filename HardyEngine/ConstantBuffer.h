#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Graphics& _graphics, const C& consts) 
	{
		D3D11_MAPPED_SUBRESOURCE ConstantBufferSubResource;
		GetContext(_graphics)->Map(m_ConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u,&ConstantBufferSubResource);
		memcpy(ConstantBufferSubResource.pData, &consts, sizeof(consts));
		GetContext(_graphics)->Unmap(m_ConstantBuffer.Get(), 0u);

	}
	ConstantBuffer(Graphics& _Graphics, const C& consts)
	{


		D3D11_BUFFER_DESC ConstantBufferDescription;
		ConstantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		ConstantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ConstantBufferDescription.MiscFlags = 0u;
		ConstantBufferDescription.ByteWidth = sizeof(consts);
		ConstantBufferDescription.StructureByteStride = 0u;
		
		D3D11_SUBRESOURCE_DATA ConstantBufferData = {};
		ConstantBufferData.pSysMem = &consts;
		GetDevice(_Graphics)->CreateBuffer(&ConstantBufferDescription, &ConstantBufferData, &m_ConstantBuffer);
	}
	ConstantBuffer(Graphics& _Graphics)
	{


		D3D11_BUFFER_DESC ConstantBufferDescription;
		ConstantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		ConstantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ConstantBufferDescription.MiscFlags = 0u;
		ConstantBufferDescription.ByteWidth = sizeof( C );
		ConstantBufferDescription.StructureByteStride = 0u;
			
		GetDevice(_Graphics)->CreateBuffer(&ConstantBufferDescription, nullptr, &m_ConstantBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
};


template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::m_ConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& _Graphics) noexcept override
	{
		GetContext(_Graphics)->VSSetConstantBuffers(0u, 1u, m_ConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::m_ConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& _Graphics) noexcept override
	{
		GetContext(_Graphics)->PSSetConstantBuffers(0u, 1u, m_ConstantBuffer.GetAddressOf());
	}
};

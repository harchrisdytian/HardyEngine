#include "Sampler.h"
#include "GraphicsThrowMacros.h"

Sampler::Sampler(Graphics& _Graphics)
{
	INFOMAN(_Graphics);
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GFX_THROW_INFO(GetDevice(_Graphics)->CreateSamplerState(&samplerDesc, &m_Sampler));
}

void Sampler::Bind(Graphics& _Graphics)
{
	GetContext(_Graphics)->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());
}

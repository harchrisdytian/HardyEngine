#include "Texture.h"
#include "ImageWrapper.h"
#include "GraphicsThrowMacros.h"
Texture::Texture(Graphics& _Graphics, const ImageWrapper& _Image)
{
	INFOMAN(_Graphics);
	// create texture resource
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = _Image.GetWidth();
	textureDesc.Height = _Image.GetHeight();
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = _Image.GetBufferPtr();
	sd.SysMemPitch = _Image.GetWidth() * sizeof(ImageWrapper::Color);
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	GFX_THROW_INFO(GetDevice(_Graphics)->CreateTexture2D(
		&textureDesc, &sd, &pTexture
	));

	// create the resource view on the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	GFX_THROW_INFO(GetDevice(_Graphics)->CreateShaderResourceView(
		pTexture.Get(), &srvDesc, &m_textureView
	));
}

void Texture::Bind(Graphics& _Graphics)
{
	GetContext(_Graphics)->PSSetShaderResources(0u, 1u, m_textureView.GetAddressOf());
}

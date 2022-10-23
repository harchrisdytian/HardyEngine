#include "PixelShader.h"
#include "GraphicsThrowMacros.h"

PixelShader::PixelShader(Graphics& _graphics, const std::wstring& path)
{
	INFOMAN(_graphics);

	Microsoft::WRL::ComPtr<ID3DBlob> byteCodeBlob;

	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &byteCodeBlob));
	GFX_THROW_INFO(GetDevice(_graphics)->CreatePixelShader(byteCodeBlob->GetBufferPointer(), byteCodeBlob->GetBufferSize(), nullptr, &m_PixelShader));
}

void PixelShader::Bind(Graphics& _graphics)
{
	GetContext(_graphics)->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
}

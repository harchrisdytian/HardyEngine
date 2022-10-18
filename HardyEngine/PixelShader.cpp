#include "PixelShader.h"

PixelShader::PixelShader(Graphics& _graphics, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> byteCodeBlob;
	D3DReadFileToBlob(path.c_str(), &byteCodeBlob);
	GetDevice(_graphics)->CreatePixelShader(byteCodeBlob->GetBufferPointer(), byteCodeBlob->GetBufferSize(), nullptr, &m_PixelShader);
}

void PixelShader::Bind(Graphics& _graphics)
{
	GetContext(_graphics)->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
}

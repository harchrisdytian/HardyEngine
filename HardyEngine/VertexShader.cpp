#include "VertexShader.h"

VertexShader::VertexShader(Graphics& _graphics, const std::wstring path)
{
	D3DReadFileToBlob(path.c_str(), &ByteCodeBlob);
	GetDevice(_graphics)->CreateVertexShader(ByteCodeBlob->GetBufferPointer(), ByteCodeBlob->GetBufferSize(), nullptr, &m_VertexShader);
}

void VertexShader::Bind(Graphics& _graphics)
{
	GetContext(_graphics)->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

}

ID3DBlob* VertexShader::GetByteCode()
{
	return ByteCodeBlob.Get();
}

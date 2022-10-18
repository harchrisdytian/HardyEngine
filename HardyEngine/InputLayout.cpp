#include "InputLayout.h"

InputLayout::InputLayout(Graphics& _graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* m_VertexShaderBytecode)
{
	GetDevice(_graphics)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		m_VertexShaderBytecode->GetBufferPointer(),
		m_VertexShaderBytecode->GetBufferSize(),
		&m_InputLayout
	);
}


void InputLayout::Bind(Graphics& _graphics)
{
	GetContext(_graphics)->IASetInputLayout(m_InputLayout.Get());
}

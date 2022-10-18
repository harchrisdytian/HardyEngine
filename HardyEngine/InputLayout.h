#pragma once

#include "Bindable.h"

class InputLayout :  public Bindable
{
	InputLayout(Graphics& _graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* _VertexShaderBytecode);
	void Bind(Graphics& _graphics) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
};


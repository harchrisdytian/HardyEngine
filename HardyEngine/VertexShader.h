#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& _graphics, const std::wstring& path);
	void Bind(Graphics& _graphics) override;
	ID3DBlob* GetByteCode();
private: 
	Microsoft::WRL::ComPtr<ID3DBlob> ByteCodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;

};


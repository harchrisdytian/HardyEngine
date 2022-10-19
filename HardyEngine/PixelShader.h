#pragma once

#include "Bindable.h"
class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& _graphics, const std::wstring& path);
	void Bind(Graphics& _graphics) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
};


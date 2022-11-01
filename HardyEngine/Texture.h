#pragma once
#include "Bindable.h"
class Texture : public Bindable
{
public:
	Texture(Graphics& _Graphics, const class ImageWrapper& _Image);
	void Bind(Graphics& _Graphics);
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureView;
};


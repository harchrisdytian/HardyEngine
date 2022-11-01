#pragma once
#include "Bindable.h"
class Sampler : public Bindable
{
public:
	Sampler(Graphics& _Graphics);
	void Bind(Graphics& _Graphics) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
};


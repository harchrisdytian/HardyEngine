#pragma once
#include"Bindable.h"
class Topology : public Bindable
{
public:
	Topology(Graphics& _Graphics, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Graphics& _Graphics)  override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};


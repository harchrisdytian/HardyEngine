#pragma once
#include "Bindable.h"
class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics& _Graphics, const std::vector<V>& verticies);
	void Bind(Graphics& _Graphics) override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
};


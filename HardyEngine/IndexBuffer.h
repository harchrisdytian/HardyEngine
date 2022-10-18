#pragma once
#include "Bindable.h"
class IndexBuffer : Bindable
{
public:
	IndexBuffer(Graphics& _graphics,std::vector<unsigned short> indices);
	void Bind(Graphics& _graphics) override;
	UINT GetCount() const;
protected:

	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};



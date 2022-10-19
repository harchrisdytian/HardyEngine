#pragma once
#include "Graphics.h"
#include <DirectXMath.h>


class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	void Draw(Graphics& _Graphics) const;
	virtual void Update(float dt) = 0;
	void AddBind(std::unique_ptr<Bindable> bind);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> _indexBuf);
	virtual ~Drawable() = default;

private:
	const IndexBuffer* m_IndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;

};


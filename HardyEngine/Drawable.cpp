#include "Drawable.h"
#include "Bindable.h"
#include "IndexBuffer.h"

void Drawable::Draw(Graphics& _Graphics) const
{
	for (auto& b : binds) {
		b->Bind(_Graphics)
	}
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind)
{
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> _indexBuf)
{
	m_IndexBuffer = _indexBuf.get();
	binds.push_back(std::move(_indexBuf));
}

#include "Drawable.h"
#include "IndexBuffer.h"
#include "GraphicsThrowMacros.h"
#include "Bindable.h"

void Drawable::Draw(Graphics& _Graphics) const
{
	for (auto& b : binds) {

		b->Bind(_Graphics);
	}
	for (auto& b : GetStaticBinds()) {
		b->Bind(_Graphics);
	}
	_Graphics.DrawIndexed(m_IndexBuffer->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind)
{

	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> _indexBuf)
{
	assert("Attempting to add index buffer a second time" && m_IndexBuffer == nullptr);
	m_IndexBuffer = _indexBuf.get();
	binds.push_back( std::move(_indexBuf));
}

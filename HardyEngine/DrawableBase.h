#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"


template <class T>
class DrawableBase : public Drawable
{
protected:
	static bool IsStaticInitialized() 
	{
		return !staticBinds.empty();

	}
	static void AddStaticBind(std::unique_ptr<Bindable> bind)
	{
		assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		staticBinds.push_back(std::move(bind));
	}
	 void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> _ibuf)
	{
		assert("Attempting to add index buffer a second time" && m_IndexBuffer == nullptr);
		m_IndexBuffer = _ibuf.get();
		staticBinds.push_back(std::move(_ibuf));
	}
	void SetIndexFromStatic()
	{
		assert("Attempting to add index buffer a second time" && m_IndexBuffer == nullptr);
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				m_IndexBuffer = p;
				return;
			}
		}
		assert("Failed to find index buffer in static binds" && m_IndexBuffer != nullptr);
	}
private:
	const std::vector<std::unique_ptr<Bindable>> &GetStaticBinds() const override {
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;	
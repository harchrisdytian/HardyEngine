#pragma once
#include <DirectXMath.h>
#include <vector>


template <class T>
class IndexTriangleList

{
public:
	IndexTriangleList() = default;
	IndexTriangleList(std::vector<T> _verts_in, std::vector<unsigned short> _indices_in) : 
		Vertices(std::move(_verts_in)), 
		Indices(std::move(_indices_in))
	{ 
		assert(Vertices.size() > 2);
		assert(Indices.size() % 3 == 0);
	}
	void Transform(DirectX::FXMMATRIX matrix)
	{
		for (auto& v : Vertices)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
			DirectX::XMStoreFloat3(
				&v.pos,
				DirectX::XMVector3Transform(pos, matrix)
			);
		}
	}

public:
	std::vector<T> Vertices;
	std::vector<unsigned short> Indices;

};

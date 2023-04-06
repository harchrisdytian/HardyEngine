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

	 void SetNormalsFlat() 
	{
		assert(Indices.size() % 3 == 0 && Indices.size() > 0);
		
		for (size_t i = 0; i < Indices.size(); i += 3) 
		{
			auto& vert0 = Vertices[Indices[i]];
			auto& vert1 = Vertices[Indices[i + 1]];
			auto& vert2 = Vertices[Indices[i + 2]];
			const DirectX::FXMVECTOR pos0 = DirectX::XMLoadFloat3(&vert0.pos);
			const DirectX::FXMVECTOR pos1 = DirectX::XMLoadFloat3(&vert1.pos);
			const DirectX::FXMVECTOR pos2 = DirectX::XMLoadFloat3(&vert2.pos);

			//getting the normal from positions via cross
			const DirectX::FXMVECTOR normal = DirectX::XMVector3Normalize(
				DirectX::XMVector3Cross( DirectX::XMVectorSubtract(pos1 , pos0) , DirectX::XMVectorSubtract(pos2 , pos0) )
			);

			DirectX::XMStoreFloat3( &vert0.normal, normal);
			DirectX::XMStoreFloat3( &vert1.normal, normal);
			DirectX::XMStoreFloat3 (&vert2.normal, normal);
		}
	}

public:
	std::vector<T> Vertices;
	std::vector<unsigned short> Indices;

};

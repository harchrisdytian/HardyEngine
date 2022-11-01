#include "Cube.h"

#include "TransformConstantBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Topology.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include <memory>
#include "Cuboid.h"
Cube::Cube(Graphics& _Graphics,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist, 
	std::uniform_real_distribution<float>& ddist, 
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist):
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
		if (!IsStaticInitialized())
		{
			struct Vertex
			{
				DirectX::XMFLOAT3 pos;
			};

			const auto model = Cuboid::Make<Vertex>();
			
			//vertex buffer
			AddStaticBind(std::make_unique<VertexBuffer>(_Graphics, model.Vertices));

			auto vertShade = std::make_unique<VertexShader>(_Graphics, L"VertexShaderIndex.cso");
			auto byteVertShade = vertShade->GetByteCode();
			AddStaticBind(std::move(vertShade));

			AddStaticBind(std::make_unique<PixelShader>(_Graphics, L"PixelShaderIndex.cso"));

			
			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(_Graphics, model.Indices));

			struct PixelShaderConstants
			{
				struct
				{
					float r;
					float g;
					float b;
					float a;
				} face_colors[8];
			};
			const PixelShaderConstants cb2 =
			{
				{
					{ 1.0f,1.0f,1.0f },
					{ 1.0f,0.0f,0.0f },
					{ 0.0f,1.0f,0.0f },
					{ 1.0f,1.0f,0.0f },
					{ 0.0f,0.0f,1.0f },
					{ 1.0f,0.0f,1.0f },
					{ 0.0f,1.0f,1.0f },
					{ 0.0f,0.0f,0.0f }
				}
			};
			AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(_Graphics, cb2));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDescription =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			};
			AddStaticBind(std::make_unique<InputLayout>(_Graphics, InputElementDescription, byteVertShade));

			AddStaticBind(std::make_unique<Topology>(_Graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}
	else {
		SetIndexFromStatic();
	}


	AddBind(std::make_unique<TransformConstantBuffer>(_Graphics, *this));

	DirectX::XMStoreFloat3x3(
		&mt,
		DirectX::XMMatrixScaling(1.0f, 1.0f, bdist(rng))
	);

}

void Cube::Update(float dt) 
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Cube::GetTransformXM() const 
{
	return DirectX::XMLoadFloat3x3( &mt) * 
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}

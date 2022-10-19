#include "Topology.h"

Topology::Topology(Graphics& _Graphics, D3D11_PRIMITIVE_TOPOLOGY type):
	type(type)
{
}

void Topology::Bind(Graphics& _Graphics)
{
	GetContext(_Graphics)->IASetPrimitiveTopology(type);
}

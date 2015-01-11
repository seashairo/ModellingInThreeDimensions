#include "stdafx.h"
#include "PlaneMesh.h"
#include <DirectXmath.h>
using namespace DirectX;


PlaneMesh::PlaneMesh(void)  //see CubeMesh for structure comments; this functions identically
{
	struct PlaneVertex

	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normals;
	};

	PlaneVertex planeVertices[] =  //to do: fill in verticies for a Plane texture
	{
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)}
	};
}


PlaneMesh::~PlaneMesh(void)
{
}

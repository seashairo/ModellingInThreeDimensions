#include "stdafx.h"
#include "CubeMesh.h"
#include <DirectXmath.h>
using namespace DirectX;



CubeMesh::CubeMesh(void)
{

			struct CubeVertex
		{
		  XMFLOAT3 position; //stores coordinates of points in a polygon 
		  XMFLOAT2 texture; //stores texture map coordinates for polygon
		  XMFLOAT3 normals; //stores normal vectors of points in polygon
		};
			//initialize mesh
			CubeVertex cubeVertices[] = 
        { 
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3( 0.0, 0.0, -1.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0, -1.0,  1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3( 1.0, 0.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0,  1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3(-1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3( 1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3( 1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3(-1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3(-1.0, -1.0,  1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3( 0.0, 0.0,  1.0)},
			{ XMFLOAT3(-1.0,  1.0,  1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3(-1.0, 0.0,  0.0)},
			{ XMFLOAT3(-1.0,  1.0,  1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3(-1.0,  1.0, -1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0,  1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3( 1.0,  1.0, -1.0), XMFLOAT2(1.0, 1.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0, -1.0), XMFLOAT2(0.0, 0.0), XMFLOAT3( 0.0,-1.0,  0.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0,-1.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0, 1.0,  0.0)},
			{ XMFLOAT3(-1.0, -1.0,  1.0), XMFLOAT2(0.0, 1.0), XMFLOAT3( 0.0,-1.0,  0.0)},
			{ XMFLOAT3( 1.0, -1.0, -1.0), XMFLOAT2(1.0, 0.0), XMFLOAT3( 0.0,-1.0,  0.0)},
        }; 
}


CubeMesh::~CubeMesh(void)
{
}

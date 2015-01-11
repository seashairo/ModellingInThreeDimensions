#pragma once
#include <DirectXMath.h>
#include "PlaneMesh.h"
#include "TextureClass.h"
using namespace DirectX;

class PlaneClass
{
public:
	PlaneClass(XMFLOAT3, TextureClass);
	~PlaneClass(void);
};


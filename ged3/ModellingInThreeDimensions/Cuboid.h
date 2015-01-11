#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Cuboid
{
public:
	Cuboid(XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3);
	int SetPoint(char, XMFLOAT3);
	XMFLOAT3 GetPoint(char);
	~Cuboid(void);
};


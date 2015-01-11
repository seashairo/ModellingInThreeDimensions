#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Sphere
{
public:
	Sphere(XMFLOAT3, int);
	int SetPoint(XMFLOAT3);
	int SetRadius(int);
	XMFLOAT3 GetPoint(void);
	int GetRadius(void);
	~Sphere(void);
};


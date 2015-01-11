#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class RectanglePlane
{
public:
	RectanglePlane(XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3);
	int SetPoint(char, XMFLOAT3);
	XMFLOAT3 GetPoint(char);
	~RectanglePlane(void);
};


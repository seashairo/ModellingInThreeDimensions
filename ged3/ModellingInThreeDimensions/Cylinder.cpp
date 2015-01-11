#include "stdafx.h"
#include "Cylinder.h"
#pragma once;

XMFLOAT3 cylA;
XMFLOAT3 cylB;
int cylRadius;

Cylinder::Cylinder(XMFLOAT3 a, XMFLOAT3 b, int radius)
{
	cylA = a;
	cylB = b;
	cylRadius = radius;
}

inline int SetPoint(char x, XMFLOAT3 a)
{
	switch (x)
	{
	case 'a': cylA = a;
		break;
	case 'b': cylB = a;
		break;
	}
	return 0;
}

inline XMFLOAT3 GetPoint(char x)
{
	switch (x)
	{
	case 'a': return cylA;
		break;
	case 'b': return cylB;
		break;
	}
	return NULL;
}

inline int SetRadius(int radius)
{
	cylRadius = radius;
	return 0;
}

inline int GetRadius(void)
{
	return cylRadius;
}
Cylinder::~Cylinder(void)
{
}

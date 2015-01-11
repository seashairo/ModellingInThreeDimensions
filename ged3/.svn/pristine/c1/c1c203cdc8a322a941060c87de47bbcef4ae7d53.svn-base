#include "stdafx.h"
#include "Sphere.h"
#pragma once;

XMFLOAT3 sphA;
int sphRadius;


Sphere::Sphere(XMFLOAT3 a, int radius)
{
	
	sphA = a;
	sphRadius = radius;
}

inline int SetPoint(XMFLOAT3 a)
{
	sphA = a;
	return 0;
}

inline int SetRadius(int radius)
{
	sphRadius = radius;
	return 0;
}

inline XMFLOAT3 GetPoint(void)
{
	return sphA;
}

inline int GetRadius(void)
{
	return sphRadius;
}

Sphere::~Sphere(void)
{
}

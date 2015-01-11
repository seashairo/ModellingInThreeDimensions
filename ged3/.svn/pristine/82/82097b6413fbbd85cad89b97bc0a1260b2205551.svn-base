#include "stdafx.h"
#include "RectanglePlane.h"
#pragma once;

XMFLOAT3 recA;
XMFLOAT3 recB;
XMFLOAT3 recC;
XMFLOAT3 recD;

RectanglePlane::RectanglePlane(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d)
{
	recA = a;
	recB = b;
	recC = c;
	recD = d;
}

inline int SetPoint(char x, XMFLOAT3 a)
{
	switch (x)
	{
	case 'a': recA = a;
		break;
	case 'b': recB = a;
		break;
	case 'c': recC = a;
		break;
	case 'd': recD = a;
		break;
	}

	return 0;
}

inline XMFLOAT3 GetPoint(char x)
{
	switch (x)
	{
	case 'a': return recA;
		break;
	case 'b': return recB;
		break;
	case 'c': return recC;
		break;
	case 'd': return recD;
		break;
	}
}

RectanglePlane::~RectanglePlane(void)
{
}

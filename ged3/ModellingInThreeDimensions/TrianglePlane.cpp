#include "stdafx.h"
#include "TrianglePlane.h"
#pragma once;

	XMFLOAT3 triA;
	XMFLOAT3 triB;
	XMFLOAT3 triC;

	TrianglePlane::TrianglePlane(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
	{
		triA = a;
		triB = b;
		triC = c;
	}

	
	inline int SetPoint(char x, XMFLOAT3 a)
	{
		switch (x)
		{
			case 'a': triA = a;
				break;
			case 'b': triB = a;
				break;
			case 'c': triC = a;
				break;

				return 0;
		}

	}

	inline XMFLOAT3 GetPoint(char x)
	{

		switch (x)
		{
		case 'a': return triA;
			break;
		case 'b': return triB;
			break;
		case 'c': return triC;
			break;
		}
	}



TrianglePlane::~TrianglePlane(void)
{
}

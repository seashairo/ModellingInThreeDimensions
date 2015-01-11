////////////////////////////////////////////////////////////////////////////////
// Filename: foliageshaderclass.h
// http://www.rastertek.com/terdx10tut19.html Used for Reference.
////////////////////////////////////////////////////////////////////////////////
#ifndef _FOLIAGESHADERCLASS_H_
#define _FOLIAGESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: FoliageShaderClass
////////////////////////////////////////////////////////////////////////////////
class FoliageShaderClass
{
public:
	FoliageShaderClass(void);
	FoliageShaderClass(const FoliageShaderClass&);
	~FoliageShaderClass(void);

	bool Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*, int, int, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*);

private:
	bool InitializeShader(ID3D10Device*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*);
	void RenderShader(ID3D10Device*, int, int);

private:
	ID3D10Effect* m_effect;
	ID3D10EffectTechnique* m_technique;
	ID3D10InputLayout* m_layout;

	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_texturePtr;
};

#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTSHADERCLASS_H_
#define _LIGHTSHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
#include "Log.h"
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderClass
////////////////////////////////////////////////////////////////////////////////
class LightShaderClass
{
public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	void Render(ID3D10Device*, int, int, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView**,D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
			D3DXVECTOR3, D3DXVECTOR4, float);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*);
	void ShutdownShader();

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView**, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3,
							D3DXVECTOR4, float);
	void RenderShader(ID3D10Device*, int, int, int);

private:
	ID3D10Effect* m_effect;
	ID3D10EffectTechnique* m_technique;
	ID3D10InputLayout* m_layout;

	ID3D10EffectMatrixVariable* m_worldMatrixPtr;
	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_textureArrayPtr;
	
	ID3D10EffectVectorVariable* m_ambientColorPtr;
	ID3D10EffectVectorVariable* m_diffuseColorPtr;
	ID3D10EffectVectorVariable* m_lightDirectionPtr;

	ID3D10EffectVectorVariable* cameraPositionPtr;
	ID3D10EffectVectorVariable* specularColorPtr;
	ID3D10EffectScalarVariable* specularPowerPtr;
};

#endif
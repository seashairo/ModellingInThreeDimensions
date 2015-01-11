////////////////////////////////////////////////////////////////////////////////
// Filename: watershaderclass.h
// http://www.rastertek.com/tertut16.html Used for Reference.
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATERSHADERCLASS_H_
#define _WATERSHADERCLASS_H_
#include <d3d10.h>
#include <D3DX10math.h>
#include <fstream>
#include "Log.h"
using namespace std;

class WaterShaderClass
{
public:
	WaterShaderClass();
	WaterShaderClass(const WaterShaderClass&);
	~WaterShaderClass();

	bool Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, ID3D10ShaderResourceView*, 
		    ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR2, float, float, D3DXVECTOR4, D3DXVECTOR3, float, ID3D10ShaderResourceView*);

private:
	bool InitializeShader(ID3D10Device*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, ID3D10ShaderResourceView*, 
				 ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR2, float, float, D3DXVECTOR4, D3DXVECTOR3, float, ID3D10ShaderResourceView*);
	void RenderShader(ID3D10Device*, int);

	void frame();
	

private:
	float m_waterTranslation;

	ID3D10Effect* m_effect;
	ID3D10EffectTechnique* m_technique;
	ID3D10InputLayout* m_layout;

	ID3D10EffectMatrixVariable* m_worldMatrixPtr;
	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
	ID3D10EffectMatrixVariable* m_reflectionMatrixPtr;
	ID3D10EffectMatrixVariable* m_inverseViewMatrix;
	
	ID3D10EffectMatrixVariable* m_inverseTranposeMatrix;
	ID3D10EffectShaderResourceVariable* m_refractionTexturePtr;
	ID3D10EffectShaderResourceVariable* m_reflectionTexturePtr;
	ID3D10EffectShaderResourceVariable* m_normalTexturePtr;
	ID3D10EffectShaderResourceVariable* m_skyTexturePtr;

	ID3D10EffectVectorVariable* m_cameraPositionPtr;
	ID3D10EffectVectorVariable* m_normalMapTilingPtr;
	ID3D10EffectScalarVariable* m_waterTranslationPtr;
	ID3D10EffectScalarVariable* m_reflectRefractScalePtr;
	ID3D10EffectVectorVariable* m_refractionTintPtr;
	ID3D10EffectVectorVariable* m_lightDirectionPtr;
	ID3D10EffectScalarVariable* m_specularShininessPtr;
	
};

#endif
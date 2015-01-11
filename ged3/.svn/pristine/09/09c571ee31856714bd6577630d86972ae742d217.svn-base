////////////////////////////////////////////////////////////////////////////////
// Filename: terrainshaderclass.h
// http://www.rastertek.com/tertut02.html Used for reference.
// http://www.rastertek.com/tertut14.html Used for reference.
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: Terrain Shader Class
////////////////////////////////////////////////////////////////////////////////
class TerrainShaderClass
{
public:

	TerrainShaderClass(void);
	TerrainShaderClass(const TerrainShaderClass&);
	~TerrainShaderClass(void);

	bool Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, ID3D10ShaderResourceView*,ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,//Shadowing
								D3DXMATRIX lightViewMatrix, D3DXMATRIX lightProjectionMatrix,ID3D10ShaderResourceView* depthMapTexture, D3DXVECTOR3 lightPosition
								, D3DXVECTOR3 cameraPosition);

private:
	bool InitializeShader(ID3D10Device*, WCHAR*);
	void ShutdownShader();

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, ID3D10ShaderResourceView*, ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,//Shadowing
								D3DXMATRIX lightViewMatrix, D3DXMATRIX lightProjectionMatrix,ID3D10ShaderResourceView* depthMapTexture, D3DXVECTOR3 lightPosition
								, D3DXVECTOR3 cameraPosition);
	void RenderShader(ID3D10Device*, int);

private:

	//effects
	ID3D10Effect* m_effect;

	//techniques
	ID3D10EffectTechnique* m_technique;

	//layout
	ID3D10InputLayout* m_layout;

	//mutual attributes
	ID3D10EffectMatrixVariable* m_worldMatrixPtr;
	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_texturePtr;
	ID3D10EffectShaderResourceVariable* m_texturePtr1;
	ID3D10EffectShaderResourceVariable* m_texturePtr2;
	ID3D10EffectVectorVariable* m_lightDirectionPtr;

	ID3D10EffectVectorVariable* m_ambientColorPtr;
	ID3D10EffectVectorVariable* m_diffuseColorPtr;

	ID3D10EffectVectorVariable* m_clipPlanePtr;

	//Shadowing
	ID3D10EffectMatrixVariable* m_lightViewMatrixPtr, *m_lightProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_depthMapTexture;
	ID3D10EffectVectorVariable* m_lightPositionPtr;
	ID3D10EffectVectorVariable* m_cameraPositionPtr;
};


////////////////////////////////////////////////////////////////////////////////
// Filename: BasicShaderClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BASIC_H_
#define _BASIC_H_


//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
#include "Log.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: Shader Manager Class
////////////////////////////////////////////////////////////////////////////////
class BasicShaderClass
{
public:


	BasicShaderClass();
	BasicShaderClass(const BasicShaderClass&);
	~BasicShaderClass();

	void Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
							  ID3D10ShaderResourceView** textureArray, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition,
								D3DXVECTOR4 specularColor, float specularPower,
								//Shadowing
								D3DXMATRIX lightViewMatrix, D3DXMATRIX lightProjectionMatrix,ID3D10ShaderResourceView* depthMapTexture, D3DXVECTOR3 lightPosition
								);
private:
	void ShutdownShader();
private:

	//effects
	ID3D10Effect* m_effects;

	//techniques
	ID3D10EffectTechnique* m_techniques;

	//layouts
	ID3D10InputLayout* m_Layouts;

	//mutual attributes
	ID3D10EffectMatrixVariable* m_worldMatrixPtr;
	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
	
	ID3D10EffectVectorVariable* m_ambientColorPtr;
	ID3D10EffectVectorVariable* m_diffuseColorPtr;
	ID3D10EffectVectorVariable* m_lightDirectionPtr;

	ID3D10EffectVectorVariable* m_cameraPositionPtr;
	ID3D10EffectVectorVariable* m_specularColorPtr;
	ID3D10EffectScalarVariable* m_specularPowerPtr;

	ID3D10EffectShaderResourceVariable* m_texturePtr;

	//Shadowing
	ID3D10EffectMatrixVariable* m_lightViewMatrixPtr, *m_lightProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_depthMapTexture;
	ID3D10EffectVectorVariable* m_lightPositionPtr;
};

#endif
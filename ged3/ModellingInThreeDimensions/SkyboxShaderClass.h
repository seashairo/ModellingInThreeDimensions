////////////////////////////////////////////////////////////////////////////////
// Filename: SkyboxShaderClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYBOX_H_
#define _SKYBOX_H_


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
class SkyboxShaderClass
{
public:

	SkyboxShaderClass();
	SkyboxShaderClass(const SkyboxShaderClass&);
	~SkyboxShaderClass();

	void Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount, D3DXMATRIX,D3DXMATRIX,D3DXMATRIX, ID3D10ShaderResourceView** textureArray);
	
private:
	void ShutdownShader();
private:

	//effects
	ID3D10Effect* m_effects;

	//techniques
	ID3D10EffectTechnique* m_techniques;

	//layout
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

};

#endif
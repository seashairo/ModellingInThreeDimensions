////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GLASS_H_
#define _GLASS_H_


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
class GlassShaderClass
{
public:


	GlassShaderClass();
	GlassShaderClass(const GlassShaderClass&);
	~GlassShaderClass();

	void Initialize(ID3D10Device*);
	void Shutdown();
	void RenderGlass(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
							  ID3D10ShaderResourceView** textures,ID3D10ShaderResourceView* refractionTexture, float refractionScale);
	
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

	//Glass
	ID3D10EffectScalarVariable* m_refractionScalePtr;
	ID3D10EffectShaderResourceVariable* m_refractionTexturePtr;
	ID3D10EffectVectorVariable* m_clipPlanePtr;
};

#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARALLAX_H_
#define _PARALLAX_H_


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
class ParallaxShaderClass
{
public:


	ParallaxShaderClass();
	ParallaxShaderClass(const ParallaxShaderClass&);
	~ParallaxShaderClass();

	void Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*, int , int , int , D3DXMATRIX , D3DXMATRIX , D3DXMATRIX ,  D3DXMATRIX , D3DXMATRIX,
							  ID3D10ShaderResourceView** , D3DXVECTOR3 , D3DXVECTOR4 , D3DXVECTOR4 , D3DXVECTOR3 ,
								D3DXVECTOR4 , float, D3DXVECTOR2,
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

	//Parallax
	ID3D10EffectMatrixVariable* m_parallaxWorldInverseTranspose;
    ID3D10EffectMatrixVariable* m_parallaxWorldViewProjection;
	ID3D10EffectVectorVariable* m_scalebias;

		//Shadowing
	ID3D10EffectMatrixVariable* m_lightViewMatrixPtr, *m_lightProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable* m_depthMapTexture;
	ID3D10EffectVectorVariable* m_lightPositionPtr;
};

#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
#include "Log.h"

//include shaders
#include "BasicShaderClass.h"
#include "BumpmapShaderClass.h"
#include "GlassShaderClass.h"
#include "SkyboxShaderClass.h"
#include "ParallaxShaderClass.h"
#include "TextureOnlyShaderClass.h"
#include "WaterShaderClass.h"
#include "TerrainShaderClass.h"
#include "FoliageShaderClass.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: Shader Manager Class
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	enum RenderEffect
	{
		EFFECT_TEXTURE_ONLY,
		EFFECT_BASIC,
		EFFECT_BUMPMAP,
		EFFECT_SKY,
		EFFECT_PARALLAX,
		EFFECT_GLASS,
		EFFECT_TERRAIN,
		EFFECT_WATER,
		EFFECT_FOLIAGE,
		NO_OF_EFFECTS,
	};

	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	void Initialize(ID3D10Device*);
	void Shutdown();

	BasicShaderClass* m_basicEffect;
	TextureOnlyShaderClass* m_textureOnlyEffect;
	TerrainShaderClass* m_terrainEffect;
	GlassShaderClass* m_glassEffect;
	BumpmapShaderClass* m_bumpEffect;
	ParallaxShaderClass* m_parallaxEffect;
	SkyboxShaderClass* m_skyboxEffect;
	WaterShaderClass* m_waterEffect;
	FoliageShaderClass* m_foliageEffect;

private:
	void ShutdownShader();
private:



};

#endif
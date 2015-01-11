#include "ShaderManager.h"


// Initialize the variables. Set all the pointers to 0 to initialize them.
ShaderManagerClass::ShaderManagerClass(){
}

ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other){
}

ShaderManagerClass::~ShaderManagerClass(){
}

// Initializes the light.fx shader file
void ShaderManagerClass::Initialize(ID3D10Device* device){

	m_basicEffect = new BasicShaderClass;
	m_basicEffect->Initialize(device);

	m_textureOnlyEffect = new TextureOnlyShaderClass;
	m_textureOnlyEffect->Initialize(device);

	m_bumpEffect = new BumpmapShaderClass;
	m_bumpEffect->Initialize(device);

	m_glassEffect = new GlassShaderClass;
	m_glassEffect->Initialize(device);

	m_skyboxEffect = new SkyboxShaderClass;
	m_skyboxEffect->Initialize(device);

	m_parallaxEffect = new ParallaxShaderClass;
	m_parallaxEffect->Initialize(device);

	m_waterEffect = new WaterShaderClass;
	m_waterEffect -> Initialize(device);

	m_terrainEffect = new TerrainShaderClass;
	m_terrainEffect -> Initialize(device);

	m_foliageEffect = new FoliageShaderClass;
	m_foliageEffect -> Initialize(device);
}

// Shutsdown the shader
void ShaderManagerClass::ShutdownShader(){
	m_basicEffect = 0;
	m_textureOnlyEffect = 0;
	m_bumpEffect = 0;
	m_glassEffect = 0;
	m_skyboxEffect = 0;
	m_parallaxEffect = 0;
	m_waterEffect = 0;
	m_terrainEffect = 0;
	m_foliageEffect = 0;
}

// Shutsdown the shader
void ShaderManagerClass::Shutdown(){
	ShutdownShader();
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "3DManagerClass.h"
#include "cameraclass.h"
#include "EntityClass.h"
#include "MeshClass.h"
#include "lightshaderclass.h"
#include "TextureShaderClass.h"
#include "TerrainShaderClass.h"
#include "lightclass.h"
#include "inputClass.h"
#include "ResourceManagerClass.h"
#include <vector>
#include <iostream>
#include "FrustumClass.h"
#include "OctreeSceneGraph.h"
#include "ShaderManager.h"
#include "CommonHeader.h"
#include "EntityPack.h"
#include "rendertextureclass.h"
#include "WaterShaderClass.h"
#include "RefractionShaderClass.h"
#include "ReflectionShaderClass.h"
#include "DeptShaderClass.h"

#include <unordered_map>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1500.0f;
const float SCREEN_NEAR = 0.5f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass(InputClass* input);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float, int);
	bool Render();

	void RenderRefractionToTexture();
	void RenderReflectionToTexture();
	void RenderToTexture();
	void RenderDepthToTexture();

	void CameraInput();
	void LightInput();
	void OtherInput();
	void ControlInput();
	void PlayerInput(EntityClass*);
	void PlayerInputPack();
	CameraClass* m_Camera;

	void BuildRay(int, int, D3DXVECTOR3&, D3DXVECTOR3&);
	void Pick(D3DXVECTOR3, D3DXVECTOR3);
	bool RaySphereIntersect(D3DXVECTOR3, D3DXVECTOR3, float);
	void MoveTo(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, float);

	void BuildScene();
	void LoadTextures();
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	void ShutdownHeightMap();
	void CreateMeshes();
	void WaterMovement();

	struct position
	{
		float x;
		float y;
		float z;
	};

	position GetCameraPosition();
	position GetEntityPosition(int index);

	void CreateSceneOne();
	void CreateSceneTwo();
	void CreateSceneThree();
	void CreateSceneFour();
	void CreateSceneFive();
	void CreateSceneSix();
	void CreateSceneSeven();

	bool CheckUnderwater();

	ResourceManagerClass* m_manager;
	void Loading(int);

	bool soundChecking;
	bool soundFlags[5];private:
	void SpawnBubble();

private:
	D3DClass* m_D3D;
	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;
	TerrainShaderClass* m_TerrainShader;
	ReflectionShaderClass* m_ReflectionShader;
	RefractionShaderClass* m_RefractionShader;
	WaterShaderClass* m_WaterShader;
	DepthShaderClass* m_DepthShader;
	LightClass* m_Light;
	InputClass* m_Input;
	RenderTextureClass* m_RenderTexture, *m_RefractionTexture, *m_ReflectionTexture, *m_ShadowTexture;
	MeshClass* m_mesh;
	EntityPack* m_controlledEntities;
	EntityPack* m_controlGroups[3];
	EntityClass* m_skybox;

	//ResourceManagerClass* m_manager;
	ShaderManagerClass* m_shaderManager;
	FrustumClass* m_Frustum;
	OctreeSceneGraph* m_SceneGraph;

	float m_waterHeight, m_waterTranslation;

	int m_screenWidth;
	int m_screenHeight;
	int m_terrainWidth;
	int m_terrainHeight;
	unsigned char* bitmapImage;

	D3DXVECTOR3 m_cornerOne; // Close bottom left
	D3DXVECTOR3 m_cornerTwo; // Far top right

	//Light attributes
	D3DXVECTOR3 m_lightPos;
	D3DXVECTOR3 m_lookAt;
	void UpdateLight();

	bool m_sceneOne;
};

#endif
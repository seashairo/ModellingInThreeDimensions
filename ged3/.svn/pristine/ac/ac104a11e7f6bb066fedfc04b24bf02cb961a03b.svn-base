////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "InputClass.h"
#include <dos.h>

#include <functional>

GraphicsClass::GraphicsClass(InputClass* input)
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_TextureShader = 0;
	m_RenderTexture = 0;
	m_RefractionShader = 0;
	m_TerrainShader = 0;
	m_WaterShader = 0;
	m_ReflectionShader = 0;
	m_RefractionShader = 0;
	m_Light = 0;
	m_Input = input;
	m_manager = 0;
	m_shaderManager = 0;
	m_mesh = 0;
	m_Frustum = 0;
	m_SceneGraph = 0;
	m_terrainWidth = 0;
	m_terrainHeight = 0;
	m_controlledEntities = 0;
	m_controlGroups[0] = 0; m_controlGroups[1] = 0; m_controlGroups[2] = 0;
	bitmapImage = 0;
	for(int i = 0; i < 5; i++){
		soundFlags[i] = false;
	}
	soundChecking = false;
	m_sceneOne = false;

	m_cornerOne = D3DXVECTOR3(0, 0, 0);
	m_cornerTwo = D3DXVECTOR3(0, 0, 0);
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}
	Log::COut("Created D3DClass.");

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	Log::COut("Initialized D3DClass.");

	// Create the camera object.
	Log::COut("Created CameraClass.");
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetRotation(10, 45, 0);
	m_Camera->SetPosition(-20, 45, -20);
	Log::COut("Set initial camera position to: (" + 
		std::to_string(-20) + ", " + 
		std::to_string(45) + ", " +
		std::to_string(-20) + ")");

	m_manager = new ResourceManagerClass;
	result = m_manager->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the resource manager.", L"Error", MB_OK);
		return false;
	}

	m_TextureShader = new TextureShaderClass;
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader.", L"Error", MB_OK);
		return false;
	}
	Log::COut("Initialized TextureShaderClass.");

	m_manager->AddTexture("loading01", m_D3D->GetDevice(), L"../ModellingInThreeDimensions/data/loading/loading1b.png", 
		L"../ModellingInThreeDimensions/data/bump00.dds", L"../ModellingInThreeDimensions/data/spec00.dds");
	m_manager->AddTexture2D("loading01", m_D3D->GetDevice(), m_manager->GetTexture("loading01"), m_screenWidth, m_screenHeight, 800, 600);
	m_manager->AddTexture("loading02", m_D3D->GetDevice(), L"../ModellingInThreeDimensions/data/loading/loading2b.png", 
		L"../ModellingInThreeDimensions/data/bump00.dds", L"../ModellingInThreeDimensions/data/spec00.dds");
	m_manager->AddTexture2D("loading02", m_D3D->GetDevice(), m_manager->GetTexture("loading02"), m_screenWidth, m_screenHeight, 800, 600);
	m_manager->AddTexture("loading03", m_D3D->GetDevice(), L"../ModellingInThreeDimensions/data/loading/loading3b.png", 
		L"../ModellingInThreeDimensions/data/bump00.dds", L"../ModellingInThreeDimensions/data/spec00.dds");
	m_manager->AddTexture2D("loading03", m_D3D->GetDevice(), m_manager->GetTexture("loading03"), m_screenWidth, m_screenHeight, 800, 600);
	m_manager->AddTexture("loading04", m_D3D->GetDevice(), L"../ModellingInThreeDimensions/data/loading/loading4b.png", 
		L"../ModellingInThreeDimensions/data/bump00.dds", L"../ModellingInThreeDimensions/data/spec00.dds");
	m_manager->AddTexture2D("loading04", m_D3D->GetDevice(), m_manager->GetTexture("loading04"), m_screenWidth, m_screenHeight, 800, 600);
	m_manager->AddTexture("loading05", m_D3D->GetDevice(), L"../ModellingInThreeDimensions/data/loading/loading5b.png", 
		L"../ModellingInThreeDimensions/data/bump00.dds", L"../ModellingInThreeDimensions/data/spec00.dds");
	m_manager->AddTexture2D("loading05", m_D3D->GetDevice(), m_manager->GetTexture("loading05"), m_screenWidth, m_screenHeight, 800, 600);
	Loading(1);


	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Terrain shader object.", L"Error", MB_OK);
		return false;
	}
	Log::COut("Initialized TerrainShaderClass.");

	m_WaterShader = new WaterShaderClass;
	if(!m_WaterShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_WaterShader->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Water shader object.", L"Error", MB_OK);
		return false;
	}
	Log::COut("Initialized WaterShaderClass.");

	m_RefractionShader = new RefractionShaderClass;
	if(!m_WaterShader)
	{
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}
	Log::COut("Initialized Render Texture Class.");


	//create shader manager
	m_shaderManager = new ShaderManagerClass;
	m_shaderManager->Initialize(m_D3D->GetDevice());

	// Initialize the texture shader.
	m_TextureShader = new TextureShaderClass;
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader.", L"Error", MB_OK);
		return false;
	}
	Log::COut("Initialized TextureShaderClass.");

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if(!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if(!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection shader object.
	m_ReflectionShader = new ReflectionShaderClass;
	if(!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	m_DepthShader = new DepthShaderClass;
	result = m_DepthShader->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}
	Loading(2);
	m_ShadowTexture = new RenderTextureClass;
	// Initialize the shadow render to texture object.
	result = m_ShadowTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	Log::COut("Light Source Created");

	if(!m_Light)
	{
		return false;
	}
	Log::COut("Created LightClass.");

	// Initialize the light direction.
	//m_Light->SetLightDirection(0.0f, 0.0f, 1.0f);

	// Initialize the ambient and diffuse light color.
	m_Light->SetAmbientColor(0.2f, 0.2f, 0.2f, 0.2f);
	m_Light->SetDiffuseColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Initialize the specular color and power.
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);
	
	m_lightPos = D3DXVECTOR3(0,20, 0);
	m_lookAt = D3DXVECTOR3(45, 0, 45);

	UpdateLight();
	// Create the resource manager.
	

	//Create the OctreeSceneGraph
	m_SceneGraph = new OctreeSceneGraph;
	m_SceneGraph->rootNode = m_SceneGraph->BuildOctree(NULL, D3DXVECTOR3(0, 0, 0), 5000.0f, 3);
	if(m_SceneGraph->rootNode == NULL) {
		MessageBox(hwnd, L"Could not initialize the scene graph.", L"Error", MB_OK);
		return false;
	}

	m_controlledEntities = new EntityPack;
	m_controlledEntities->Initialize();

	for(int i = 0; i < 3; i++){
		m_controlGroups[i] = new EntityPack;
		m_controlGroups[i]->Initialize();
	}
	//Set the height of the water.
	m_waterHeight = 2.75f;

	//Initialize the position of the water.
	m_waterTranslation = 0.0f;
	Loading(2);

	BuildScene();

	m_controlledEntities->SetFormation(EntityPack::Formations::NONE);

	return true;
}

void GraphicsClass::Shutdown()
{
	if(m_controlledEntities){
		m_controlledEntities->Shutdown();
		delete m_controlledEntities;
		m_controlledEntities = 0;
	}

	// Release the water shader object.
	if(m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the texture shader.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the refraction shader object.
	if(m_RefractionShader)
	{
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	// Release the reflection shader object.
	if(m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the reflection render to texture object.
	if(m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if(m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}


	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the light shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	int i=0;
	return;
}

void GraphicsClass::BuildScene(){
	LoadTextures();
	Loading(3);
	CreateMeshes();

	// Moved stuff from here to CreateSceneOne so we can set up different things via button press
	// (a Phil suggestion)
	CreateSceneOne();
}

// Add textures to be used into the resource manager
// Each instance includes the main texture, bump normal map and specular map
void GraphicsClass::LoadTextures(){
	ID3D10Device* device = m_D3D->GetDevice();
	WCHAR* spec00 = L"../ModellingInThreeDimensions/data/spec00.dds";
	WCHAR* bump00 = L"../ModellingInThreeDimensions/data/bump00.dds";

	m_manager->AddTexture("rock", device,
		L"../ModellingInThreeDimensions/data/rock/rock_diffuse.dds", 
		L"../ModellingInThreeDimensions/data/rock/rock_bump.dds",
		L"../ModellingInThreeDimensions/data/rock/rock_height.dds");

	m_manager->AddTexture("bridge", device,
	L"../ModellingInThreeDimensions/data/New Models/bridge.jpg", 
	L"../ModellingInThreeDimensions/data/New Models/bridge_normal.jpg",
	L"../ModellingInThreeDimensions/data/New Models/bridge_spec.jpg");

	m_manager->AddTexture("killerWhale", device,
	L"../ModellingInThreeDimensions/data/New Models/Killer_Whale_D.jpg", 
	L"../ModellingInThreeDimensions/data/New Models/Killer_Whale_N.jpg",
	L"../ModellingInThreeDimensions/data/New Models/Killer_Whale_D_DISP.jpg");

	m_manager->AddTexture("orca", device,
	L"../ModellingInThreeDimensions/data/New Models/ORCA.jpg");

		m_manager->AddTexture("shark", device,
	L"../ModellingInThreeDimensions/data/New Models/TGRSHARK.jpg");

	m_manager->AddTexture("rock1", device,
	L"../ModellingInThreeDimensions/data/New Models/Rock1_D.jpg", 
	L"../ModellingInThreeDimensions/data/New Models/Rock1_D_NRM.jpg",
	L"../ModellingInThreeDimensions/data/New Models/Rock1_D_OCC.jpg");

	m_manager->AddTexture("rockWall", device,
		L"../ModellingInThreeDimensions/data/rockWall/rockwall_diffuse.dds", 
		L"../ModellingInThreeDimensions/data/rockWall/rockwall_bump.dds",
		L"../ModellingInThreeDimensions/data/rockWall/rockwall_height.dds");

	m_manager->AddTexture("stone", device, 
		L"../ModellingInThreeDimensions/data/stone01.dds", 
		L"../ModellingInThreeDimensions/data/bump01.dds", 
		L"../ModellingInThreeDimensions/data/spec01.dds");

	m_manager->AddTexture("russel", device, L"../ModellingInThreeDimensions/data/rk.dds", bump00, spec00);
	m_manager->AddTexture("seafloor", device, L"../ModellingInThreeDimensions/data/seafloor.dds", bump00, spec00);
	m_manager->AddTexture("tinyskin", device, L"../ModellingInThreeDimensions/data/Tiny_skin.png", bump00, spec00);
	m_manager->AddTexture("cityBase", device, L"../ModellingInThreeDimensions/data/cityBase.bmp", bump00, spec00);
	m_manager->AddTexture("blueCar", device, L"../ModellingInThreeDimensions/data/redCar.bmp", bump00, spec00);
	m_manager->AddTexture("redCar", device, L"../ModellingInThreeDimensions/data/blueCar.bmp", bump00, spec00);
	m_manager->AddTexture("rainbowCar", device, L"../ModellingInThreeDimensions/data/rainbowCar.bmp", bump00, spec00);
	m_manager->AddTexture("dickyCar", device, L"../ModellingInThreeDimensions/data/dickyCar.bmp", bump00, spec00);
	m_manager->AddTexture("purpleCar", device, L"../ModellingInThreeDimensions/data/purpleCar.bmp", bump00, spec00);
	m_manager->AddTexture("greenSkyscraper", device, L"../ModellingInThreeDimensions/data/skyscraper.bmp", bump00, spec00);
	m_manager->AddTexture("mouse", device, L"../ModellingInThreeDimensions/data/mouse.dds", bump00, spec00);
	m_manager->AddTexture("waterOverlay", device, L"../ModellingInThreeDimensions/data/waterOverlay.png", bump00, spec00);
	m_manager->AddTexture("test", device, L"../ModellingInThreeDimensions/data/test.dds", bump00, spec00);
	m_manager->AddTexture("foliage", device, L"../ModellingInThreeDimensions/data/foliage/grass.dds", bump00, spec00);
	m_manager->AddTexture("datgrass", device, L"../ModellingInThreeDimensions/data/terrain/grass.dds", bump00, spec00);
	m_manager->AddTexture("datslope", device, L"../ModellingInThreeDimensions/data/terrain/slope.dds", bump00, spec00);
	m_manager->AddTexture("datrock", device, L"../ModellingInThreeDimensions/data/terrain/rock.dds", bump00, spec00);
	m_manager->AddTexture("tutorialF2", device, L"../ModellingInThreeDimensions/data/tutorialF2.png", bump00, spec00);
	m_manager->AddTexture("tutorialF3", device, L"../ModellingInThreeDimensions/data/tutorialF3.png", bump00, spec00);
	m_manager->AddTexture("tutorialF4", device, L"../ModellingInThreeDimensions/data/tutorialF4.png", bump00, spec00);
	m_manager->AddTexture("tutorialF6", device, L"../ModellingInThreeDimensions/data/tutorialF6.png", bump00, spec00);
	m_manager->AddTexture("rainbow", device, L"../ModellingInThreeDimensions/data/rainbow.png", bump00, spec00);

	m_manager->AddTexture("water01", device, L"../ModellingInThreeDimensions/data/water/water01.dds", 
		L"../ModellingInThreeDimensions/data/glass/bump03.dds", spec00);

	m_manager->AddTexture("parallax", device, L"../ModellingInThreeDimensions/data/stoneTexture.jpg", 
		L"../ModellingInThreeDimensions/data/stoneNormalMap.jpg",
		L"../ModellingInThreeDimensions/data/stoneHeightMap.jpg");

	m_manager->AddTexture("four", device, L"../ModellingInThreeDimensions/data/four/wood.jpg", 
		L"../ModellingInThreeDimensions/data/four/four_NM_height.jpg",
				L"../ModellingInThreeDimensions/data/four/four_NM_height.jpg");

	m_manager->AddTexture("rock2", device, L"../ModellingInThreeDimensions/data/rock2/shaders_offest_diffuse.jpg", 
		L"../ModellingInThreeDimensions/data/rock2/shaders_offest_normalmap.jpg",
				L"../ModellingInThreeDimensions/data/rock2/shaders_offest_heightmap.jpg");

	m_manager->AddTexture("sand", device, L"../ModellingInThreeDimensions/data/SandDusty/SandDusty_diff.dds", 
	L"../ModellingInThreeDimensions/data/SandDusty/SandDusty_ddn.dds",
			L"../ModellingInThreeDimensions/data/SandDusty/SandDusty_displacement.dds");

	m_manager->AddTexture("glass", device, L"../ModellingInThreeDimensions/data/glass/glass01.dds", 
				L"../ModellingInThreeDimensions/data/glass/bump03.dds");

	//sky texture
	m_manager->AddCubemapTexture("sky", device, L"../ModellingInThreeDimensions/data/sky/beachSky.dds");

	// Texture2Ds
	m_manager->AddTexture2D("mouse", device, m_manager->GetTexture("mouse"), 
		m_screenWidth, m_screenHeight, 32, 32);
	m_manager->AddTexture2D("waterOverlay", device, m_manager->GetTexture("waterOverlay"), 
		m_screenWidth, m_screenHeight, 1024, 1024);

	m_manager->AddTexture("salmon", device, L"../ModellingInThreeDimensions/data/Fish/SalmonFish.jpg");
}

// Add all the meshes you want into the resource manager
void GraphicsClass::CreateMeshes(){
	#pragma region Testing custom mesh
	VertexHeader::VertexType* t_vertices = new VertexHeader::VertexType[4];
	unsigned long* t_indices = new unsigned long[6];
	int t_vCount = 4;
	int t_iCount = 6;

	t_vertices[0].position = D3DXVECTOR3( 1.0f, -1.0f, 0.0f); // top left
	t_vertices[1].position = D3DXVECTOR3( 1.0f,  1.0f, 0.0f); // top right
	t_vertices[2].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); // bottom left
	t_vertices[3].position = D3DXVECTOR3(-1.0f,  1.0f, 0.0f); // bottom right

	// Set the texture coordinates
	t_vertices[0].texture = D3DXVECTOR2(0, 0);// top left
	t_vertices[1].texture = D3DXVECTOR2(1, 0);// top right
	t_vertices[2].texture = D3DXVECTOR2(0, 1);// bottom left
	t_vertices[3].texture = D3DXVECTOR2(1, 1);// bottom right

	// Set the normals for the vertices.
	for(int i = 0; i < t_vCount; i++){
		t_vertices[i].normal = D3DXVECTOR3(t_vertices[i].position.x,
			t_vertices[i].position.y, t_vertices[i].position.z);
	}

	// Set the indices
	t_indices[0] = 0;	t_indices[1] = 1;	t_indices[2] = 2;
	t_indices[3] = 1;	t_indices[4] = 3;	t_indices[5] = 2;
	m_manager->AddMesh("cust_1");
	m_manager->GetMesh("cust_1")->AddCustom(t_vertices, t_indices, t_vCount, t_iCount);
	#pragma endregion
	//Add terrain to m_manager
	LoadHeightMap("../ModellingInThreeDimensions/data/terrain/heightmap03_shallow.bmp");
	m_manager->AddMesh("terrain");
	m_manager->GetMesh("terrain")->AddTerrain(m_terrainWidth, m_terrainHeight, bitmapImage, 7.5f);
	Loading(4);
	m_manager->AddMesh("terrain2");
	m_manager->GetMesh("terrain2")->AddExternalTransformedMesh(*(m_manager->GetMesh("terrain")), 0, 0, 0, 0.353, 0.4, 0.212, 0, 0, 0);

	LoadHeightMap("../ModellingInThreeDimensions/data/terrain/heightmap01.bmp");
	m_manager->AddMesh("terrain3");
	m_manager->GetMesh("terrain3")->AddTerrain(m_terrainWidth, m_terrainHeight, bitmapImage, 1);

	m_manager->AddMesh("water");
	m_manager->GetMesh("water")->AddWater(255);

	m_manager->AddMesh("Seaweed");
	m_manager->GetMesh("Seaweed")->AddPlane();

	m_manager->AddMesh("sphere");
	m_manager->GetMesh("sphere")->AddSphere(50,50,0,0,0,3,3,3,0,0,0);

	m_manager->AddMesh("cube");

	m_manager->GetMesh("cube")->AddCube(1, 0, 0, 0, 1, 1, 1, 0, 0, 0);

	m_manager->AddMesh("sky");
	m_manager->GetMesh("sky")->AddSkybox();

	m_manager->AddMesh("ground");
	m_manager->GetMesh("ground")->AddPlane();
	m_manager->GetMesh("ground")->ScaleMesh(50, 50, 50);
	//m_manager->GetMesh("ground")->CalculateModelVectors();

	m_manager->AddMesh("tutMesh");
	m_manager->GetMesh("tutMesh")->AddPlane();
	m_manager->GetMesh("tutMesh")->ScaleMesh(32, 24, 1);
	m_manager->GetMesh("tutMesh")->RotateMesh(90, 0, 0);

	m_manager->AddMesh("ground1");
	m_manager->GetMesh("ground1")->AddPlane();
	m_manager->GetMesh("ground1")->ScaleMesh(127.5, 20, 1);
	//m_manager->GetMesh("ground1")->CalculateModelVectors();

	m_manager->AddMesh("star");
	m_manager->GetMesh("star")->AddCube(2, 0, 0, 0, 1, 1, 1, 0, 0, 0);
	m_manager->GetMesh("star")->AddCube(1, 45, 45, 45, 1, 1, 1, 2.5, 0, 2.5);
	m_manager->GetMesh("star")->AddCube(1, 45, 45, 45, 1, 1, 1, -2.5, 0, -2.5);
	m_manager->GetMesh("star")->AddCube(1, 45, 45, 45, 1, 1, 1, -2.5, 0, 2.5);
	m_manager->GetMesh("star")->AddCube(1, 45, 45, 45, 1, 1, 1, 2.5, 0, -2.5);

	m_manager->AddMesh("sphere_test");
	m_manager->GetMesh("sphere_test")->AddSphere(5, 5);

	m_manager->AddMesh("car");
	m_manager->GetMesh("car")->AddCuboid(4, 1, 2);
	m_manager->GetMesh("car")->AddCuboid(2, 1.5, 2, 0, 0, 0, 1.2, 0.6, 1, -0.1, 1, 0);
	m_manager->GetMesh("car")->AddSphere(8, 8, 0, 0, 0, 0.6, 0.6, 0.6, -2, -0.75, -1);
	m_manager->GetMesh("car")->AddSphere(8, 8, 0, 0, 0, 0.6, 0.6, 0.6, -2, -0.75, 1);
	m_manager->GetMesh("car")->AddSphere(8, 8, 0, 0, 0, 0.6, 0.6, 0.6, 2, -0.75, -1);
	m_manager->GetMesh("car")->AddSphere(8, 8, 0, 0, 0, 0.6, 0.6, 0.6, 2, -0.75, 1);
	m_manager->GetMesh("car")->ScaleMesh(12, 12, 12);

	int index = m_manager->AddMesh("cube2");
	m_manager->GetMesh("cube2")->AddCube(1);

	index = m_manager->AddMesh("cube3");
	m_manager->GetMesh("cube3")->AddCube(2);
	m_manager->GetMesh("cube3")->AddCube(1, 0, 0, 0, 1, 1, 1, 0, 0, 1.5);

	m_manager->AddMesh("salmon");
	m_manager->GetMesh("salmon")->AddModel("../ModellingInThreeDimensions/data/Fish/SALMON.obj");
	m_manager->GetMesh("salmon")->ScaleMesh(10, 10, 10);

	m_manager->AddMesh("bridge");
	m_manager->GetMesh("bridge")->AddModel("../ModellingInThreeDimensions/data/New Models/bridge.obj");

	m_manager->AddMesh("rock1");
	m_manager->GetMesh("rock1")->AddModel("../ModellingInThreeDimensions/data/New Models/Rock1.obj");

	m_manager->AddMesh("shark");
	m_manager->GetMesh("shark")->AddModel("../ModellingInThreeDimensions/data/New Models/TGRSHARK.obj");

	m_manager->AddMesh("killerWhale");
	m_manager->GetMesh("killerWhale")->AddModel("../ModellingInThreeDimensions/data/New Models/Killer_Whale.obj");

	m_manager->AddMesh("orca");
	m_manager->GetMesh("orca")->AddModel("../ModellingInThreeDimensions/data/New Models/ORCA.obj");

	m_manager->AddMesh("roof");
	m_manager->GetMesh("roof")->AddPyramid();


	index = m_manager->AddMesh("wallCube");
	m_manager->GetMesh("wallCube")->AddCube(0.5);

	index = m_manager->AddMesh("tank");
	m_manager->GetMesh("tank")->AddPlane(0, 0, 0, 2, 1, 1, 0, 0, -1.2); // Close wall
	m_manager->GetMesh("tank")->AddPlane(0, 180, 0, 2, 1, 1, 0, 0, 1.2); // Far wall
	m_manager->GetMesh("tank")->AddPlane(0, 270, 0, 1.2, 1, 1, 2, 0, 0); // Right wall
	m_manager->GetMesh("tank")->AddPlane(0, 90, 0, 1.2, 1, 1, -2, 0, 0); // Left wall

	index = m_manager->AddMesh("tank2");
	m_manager->GetMesh("tank2")->AddPlane(0, 180, 0, 2, 1, 1, 0, 0, -1.2); // Close wall
	m_manager->GetMesh("tank2")->AddPlane(0, 0, 0, 2, 1, 1, 0, 0, 1.2); // Far wall
	m_manager->GetMesh("tank2")->AddPlane(0, 90, 0, 1.2, 1, 1, 2, 0, 0); // Right wall
	m_manager->GetMesh("tank2")->AddPlane(0, 270, 0, 1.2, 1, 1, -2, 0, 0); // Left wall
	m_manager->GetMesh("tank")->AddExternalTransformedMesh(*(m_manager->GetMesh("tank2")), 0, 0, 0, 0.9, 1, 0.9, 0, 0, 0);
	m_manager->GetMesh("tank")->AddPlane(90, 0, 0, 0.1, 1.2, 1, -1.9, 1, 0); // Top left
	m_manager->GetMesh("tank")->AddPlane(90, 0, 0, 0.1, 1.2, 1, 1.9, 1, 0); // Top right
	m_manager->GetMesh("tank")->AddPlane(90, 90, 0, 0.1, 2, 1, 0, 1, -1.1); // Top close
	m_manager->GetMesh("tank")->AddPlane(90, 90, 0, 0.1, 2, 1, 0, 1, 1.1); // Top far
	m_manager->GetMesh("tank")->AddPlane(270, 0, 0, 2, 1.2, 1, 0, -1, 0); // Bottom facing down
	m_manager->GetMesh("tank")->AddPlane(90, 0, 0, 2, 1.2, 1, 0, -1, 0); // Bottom facing up
	Loading(5);

	m_manager->FinaliseMeshes(m_D3D->GetDevice());
}

bool GraphicsClass::LoadHeightMap(char* filename)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	
	//Begin by opening the file and then read it into a unsigned char array. Close the file after we are finished reading the data from it.

	// Open the height map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Save the dimensions of the terrain.
	m_terrainWidth = bitmapInfoHeader.biWidth;
	m_terrainHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = m_terrainWidth * m_terrainHeight * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}
}

bool GraphicsClass::Frame(float time, int fps)
{
	bool result;

	CameraInput();
	OtherInput();

	//Update the scene graph to check for moving entities.
	m_SceneGraph->UpdateOctree(m_SceneGraph->rootNode);

	if(m_manager->GetEntityCount() == 0) return true;

	SpawnBubble();

	RenderToTexture();
	RenderRefractionToTexture();
	RenderDepthToTexture();
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::RenderToTexture()
{
	ID3D10Device* device = m_D3D->GetDevice();
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,lightViewMatrix, lightProjectionMatrix;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

		//Shadow
	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	m_D3D->DisableZBuffer();
	m_skybox->Render(device);
	D3DXVECTOR3 camPos = m_Camera->GetPosition();
	D3DXMatrixTranslation(&worldMatrix, camPos.x, camPos.y, camPos.z);
	m_shaderManager->m_skyboxEffect->Render(device, m_skybox->GetIndexCount(), m_skybox->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, m_skybox->GetTextureArray());
	m_D3D->EnableZBuffer();

	for (int i = 0; i < m_manager->GetEntityCount(); i++){
		m_D3D->GetWorldMatrix(worldMatrix);
			//// Get the entity we want to render.
		EntityClass* entity = m_manager->GetEntity(i);

		//// Apply transformations.
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &entity->GetTransformMatrix());
				//Supporting Matrices
		D3DXMATRIX pvm ;
		D3DXMatrixMultiply(&pvm, &projectionMatrix, &viewMatrix);
		D3DXMatrixMultiply(&pvm, &worldMatrix, &pvm);
		D3DXMATRIX worldInverseTranspose;
		D3DXMatrixInverse(&worldInverseTranspose, 0, &worldMatrix);
		D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);

		//// Render entity.
		entity->Render(m_D3D->GetDevice());

		switch (entity->GetEffect())
		{
			case ShaderManagerClass::EFFECT_BASIC:
				m_shaderManager->m_basicEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_TEXTURE_ONLY:
				m_shaderManager->m_textureOnlyEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_BUMPMAP:
				m_shaderManager->m_bumpEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_PARALLAX:
				m_shaderManager->m_parallaxEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix,  worldInverseTranspose, pvm, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), D3DXVECTOR2(0.04,-0.03),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_FOLIAGE:
				m_shaderManager->m_foliageEffect->Render(device, entity->GetVertexCount(), 0, viewMatrix, projectionMatrix, entity->GetTextureArray()[0]);	 
					break;
			case ShaderManagerClass::EFFECT_TERRAIN:
				m_shaderManager->m_terrainEffect->Render(device, entity->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_manager->GetTexture("datgrass")->GetTextureArray()[0], m_manager->GetTexture("datslope")->GetTextureArray()[0], m_manager->GetTexture("datrock")->GetTextureArray()[0], 
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition(), m_Camera->GetPosition());
				break;

		}
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return;
}

bool GraphicsClass::Render()
{
	D3DXVECTOR4 clipPlane;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, reflectionMatrix,lightViewMatrix, lightProjectionMatrix;
	ID3D10Device* device = m_D3D->GetDevice();
	WaterMovement();

	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	//Shadow
	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	////terrain shader render
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionMatrix);
	//// Get the entity we want to render.

	// Skybox ---- This will render UNDER everything else so its always behind the depth buffer
	m_D3D->DisableZBuffer();
	m_skybox->Render(device);
	D3DXVECTOR3 camPos = m_Camera->GetPosition();
	D3DXMatrixTranslation(&worldMatrix, camPos.x, camPos.y, camPos.z);
	m_shaderManager->m_skyboxEffect->Render(device, m_skybox->GetIndexCount(), m_skybox->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, m_skybox->GetTextureArray());
	m_D3D->EnableZBuffer();
	// Skybox
	
	// Iterates through all entities and renders them with the lightshader.
	PlayerInputPack();
	for (int i = 0; i < m_manager->GetEntityCount(); i++){
		//each object has its own world
		m_D3D->GetWorldMatrix(worldMatrix);

		// Get the entity we want to render.
		EntityClass* entity = m_manager->GetEntity(i);

		// Update entity & bind 
		entity->Render(device);

		// Apply transformations.
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &entity->GetTransformMatrix());
		//Supporting Matrices
		D3DXMATRIX pvm ;
		pvm = viewMatrix * projectionMatrix;

		D3DXMATRIX worldInverseTranspose;
		D3DXMatrixInverse(&worldInverseTranspose, 0, &worldMatrix);
		D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);

		switch (entity->GetEffect())
		{
			case ShaderManagerClass::EFFECT_BASIC:
				m_shaderManager->m_basicEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_TEXTURE_ONLY:
				m_shaderManager->m_textureOnlyEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_BUMPMAP:
				m_shaderManager->m_bumpEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_PARALLAX:
				m_shaderManager->m_parallaxEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix,  worldInverseTranspose, pvm, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), D3DXVECTOR2(0.04,-0.03),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_GLASS:
				m_shaderManager->m_glassEffect->RenderGlass(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_RenderTexture->GetShaderResourceView(), 0.01f);
				break;
			case ShaderManagerClass::EFFECT_WATER:
				m_shaderManager->m_waterEffect->Render(device, entity->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, 
					m_RenderTexture->GetShaderResourceView(), m_RefractionTexture->GetShaderResourceView(), 
					entity->GetTextureArray()[0], m_Camera->GetPosition(), D3DXVECTOR2(0.01f,0.02f),m_waterTranslation, 0.03f, D3DXVECTOR4(0.0f, 0.8f, 1.0f, 1.0f), m_Light->GetLightDirection(), 200.0f,
					m_manager->GetTexture("sky")->GetTextureArray()[0]);
				break;
			case ShaderManagerClass::EFFECT_TERRAIN:
				m_shaderManager->m_terrainEffect->Render(device, entity->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_manager->GetTexture("datgrass")->GetTextureArray()[0], m_manager->GetTexture("datslope")->GetTextureArray()[0], m_manager->GetTexture("datrock")->GetTextureArray()[0], 
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition(), m_Camera->GetPosition());
				break;
		   case ShaderManagerClass::EFFECT_FOLIAGE:
			m_shaderManager->m_foliageEffect->Render(device, entity->GetVertexCount(), 0, viewMatrix, projectionMatrix, entity->GetTextureArray()[0]);	 
				break;
		}
			
	}

	// Process dummy entities for movement
	for (int i = 0; i < m_manager->GetDummyCount(); i++){
		EntityClass* dummy = m_manager->GetDummy(i);
		dummy->Render(device);
		if(dummy->GetAI()->GetBehaviour() == 0) m_manager->RemoveDummy(*dummy);
	}

	// Draw 2D things over other things. DON'T PUT ANYTHING AFTER THIS EXCEPT FOR THE ENDSCENE() CALL!
	worldMatrix = m_Camera->GetWorldMatrix();
	m_D3D->DisableZBuffer();
	m_D3D->EnableAlphaBlending();
	Texture2D* tex = m_manager->GetTexture2D("mouse");
	tex->Render(device, m_Input->GetMousePosition().x, m_Input->GetMousePosition().y);
	m_TextureShader->Render(device, tex->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, tex->GetTexture());
	if(CheckUnderwater()){
		tex = m_manager->GetTexture2D("waterOverlay");
		tex->Render(device, 0, 0);
		m_TextureShader->Render(device, tex->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, tex->GetTexture());
	}
	m_D3D->DisableAlphaBlending();
	m_D3D->EnableZBuffer();

	m_D3D->EndScene();

	return true;
}

void GraphicsClass::RenderRefractionToTexture()
{
	D3DXVECTOR4 clipPlane;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,lightViewMatrix, lightProjectionMatrix;
	ID3D10Device* device = m_D3D->GetDevice();
	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
		
	//Shadow
	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	PlayerInputPack();
	for (int i = 0; i < m_manager->GetEntityCount(); i++){
		//each object has its own world
		m_D3D->GetWorldMatrix(worldMatrix);

		// Get the entity we want to render.
		EntityClass* entity = m_manager->GetEntity(i);

		// Apply transformations.
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &entity->GetTransformMatrix());
		//Supporting Matrices
		D3DXMATRIX pvm ;
		pvm = worldMatrix * viewMatrix * projectionMatrix;

		D3DXMATRIX worldInverseTranspose;
		D3DXMatrixInverse(&worldInverseTranspose, 0, &worldMatrix);
		D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);

		// Render entity.
		entity->Render(m_D3D->GetDevice());
	
		switch (entity->GetEffect())
		{
			case ShaderManagerClass::EFFECT_BASIC:
				m_shaderManager->m_basicEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_TEXTURE_ONLY:
				m_shaderManager->m_textureOnlyEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_BUMPMAP:
				m_shaderManager->m_bumpEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_PARALLAX:
				m_shaderManager->m_parallaxEffect->Render(device, entity->GetIndexCount(), entity->GetVertexCount(), 1, 
					worldMatrix, viewMatrix, projectionMatrix,  worldInverseTranspose, pvm, entity->GetTextureArray(),
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), D3DXVECTOR2(0.04,-0.03),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition()
					);
				break;
			case ShaderManagerClass::EFFECT_TERRAIN:
				m_shaderManager->m_terrainEffect->Render(device, entity->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_manager->GetTexture("datgrass")->GetTextureArray()[0], m_manager->GetTexture("datslope")->GetTextureArray()[0], m_manager->GetTexture("datrock")->GetTextureArray()[0], 
					m_Light->GetLightDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					//Shadow
					lightViewMatrix, lightProjectionMatrix,  m_ShadowTexture->GetShaderResourceView(),m_Light->GetPosition(), m_Camera->GetPosition());
				break;
		   case ShaderManagerClass::EFFECT_FOLIAGE:
			m_shaderManager->m_foliageEffect->Render(device, entity->GetVertexCount(), 0, viewMatrix, projectionMatrix, entity->GetTextureArray()[0]);	 
				break;
		}
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return;
}

void GraphicsClass::RenderDepthToTexture()
{
	ID3D10Device* device = m_D3D->GetDevice();
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix,lightViewMatrix, lightProjectionMatrix,reflectionMatrix;

	// Set the render target to be the render to texture.
	m_ShadowTexture->SetRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView());

	// Clear the render to texture.
	m_ShadowTexture->ClearRenderTarget(m_D3D->GetDevice(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

		// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	for (int i = 0; i < m_manager->GetEntityCount(); i++){
		m_D3D->GetWorldMatrix(worldMatrix);
			//// Get the entity we want to render.
		EntityClass* entity = m_manager->GetEntity(i);

		//// Apply transformations.
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &entity->GetTransformMatrix());

		//// Render entity.
		entity->Render(m_D3D->GetDevice());		
				
		//Supporting Matrices
		D3DXMATRIX pvm ;
		m_Camera->GetReflectionViewMatrix(reflectionMatrix);
		D3DXMATRIX worldInverseTranspose;
		D3DXMatrixInverse(&worldInverseTranspose, 0, &worldMatrix);
		D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);

		switch (entity->GetEffect())
		{
			case ShaderManagerClass::EFFECT_TEXTURE_ONLY:
			case ShaderManagerClass::EFFECT_BASIC:
			case ShaderManagerClass::EFFECT_BUMPMAP:							
			case ShaderManagerClass::EFFECT_PARALLAX:
			case ShaderManagerClass::EFFECT_TERRAIN:
			//Render dept shader
				m_DepthShader->Render(m_D3D->GetDevice(), entity->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
				break;
		}
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();
	return;
}

void GraphicsClass::CameraInput(){
	
	// || Change Camera Mode || Free Look (0) || Orbit (1) || Chase (2) ||
	if(m_Input->KeyJustDown(DIK_C) == true){
		m_Camera->ToggleCamera();
	}

	// Check Camera Type
	if(m_Camera->m_cameraType == 0)
	{	
		// Turn off other camera mode
		m_Camera->m_chase = false;
		m_Camera->m_rotate = false;
	
		// Move the camera in out out
		if(m_Input->IsKeyPressed(DIK_W) == true){
			m_Camera->UpdatePosition(0.0f, 0.0f, m_Camera->GetMoveSpeedZ());
		}
		if(m_Input->IsKeyPressed(DIK_S) == true){
			m_Camera->UpdatePosition(0.0f, 0.0f, -m_Camera->GetMoveSpeedZ());
		}

		// Move the camera left or right
		if(m_Input->IsKeyPressed(DIK_A) == true){
			m_Camera->UpdatePosition(-m_Camera->GetMoveSpeedX(), 0.0f, 0.0f);
		}
		if(m_Input->IsKeyPressed(DIK_D) == true){
			m_Camera->UpdatePosition(m_Camera->GetMoveSpeedX(), 0.0f, 0.0f);
		}

		// Move the camera up or down
		if(m_Input->IsKeyPressed(DIK_Q) == true){
			m_Camera->UpdatePosition(0.0f, m_Camera->GetMoveSpeedY(), 0.0f);
		}
		if(m_Input->IsKeyPressed(DIK_E) == true){
			m_Camera->UpdatePosition(0.0f, -m_Camera->GetMoveSpeedY(), 0.0f);
		}

		// Yaw (rotate around the Y axis)
		if(m_Input->IsKeyPressed(DIK_LEFT) == true){
			m_Camera->UpdateRotation(0.0f, -m_Camera->GetRotationSpeedY(), 0.0f);
		}
		if(m_Input->IsKeyPressed(DIK_RIGHT) == true){
			m_Camera->UpdateRotation(0.0f, m_Camera->GetRotationSpeedY(), 0.0f);
		}

		// Pitch (rotate around the X axis)
		if(m_Input->IsKeyPressed(DIK_DOWN) == true){
			m_Camera->UpdateRotation(-m_Camera->GetRotationSpeedX(), 0.0f, 0.0f);
		}
		if(m_Input->IsKeyPressed(DIK_UP) == true){
			m_Camera->UpdateRotation(m_Camera->GetRotationSpeedX(), 0.0f, 0.0f);
		}

		// Pitch (rotate around the X axis)
		if(m_Input->IsKeyPressed(DIK_COMMA) == true){
			m_Camera->UpdateRotation(0.0f, 0.0f, m_Camera->GetRotationSpeedZ());
		}
		if(m_Input->IsKeyPressed(DIK_PERIOD) == true){
			m_Camera->UpdateRotation(0.0f, 0.0f, -m_Camera->GetRotationSpeedZ());
		}
	}
	// Check Camera Type
	if(m_Camera->m_cameraType == 1)
	{
		// Turn off other camera mode
		m_Camera->m_chase = false;
	
		// Orbit Camera
		if(m_Input->KeyJustDown(DIK_SPACE) == true){
			m_Camera->ToggleOrbit();
		}
		
		// Allow user to Orbit a different Radius
		if(m_Input->KeyJustDown(DIK_W) == true){
			m_Camera->m_orbitRadius += 5;
			Log::COut("Camera Orbit Radius: " + std::to_string(m_Camera->m_orbitRadius));
		}
		if(m_Input->KeyJustDown(DIK_S) == true){
			m_Camera->m_orbitRadius -= 5;
			Log::COut("Camera Orbit Radius: " + std::to_string(m_Camera->m_orbitRadius));
		}
		
		// Allow User to Orbit to different directions and at different speeds	
		if(m_Input->KeyJustDown(DIK_UP) == true){
			m_Camera->m_orbitSpeed += 1;
			Log::COut("Camera Orbit Speed: " + std::to_string(m_Camera->m_orbitSpeed));
		}
		if(m_Input->KeyJustDown(DIK_DOWN) == true){
			m_Camera->m_orbitSpeed -= 1;
			Log::COut("Camera Orbit Speed: " + std::to_string(m_Camera->m_orbitSpeed));
		}
	}

	// Toggle relative movement/rotation
	if(m_Input->KeyJustDown(DIK_Z) == true){
		m_Camera->ToggleMoveRelative();
	}
	if(m_Input->KeyJustDown(DIK_X) == true){
		m_Camera->ToggleRotateRelative();
	}
	
	if(m_Input->KeyJustDown(DIK_P) == true){
		Log::COut("Camera Position is: " + std::to_string(m_Camera->m_positionX) + " " + std::to_string(m_Camera->m_positionY) + " " + std::to_string(m_Camera->m_positionZ));
	}
}

// This is how we move a player controlled thingy
void GraphicsClass::PlayerInput(EntityClass* e){
	if(m_Input->IsKeyPressed(DIK_Y) == true){
		e->UpdateRotation(D3DXToRadian(2), 0, 0);
	}
	if(m_Input->IsKeyPressed(DIK_I) == true){
		e->UpdateRotation(-D3DXToRadian(2), 0, 0);
	}
	if(m_Input->IsKeyPressed(DIK_U) == true){
		e->UpdatePositionRelative(0, 0, 0.5);
	}
	if(m_Input->IsKeyPressed(DIK_J) == true){
		e->UpdatePositionRelative(0, 0, -0.5);
	}
	if(m_Input->IsKeyPressed(DIK_H) == true){
		e->UpdateRotation(0, -D3DXToRadian(5), 0);
	}
	if(m_Input->IsKeyPressed(DIK_K) == true){
		e->UpdateRotation(0, D3DXToRadian(5), 0);
	}

}

// Moves all currently selected entities
void GraphicsClass::PlayerInputPack(){
	if(m_controlledEntities->GetCount() == 0) return;

	list<EntityClass*> l = m_controlledEntities->GetMemberList();

	for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
		if(m_Input->IsKeyPressed(DIK_Y) == true){
			(*it)->UpdateRotation(D3DXToRadian(2), 0, 0);
		}
		if(m_Input->IsKeyPressed(DIK_I) == true){
			(*it)->UpdateRotation(-D3DXToRadian(2), 0, 0);
		}
		if(m_Input->IsKeyPressed(DIK_U) == true){
			(*it)->UpdatePositionRelative(0, 0, 0.5);
		}
		if(m_Input->IsKeyPressed(DIK_J) == true){
			(*it)->UpdatePositionRelative(0, 0, -0.5);
		}
		if(m_Input->IsKeyPressed(DIK_H) == true){
			(*it)->UpdateRotation(0, -D3DXToRadian(5), 0);
		}
		if(m_Input->IsKeyPressed(DIK_K) == true){
			(*it)->UpdateRotation(0, D3DXToRadian(5), 0);
		}
	}
}

// Stuff thats not for the player or camera.
void GraphicsClass::OtherInput(){
	// Mouse input
	// Picking
	if(m_Input->MouseJustDown(0)){
		if(!m_Input->IsKeyPressed(DIK_LSHIFT)){
			m_controlledEntities->ClearMembers();
		}

		D3DXVECTOR3 rayDir, rayOrig;
		BuildRay(m_Input->GetMousePosition().x, m_Input->GetMousePosition().y, rayDir, rayOrig);
		Pick(rayDir, rayOrig);
	}

	// Moving through clicking
	if(m_Input->MouseJustDown(1)){
		D3DXVECTOR3 rayDir, rayOrig;
		BuildRay(m_Input->GetMousePosition().x, m_Input->GetMousePosition().y, rayDir, rayOrig);
		MoveTo(rayDir, rayOrig, D3DXVECTOR3(0, 1, 0), 0);
	}

	// Control groups
	if(m_Input->IsKeyPressed(DIK_LCONTROL)){
		if(m_Input->KeyJustDown(DIK_1)){
			if(m_controlledEntities->GetCount() != 0){
				list<EntityClass*> l = m_controlledEntities->GetMemberList();
				m_controlGroups[0]->ClearMembers();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlGroups[0]->AddMember((*it));
				}
			}
		}
		if(m_Input->KeyJustDown(DIK_2)){
			if(m_controlledEntities->GetCount() != 0){
				list<EntityClass*> l = m_controlledEntities->GetMemberList();
				m_controlGroups[1]->ClearMembers();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlGroups[1]->AddMember((*it));
				}
			}
		}
		if(m_Input->KeyJustDown(DIK_3)){
			if(m_controlledEntities->GetCount() != 0){
				list<EntityClass*> l = m_controlledEntities->GetMemberList();
				m_controlGroups[2]->ClearMembers();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlGroups[2]->AddMember((*it));
				}
			}
		}
	}else{
		if(m_Input->KeyJustDown(DIK_1)){
			if(m_controlGroups[0]->GetCount() != 0){
				if(!m_Input->IsKeyPressed(DIK_LSHIFT)){
					m_controlledEntities->ClearMembers();
				}
				list<EntityClass*> l = m_controlGroups[0]->GetMemberList();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlledEntities->AddMember((*it));
				}
			}
		}
		if(m_Input->KeyJustDown(DIK_2)){
			if(m_controlGroups[1]->GetCount() != 0){
				if(!m_Input->IsKeyPressed(DIK_LSHIFT)){
					m_controlledEntities->ClearMembers();
				}				
				list<EntityClass*> l = m_controlGroups[1]->GetMemberList();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlledEntities->AddMember((*it));
				}
			}
		}
		if(m_Input->KeyJustDown(DIK_3)){
			if(m_controlGroups[2]->GetCount() != 0){
				if(!m_Input->IsKeyPressed(DIK_LSHIFT)){
					m_controlledEntities->ClearMembers();
				}				
				list<EntityClass*> l = m_controlGroups[2]->GetMemberList();
				for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
					m_controlledEntities->AddMember((*it));
				}
			}
		}
	}

	static bool m_WireframeMode = false;
	if(m_Input->KeyJustDown(DIK_SPACE) == true)
	{
		m_WireframeMode = !m_WireframeMode;

		D3D10_RASTERIZER_DESC rasterDesc;
		ID3D10RasterizerState* m_rasterState;

		// Setup the raster description which will determine how and what polygons will be drawn.
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		//Wire Frame Mode
		if(m_WireframeMode)
		{
			rasterDesc.CullMode = D3D10_CULL_NONE;
			rasterDesc.FillMode = D3D10_FILL_WIREFRAME;
		}
		else
		{
			rasterDesc.CullMode = D3D10_CULL_BACK;
			rasterDesc.FillMode = D3D10_FILL_SOLID;
		}
	
		m_D3D->GetDevice()->CreateRasterizerState(&rasterDesc, &m_rasterState);
			// Now set the rasterizer state.
			m_D3D->GetDevice()->RSSetState(m_rasterState);
	}

	if(m_Input->KeyJustDown(DIK_F)){
		m_controlledEntities->NextFormation();
	}

	if(m_Input->KeyJustDown(DIK_F1)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = false;
		CreateSceneOne();
	}

	if(m_Input->KeyJustDown(DIK_F2)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = false;
		m_sceneOne = false;
		CreateSceneTwo();
	}

	if(m_Input->KeyJustDown(DIK_F3)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = false;
		m_sceneOne = false;
		CreateSceneThree();
	}

	if(m_Input->KeyJustDown(DIK_F4)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = false;
		m_sceneOne = false;
		CreateSceneFour();
	}

	if(m_Input->KeyJustDown(DIK_F5)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = true;
		m_sceneOne = false;
		CreateSceneFive();
	}

	if(m_Input->KeyJustDown(DIK_F6)){
		m_manager->ClearEntityArray();
		m_controlledEntities->ClearMembers();
		for(int i = 0; i < 3; i++){
			m_controlGroups[i]->ClearMembers();
		}
		soundChecking = true;
		m_sceneOne = false;
		CreateSceneSix();
	}

	// Begin janky sound demo code
	if(soundChecking == true){
		if(m_controlledEntities->Contains(m_manager->GetEntity(0))){
			soundFlags[0] = true;
		}

		if(m_controlledEntities->Contains(m_manager->GetEntity(1))){
			soundFlags[1] = true;
		}

		if(m_controlledEntities->Contains(m_manager->GetEntity(2))){
			soundFlags[2] = true;
		}
		m_controlledEntities->ClearMembers();
	}
}

#pragma region Picking Related Stuff

void GraphicsClass::BuildRay(int mouseX, int mouseY, D3DXVECTOR3 &rayDirOut, D3DXVECTOR3 &rayOrigOut){
	float pointX, pointY;
	D3DXMATRIX projectionMatrix, inverseProjectionMatrix, viewMatrix, inverseViewMatrix;
	D3DXVECTOR3 direction, origin;

	// Get the v/p/iv/ip matrices.
	m_D3D->GetProjectionMatrix(projectionMatrix);
	D3DXMatrixInverse(&inverseProjectionMatrix, NULL, &projectionMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);

	// Viewport space: Mouse coordinates
	// NDS Space: (-1, 1) range
	// Viewport -> NDS
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;

	// Z always starts at 1 - ray is going into screen.
	rayDirOut = D3DXVECTOR3(pointX, pointY, 1);
	
	// NDS -> View :: inverse projection matrix
	D3DXVec3TransformCoord(&rayDirOut, &rayDirOut, &inverseProjectionMatrix);

	// View -> World :: inverse view matrix
	D3DXVec3TransformCoord(&rayDirOut, &rayDirOut, &inverseViewMatrix);

	rayOrigOut = m_Camera->GetPosition();
}

// Select an entity
void GraphicsClass::Pick(D3DXVECTOR3 rayDirection, D3DXVECTOR3 rayOrigin){
	D3DXMATRIX worldMatrix, inverseWorldMatrix;
	D3DXVECTOR3 direction, origin;

	// Now try to smoosh this ray against all our entities.
	for (int i = 0; i < m_manager->GetEntityCount(); i++){
		// Get the entity so we dont have to keep calling GetEntity.
		EntityClass* entity = m_manager->GetEntity(i);

		// If entity can't be picked, move to the next one.
		if(entity->GetCanBePicked() == false) continue;

		// Get the world and inverse world matrices.
		m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &entity->GetTranslateMatrix());
		D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

		// World -> Model :: inverse world matrix (and normalize the ray)
		D3DXVec3TransformCoord(&direction, &rayDirection, &inverseWorldMatrix);
		D3DXVec3Normalize(&direction, &direction);
		D3DXVec3TransformCoord(&origin, &rayOrigin, &inverseWorldMatrix);

		// Test if our ray intersects with a sphere centred on the mesh co-ordinates.
		bool intersect = RaySphereIntersect(origin, direction, entity->GetMeshRadius());

		// If it is intersecting, set the entity to being controlled.
		//entity->SetIsBeingControlled(intersect);
		if(intersect){
			m_controlledEntities->AddMember(entity);
		}
		
		//Log::COut(to_string(intersect));
	}

	return;
}

bool GraphicsClass::RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius)
{
	// Ray-sphere intersection stuff...
	// rayOrigin = point ray came from == O
	// rayDirection = direction it is travelling in == D
	// position = the translation of the mesh == C
	// radius = the radius of the mesh == R
	// a = D.D
	// b = 2(O-C).D
	// c = (O-C).(O-C) - r²
	// However, we've moved the ray into the entity's space, so a, b and c are...
	// a = D.D
	// b = 2(D.O)
	// c = O.O - r²

	// There's also a lot of really mathsy stuff about the equations of lines and spheres, but I won't
	// write them out here. Anyway, replacing this stuff leaves a quadratic equation where the discriminant
	// Delta = b²-4ac.
	// If delta < 0 then the ray missed, if delta == 0 then there is 1 intersection, and if delta > 0 then
	// the are 2 intersection points.

	float a = D3DXVec3Dot(&rayDirection, &rayDirection);
	float b = 2 * (D3DXVec3Dot(&rayDirection, &rayOrigin));
	float c = D3DXVec3Dot(&rayOrigin, &rayOrigin) - (radius * radius);
	float delta = (b * b) - (4 * a * c);

	return !(delta < 0);
}

void GraphicsClass::MoveTo(D3DXVECTOR3 rayDirection, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 planeNormal, float planeDistanceFromOrigin){
	// Ray P = P0 + tV
	// Plane P.N + d = 0
	// (P0 + tV).N + d = 0
	// t = -(P0.N + d) / (V.N)
	// P = P0 + tV

	// Find t
	float t = -(D3DXVec3Dot(&rayOrigin, &planeNormal) + planeDistanceFromOrigin)
				/ D3DXVec3Dot(&rayDirection, &planeNormal);
	if(t < 0) return; // If t is less than 0, it intersects behind us somewhere.

	// Find p
	D3DXVECTOR3 p = rayOrigin + (t * rayDirection);

	int i = m_manager->AddDummy(m_D3D->GetDevice());
	EntityClass* dummy = m_manager->GetDummy(i);
	m_controlledEntities->MoveTo(p, dummy);
}

 GraphicsClass::position GraphicsClass::GetCameraPosition()
{
	position temp;
	temp.x= m_Camera->m_positionX;
	temp.y= m_Camera->m_positionY;
	temp.z= m_Camera->m_positionZ;
	return temp;
}

  GraphicsClass::position GraphicsClass::GetEntityPosition(int index)
{
	if(index >= m_manager->GetEntityCount()){
		position temp;
		temp.x = 0; temp.y = 0; temp.z = 0;
	}

	EntityClass* entity = m_manager->GetEntity(index);
	D3DXVECTOR3 temp = entity->GetPosition();
	position temp2;
	temp2.x = temp.x;
	temp2.y = temp.y;
	temp2.z = temp.z;
	return temp2;
}

#pragma endregion

void GraphicsClass::CreateSceneOne(){
	
	m_sceneOne = true;
	
	//reset light to original if has been changed
	m_lightPos = D3DXVECTOR3(0,20, 0);
	m_lookAt = D3DXVECTOR3(45, 0, 45);
	UpdateLight();

	m_Camera->SetRotation(10, 45, 0);
	m_Camera->SetPosition(-20, 45, -20);

	//build scene
	int index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("sand"), m_manager->GetMesh("terrain"));
	EntityClass* e = m_manager->GetEntity(index);
	e->SetEffect(ShaderManagerClass::EFFECT_TERRAIN);
	e->SetPosition(0, -4, 0);

	m_cornerOne = D3DXVECTOR3(0, -4, 1);
	m_cornerTwo = D3DXVECTOR3(256, 20, 256);
	//Water
	index =  m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("water01"), m_manager->GetMesh("water"));
	e = m_manager->GetEntity(index);
	e->SetEffect(ShaderManagerClass::EFFECT_WATER);
	e->SetPosition(0, 0, 0);


	// Skybox
	m_skybox = new EntityClass;
	m_skybox->Initialize(m_D3D->GetDevice(), m_manager->GetTexture("sky"), m_manager->GetMesh("sky"));
	m_skybox->SetEffect(ShaderManagerClass::EFFECT_SKY);
	m_skybox->SetPosition(0, 0, 0);

	//parallax mapping 
	//create roof
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rockWall"), m_manager->GetMesh("roof"));
	e = m_manager->GetEntity(index);
	e->SetPosition(10, -1.2, 15);
	e->SetScale(3);
	//e->SetIsRotating(1);
	e->SetRotateSpeed(0, D3DXToRadian(1), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_PARALLAX);

	//stick with body
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rockWall"), m_manager->GetMesh("cube"));
	e = m_manager->GetEntity(index);
	e->SetPosition(10, -2.2, 15);
	e->SetScale(2);
	//e->SetIsRotating(1);
	e->SetRotateSpeed(0, D3DXToRadian(1), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_PARALLAX);

	//glass effect1
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("ground1"));
	e = m_manager->GetEntity(index);
	e->SetPosition(127.5, 16, 0);
	e->SetEffect(ShaderManagerClass::EFFECT_GLASS);

	//glass effect2
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("ground1"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, 16, 127.5);
	e->SetRotation(0,D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_GLASS);

	//glass effect3
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("ground1"));
	e = m_manager->GetEntity(index);
	e->SetPosition(127.5, 16, 255);
	e->SetRotation(0,D3DXToRadian(180), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_GLASS);

	//glass effect4
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("ground1"));
	e = m_manager->GetEntity(index);
	e->SetPosition(255, 16, 127.5);
	e->SetRotation(0,D3DXToRadian(270), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_GLASS);

	// Solo fish
	for(int i = 0; i < 15; i++){
		index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("salmon"), m_manager->GetMesh("salmon"));		
		e = m_manager->GetEntity(index);
		e->SetPosition(20, 5, 20);
		e->GetAI()->SetMaxSpeed(0.1);
		e->SetCanbePicked(1);
		e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
		e->GetAI()->SetBehaviourWander(D3DXVECTOR3(m_cornerOne.x, m_cornerOne.y + 2, m_cornerOne.z), m_cornerTwo);
	}

	// Create Whale Rock

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rock1"), m_manager->GetMesh("killerWhale"));
	e = m_manager->GetEntity(index);
	e->SetPosition(30, -1, 65);
	e->SetScale(3);
	e->SetRotation(0, D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);

	//Create Bubble Emittors;

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rock1"), m_manager->GetMesh("roof"));
	e = m_manager->GetEntity(index);
	e->SetPosition(86, -4, 42);
	e->SetScale(3);
	e->SetRotation(0, D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rock1"), m_manager->GetMesh("roof"));
	e = m_manager->GetEntity(index);
	e->SetPosition(36, -4, 50);
	e->SetScale(3);
	e->SetRotation(0, D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rock1"), m_manager->GetMesh("roof"));
	e = m_manager->GetEntity(index);
	e->SetPosition(100, -4, 100);
	e->SetScale(3);
	e->SetRotation(0, D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rock1"), m_manager->GetMesh("roof"));
	e = m_manager->GetEntity(index);
	e->SetPosition(125, -4, 6);
	e->SetScale(3);
	e->SetRotation(0, D3DXToRadian(90), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);

	// Fishpacks
	for(int i = 0; i < 4; i++){
		index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("salmon"), m_manager->GetMesh("salmon"));		
		e = m_manager->GetEntity(index);
		e->SetPosition(20, 5, 20);
		e->GetAI()->SetMaxSpeed(0.1);
		e->SetCanbePicked(1);
		e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
		e->SetScale(1.2);
		e->GetAI()->SetBehaviourWander(D3DXVECTOR3(m_cornerOne.x, m_cornerOne.y + 2, m_cornerOne.z), m_cornerTwo);

		index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("salmon"), m_manager->GetMesh("salmon"));		
		e = m_manager->GetEntity(index);
		e->SetPosition(20, 5, 20);
		e->GetAI()->SetMaxSpeed(0.12);
		e->SetCanbePicked(1);
		e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
		e->GetAI()->SetBehaviourMoveToOffset(m_manager->GetEntity(index-1), -3, 0, -3);

		index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("salmon"), m_manager->GetMesh("salmon"));		
		e = m_manager->GetEntity(index);
		e->SetPosition(20, 5, 20);
		e->GetAI()->SetMaxSpeed(0.12);
		e->SetCanbePicked(1);
		e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
		e->GetAI()->SetBehaviourMoveToOffset(m_manager->GetEntity(index-1), 6, 0, -3);
	}

	// A couple sharks
	for(int i = 0; i < 2; i++){
		index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("killerWhale"), m_manager->GetMesh("killerWhale"));		
		e = m_manager->GetEntity(index);
		e->SetScale(1.8);
		e->SetPosition(20, 5, 20);
		e->GetAI()->SetMaxSpeed(0.09);
		e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
		e->GetAI()->AddChaseTarget(m_manager->GetEntity(20 + i), 0);
	}

#pragma region Attempt at avoiding mountains
	/*index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("sphere"));		
	e = m_manager->GetEntity(index);
	e->SetPosition(156, -2.5, 48.5);
	e->GetAI()->SetMaxSpeed(0.12);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
	e->SetScale(4);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("sphere"));		
	e = m_manager->GetEntity(index);
	e->SetPosition(156.5, -5.5, 29);
	e->GetAI()->SetMaxSpeed(0.12);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
	e->SetScale(4);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("sphere"));		
	e = m_manager->GetEntity(index);
	e->SetPosition(176, -1, 74);
	e->GetAI()->SetMaxSpeed(0.12);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
	e->SetScale(4);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("sphere"));		
	e = m_manager->GetEntity(index);
	e->SetPosition(159, -4, 123.5);
	e->GetAI()->SetMaxSpeed(0.12);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
	e->SetScale(4);

	int c = m_manager->GetEntityCount();
	for(int i = 0; i < c-4; i++){
		if(m_manager->GetEntity(i)->GetCanBePicked() == 0) continue;
		EntityClass* eA = m_manager->GetEntity(i);

		EntityClass* eB = m_manager->GetEntity(c-1);
		eA->GetAI()->AddAvoidTarget(eB);

		eB = m_manager->GetEntity(c-2);
		eA->GetAI()->AddAvoidTarget(eB);

		eB = m_manager->GetEntity(c-3);
		eA->GetAI()->AddAvoidTarget(eB);

		eB = m_manager->GetEntity(c-4);
		eA->GetAI()->AddAvoidTarget(eB);
	}*/
	
#pragma endregion

} // End of CreateSceneOne

void GraphicsClass::CreateSceneTwo(){
	int index;
	EntityClass* e;

	// Controlled
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("blueCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-20, 0, 20);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	m_controlledEntities->AddMember(e);

	// Predator
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-20, 0, 0);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->AddChaseTarget(m_manager->GetEntity(index-1), 0);
	e->GetAI()->AddAvoidTarget(m_manager->GetEntity(index-1));

	// Coward 1
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("dickyCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-15, 0, 20);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->AddFleeTarget(m_manager->GetEntity(index-2), 15);

	// Coward 2
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("dickyCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-25, 0, 20);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->AddFleeTarget(m_manager->GetEntity(index-3), 15);

	// Aligner
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("purpleCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, 0, -25);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->AddAlignTarget(m_manager->GetEntity(index-4));

	// Imitator - matches the predator
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("greenSkyscraper"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(20, 0, 0);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.02);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->AddVelocityMatchTarget(m_manager->GetEntity(index-4));

	// Wanderer
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rainbowCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(25, 12.5, 20);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
	e->GetAI()->SetBehaviourWanderFloat(25);

	// Tutorial Plane
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("tutorialF2"), m_manager->GetMesh("tutMesh"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, -10, 0);
	e->SetScale(2);

	m_Camera->SetPosition(0, 100, 0);
	m_Camera->SetRotation(90, 0, 0);

	m_cornerOne = D3DXVECTOR3(0, 0, 0);
	m_cornerTwo = D3DXVECTOR3(0, 0, 0);
}

void GraphicsClass::CreateSceneThree(){
	int index;
	EntityClass* e;
	
	m_Camera->SetRotation(16, 32, 0);
	m_Camera->SetPosition(-12, 18, -24);

	// The wall
	for(int i = -8; i < 8; i++){
		for(int j = -8; j < 8; j++){
			index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("wallCube"));
			e = m_manager->GetEntity(index);
			e->SetPosition(i*0.5, j*0.5, 20);
			e->SetCanbePicked(1);
		}
	}

	// The Cannonball
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("seafloor"), m_manager->GetMesh("sphere"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, 0, -50);
	e->SetScale(0.75);
	e->SetCanbePicked(1);
	e->GetAI()->SetBehaviourMoveTowards(0, 0, 500);
	e->GetAI()->SetMaxSpeed(0.2);

	// Make the wall avoid the ball
	for(int i = 0; i < m_manager->GetEntityCount(); i++){
		if(m_manager->GetEntity(i)->GetCanBePicked() == 0) continue;
		EntityClass* eA = m_manager->GetEntity(i);
		if(eA == e) continue;
		eA->GetAI()->AddAvoidTarget(e);
	}

	// Tutorial Plane
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("tutorialF3"), m_manager->GetMesh("tutMesh"));
	e = m_manager->GetEntity(index);
	e->SetPosition(30, 0, 45);
	e->SetRotation(D3DXToRadian(-90), 45, 0);
	e->SetScale(1);

	m_cornerOne = D3DXVECTOR3(0, 0, 0);
	m_cornerTwo = D3DXVECTOR3(0, 0, 0);
}

void GraphicsClass::CreateSceneFour(){
	int index;
	EntityClass* e;
	
	for(int i = -4; i < 4; i++){
		for(int j = -4; j < 4; j++){
			int whatCube = rand() % 5 + 1;
			switch (whatCube){
			case 1:
				index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("greenSkyscraper"), m_manager->GetMesh("cube3"));
				m_controlGroups[0]->AddMember(m_manager->GetEntity(index));
				break;
			case 2:
				index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("cube3"));
				m_controlGroups[1]->AddMember(m_manager->GetEntity(index));
				break;
			case 3:
				index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("blueCar"), m_manager->GetMesh("cube3"));
				m_controlGroups[2]->AddMember(m_manager->GetEntity(index));
				break;
			case 4:
				index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("purpleCar"), m_manager->GetMesh("cube3"));
				break;
			case 5:
				index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("dickyCar"), m_manager->GetMesh("cube3"));
				break;
			}
			
			e = m_manager->GetEntity(index);
			e->SetPosition(i*5, 0, j*5);
			e->SetCanbePicked(1);
			e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);
		}
	}

	for(int i = 0; i < m_manager->GetEntityCount(); i++){
		if(m_manager->GetEntity(i)->GetCanBePicked() == 0) continue;
		EntityClass* eA = m_manager->GetEntity(i);

		for(int j = 0; j < m_manager->GetEntityCount(); j++){
			if(m_manager->GetEntity(j)->GetCanBePicked() == 0) continue;
			EntityClass* eB = m_manager->GetEntity(j);
			if(eA == eB) continue;
			eA->GetAI()->AddAvoidTarget(eB);
		}
	}

	// Tutorial Plane
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("tutorialF4"), m_manager->GetMesh("tutMesh"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, -10, 0);
	e->SetScale(2);

	m_Camera->SetPosition(0, 105, 0);
	m_Camera->SetRotation(90, 0, 0);
}

//Show off Shader Manager
void GraphicsClass::CreateSceneFive(){
	int index;
	EntityClass* e;

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("greenSkyscraper"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-3.5, 80, -8);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("redCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0.5, 80, -8);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("blueCar"), m_manager->GetMesh("cube3"));
	e = m_manager->GetEntity(index);
	e->SetPosition(5, 80, -8);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetCanbePicked(1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);

	// Tutorial Plane
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("tutorialF6"), m_manager->GetMesh("tutMesh"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, -10, 0);
	e->SetScale(2);

	m_Camera->SetPosition(0, 105, 0);
	m_Camera->SetRotation(90, 0, 0);

	m_cornerOne = D3DXVECTOR3(0, 0, 0);
	m_cornerTwo = D3DXVECTOR3(0, 0, 0);
}

void GraphicsClass::CreateSceneSix(){
	//New light direction
	m_lightPos = D3DXVECTOR3(-20,20, 0);
	m_lookAt = D3DXVECTOR3(45, 0, 45);
	UpdateLight();

	m_cornerOne = D3DXVECTOR3(0, 0, 0);
	m_cornerTwo = D3DXVECTOR3(0, 0, 0);

	int index;
	EntityClass* e;

	m_Camera->SetRotation(0, 0, 0);
	m_Camera->SetPosition(0, 0, 0);

	// Plane to cast shadow 
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rainbow"), m_manager->GetMesh("cube"));
	e = m_manager->GetEntity(index);
	e->SetPosition(10, -20, 10);
	//e->SetRotation(D3DXToRadian(-90), 0, 0);
	e->SetScale(20);
	e->SetCanbePicked(1);
	e->GetAI()->SetMaxSpeed(0.1);
	e->SetEffect(ShaderManagerClass::EFFECT_TEXTURE_ONLY);

	// Parallax Cube
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("rockWall"), m_manager->GetMesh("cube"));
	e = m_manager->GetEntity(index);
	e->SetPosition(0, 0, 10);
	e->SetScale(2);
	e->SetIsRotating(1);
	e->SetRotateSpeed(0, D3DXToRadian(0.1), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_PARALLAX);

	// Bump mapped cube
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("stone"), m_manager->GetMesh("cube"));
	e = m_manager->GetEntity(index);
	e->SetPosition(3, 0, 10);
	e->SetScale(2);
	e->SetIsRotating(1);
	e->SetRotateSpeed(0, D3DXToRadian(0.1), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BUMPMAP);

	// Basic cube
	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("datrock"), m_manager->GetMesh("cube"));
	e = m_manager->GetEntity(index);
	e->SetPosition(-3, 0, 10);
	e->SetScale(2);
	e->SetIsRotating(1);
	e->SetRotateSpeed(0, D3DXToRadian(0.1), 0);
	e->SetEffect(ShaderManagerClass::EFFECT_BASIC);
}

void GraphicsClass::WaterMovement(){
	// Update the position of the water to simulate motion.
	static boolean updown = true;
	
	
	if (updown == true)
	{
		m_waterTranslation += 0.0015f;
		if (m_waterTranslation >0.3f)
		{
			updown = false;
		}
	}
	
	if (updown == false)
	{
		m_waterTranslation -= 0.0015f;
		if (m_waterTranslation < 0.00f)
		{
			updown = true;
		}
	}

	return;
}

bool GraphicsClass::CheckUnderwater(){
	// One = Close bottom left
	// Two = Far top right
	D3DXVECTOR3 pos = m_Camera->GetPosition();

	if(pos.x > m_cornerOne.x && pos.x < m_cornerTwo.x &&
		pos.y > m_cornerOne.y && pos.y < m_cornerTwo.y &&
		pos.z > m_cornerOne.x && pos.z < m_cornerTwo.z){
		return true;
	}

	return false;
}

void GraphicsClass::Loading(int i){
	m_D3D->BeginScene(0, 0, 0, 0);
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	worldMatrix = m_Camera->GetWorldMatrix();
	m_D3D->DisableZBuffer();
	m_D3D->EnableAlphaBlending();
	Texture2D* tex = m_manager->GetTexture2D("loading01");
	switch(i){
		case 1:
			tex = m_manager->GetTexture2D("loading01");
			break;
		case 2:
			tex = m_manager->GetTexture2D("loading02");
			break;
		case 3:
			tex = m_manager->GetTexture2D("loading03");
			break;
		case 4:
			tex = m_manager->GetTexture2D("loading04");
			break;
		case 5:
			tex = m_manager->GetTexture2D("loading05");
			break;
	}
	
	tex->Render(m_D3D->GetDevice(), 0, 0);
	m_TextureShader->Render(m_D3D->GetDevice(), tex->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, tex->GetTexture());
	m_D3D->DisableAlphaBlending();
	m_D3D->EnableZBuffer();
	m_D3D->EndScene();
}

void GraphicsClass::UpdateLight(){
	D3DXVECTOR3 lookDirection;
	D3DXVec3Subtract(&lookDirection, &m_lookAt, &m_lightPos);
	D3DXVec3Normalize(&lookDirection, &lookDirection);
	m_Light->SetPosition(m_lightPos.x, m_lightPos.y, m_lightPos.z);
	m_Light->SetLookAt(m_lookAt.x, m_lookAt.y, m_lookAt.z);
	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// Initialize the light direction.
	m_Light->SetLightDirection(lookDirection.x, lookDirection.y, lookDirection.z);
}

void GraphicsClass::SpawnBubble(){

	if(m_sceneOne == false)return;

	for(int i = 0; i < m_manager->GetEntityCount(); i++){
		EntityClass* ent = m_manager->GetEntity(i);
		if(ent->GetIsTranslating() == true && ent->GetEffect() == ShaderManagerClass::EFFECT_WATER &&
			ent->GetPosition().y > m_cornerTwo.y){
				m_manager->RemoveEntity(*ent);
		}
	}
	static int threshold = 60;
	static int counter = 0;
	counter++;
	if(counter != threshold) return;
	counter = 0;

	threshold = rand() % 35 + 15;  
	int index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("sphere_test"));
	EntityClass *e = m_manager->GetEntity(index);
	e->SetPosition(86, -1, 42);
	e->SetScale(0.2);
	e->SetIsTranslating(true);
	e->SetTranslateSpeed(0.05);
	e->SetTranslateDirection(0,1,0);
	e->SetEffect(ShaderManagerClass::EFFECT_WATER);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("sphere_test"));
	e = m_manager->GetEntity(index);
	e->SetPosition(36, -1, 50);
	e->SetScale(0.2);
	e->SetIsTranslating(true);
	e->SetTranslateSpeed(0.05);
	e->SetTranslateDirection(0,1,0);
	e->SetEffect(ShaderManagerClass::EFFECT_WATER);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("sphere_test"));
	e = m_manager->GetEntity(index);
	e->SetPosition(100, -1, 100);
	e->SetScale(0.2);
	e->SetIsTranslating(true);
	e->SetTranslateSpeed(0.05);
	e->SetTranslateDirection(0,1,0);
	e->SetEffect(ShaderManagerClass::EFFECT_WATER);

	index = m_manager->AddEntity(m_D3D->GetDevice(), m_manager->GetTexture("glass"), m_manager->GetMesh("sphere_test"));
	e = m_manager->GetEntity(index);
	e->SetPosition(125, -1, 6);
	e->SetScale(0.2);
	e->SetIsTranslating(true);
	e->SetTranslateSpeed(0.05);
	e->SetTranslateDirection(0,1,0);
	e->SetEffect(ShaderManagerClass::EFFECT_WATER);

}
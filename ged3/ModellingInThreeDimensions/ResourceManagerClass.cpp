#include "ResourceManagerClass.h"

#pragma region Standard Stuff
ResourceManagerClass::ResourceManagerClass(){
	m_skyWidth = 2000;
}

ResourceManagerClass::ResourceManagerClass(const ResourceManagerClass& other){
}

ResourceManagerClass::~ResourceManagerClass(){
}

bool ResourceManagerClass::Initialize(){
	Log::COut("Initialized resource manager.");
	return true;
}

void ResourceManagerClass::Shutdown(){
}
#pragma endregion

#pragma region Entities

// Gets the number of stored entities.
int ResourceManagerClass::GetEntityCount(){
	return m_entities.size();
}

// Adds a given entity to the list.
// Returns the id of the new entity.
int ResourceManagerClass::AddEntity(EntityClass* entity){
	m_entities.push_back(entity);
	Log::COut("Added entity to resource manager at location " + to_string(m_entities.size() - 1) + ".");
	return m_entities.size() - 1;
}

// Adds a new entity to the list
// Returns the id of the new entity.
int ResourceManagerClass::AddEntity(ID3D10Device* device, TextureClass* texture, MeshClass* mesh){
	
	m_entities.push_back(new EntityClass);
	m_entities.back()->Initialize(device,  texture,  mesh);
	Log::COut("Added new entity to resource manager at location " + to_string(m_entities.size() - 1) + ".");
	return m_entities.size() - 1;
}

// Get an entity from the list.
EntityClass* ResourceManagerClass::GetEntity(int id){
	list<EntityClass*>::iterator it = m_entities.begin();
    advance(it, id);

	return (*it);
}

void ResourceManagerClass::RemoveEntity(EntityClass& removeable){
	m_entities.remove(&removeable);
	//Log::COut("Removed entity from resource manager...");
}

//Allows the copying of the entites vector in another class
void ResourceManagerClass::CopyEntityArray(vector<EntityClass*>& entityVector){
	entityVector.resize(m_entities.size());
	copy(m_entities.begin(), m_entities.end(), entityVector.begin());
	return;
}

// Clears out all the entities in the manager
void ResourceManagerClass::ClearEntityArray(){
	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		(*it)->Shutdown();
	}
	m_entities.clear();
	Log::COut("Removed all entities.");
}

#pragma endregion

#pragma region Meshes

// Returns the number of stored meshes.
int ResourceManagerClass::GetMeshCount(){
	return m_meshes.size();
}

// Adds a given mesh to the list with a given key.
// Returns false if a mesh already exists with that key.
bool ResourceManagerClass::AddMesh(string key, MeshClass* mesh){
	if(m_meshes[key])
	{
		return false;
		Log::COut("Mesh already exists in resource manager with key " + key + ".");
	}

	m_meshes[key] = mesh;
	Log::COut("Added mesh to resource manager with key " + key + ".");

	return true;
}

// Adds a new mesh to the list with a given key.
// Returns false if a mesh already exists with that key.
bool ResourceManagerClass::AddMesh(string key){
	if(m_meshes[key])
	{
		return false;
		Log::COut("Mesh already exists in resource manager with key " + key + ".");
	}

	m_meshes[key] = new MeshClass;
	m_meshes[key]->Initialize();
	Log::COut("Added mesh to resource manager with key " + key + ".");

	return true;
}

// Returns the mesh with the given key.
MeshClass* ResourceManagerClass::GetMesh(string key){
	return m_meshes[key];
}

void ResourceManagerClass::FinaliseMeshes(ID3D10Device* device){
	for (std::unordered_map<string, MeshClass*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
	{
		it->second->InitializeBuffers(device);
	}
}

#pragma endregion

#pragma region Textures

// Returns the number of stored Texturees.
int ResourceManagerClass::GetTextureCount(){
	return m_textures.size();
}

// Adds a given Texture to the list with a given key.
// Returns false if a Texture already exists with that key.
bool ResourceManagerClass::AddTexture(string key, TextureClass* Texture){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = Texture;
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

// Adds a new Texture to the list with a given key.
// Returns false if a Texture already exists with that key.
bool ResourceManagerClass::AddTexture(string key, ID3D10Device* device, WCHAR* filename){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = new TextureClass;
	m_textures[key]->InitTexture(device, filename);
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

bool ResourceManagerClass::AddCubemapTexture(string key, ID3D10Device* device, WCHAR* filename){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = new TextureClass;
	m_textures[key]->InitCubeTexture(device, filename);
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

bool ResourceManagerClass::AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = new TextureClass;
	m_textures[key]->InitTexture(device, filename, filename2);
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

bool ResourceManagerClass::AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2, WCHAR* filename3){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = new TextureClass;
	m_textures[key]->InitTexture(device, filename, filename2, filename3);
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

bool ResourceManagerClass::AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2, WCHAR* filename3, WCHAR* filename4){
	if(m_textures[key])
	{
		return false;
		Log::COut("Texture already exists in resource manager with key " + key + ".");
	}

	m_textures[key] = new TextureClass;
	m_textures[key]->InitTexture(device, filename, filename2, filename3, filename4);
	Log::COut("Added Texture to resource manager with key " + key + ".");

	return true;
}

// Returns the Texture with the given key.
TextureClass* ResourceManagerClass::GetTexture(string key){
	return m_textures[key];
}

#pragma endregion

#pragma region texture2D
	int GetTexture2DCount();
	bool AddTexture2D(string key, Texture2D* texture);
	bool AddTexture2D(string key, ID3D10Device* device, WCHAR* filename);
	Texture2D* GetTexture2D(string key);

	// Returns the number of stored Texture2Des.
	int ResourceManagerClass::GetTexture2DCount(){
		return m_texture2Ds.size();
	}

	// Adds a given Texture2D2D to the list with a given key.
	// Returns false if a Texture2D already exists with that key.
	bool ResourceManagerClass::AddTexture2D(string key, Texture2D* Texture2D){
		if(m_texture2Ds[key])
		{
			return false;
			Log::COut("Texture2D already exists in resource manager with key " + key + ".");
		}

		m_texture2Ds[key] = Texture2D;
		Log::COut("Added Texture2D to resource manager with key " + key + ".");

		return true;
	}

	// Adds a new Texture2D to the list with a given key.
	// Returns false if a Texture2D already exists with that key.
	bool ResourceManagerClass::AddTexture2D(string key, ID3D10Device* device, TextureClass* texture, int screenWidth, int screenHeight, int textureWidth, int textureHeight){
		if(m_texture2Ds[key])
		{
			return false;
			Log::COut("Texture2D already exists in resource manager with key " + key + ".");
		}

		m_texture2Ds[key] = new Texture2D;
		m_texture2Ds[key]->Initialize(device, screenWidth, screenHeight, texture, textureWidth, textureHeight);
		Log::COut("Added Texture2D to resource manager with key " + key + ".");

		return true;
	}

	// Returns the Texture2D with the given key.
	Texture2D* ResourceManagerClass::GetTexture2D(string key){
		return m_texture2Ds[key];
	}
#pragma endregion

#pragma region Dummies

// Gets the number of stored entities.
int ResourceManagerClass::GetDummyCount(){
	return m_dummies.size();
}

// Adds a given Dummy to the list.
// Returns the id of the new Dummy.
int ResourceManagerClass::AddDummy(EntityClass* Dummy){
	m_dummies.push_back(Dummy);
	Log::COut("Added Dummy to resource manager at location " + to_string(m_dummies.size() - 1) + ".");
	return m_entities.size() - 1;
}

// Adds a new Dummy to the list
// Returns the id of the new Dummy.
int ResourceManagerClass::AddDummy(ID3D10Device* device){
	
	m_dummies.push_back(new EntityClass);
	m_dummies.back()->Initialize(device,  GetTexture("blueCar"),  GetMesh("cube"));
	Log::COut("Added new Dummy to resource manager at location " + to_string(m_dummies.size() - 1) + ".");
	return m_dummies.size() - 1;
}

// Get an Dummy from the list.
EntityClass* ResourceManagerClass::GetDummy(int id){
	list<EntityClass*>::iterator it = m_dummies.begin();
    advance(it, id);

	return (*it);
}

void ResourceManagerClass::RemoveDummy(EntityClass& removeable){
	m_dummies.remove(&removeable);
	removeable.Shutdown();
	delete &removeable;
	Log::COut("Removed a dummy!");
}
#pragma endregion
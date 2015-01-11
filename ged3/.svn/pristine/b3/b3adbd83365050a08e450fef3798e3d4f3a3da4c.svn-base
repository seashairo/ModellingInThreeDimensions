////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceManagerClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _RESOURCEMANAGERCLASS_H_
#define _RESOURCEMANAGERCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "EntityClass.h"
#include "MeshClass.h"
#include "TextureClass.h"
#include "Log.h"
#include "PlayerClass.h"
#include "Texture2D.h"

#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Class name: ResourceManagerClass
////////////////////////////////////////////////////////////////////////////////
class ResourceManagerClass{

public:
	ResourceManagerClass();
	ResourceManagerClass(const ResourceManagerClass&);
	~ResourceManagerClass();

	bool Initialize();
	void Shutdown();

	// Entity stuff
	int GetEntityCount();
	int AddEntity(EntityClass*);
	int AddEntity(ID3D10Device* device, TextureClass* texture, MeshClass* mesh);
	EntityClass* GetEntity(int id);
	void RemoveEntity(EntityClass&);
	void CopyEntityArray(vector<EntityClass*>& entityList);
	void ClearEntityArray();

	// Mesh stuff
	int GetMeshCount();
	bool AddMesh(string key, MeshClass* mesh);
	bool AddMesh(string key);
	MeshClass* GetMesh(string key);
	void FinaliseMeshes(ID3D10Device* device);

	// Texture stuff
	int GetTextureCount();
	bool AddTexture(string key, TextureClass* texture);
	bool AddTexture(string key, ID3D10Device* device, WCHAR* filename);
	bool AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2);
	bool AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2, WCHAR* filename3);
	bool AddTexture(string key, ID3D10Device* device, WCHAR* filename, WCHAR* filename2, WCHAR* filename3, WCHAR* filename4);
	bool AddCubemapTexture(string key, ID3D10Device* device, WCHAR* filename);
	TextureClass* GetTexture(string key);

	// Texture2D stuff
	int GetTexture2DCount();
	bool AddTexture2D(string, Texture2D*);
	bool AddTexture2D(string, ID3D10Device*, TextureClass*, int, int, int, int);
	Texture2D* GetTexture2D(string);

	//Sound Stuff
	bool AddSound(string);
	string GetSound(string key);

	// Dummy stuff
	int GetDummyCount();
	int AddDummy(EntityClass*);
	int AddDummy(ID3D10Device* device);
	EntityClass* GetDummy(int id);
	void RemoveDummy(EntityClass&);

	list<EntityClass*> m_entities;

private:
	//list<EntityClass*> m_entities;
	unordered_map<string, MeshClass*> m_meshes;
	unordered_map<string, TextureClass*> m_textures;
	unordered_map<string, Texture2D*> m_texture2Ds;
	list<EntityClass*> m_dummies;

	float m_skyWidth;
};


#endif
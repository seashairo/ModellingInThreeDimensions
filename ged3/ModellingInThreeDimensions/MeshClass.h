////////////////////////////////////////////////////////////////////////////////
// Filename: meshclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MESHCLASS_H_
#define _MESHCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <D3D10.h>
#include <D3DX10math.h>
#include "Log.h"
#include "Maya3DImporter.h"
#include "VertexHeader.h"

const int TEXTURE_REPEAT = 8;

////////////////////////////////////////////////////////////////////////////////
// Class name: MeshClass
////////////////////////////////////////////////////////////////////////////////
class MeshClass{
public: 
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct HeightMapType
	{
		float x, y, z;

	};

	struct FoliageType
	{
		float x, z;
		float r, g, b;
	};
	struct VectorType
	{
		float x, y ,z;
	};

		struct InstanceType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 color;
		D3DXMATRIX matrix;
	};

public:
	MeshClass();
	MeshClass(const MeshClass&);
	~MeshClass();

	bool Initialize();
	void Shutdown();

	VertexHeader::VertexType* GetVertices();
	VertexHeader::VertexType* GetVertexData();
	unsigned long* GetIndices();

	int GetVertexCount();
	int GetIndexCount();
	float GetRadius();

	void AddPlane();
	void AddCube(float length);
	void AddPyramid();
	void AddCuboid(float xLength, float yLength, float zLength);
	void AddSphere(int longLines, int latLines);
	void AddTerrain(int width, int height, unsigned char*, float heightFactor);
	void AddWater(int waterSize);
	void BecomeSphere(float, int, int);
	void AddModel(char* fileName);
	void AddCustom(VertexHeader::VertexType*, unsigned long*, int, int);
	void AddSkybox();
	void AddFoliage(int foliageCount);

	void AddPlane(float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);
	void AddCube(float length,
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);

	void AddCuboid(float xLength, float yLength, float zLength, 
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);
	void AddModel(char* fileName, float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);
	void AddSphere(int latLines, int longLines, float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);
	void AddCustom(VertexHeader::VertexType*, unsigned long*, int, int,
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);

	// Transformations for the mesh
	// I'd personally use these if I wanted to create a composite mesh (function to be added...)
	void TranslateMesh(float xOfs, float yOfs, float zOfs);
	void ScaleMesh(float xScale, float yScale, float zScale);
	void RotateMesh(float xRot, float yRot, float zRot);
	// Composite transformation
	void TransformMesh(float xRot, float yRot, float zRot, float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);

	void AddExternalMesh(MeshClass& other);
	void AddExternalTransformedMesh(MeshClass& other, 
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);

	void CalculateRadius();
	void ShutdownHeightMap();
	void CalculateModelVectors();
	void CalculateTerrainNormals();

	bool InitializeBuffers(ID3D10Device*);
	void InitializeInstanceBuffers(ID3D10Device*, InstanceType);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);

	static ID3D10Buffer* prevMesh;
private:
	int m_vertexCount;
	int m_indexCount;

	vector<VertexHeader::VertexType> m_vertices;
	vector<unsigned long> m_indices;

	int m_internalVertexCount;
	int m_internalIndexCount;
	int m_internalInstances;
	int m_instanceCount;
	float m_radius, m_xOffset, m_zOffset, m_heightFactor;

	int m_TerrainWidth;
	int m_TerrainHeight;

	VertexHeader::VertexType* m_internalVertices;
	D3DXVECTOR3* m_terrainNormals;
	D3DXVECTOR3** m_heightMap;
	D3DXVECTOR3* normalValues;
	D3DXVECTOR2* m_texValues;

	unsigned long* m_internalIndices;
	bool GenerateFoliagePositions(int m_foliageCount);
	
	void CalculateTangentBinormal(VertexHeader::VertexType, VertexHeader::VertexType, VertexHeader::VertexType, 
									D3DXVECTOR3&, D3DXVECTOR3&);
	void MeshClass::CalculateTangentBinormal(D3DXVECTOR3& tangent, D3DXVECTOR3& normal, D3DXVECTOR3& binormal);
	void CalculateNormal(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3&);

	void AddInternalMesh();
	void AddInternalTransformedMesh(float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs);

	void SetInternalPlane();
	// Create primitives around (0,0,0)
	// This means rotating will rotate around the origin (e.g. not appearing to orbit)
	void SetInternalCube(float length);
	void SetInternalPyramid();
	void SetInternalCuboid(float xLength, float yLength, float zLength);
	void SetInternalModel(char* fileName);
	void SetInternalSphere(int latLines, int longLines);
	bool SetInternalTerrain(int width, int height, unsigned char*, float);
	void SetInternalFoliage(int foliagecount);
	void SetInternalWater(int waterSize);
	void SetInternalSkybox();

	
	Maya3DImporter* m_importer;
	FoliageType* m_foliageArray;
	InstanceType* m_foliageInstance;
	//HeightMapType* m_heightMap;
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	
};


#endif
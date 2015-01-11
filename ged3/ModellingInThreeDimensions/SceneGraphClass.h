////////////////////////////////////////////////////////////////////////////////
// Filename: SceneGraphClass.h
////////////////////////////////////////////////////////////////////////////////

#pragma once

const int MAX_ENTITIES = 4;

//////////////
// INCLUDES //
//////////////

#include "FrustumClass.h"
#include <vector>
#include "EntityClass.h"
#include "ResourceManagerClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: SceneGraphClass
////////////////////////////////////////////////////////////////////////////////

class SceneGraphClass
{
private:
	
	struct NodeType
	{
		float positionX, positionZ, width;
		vector<EntityClass*> m_nodeEntities;
		NodeType* nodes[MAX_ENTITIES];
	};

public:
	SceneGraphClass(void);
	SceneGraphClass(const SceneGraphClass&);
	~SceneGraphClass(void);

	bool Initialize(ResourceManagerClass* entities);

private:
	void CalculateMeshDimensions(int, float&, float&, float&);
	void CreateTreeNode(NodeType*, float, float, float);
	int CountEntities(float, float, float);
	bool IsEntityContained(int, float, float, float);
	void ReleaseNode(NodeType*);
	void RenderNode(NodeType*, FrustumClass*);

private:
	int m_objectCount;

	vector<EntityClass*> m_entities;
	NodeType* m_parentNode;
};


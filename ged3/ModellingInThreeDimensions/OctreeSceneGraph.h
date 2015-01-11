#pragma once

#include "EntityClass.h"

#include <List>
#include <cmath>

struct Node
{
	D3DXVECTOR3 center;
	float halfWidth;

	Node* parent;
	Node* pChild[8];
	std::list<EntityClass*> entityList;
};

class OctreeSceneGraph
{
public:
	Node* rootNode;
public:
	OctreeSceneGraph(void);
	~OctreeSceneGraph(void);

	bool Initialize();

	Node* BuildOctree(Node* parentNode, D3DXVECTOR3 center, float halfWidth, int stopDepth);
	void UpdateOctree(Node* ptree);

	void InsertEntity(Node* pTree, EntityClass* pEntity);

	void TestAllCollisions(Node *pTree);
};
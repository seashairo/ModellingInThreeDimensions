#include "stdafx.h"
#include "SceneGraphClass.h"


SceneGraphClass::SceneGraphClass(void)
{
	m_parentNode = 0;
	
}

SceneGraphClass::SceneGraphClass(const SceneGraphClass& other)
{
}

SceneGraphClass::~SceneGraphClass(void)
{
}

bool SceneGraphClass::Initialize(ResourceManagerClass* entities)
{
	
	float centerX, CenterZ, width;
	
	
	entities->CopyEntityArray(m_entities);

	
	//Get the number of objects in the world.
	m_objectCount = m_entities.size();
	
	CalculateMeshDimensions(m_objectCount, centerX, CenterZ, width);

	m_parentNode = new NodeType;
	if(!m_parentNode)
	{
		return false;
	}

	//Recursively build the quad tree based on the object list data and mesh dimenisions
	CreateTreeNode(m_parentNode, centerX, CenterZ, width);
	
	
	return true;
}


void SceneGraphClass::CalculateMeshDimensions(int objectCount, float& centerX, float& centerZ, float& meshWidth)
{
	int i;
	float maxWidth, maxDepth, minWidth, minDepth, width, depth, maxX, maxZ;

	//Intialize the center position of the mesh to zero.
	centerX = 0.0f;
	centerZ = 0.0f;

	//sum all the vertices in the mesh
	for (i=0; i<objectCount; i++)
	{
		centerX += m_entities.at(i)->GetPosition().x;
		centerZ += m_entities.at(i)->GetPosition().z;
	}

	//Divide it by the number if vertuces to find the mid-point of the mesh.
	centerX = centerX / (float)objectCount;
	centerZ = centerZ / (float)objectCount;

	//Initialize the maximum and minimum size of the mesh.
	maxWidth = 0.0f;
	maxDepth = 0.0f;

	minWidth = fabsf(m_entities.at(0)->GetPosition().x - centerX);
	minDepth = fabsf(m_entities.at(0)->GetPosition().z - centerZ);

	//go Through all the objects and find the largest and smallest postion
	for (i=0; i < objectCount; i++)
	{
		width = fabsf(m_entities.at(0)->GetPosition().x - centerX);
		depth = fabsf(m_entities.at(0)->GetPosition().z - centerZ);

		if (width > maxWidth) { maxWidth = width; }
		if (depth < maxDepth) { maxDepth = depth; }
		if (width > minWidth) { maxWidth = width; }
		if (depth < minDepth) { maxDepth = depth; }
	}

	//Find the absolute maximum value between the min and max depth and width.
	maxX = (float)max(fabs(minWidth) , fabs(maxWidth));
	maxZ = (float)max(fabs(minDepth) , fabs(maxDepth));

	//Calculate the maximum diameter of the mesh.
	meshWidth = max(maxX, maxZ) * 2.0f;

	return;
}


void SceneGraphClass::CreateTreeNode(NodeType* node, float positionX, float positionZ, float width)
{
	int numEntities, i, count;
	float offsetX, offsetZ;
	unsigned long* indices;
	bool result;

	node->positionX = positionX;
	node->positionZ = positionZ;
	node->width = width;

	node->nodes[0] = 0;
	node->nodes[1] = 0;
	node->nodes[2] = 0;
	node->nodes[3] = 0;

	numEntities = CountEntities(positionX, positionZ, width);

	//Case 1: If there are no entities in this node then return as it is empty and requires no processing
	if(numEntities == 0)
	{
		return;
	}

	//Case 2: There are too many entities in this node then split it into 4 smaller nodes
	if(numEntities > MAX_ENTITIES)
	{
		for (i = 0; i<4; i++)
		{
			//Calculate the position offsets for the new child node
			offsetX = (((i % 2) < 1) ? - 1.0f : 1.0f) * (width / 4.0f);
			offsetZ = (((i % 4) < 2) ? - 1.0f : 1.0f) * (width / 4.0f);
			//See if there are any entities in the new node
			count = CountEntities((positionX + offsetX),(positionZ + offsetZ), (width / 2.0f));
			if(count > 0)
			{
				//if there are entities inside where this new node would be then create the child node.
				node->nodes[i] = new NodeType;

				//Extend the tree starting from this new child node now.
				CreateTreeNode(node->nodes[i],(positionX + offsetX),(positionZ + offsetZ),(width / 2.0f));
			}
		}

		return;
	}
	//Case 3: If this node is not empty and the entity count for it is less than the max then
	//this node is a leaf node so create the list of entities to store in it
	if (numEntities < MAX_ENTITIES && numEntities > 1)
	{
		
		int count = 0;
		for (i = 0; i < m_objectCount; i++)
		{
			
				result = IsEntityContained(i, positionX, positionZ, width);
				if(result == true)
				{
					node->m_nodeEntities.resize(4);
					node->m_nodeEntities.at(count) = m_entities.at(count);
					count++;
				}
		}
		return;
	}
}

int SceneGraphClass::CountEntities(float positionX, float positionZ, float width)
{
	int count, i;
	bool result;

	//Initialize the count to zero.
	count = 0;

	//go through all the entities in the entire world and check which ones should be inside this node.
	for(i=0; i < m_entities.size(); i++)
	{
		//if the entity is inside the node then increment the count by one
		result = IsEntityContained(i, positionX, positionZ, width);
		if(result == true)
		{
			count++;
		}
	}
	return count;
}

bool SceneGraphClass::IsEntityContained(int element, float positionX, float positionZ, float width)
{
	float radius;
	float x1, z1;
	

	//Calculate the radius of this entity.
	radius = width / 2.0f;

	x1 = m_entities.at(element)->GetPosition().x;
	z1 = m_entities.at(element)->GetPosition().z;

	//check to see if the minimum of the x,z coordinates of the entity is inside the node.
	if(x1 > (positionX + radius))
	{
		return false;
	}

	if(z1 > (positionX + radius))
	{
		return false;
	}

	//Check to see if the maximum of the x,z coordinates of the entity is inside the node.
	if(x1 < (positionX - radius))
	{
		return false;
	}

	if(z1 < (positionZ - radius))
	{
		return false;
	}

	return true;
}

void SceneGraphClass::ReleaseNode(NodeType* node)
{
	int i;

	//Recursively go down the tree and release the bottom nodes first.
	for(i=0; i < 4; i++)
	{
		if(node->nodes[i] !=0)
		{
			ReleaseNode(node->nodes[i]);
		}
	}

	//Release the four child nodes.
	for(i=0; i<4; i++)
	{
		if(node->nodes[i])
		{
			delete node->nodes[i];
			node->nodes[i] = 0;
		}
	}
	return;
}
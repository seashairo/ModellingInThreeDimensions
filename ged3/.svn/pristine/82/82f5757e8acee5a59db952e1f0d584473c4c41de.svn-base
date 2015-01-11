#include "OctreeSceneGraph.h"

#include "Log.h"

OctreeSceneGraph::OctreeSceneGraph(void) {
}

OctreeSceneGraph::~OctreeSceneGraph(void) {
}

bool OctreeSceneGraph::Initialize() {
	return true;
}

Node* OctreeSceneGraph::BuildOctree(Node* parentNode, D3DXVECTOR3 center, float halfWidth, int stopDepth) {
	if (stopDepth < 0 ) {return NULL;}

	else {
		Node *pNode = new Node;
		pNode->center = center;
		pNode->halfWidth = halfWidth;
		pNode->parent = parentNode;

		D3DXVECTOR3 offset;
		float step = halfWidth * 0.5f;
		for (int i = 0; i < 8; i++) {
			offset.x = ((i & 1) ? step : -step);
			offset.y = ((i & 2) ? step : -step);
			offset.z = ((i & 4) ? step : -step);
			pNode->pChild[i] = BuildOctree(pNode, offset, step, stopDepth - 1);
		}

		return pNode;
	}
}

void OctreeSceneGraph::UpdateOctree(Node* pTree) {
	for(std::list<EntityClass*>::iterator iterator = pTree->entityList.begin(); iterator != pTree->entityList.end();) {
		if((*iterator)->hasMoved) {
			InsertEntity(rootNode, (*iterator));
			iterator = pTree->entityList.erase(iterator);
		} else {
			++iterator;
		}
	}

	for(int i=0; i<8; ++i) {
		if (pTree->pChild[i] != NULL) {
			UpdateOctree(pTree->pChild[i]);
		}
	}
}

void OctreeSceneGraph::InsertEntity(Node* pTree, EntityClass* pEntity) {
	int index = 0;
	bool straddle = false, beyond = false;

	for (int i = 0; i < 3; i++) {
		float delta = pEntity->GetPosition()[i] - pTree->center[i];

		if (std::abs(delta) > pEntity->GetMeshRadius() + pTree->halfWidth) {
			//beyond = true;
			break;
		}

		if (std::abs(delta) <= pEntity->GetMeshRadius()) {
			straddle = true;
			break;
		}

		if (delta > 0.0f) {
			index |= (1 << i);
		}
	}

	if(beyond) {
		if(pTree->parent == NULL) {
			pTree->entityList.push_front(pEntity);
		} else {
			InsertEntity(pTree->parent, pEntity);
		}
	} else {

		if(straddle || pTree->pChild[index] == NULL) {
			pTree->entityList.push_front(pEntity);
		} else {
			InsertEntity(pTree->pChild[index], pEntity);
		}

	}
}
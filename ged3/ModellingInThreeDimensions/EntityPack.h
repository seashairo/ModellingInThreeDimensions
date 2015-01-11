#ifndef _ENTITYPACK_H_
#define _ENTITYPACK_H_

// Includes
#include <list>
#include "EntityClass.h"

// Class
class EntityPack
{
public:
	enum Formations{NONE, LINE, COLUMN, FLYINGV, WEDGE};

public:
	EntityPack();

	bool Initialize();
	void Shutdown();

	bool AddMember(EntityClass*);
	void RemoveMember(EntityClass*);
	bool Contains(EntityClass*);
	void ClearMembers();

	int GetCount();
	float GetLowSpeed();
	D3DXVECTOR3 GetCentrePoint();
	list<EntityClass*> GetMemberList();

	void SetFormation(Formations);
	void NextFormation();
	void MoveTo(D3DXVECTOR3, EntityClass*);
	void LineFormation(D3DXVECTOR3, EntityClass*);
	void ColumnFormation(D3DXVECTOR3, EntityClass*);
	void VFormation(D3DXVECTOR3, EntityClass*);
	void WedgeFormation(D3DXVECTOR3, EntityClass*);

private:

private:
	list<EntityClass*> m_entities;
	int m_count;
	int m_capacity;
	float m_lowSpeed;
	Formations m_formation;
};

#endif
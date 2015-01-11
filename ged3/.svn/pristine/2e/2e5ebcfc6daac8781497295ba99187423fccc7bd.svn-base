#include "EntityPack.h"

EntityPack::EntityPack(){}
bool EntityPack::Initialize(){
	m_count = 0;
	m_capacity = 10;
	m_formation = Formations::FLYINGV;

	return true;
}
void EntityPack::Shutdown(){}

bool EntityPack::AddMember(EntityClass* e){
	if(m_count == m_capacity) return false;
	if(Contains(e)) return false;
	m_entities.push_back(e);
	m_count++;
	m_lowSpeed = min(m_lowSpeed, e->GetAI()->GetMaxSpeed());
	return true;
}

void EntityPack::RemoveMember(EntityClass* e){
	m_entities.remove(e);
	m_count--;
	m_lowSpeed = min(m_lowSpeed, e->GetAI()->GetMaxSpeed());
}

bool EntityPack::Contains(EntityClass* e){
	if(m_count == 0) return false;
	 auto it = find(m_entities.begin(), m_entities.end(), e);
	 if(it == m_entities.end()) return false;
	 return true;
}

void EntityPack::ClearMembers(){
	m_entities.clear();
	m_count = 0;
}

int EntityPack::GetCount(){
	return m_count;
}

list<EntityClass*> EntityPack::GetMemberList(){
	return m_entities;
}

float EntityPack::GetLowSpeed(){
	return m_lowSpeed;
}

// Gets the centre point of the pack
D3DXVECTOR3 EntityPack::GetCentrePoint(){
	D3DXVECTOR3 ret = D3DXVECTOR3(0, 0, 0);
	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		ret += (*it)->GetPosition();
	}
	ret /= m_count;
	return ret;
}

void EntityPack::SetFormation(Formations inFormation){
	m_formation = inFormation;
	Log::COut("Entities will now move in formation: " + to_string(m_formation));
}

void EntityPack::NextFormation(){
	switch(m_formation){
	case Formations::NONE:
		m_formation = Formations::LINE;
		Log::COut("Current formation is: Line");
		break;
		case Formations::LINE:
		m_formation = Formations::COLUMN;
		Log::COut("Current formation is: Column");
		break;
		case Formations::COLUMN:
		m_formation = Formations::FLYINGV;
		Log::COut("Current formation is: Flying V");
		break;
		case Formations::FLYINGV:
		m_formation = Formations::WEDGE;
		Log::COut("Current formation is: Wedge");
		break;
		case Formations::WEDGE:
		m_formation = Formations::NONE;
		Log::COut("Current formation is: None");
		break;
	}

	
}

void EntityPack::MoveTo(D3DXVECTOR3 destination, EntityClass* dummy){
	/*if(m_count == 0) return;
	list<EntityClass*> l = m_entities;
	for (std::list<EntityClass*>::iterator it = l.begin(); it != l.end(); it++){
		(*it)->GetAI()->SetBehaviourMoveTowards(destination.x, destination.y, destination.z);
	}*/
	dummy->SetPosition(GetCentrePoint().x, GetCentrePoint().y, GetCentrePoint().z);
	dummy->GetAI()->SetBehaviourMoveTowards(destination.x, destination.y, destination.z);
	dummy->GetAI()->SetCurrentSpeed(m_lowSpeed * 0.8);

	switch(m_formation){
	case Formations::NONE:
		if(m_count == 0) return;
		for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
			(*it)->GetAI()->SetBehaviourMoveTowards(destination.x, destination.y, destination.z);
		}
		break;

	case Formations::LINE:
		LineFormation(destination, dummy);
		break;

	case Formations::COLUMN:
		ColumnFormation(destination, dummy);
		break;

	case Formations::FLYINGV:
		VFormation(destination, dummy);
		break;
	case Formations::WEDGE:
		WedgeFormation(destination, dummy);
		break;
	}
}

void EntityPack::LineFormation(D3DXVECTOR3 destination, EntityClass* dummy){
	if(m_count == 0) return;

	int ind = -1;
	int amountToChange = 5;
	int offs = 0;

	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		(*it)->GetAI()->SetBehaviourMoveToOffset(dummy, offs * ind, 0, 0);

		ind = -ind;
		if(ind == 1) offs += amountToChange;
	}
}

void EntityPack::ColumnFormation(D3DXVECTOR3 destination, EntityClass* dummy){
	if(m_count == 0) return;

	int amountToChange = -8;
	int offs = 0;
	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		(*it)->GetAI()->SetBehaviourMoveToOffset(dummy, 0, 0, offs);

		offs += amountToChange;
	}
}

void EntityPack::VFormation(D3DXVECTOR3 destination, EntityClass* dummy){
	if(m_count == 0) return;

	int amountToChange = 5;
	float offs = 0;
	int ind = -1;

	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		(*it)->GetAI()->SetBehaviourMoveToOffset(dummy, offs * ind, 0, -offs * 1.5);

		ind = -ind;
		if(ind == 1) offs += amountToChange;
	}
}

void EntityPack::WedgeFormation(D3DXVECTOR3 destination, EntityClass* dummy){
	if(m_count == 0) return;

	int amountToChangeX = 7;
	int amountToChangeZ = 7;
	float offsX = 0;
	int offsZ = 0;
	int lastInc = 0;
	int inc = 0;

	for (std::list<EntityClass*>::iterator it = m_entities.begin(); it != m_entities.end(); it++){
		(*it)->GetAI()->SetBehaviourMoveToOffset(dummy, offsX, 0, -offsZ);

		offsX += amountToChangeX;

		inc++;
		if(inc > lastInc){
			lastInc++;
			inc = 0;
			offsZ += amountToChangeZ;
			offsX = (-amountToChangeX * lastInc)/2;
		}
	}
}
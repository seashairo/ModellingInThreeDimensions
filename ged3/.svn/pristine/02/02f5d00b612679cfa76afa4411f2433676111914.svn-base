#ifndef _AI_H_
#define _AI_H_

// Includes
class EntityClass;
#include <D3DX10math.h>
#include <cstdlib>
#include <ctime>
#include <list>

#include "StateMachine.h"
#include "ActionManager.h"
class GraphicsClass;

enum EntityType {NONE, Predator, Prey};

// Class
class AI
{
private:
	struct aiTarget{
		EntityClass* target;
		float distance;

		aiTarget(EntityClass* inTarget, float inDistance){
			target = inTarget;
			distance = inDistance;
		}
	};

	struct aiOffset{
		EntityClass* target;
		float x, y, z;

		aiOffset(EntityClass* inTarget, float xIn, float yIn, float zIn){
			target = inTarget;
			x = xIn;
			y = yIn;
			z = zIn;
		}
	};

	enum Behaviours{NONE, MOVETOWARDS, WANDER, MOVETOOFFSET, WANDERCUBE};

public:
	AI();

	bool Initialize(EntityClass*);
	void Shutdown();

	void Think();
	Behaviours GetBehaviour();

	// General movement stuff
	void SetAcceleration(float);
	float GetAcceleration();
	void SetMaxSpeed(float);
	float GetMaxSpeed();
	void SetCurrentSpeed(float);
	float GetCurrentSpeed();
	void SetTurnRate(float);
	float GetTurnRate();

	// Set behaviours
	void SetBehaviourMoveTowards(float, float, float);
	void SetBehaviourFlee(EntityClass*, float);
	void SetBehaviourWanderFloat(float);
	void SetBehaviourWander(D3DXVECTOR3, D3DXVECTOR3);
	void SetBehaviourMoveToOffset(EntityClass*, float, float, float);

	// Add Targets
	void AddChaseTarget(EntityClass*, float);
	void AddFleeTarget(EntityClass*, float);
	void AddVelocityMatchTarget(EntityClass*);
	void AddAlignTarget(EntityClass*);
	void AddAvoidTarget(EntityClass*);

	// Remove Targets
	void RemoveChaseTarget(EntityClass*);
	void RemoveFleeTarget(EntityClass*);
	void RemoveVelocityMatchTarget(EntityClass*);
	void RemoveAlignTarget(EntityClass*);
	void RemoveAvoidTarget(EntityClass*);

	float RandomFloat(float, float);
	void SetEnabled(bool);
	
	//Decision Modelling Stuff:
	void BuildPredatorStateMachine();
	void BuildPreyStateMachine();

	StateMachine stateMachine;
	ActionManager actionManager;
	GraphicsClass* graphicsClassRef;
	bool hasStateMachine;

private:
	void MoveTowards();
	bool Arrive();
	void Chase();
	void Flee();
	void Wander();
	D3DXVECTOR3 GetRandomWanderDestination();
	D3DXVECTOR3 GetRandomWanderDestination(D3DXVECTOR3, D3DXVECTOR3);
	void MatchVelocity();
	void Align();
	void LookWhereYoureGoing();
	void Offsets();
	bool ArriveOffs();

	void Avoid();

	EntityClass* targetEntity;
	float minDistance, maxDistance, targetEntityDistance;
	void FindNearEntityOfType(EntityType testEntityType);

private:
	EntityClass* m_attachedTo;
	Behaviours m_currentBehaviour;
	bool m_lookAt;
	bool m_enabled;

	// Stuff about the entity we're attached to - so we don't have to keep calling GetX
	D3DXVECTOR3 m_attachedPosition;
	D3DXVECTOR3 m_attachedRotation;
	D3DXVECTOR3 m_attachedVelocity;
	float m_attachedRadius;
	D3DXVECTOR3 m_updatePosition;
	D3DXVECTOR3 m_updateRotation;

	// General movement stuff
	float m_acceleration;
	float m_currentSpeed;
	float m_maxSpeed;
	float m_turnRate;

	// Other stuff
	D3DXVECTOR3 m_destination;
	float m_wanderRadius;
	D3DXVECTOR3 m_wanderOrigin;
	bool m_needNewWanderPoint;
	D3DXVECTOR3 m_cornerOne, m_cornerTwo;

	// New AI stuff
	// Chasing
	list<aiTarget*> m_chaseTargets;
	int m_numChaseTargets;
	// Fleeing
	list<aiTarget*> m_fleeTargets;
	int m_numFleeTargets;
	// Velocity Matching
	list<EntityClass*> m_velocityMatchingTargets;
	int m_numVelMatchTargets;
	// Alignment
	list<EntityClass*> m_alignTargets;
	int m_numAlignTargets;
	// Avoid
	list<EntityClass*> m_avoidTargets;
	int m_numAvoidTargets;
	// Offset from target
	aiOffset* m_offset;
};

#endif
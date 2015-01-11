//State Machine code derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "CommonHeader.h"
#include "GraphicsClass.h"


AI::AI(){
	m_acceleration = 0.1;
	m_maxSpeed = 0.2;
	m_currentSpeed = 0;
	m_turnRate = D3DXToRadian(3);

	m_destination = D3DXVECTOR3(0, 0, 0);
	m_wanderOrigin = D3DXVECTOR3(0, 0, 0);
	m_needNewWanderPoint = 0;

	m_currentBehaviour = Behaviours::NONE;

	m_numChaseTargets = 0;
	m_numFleeTargets = 0;
	m_numAlignTargets = 0;
	m_numVelMatchTargets = 0;
	m_enabled = false;	hasStateMachine = false;}

bool AI::Initialize(EntityClass* e){
	m_attachedTo = e;

	
	stateMachine = StateMachine();
	actionManager = ActionManager();

	minDistance = 0, maxDistance = 20;

	return true;
}

void AI::Shutdown(){
	m_attachedTo = 0;
}

void AI::Think(){
	if(!m_enabled) return;

	// Reset before doing stuff.
	m_attachedPosition = m_attachedTo->GetPosition();
	m_attachedRotation = m_attachedTo->GetRotation();
	m_attachedVelocity = m_attachedTo->GetLastPosition() - m_attachedPosition;
	m_attachedRadius = m_attachedTo->GetMeshRadius();
	m_updatePosition = D3DXVECTOR3(0, 0, 0);
	m_updateRotation = D3DXVECTOR3(0, 0, 0);

	if ( hasStateMachine) {

		if (m_attachedTo->entityType == EntityType::Predator) {
			FindNearEntityOfType(EntityType::Prey);
		}

		if (m_attachedTo->entityType == EntityType::Prey) {
			FindNearEntityOfType(EntityType::Predator);
		}

		stateMachine.Update();
		actionManager.Execute();
	}

	switch(m_currentBehaviour){
	case Behaviours::MOVETOWARDS:
		m_currentSpeed = m_maxSpeed;
		MoveTowards();
		if(Arrive()){
			m_currentSpeed = 0;
			m_currentBehaviour = Behaviours::NONE;	
		};
		break;
	case Behaviours::MOVETOOFFSET:
		m_currentSpeed = m_maxSpeed;
		Offsets();
		Align();
		break;
	case Behaviours::WANDER:
		m_currentSpeed = m_maxSpeed;
		Wander();
		break;
	case Behaviours::WANDERCUBE:
		m_currentSpeed = m_maxSpeed;
		Wander();
		break;
	case Behaviours::NONE:
		m_currentSpeed = m_maxSpeed;
		Chase();
		Flee();
		MatchVelocity();
		Align();
		break;
	default: break;
	}

	// Update position based on chasing, fleeing, moving, wandering
	D3DXVec3Normalize(&m_updatePosition, &m_updatePosition);
	m_updatePosition *= m_maxSpeed;
	m_attachedTo->UpdatePosition(m_updatePosition.x, m_updatePosition.y, m_updatePosition.z);

	// Update rotation based on chasing, fleeing, moving, wandering

		if(m_numAlignTargets == 0) LookWhereYoureGoing();
		//m_attachedTo->SetRotation(m_updateRotation.x, m_updateRotation.y, m_updateRotation.z);

		// How much we need to rotate by to get to the right orientation.
		if(!(m_updateRotation.x == 0 && m_updateRotation.y == 0 && m_updateRotation.z == 0)){
			D3DXVECTOR3 amountToRotate = m_updateRotation - m_attachedRotation;

			if(amountToRotate.x != 0){
				// xT is the amount to rotate + 2Pi. If amountToRotate was positive, this will have no effect.
				float xT = fmod(amountToRotate.x, 2 * D3DX_PI) + (2 * D3DX_PI);
				// Sets amountToRotate to be the smaller distance of either amountToRotate or xT
				amountToRotate.x = abs(xT) < abs(amountToRotate.x) ? xT : amountToRotate.x;
				// Rotate depending on which way was shorter.
				if(amountToRotate.x > 0) { m_updateRotation.x = m_turnRate; }
				else if (amountToRotate.x < 0) { m_updateRotation.x = -m_turnRate; }
			}

			if(amountToRotate.y != 0){
				float yT = fmod(amountToRotate.y, 2 * D3DX_PI) + (2 * D3DX_PI);
				amountToRotate.y = abs(yT) < abs(amountToRotate.y) ? yT : amountToRotate.y;
				if(amountToRotate.y > 0) { m_updateRotation.y = m_turnRate; }
				else if (amountToRotate.y < 0) { m_updateRotation.y = -m_turnRate; }
			}

			if(amountToRotate.z != 0){
				float zT = fmod(amountToRotate.z, 2 * D3DX_PI) + (2 * D3DX_PI);
				amountToRotate.z = abs(zT) < abs(amountToRotate.z) ? zT : amountToRotate.z;
				if(amountToRotate.z > 0) { m_updateRotation.z = m_turnRate; }
				else if (amountToRotate.z < 0) { m_updateRotation.z = -m_turnRate; }
			}

			// Quit the jittering
			if(abs(amountToRotate.x) < (m_turnRate)) m_updateRotation.x = 0;
			if(abs(amountToRotate.y) < (m_turnRate)) m_updateRotation.y = 0;
			if(abs(amountToRotate.z) < (m_turnRate)) m_updateRotation.z = 0;

			m_attachedTo->UpdateRotation(m_updateRotation.x, m_updateRotation.y, m_updateRotation.z);
		}


	// Collision avoidance - Move out of other entities.
	m_updatePosition = D3DXVECTOR3(0, 0, 0);
	Avoid();
	D3DXVec3Normalize(&m_updatePosition, &m_updatePosition);
	m_updatePosition *= m_currentSpeed;
	m_attachedTo->UpdatePosition(m_updatePosition.x, m_updatePosition.y, m_updatePosition.z);
}

AI::Behaviours AI::GetBehaviour(){
	return m_currentBehaviour;
}

// General movement stuff
void AI::SetAcceleration(float accel){
	m_acceleration = accel;
}

float AI::GetAcceleration(){
	return m_acceleration;
}

void AI::SetMaxSpeed(float speed){
	m_maxSpeed = speed;
}

float AI::GetMaxSpeed(){
	return m_maxSpeed;
}

void AI::SetCurrentSpeed(float speed){
	m_currentSpeed = speed;
}

float AI::GetCurrentSpeed(){
	return m_currentSpeed;
}

void AI::SetTurnRate(float rate){
	m_turnRate = rate;
}

float AI::GetTurnRate(){
	return m_turnRate;
}

void AI::SetEnabled(bool b){
	m_enabled = b;
}

// Set behaviours
void AI::SetBehaviourMoveTowards(float x, float y, float z){
	SetEnabled(true);
	m_destination = D3DXVECTOR3(x, y, z);
	m_currentBehaviour = Behaviours::MOVETOWARDS;
}

void AI::SetBehaviourWanderFloat(float radius){
	SetEnabled(true);
	m_wanderOrigin = m_attachedTo->GetPosition();
	m_wanderRadius = radius;
	m_destination = GetRandomWanderDestination();
	m_currentBehaviour = Behaviours::WANDER;
}

void AI::SetBehaviourWander(D3DXVECTOR3 corner1, D3DXVECTOR3 corner2){
	SetEnabled(true);
	m_wanderRadius = -1;
	m_wanderOrigin = m_attachedTo->GetPosition();
	m_cornerOne = corner1; 
	m_cornerTwo = corner2;
	m_destination = GetRandomWanderDestination(corner1, corner2);
	m_currentBehaviour = Behaviours::WANDERCUBE;
}

void AI::SetBehaviourMoveToOffset(EntityClass* e, float x, float y, float z){
	SetEnabled(true);
	m_offset = new aiOffset(e, x, y, z);
	m_currentBehaviour = Behaviours::MOVETOOFFSET;
}

void AI::MoveTowards(){
	// Direction of travel = end - start
	D3DXVECTOR3 directionOfTravel = m_destination - m_attachedPosition;
	// Add the direction of travel to the update position.
	m_updatePosition += directionOfTravel;
}

bool AI::Arrive(){
	// If the current position is equal to the destination, stop moving.
	if(m_attachedPosition == m_destination){
		return true;
	}

	// if(sqrt(x^2 + y^2, z^2) < distance) stop moving
	// to avoid sqrt, we will instead check...
	// if(x^2 + y^2 + z^2 < distance^2) stop moving
	D3DXVECTOR3 directionOfTravel = m_destination - m_attachedPosition;
	if((directionOfTravel.x * directionOfTravel.x + directionOfTravel.y * directionOfTravel.y +
		directionOfTravel.z * directionOfTravel.z) < (m_currentSpeed * m_currentSpeed)){
		return true;
	}

	return false;
}

bool AI::ArriveOffs(){
	// Work out the actual offset
	D3DXVECTOR3 offsetVector = D3DXVECTOR3(m_offset->x, m_offset->y, m_offset->z);
	D3DXMATRIX transMat;
	D3DXVECTOR3 targetRot = m_offset->target->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&transMat, targetRot.y, targetRot.x, targetRot.z);
	D3DXVec3TransformCoord(&offsetVector, &offsetVector, &transMat);

	if(m_offset->target->GetLastPosition() - m_offset->target->GetPosition() != 0){
		// If the current position is equal to the destination, stop moving.
		D3DXVECTOR3 dest = m_offset->target->GetPosition() + offsetVector;
		if(m_attachedPosition == dest){
			return true;
		}

		// if(sqrt(x^2 + y^2, z^2) < distance) stop moving
		// to avoid sqrt, we will instead check...
		// if(x^2 + y^2 + z^2 < distance^2) stop moving
		D3DXVECTOR3 directionOfTravel = dest - m_attachedPosition;
		if((directionOfTravel.x * directionOfTravel.x + directionOfTravel.y * directionOfTravel.y +
			directionOfTravel.z * directionOfTravel.z) < (m_currentSpeed * m_currentSpeed)){
			return true;
		}
	}

	return false;
}

void AI::Chase(){
	// If there's nothing to chase, don't bother trying.
	if(m_numChaseTargets == 0) return;

	// For every chase target we have...
	for (std::list<aiTarget*>::iterator it = m_chaseTargets.begin(); it != m_chaseTargets.end(); it++){
		// Work out the distance/direction the target is in.
		D3DXVECTOR3 dest = (*it)->target->GetPosition();
		D3DXVECTOR3 directionOfTravel = dest - m_attachedPosition;

		// If the target is within chasing distance, hunt them down!
		if((*it)->distance == 0 ||
			(directionOfTravel.x * directionOfTravel.x + directionOfTravel.y * directionOfTravel.y +
			directionOfTravel.z * directionOfTravel.z) < ((*it)->distance * (*it)->distance)){
			D3DXVec3Normalize(&directionOfTravel, &directionOfTravel);
			m_updatePosition += directionOfTravel;
		}
	}
}

void AI::Flee(){
	// If there's nothing to run from, there's nothing to do here.
	if(m_numFleeTargets == 0) return;

	// For every flee target we have...
	for (std::list<aiTarget*>::iterator it = m_fleeTargets.begin(); it != m_fleeTargets.end(); it++){
		// Work out the distance/direction the target is in.
		D3DXVECTOR3 dest = (*it)->target->GetPosition();
		D3DXVECTOR3 directionOfTravel = m_attachedPosition - dest;

		// If the target is within distance, run for your life!
		if((*it)->distance == 0 ||
			(directionOfTravel.x * directionOfTravel.x + directionOfTravel.y * directionOfTravel.y +
			directionOfTravel.z * directionOfTravel.z) < ((*it)->distance * (*it)->distance)){
			D3DXVec3Normalize(&directionOfTravel, &directionOfTravel);
			m_updatePosition += directionOfTravel;
		}
	}
}

void AI::Wander(){
	MoveTowards();
	if(Arrive()){
		if(m_wanderRadius == -1){
			m_destination = GetRandomWanderDestination(m_cornerOne, m_cornerTwo);
		}else{
			m_destination = GetRandomWanderDestination();
		}
	}
}

D3DXVECTOR3 AI::GetRandomWanderDestination(){
	// Wandering will move to random points withing a given area. For us,
	// that area is a sphere of radius m_wanderRadius around where the wandering started.
	// This method will create a vector with a random point in that sphere.

	// To just do this for a cube:
	// float x = RandomFloat(-m_wanderRadius, m_wanderRadius);
	// float y = RandomFloat(-m_wanderRadius, m_wanderRadius);
	// float z = RandomFloat(-m_wanderRadius, m_wanderRadius);
	// D3DXVECTOR3 retVal = D3DXVECTOR3(x, y, z);
	// return retVal + m_wanderOrigin;

	bool isInSphere = false;
	
	float x, y, z;
	while(!isInSphere){
		// Generate 3 random values within the diamter of the sphere.
		x = RandomFloat(-m_wanderRadius, m_wanderRadius);
		y = RandomFloat(-m_wanderRadius, m_wanderRadius);
		z = RandomFloat(-m_wanderRadius, m_wanderRadius);

		// If the point lies insdie the sphere, we can return it.
		// Otherwise, try again.
		isInSphere = ((x*x + y*y + z*z) < (m_wanderRadius*m_wanderRadius));
	}
	D3DXVECTOR3 retVal = D3DXVECTOR3(x, y, z);
	return retVal + m_wanderOrigin;
}

D3DXVECTOR3 AI::GetRandomWanderDestination(D3DXVECTOR3 corner1, D3DXVECTOR3 corner2){
	float x, y, z;
	x = RandomFloat(corner1.x, corner2.x);
	y = RandomFloat(corner1.y, corner2.y);
	z = RandomFloat(corner1.z, corner2.z);

	D3DXVECTOR3 retVal = D3DXVECTOR3(x, y, z);
	return retVal;
}

void AI::LookWhereYoureGoing(){
	if(m_updatePosition == D3DXVECTOR3(0, 0, 0)) return;
	float xRot, yRot;

	yRot = atan2(m_updatePosition.x, m_updatePosition.z);

	if (m_updatePosition.z > 0)
		xRot = atan2(-m_updatePosition.y, m_updatePosition.z);
	else
		xRot = atan2(-m_updatePosition.y, -m_updatePosition.z);

	m_updateRotation += D3DXVECTOR3(xRot, yRot, 0);
}

void AI::Avoid(){
	if(m_numAvoidTargets == 0) return;

	int decay = -10;

	// For every flee target we have...
	for (std::list<EntityClass*>::iterator it = m_avoidTargets.begin(); it != m_avoidTargets.end(); it++){
		// Work out the distance/direction the target is in.
		D3DXVECTOR3 dest = (*it)->GetPosition();
		D3DXVECTOR3 directionOfTravel = dest - m_attachedPosition;
		float distance = D3DXVec3Length(&directionOfTravel);

		if(distance < (m_attachedTo->GetMeshRadius() + (*it)->GetMeshRadius())){
			float repulsion = min(decay / distance * distance, m_maxSpeed);
			D3DXVec3Normalize(&directionOfTravel, &directionOfTravel);
			m_updatePosition += (repulsion * directionOfTravel);
		}
	}
}

// Returns a random float between min and max.
float AI::RandomFloat(float min, float max){
	float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

// Attempt to match another entity's velocity.
// Direction is matched, speed currently isn't.
void AI::MatchVelocity(){
	// If there's nothing to match, don't bother trying.
	if(m_numVelMatchTargets == 0) return;

	// For every target we have...
	for (std::list<EntityClass*>::iterator it = m_velocityMatchingTargets.begin(); it != m_velocityMatchingTargets.end(); it++){
		// Get their velocity and add it to the update position.
		float f = (*it)->GetPosition().x;
		D3DXVECTOR3 targetVelocity = (*it)->GetPosition() - (*it)->GetLastPosition();
		m_updatePosition += targetVelocity;
	}
}

void AI::Align(){
	// If there's nothing to match, don't bother trying.
	if(m_numAlignTargets == 0) return;

	// For every target we have...
	for (std::list<EntityClass*>::iterator it = m_alignTargets.begin(); it != m_alignTargets.end(); it++){
		// Get their velocity and add it to the update position.
		D3DXVECTOR3 targetRotation = (*it)->GetRotation();
		m_updateRotation += targetRotation;
	}
	m_updateRotation /= m_numAlignTargets;
}

void AI::Offsets(){
	SetEnabled(true);
	if(m_offset == 0) return;

	// How much we want to ffset by
	D3DXVECTOR3 offsetVector = D3DXVECTOR3(m_offset->x, m_offset->y, m_offset->z);

	// Create a rotation matrix based off the target's rotation
	D3DXMATRIX transMat;
	D3DXVECTOR3 targetRot = m_offset->target->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&transMat, targetRot.y, targetRot.x, targetRot.z);

	// Rotate the offset by the target's rotation
	D3DXVec3TransformCoord(&offsetVector, &offsetVector, &transMat);

	// Add the target's position to the offset position to get the final position.
	offsetVector += m_offset->target->GetPosition();

	D3DXVECTOR3 directionOfTravel = offsetVector - m_attachedPosition;
	// Add the direction of travel to the update position.
	m_updatePosition += directionOfTravel;
}

// Adds something for our entity to chase.
void AI::AddChaseTarget(EntityClass* target, float distance){
	SetEnabled(true);
	m_numChaseTargets++;
	m_chaseTargets.push_back(new aiTarget(target, distance));
}

// Adds something our entity wants to run from.
void AI::AddFleeTarget(EntityClass* target, float distance){
	SetEnabled(true);
	m_numFleeTargets++;
	m_fleeTargets.push_back(new aiTarget(target, distance));
}

// Adds something our entity wants to match the velocity of.
void AI::AddVelocityMatchTarget(EntityClass* target){
	SetEnabled(true);
	m_numVelMatchTargets++;
	m_velocityMatchingTargets.push_back(target);
}

// Adds something our entity wants to align with.
void AI::AddAlignTarget(EntityClass* target){
	SetEnabled(true);
	m_numAlignTargets++;
	m_alignTargets.push_back(target);
}

// Adds something our entity wants to not smash into.
void AI::AddAvoidTarget(EntityClass* target){
	SetEnabled(true);
	m_numAvoidTargets++;
	m_avoidTargets.push_back(target);
}

void AI::RemoveChaseTarget(EntityClass* e){
	for (std::list<aiTarget*>::iterator it = m_chaseTargets.begin(); it != m_chaseTargets.end(); it++){
		if((*it)->target->GetEID() == e->GetEID()){
			m_chaseTargets.remove((*it));
			return;
		}
	}
}

void AI::RemoveFleeTarget(EntityClass* e){
	for (std::list<aiTarget*>::iterator it = m_fleeTargets.begin(); it != m_fleeTargets.end(); it++){
		if((*it)->target->GetEID() == e->GetEID()){
			m_fleeTargets.remove((*it));
			return;
		}
	}
}

void AI::RemoveVelocityMatchTarget(EntityClass* e){
	for (std::list<EntityClass*>::iterator it = m_velocityMatchingTargets.begin(); it != m_velocityMatchingTargets.end(); it++){
		if((*it)->GetEID() == e->GetEID()){
			m_velocityMatchingTargets.remove((*it));
			return;
		}
	}
}

void AI::RemoveAlignTarget(EntityClass* e){
	for (std::list<EntityClass*>::iterator it = m_alignTargets.begin(); it != m_alignTargets.end(); it++){
		if((*it)->GetEID() == e->GetEID()){
			m_alignTargets.remove((*it));
			return;
		}
	}
}

void AI::RemoveAvoidTarget(EntityClass* e){
	for (std::list<EntityClass*>::iterator it = m_avoidTargets.begin(); it != m_avoidTargets.end(); it++){
		if((*it)->GetEID() == e->GetEID()){
			m_avoidTargets.remove((*it));
			return;
		}
	}
}

void AI::BuildPredatorStateMachine() {
	std::function<void ()> f;

	State *wanderState = new State();
	Action *wanderEntryAction = new Action();
	f = std::bind(&AI::SetBehaviourWanderFloat, this, 50);
	wanderEntryAction->SetFunction(f);
	wanderEntryAction->SetPriority(1);
	wanderState->setEntryAction(wanderEntryAction);
	wanderState->name = "Wander State";

	State *seekState = new State();
	Action *enterSeekStateAction = new Action();
	f = std::bind(&AI::AddChaseTarget, this, AI::targetEntity, 1);
	enterSeekStateAction->SetFunction(f);
	enterSeekStateAction->SetPriority(1);
	seekState->setEntryAction(enterSeekStateAction);

	Action *seekExitAction = new Action();
	f = std::bind(&AI::RemoveChaseTarget, this, AI::targetEntity);
	seekExitAction->SetFunction(f);
	seekExitAction->SetPriority(1);
	seekState->setExitAction(seekExitAction);
	seekState->name = "SeekState";

	Transition *transition = new Transition();
	transition->SetTargetState(seekState);
	FloatCondition *condition1 = new FloatCondition();
	condition1->SetValues(&minDistance, &maxDistance, &targetEntityDistance);
	transition->SetTriggerConditon(condition1);
	wanderState->addTransition(transition);

	Transition *transition2 = new Transition();
	transition2->SetTargetState(wanderState);
	FloatCondition *condition2 = new FloatCondition();
	condition2->SetValues(&minDistance, &maxDistance, &targetEntityDistance);
	transition2->SetTriggerConditon(condition2);
	seekState->addTransition(transition2);

	stateMachine.AddState(wanderState);
	stateMachine.AddState(seekState);
	stateMachine.SetInitialState(wanderState);

	hasStateMachine = true;
	m_attachedTo->entityType = EntityType::Predator;
	stateMachine.Initialize(&(actionManager));
}

void AI::BuildPreyStateMachine () {
	State *wanderState = new State();
	Action *wanderEntryAction = new Action();
	std::function<void ()> f = std::bind(&AI::SetBehaviourWanderFloat, this, 50);
	wanderEntryAction->SetFunction(f);
	wanderEntryAction->SetPriority(1);
	wanderState->setEntryAction(wanderEntryAction);
	wanderState->name = "Wander State";

	State *fleeState = new State();
	Action *fleeEnterAction = new Action();
	f = std::bind(&AI::AddFleeTarget, this,	AI::targetEntity, 20);
	fleeEnterAction->SetFunction(f);
	fleeEnterAction->SetPriority(1);
	fleeState->setEntryAction(fleeEnterAction);

	Action *fleeExitAction = new Action();
	f = std::bind(&AI::RemoveFleeTarget, this, AI::targetEntity);
	fleeExitAction->SetFunction(f);
	fleeExitAction->SetPriority(1);
	wanderState->setExitAction(fleeExitAction);
	fleeState->name = "FleeState";

	Transition *transition = new Transition();
	transition->SetTargetState(fleeState);
	FloatCondition *condition1 = new FloatCondition();
	condition1->SetValues(&minDistance, &maxDistance, &targetEntityDistance);
	transition->SetTriggerConditon(condition1);
	wanderState->addTransition(transition);

	Transition *transition2 = new Transition();
	transition2->SetTargetState(wanderState);
	FloatCondition *condition2 = new FloatCondition();
	condition2->SetValues(&minDistance, &maxDistance, &targetEntityDistance);
	transition2->SetTriggerConditon(condition2);
	fleeState->addTransition(transition2);

	stateMachine.AddState(wanderState);
	stateMachine.AddState(fleeState);
	stateMachine.SetInitialState(wanderState);

	hasStateMachine = true;
	m_attachedTo->entityType = EntityType::Prey;
	stateMachine.Initialize(&(actionManager));
}

void AI::FindNearEntityOfType (EntityType testEntityType) {
	std::list<EntityClass*>& list = graphicsClassRef->m_manager->m_entities;
	D3DXVECTOR3 differenceVector;

	for (std::list<EntityClass*>::iterator iterator = list.begin(); iterator != list.end(); ++iterator) {
		
		D3DXVec3Subtract(&differenceVector, &(*iterator)->GetPosition(), &m_attachedTo->GetPosition());
		float distance = std::abs(D3DXVec3Length(&differenceVector));

		if ( (*iterator)->entityType == testEntityType && distance < maxDistance) {
			targetEntity = *iterator;
			targetEntityDistance = distance;
		}
	}
}
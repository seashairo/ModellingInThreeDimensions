#include "CommonHeader.h"

static int entity_eid_current = 0;

EntityClass::EntityClass(){
	m_texture = 0;
	m_model = 0;
	m_AI = 0;
	m_effect = ShaderManagerClass::EFFECT_TEXTURE_ONLY; // by default shader

	m_isRotating = false;
	m_isTranslating = false;
	m_currentScale = 1.0f;
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_rotationSpeed = D3DXVECTOR3(0, 0, 0);
	m_moveSpeed = 2;
	m_direction = D3DXVECTOR3(0, 0, 0);

	//initial transform matrix
	D3DXMatrixIdentity(&m_scaleMatrix);
	D3DXMatrixIdentity(&m_rotateMatrix);
	D3DXMatrixIdentity(&m_translateMatrix);

	m_isBeingControlled = false;
	m_canBePicked = false;

	m_eid = entity_eid_current++;
}

EntityClass::EntityClass(const EntityClass& other){
}

EntityClass::~EntityClass(){
}

bool EntityClass::Initialize(ID3D10Device* device, TextureClass* texture, MeshClass* mesh){
	bool result;

	m_mesh = mesh;
	//m_mesh->CalculateModelVectors();

	m_AI = new AI;
	m_AI->Initialize(this);

	m_texture = texture;

	return true;
}

void EntityClass::Shutdown(){
	if(m_AI){
		m_AI->Shutdown();
		delete m_AI;
		m_AI = 0;
	}

	return;
}

void EntityClass::Render(ID3D10Device* device){
	m_lastPos = m_pos;
	m_lastRotation = m_lastRotation;
	
	m_AI->Think();

	if(m_isRotating)
	{
		UpdateRotation(m_rotationSpeed.x, m_rotationSpeed.y, m_rotationSpeed.z);
	}

	if(m_isTranslating)
	{
		UpdatePosition(m_moveSpeed * m_direction.x, m_moveSpeed * m_direction.y, m_moveSpeed * m_direction.z);
	}

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_mesh->RenderBuffers(device);

	return;
}

int EntityClass::GetIndexCount(){
	return m_mesh->GetIndexCount();
}

int EntityClass::GetVertexCount(){
	return m_mesh->GetVertexCount();
}

void EntityClass::SetEffect(ShaderManagerClass::RenderEffect effect){
	m_effect = effect;
}
ShaderManagerClass::RenderEffect EntityClass::GetEffect(){
	return m_effect;
}

D3DXVECTOR3 EntityClass::GetPosition(){
	return m_pos;
}

D3DXVECTOR3 EntityClass::GetLastPosition(){
	return m_lastPos;
}

ID3D10ShaderResourceView** EntityClass::GetTextureArray(){
	return m_texture->GetTextureArray();
}



D3DXMATRIX EntityClass:: GetTransformMatrix()
{
	D3DXMatrixMultiply(&m_transformMatrix, &m_rotateMatrix, &m_translateMatrix);
	D3DXMatrixMultiply(&m_transformMatrix, &m_scaleMatrix, &m_transformMatrix);

	return m_transformMatrix;
}

D3DXMATRIX EntityClass::GetTranslateMatrix(){
	return m_translateMatrix;
}

void EntityClass::SetPosition(float x, float y, float z){
	m_pos = D3DXVECTOR3(x, y, z);
	D3DXMatrixTranslation(&m_translateMatrix, x, y, z);
}

void EntityClass::UpdatePosition(float x, float y, float z){
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;
	D3DXMatrixTranslation(&m_translateMatrix, m_pos.x, m_pos.y, m_pos.z);

	hasMoved = true;
}

void EntityClass::UpdatePositionRelative(float x, float y, float z){
	D3DXVECTOR3 position(x, y, z);

	// Transform the position with the rotation matrix.
	D3DXVec3TransformCoord(&position, &position, &m_rotateMatrix);

	// Put the new position into the camera's position.
	m_pos.x += position.x;
	m_pos.y += position.y;
	m_pos.z += position.z;

	D3DXMatrixTranslation(&m_translateMatrix, m_pos.x, m_pos.y, m_pos.z);

	hasMoved = true;
}

void EntityClass::SetScale(float percentage){
	m_currentScale = percentage;
	D3DXMatrixScaling(&m_scaleMatrix, percentage, percentage, percentage);
}

// Takes radians
void EntityClass::SetRotation(float x, float y, float z){
	m_rotation.x = fmod(x, 2 * D3DX_PI);
	m_rotation.y = fmod(y, 2 * D3DX_PI);
	m_rotation.z = fmod(z, 2 * D3DX_PI);

	D3DXMatrixRotationYawPitchRoll(&m_rotateMatrix, m_rotation.y, m_rotation.x, m_rotation.z);
}

void EntityClass::UpdateRotation(float x, float y, float z){
	m_rotation.x = fmod(m_rotation.x + x, 2 * D3DX_PI);
	m_rotation.y = fmod(m_rotation.y + y, 2 * D3DX_PI);
	m_rotation.z = fmod(m_rotation.z + z, 2 * D3DX_PI);

	D3DXMatrixRotationYawPitchRoll(&m_rotateMatrix, m_rotation.y, m_rotation.x, m_rotation.z);
}

D3DXVECTOR3 EntityClass::GetRotation(){
	return m_rotation;
}

D3DXVECTOR3 EntityClass::GetLastRotation(){
	return m_lastRotation;
}

void EntityClass:: SetIsRotating(bool rotate){
	m_isRotating = rotate;
}

bool EntityClass::GetIsRotating(){
	return m_isRotating;
}

void EntityClass::SetRotateSpeed(float x, float y, float z){
	m_rotationSpeed.x = x;
	m_rotationSpeed.y = y;
	m_rotationSpeed.z = z;
}

D3DXVECTOR3 EntityClass::GetRotationSpeed(){
	return m_rotationSpeed;
}

void EntityClass::SetIsTranslating(bool b){
	m_isTranslating = b;
}

bool EntityClass::GetIsTranslating(){
	return m_isTranslating;
}

void EntityClass::SetTranslateSpeed(float speed){
	m_moveSpeed = speed;
}

void EntityClass::SetTranslateDirection(float x, float y, float z){
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;

	D3DXVec3Normalize(&m_direction, &m_direction);
}

D3DXVECTOR3 EntityClass::GetTranslateDirection(){
	return m_direction;
}

void EntityClass::SetIsBeingControlled(bool b){
	m_isBeingControlled = b;
}

bool EntityClass::GetIsBeingControlled(){
	return m_isBeingControlled;
}

void EntityClass::SetCanbePicked(bool b){
	m_canBePicked = b;
}

bool EntityClass::GetCanBePicked(){
	return m_canBePicked;
}

float EntityClass::GetMeshRadius(){
	return m_mesh->GetRadius() * m_currentScale;
}

AI* EntityClass::GetAI(){
	return m_AI;
}

int EntityClass::GetEID(){
	return m_eid;
}
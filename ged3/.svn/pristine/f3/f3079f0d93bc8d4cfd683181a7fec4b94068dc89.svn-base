#include "cameraclass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_moveSpeedX = 0.3;
	m_moveSpeedY = 0.3;
	m_moveSpeedZ = 0.3;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_rotationSpeedX = 1.5f;
	m_rotationSpeedY = 1.5f;
	m_rotationSpeedZ = 1.5f;

	m_moveRelative = true;
	m_rotateRelative = false;
	
	m_rotate = false;
	m_startingPoint = D3DXVECTOR3(0, 0, 0);
	m_startingOrientation = D3DXVECTOR3(0, 0, 0);
	m_orbitRadius = 100;
	m_orbitSpeed = 1;

	m_chase = false;

	m_cameraType = 0;

}


CameraClass::CameraClass(const CameraClass& other){
}


CameraClass::~CameraClass(){
}


void CameraClass::SetPosition(float x, float y, float z){
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;

	return;
}


void CameraClass::SetRotation(float x, float y, float z){
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void CameraClass::UpdatePosition(float x, float y, float z){

		// This will make the camera move relative to it's current facing.
		// This means W will always move towards what the camera sees.
		// Create the position vector from the entered values.

	if(m_moveRelative)
	{
		D3DXVECTOR3 position(x, y, z);

		// Put the rotation information (pitch, yaw, roll) into the rotation matrix.
		D3DXMATRIX rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 
			D3DXToRadian(m_rotationY), 
			D3DXToRadian(m_rotationX), 
			D3DXToRadian(m_rotationZ));

		// Transform the position with the rotation matrix.
		D3DXVec3TransformCoord(&position, &position, &rotationMatrix);

		// Put the new position into the camera's position.
		m_positionX += position.x;
		m_positionY += position.y;
		m_positionZ += position.z;
	}
	
	else
	{
		m_positionX += x;
		m_positionY += y;
		m_positionZ += z;
	}
}

void CameraClass::UpdateRotation(float x, float y, float z){
	
		// Rotate the camera relative to its current rotation.
		// This means that pressing UP will always move the angle
		// upwards from the user's POV.
	
	if(m_rotateRelative){
		D3DXVECTOR3 position(x, y, z);

		D3DXMATRIX rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 
			D3DXToRadian(m_rotationY), 
			D3DXToRadian(m_rotationX), 
			D3DXToRadian(m_rotationZ));
		D3DXVec3TransformCoord(&position, &position, &rotationMatrix);

		m_rotationX += position.x;
		m_rotationY += position.y;
		m_rotationZ += position.z;
	}
	
	else
	{
		m_rotationX += x;
		m_rotationY += y;
		m_rotationZ += z;
	}
	return;
}

float CameraClass::GetMoveSpeedX(){
	return m_moveSpeedX;
}

float CameraClass::GetMoveSpeedY(){
	return m_moveSpeedY;
}

float CameraClass::GetMoveSpeedZ(){
	return m_moveSpeedZ;
}

float CameraClass::GetRotationSpeedX(){
	return m_rotationSpeedX;
}

float CameraClass::GetRotationSpeedY(){
	return m_rotationSpeedY;
}

float CameraClass::GetRotationSpeedZ(){
	return m_rotationSpeedZ;
}

D3DXVECTOR3 CameraClass::GetPosition(){
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}

D3DXVECTOR3 CameraClass::GetRotation(){
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::ToggleMoveRelative(){
	m_moveRelative = !m_moveRelative;
}

void CameraClass::ToggleRotateRelative(){
	m_rotateRelative = !m_rotateRelative;
}

void CameraClass::SetChasingTarget(PlayerClass* target)
{
	m_chasingTarget = target;
}

void CameraClass::Render(){
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Orbit Camera
	if(m_rotate)
	{
		m_positionX = (m_orbitRadius * (sin(m_orbitAngle))) + m_startingPoint.x;
		m_positionZ = (-m_orbitRadius * (cos(m_orbitAngle))) + m_startingPoint.z;
		SetRotation(0, -D3DXToDegree(m_orbitAngle), 0);
		m_orbitAngle += D3DXToRadian(m_orbitSpeed);
		if(m_orbitAngle > 360) m_orbitAngle = 0;
	}

	// Chase Camera
	if(m_chase && m_chasingTarget != nullptr)
	{
		SetRotation(15, D3DXToDegree(m_chasingTarget->GetRotation().y), 0);

		m_positionX = m_chasingTarget->GetPosition().x;
		m_positionY = m_chasingTarget->GetPosition().y;
		m_positionZ = m_chasingTarget->GetPosition().z;
		
		D3DXVECTOR3 position(0, 10, -50);

		// Put the rotation information (pitch, yaw, roll) into the rotation matrix.
		D3DXMATRIX rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 
			m_chasingTarget->GetRotation().y, 
			D3DXToRadian(m_rotationX), 
			D3DXToRadian(m_rotationX));

		// Transform the position with the rotation matrix.
		D3DXVec3TransformCoord(&position, &position, &rotationMatrix);

		// Put the new position into the camera's position.
		m_positionX += position.x;
		m_positionY += position.y;
		m_positionZ += position.z;
	}

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = D3DXToRadian(m_rotationX);
	yaw   = D3DXToRadian(m_rotationY);
	roll  = D3DXToRadian(m_rotationZ);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	m_worldMatrix = rotationMatrix;
	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, m_positionX, m_positionY, m_positionZ);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &translation);

	return;
}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix){
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::RenderReflection(float height)
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.  For planar reflection invert the Y position of the camera.
	position.x = m_positionX;
	position.y = -m_positionY + (height * 2.0f);
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.  Invert the X rotation for reflection.
	pitch = -m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the reflection view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_reflectionViewMatrix, &position, &lookAt, &up);

	return;
}

void CameraClass::GetReflectionViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_reflectionViewMatrix;
	return;
}

void CameraClass::ToggleOrbit(){
	// Toggle Orbit off and set camera back to original position
	if(m_rotate)
	{
		m_rotate = false;

		m_positionX = m_startingPoint.x;
		m_positionY = m_startingPoint.y;
		m_positionZ = m_startingPoint.z;

		SetRotation(m_startingOrientation.x, m_startingOrientation.y, m_startingOrientation.z);

	}

	// Toggle Orbit on and set orientation and position to orbit around
	else
	{
		m_rotate = true;
		
		m_startingOrientation.x = GetRotation().x;
		m_startingOrientation.y = GetRotation().y;
		m_startingOrientation.z = GetRotation().z;
		
		m_orbitAngle = m_startingOrientation.y;
		
		m_startingPoint.x = m_positionX;
		m_startingPoint.y = m_positionY;
		m_startingPoint.z = m_positionZ;
	}
}

void CameraClass::ToggleChase()
{
	// Toggle Chase off and set camera back to original position
	if(m_chase){
		m_chase = false;

		m_positionX = m_startingPoint.x;
		m_positionY = m_startingPoint.y;
		m_positionZ = m_startingPoint.z;
	}

	// Toggle Chase on and set position to return to when done
	else{
		m_chase = true;

		m_startingPoint.x = m_positionX;
		m_startingPoint.y = m_positionY;
		m_startingPoint.z = m_positionZ;
	}
}

void CameraClass::ToggleCamera(){
	
	// Change Camera Mode || Free Look (0) || Orbit (1) || Chase (2) ||
	
	m_cameraType++;
	if(m_cameraType == 2)
	{
		m_cameraType = 0;
	}

	Log::COut("Camera mode: " + to_string(m_cameraType));
}

D3DXMATRIX CameraClass::GetWorldMatrix(){
	return m_worldMatrix;
}
////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "Log.h"
#include "PlayerClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void UpdatePosition(float, float, float);
	void UpdateRotation(float, float, float);

	float GetMoveSpeedX();
	float GetMoveSpeedY();
	float GetMoveSpeedZ();

	float GetRotationSpeedX();
	float GetRotationSpeedY();
	float GetRotationSpeedZ();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 position();

	void ToggleMoveRelative();
	void ToggleRotateRelative();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);
    void RenderReflection(float);
	void GetReflectionViewMatrix(D3DXMATRIX&);

	void ToggleOrbit();
	void ToggleCamera();
	void ToggleChase();

	float m_positionX, m_positionY, m_positionZ;
	float m_cameraType;
	float m_orbitRadius;
	float m_orbitSpeed;

	bool m_chase;
	bool m_rotate;

	void SetChasingTarget(PlayerClass* target);

	D3DXMATRIX GetWorldMatrix();

private:
	float m_moveSpeedX, m_moveSpeedY, m_moveSpeedZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float m_rotationSpeedX, m_rotationSpeedY, m_rotationSpeedZ;
	D3DXMATRIX m_viewMatrix, m_reflectionViewMatrix;

	bool m_moveRelative;
	bool m_rotateRelative;

	D3DXVECTOR3 m_startingPoint;
	D3DXVECTOR3 m_startingOrientation;
	float m_orbitAngle;

	PlayerClass* m_chasingTarget;

	D3DXMATRIX m_worldMatrix;
};

#endif
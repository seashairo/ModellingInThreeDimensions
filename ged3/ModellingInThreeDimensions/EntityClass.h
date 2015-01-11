////////////////////////////////////////////////////////////////////////////////
// Filename: EntityClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ENTITYCLASS_H_
#define _ENTITYCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <fstream>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"
#include "MeshClass.h"
#include "VertexHeader.h"
#include "ShaderManager.h"
#include "AI.h"
class AI;

////////////////////////////////////////////////////////////////////////////////
// Class name: EntityClass
////////////////////////////////////////////////////////////////////////////////
class EntityClass
{
public:
	EntityClass();
	EntityClass(const EntityClass&);
	virtual ~EntityClass();

	bool Initialize(ID3D10Device*, TextureClass*, MeshClass*);
	void Shutdown();
	void Render(ID3D10Device*);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetLastPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetLastRotation();
	ID3D10ShaderResourceView** GetTextureArray();
	ShaderManagerClass::RenderEffect GetEffect();
	void SetEffect(ShaderManagerClass::RenderEffect);

	D3DXMATRIX GetTransformMatrix();
	D3DXMATRIX GetTranslateMatrix();

	void SetPosition(float, float, float);
	void UpdatePosition(float, float, float);
	void UpdatePositionRelative(float, float, float);
	void SetScale(float);
	void SetRotation(float, float, float);
	void UpdateRotation(float, float, float);
	void UpdateRotationRelative(float, float, float);

	void SetIsRotating(bool rotate);
	bool GetIsRotating();
	void SetRotateSpeed(float, float, float);
	D3DXVECTOR3 GetRotationSpeed();

	void SetIsTranslating(bool);
	bool GetIsTranslating();
	void SetTranslateSpeed(float);
	void SetTranslateDirection(float, float, float);
	D3DXVECTOR3 GetTranslateDirection();

	void SetIsBeingControlled(bool);
	bool GetIsBeingControlled();

	void SetCanbePicked(bool);
	bool GetCanBePicked();
	float GetMeshRadius();

	AI* GetAI();
	EntityType entityType;

	bool hasMoved;

	int GetEID();

private:
	bool LoadModel(char*);
	bool LoadModel(char*, float, float, float);
	
	void ReleaseModel();

private:
	int m_vertexCount, m_indexCount;
	TextureClass* m_texture;
	MeshClass::ModelType* m_model;
	MeshClass* m_mesh;
	AI* m_AI;

	D3DXMATRIX m_transformMatrix;
	D3DXMATRIX m_translateMatrix;
	D3DXMATRIX m_scaleMatrix;
	D3DXMATRIX m_rotateMatrix;

	//Matrix transform fields
	bool m_isRotating;
	bool m_isTranslating;
	float m_scaleSpeed;
	float m_currentScale;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_lastPos;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_lastRotation;
	D3DXVECTOR3 m_rotationSpeed;
	float m_moveSpeed;

	ShaderManagerClass::RenderEffect m_effect;
	bool m_isBeingControlled;
	bool m_canBePicked;

	int m_eid;
};

#endif
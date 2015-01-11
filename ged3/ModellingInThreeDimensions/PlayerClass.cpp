#include "PlayerClass.h"

PlayerClass::PlayerClass() : EntityClass(){
	m_holdLeft = false;
	m_holdRight = false;
	m_holdUp = false;
	m_holdDown = false;
	m_holdBigger = false;
	m_holdSmaller = false;

	m_scaleSpeed = 0.00001f;
	m_moveSpeed = 2;
	m_input = 0;
	m_rotateSpeed = 0.1;
	SetRotateAngle(0);
	m_pos = D3DXVECTOR3(0,0,0);
}

void PlayerClass:: SetInput(InputClass* inputClass){
	m_input = inputClass;
}

void PlayerClass:: InputControl(){
	//rotate  left
	if(m_input->KeyJustDown(DIK_H) == true){
		m_holdLeft = true;
	}
	if(m_input->KeyJustUp(DIK_H) == true){
		m_holdLeft = false;
	}

	//rotate right
	if(m_input->KeyJustDown(DIK_K) == true){
		m_holdRight = true;
	}
	if(m_input->KeyJustUp(DIK_K) == true){
		m_holdRight = false;
	}

	//move forward
	if(m_input->KeyJustDown(DIK_U) == true){
		m_holdUp = true;
	}
	if(m_input->KeyJustUp(DIK_U) == true){
		m_holdUp = false;
	}

	//move forward
	if(m_input->KeyJustDown(DIK_J) == true){
		m_holdDown = true;
	}
	if(m_input->KeyJustUp(DIK_J) == true){
		m_holdDown = false;
	}

	//move forward
	if(m_input->KeyJustDown(DIK_LBRACKET) == true){
		m_holdSmaller = true;
	}
	if(m_input->KeyJustUp(DIK_LBRACKET) == true){
		m_holdSmaller = false;
	}

	//move forward
	if(m_input->KeyJustDown(DIK_RBRACKET) == true){
		m_holdBigger = true;
	}
	if(m_input->KeyJustUp(DIK_RBRACKET) == true){
		m_holdBigger = false;
	}

	TransformModel();
}

void PlayerClass::TransformModel(){
	if(m_holdLeft)
	{
		//m_currentAngle -= m_rotateSpeed;
		//SetRotateAngle(m_currentAngle);

		m_currentAngle -= m_rotateSpeed;
		D3DXMatrixRotationY(&m_rotateMatrix, m_currentAngle);
	}

	if(m_holdRight)
	{
		//m_currentAngle += m_rotateSpeed;
		//SetRotateAngle(m_currentAngle);

		m_currentAngle += m_rotateSpeed;
		D3DXMatrixRotationY(&m_rotateMatrix, m_currentAngle);
	}

	if(m_holdUp)
	{
		m_direction.x = cos(m_currentAngle+ 1.57f);
		m_direction.z = sin(m_currentAngle+ 1.57f);
		//D3DXVec3Normalize(&m_direction, &m_direction);
		m_pos.x -= m_direction.x * m_moveSpeed;
		m_pos.z += m_direction.z * m_moveSpeed;
		SetTranslate(m_pos.x, m_pos.y, m_pos.z);
		//Log::COut("angle : " + to_string(m_currentAngle) +" x dir " + to_string(m_direction.x ) + " z dir " +  to_string(m_direction.z ));
	}

	if(m_holdDown)
	{
		m_direction.x = cos(m_currentAngle+ 1.57f);
		m_direction.z = sin(m_currentAngle+ 1.57f);
		//D3DXVec3Normalize(&m_direction, &m_direction);
		m_pos.x += m_direction.x * m_moveSpeed;
		m_pos.z -= m_direction.z * m_moveSpeed;
		SetTranslate(m_pos.x, m_pos.y, m_pos.z);
		//Log::COut("angle : " + to_string(m_currentAngle) +" x dir " + to_string(m_direction.x ) + " z dir " +  to_string(m_direction.z ));
	}

	if(m_holdSmaller && m_currentScale >= 0)
	{
		m_currentScale -= m_scaleSpeed;
		SetScale(m_currentScale);
	}

	if(m_holdBigger)
	{
		m_currentScale += m_scaleSpeed;
		SetScale(m_currentScale);
	}
}
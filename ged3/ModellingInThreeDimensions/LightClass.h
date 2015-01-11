////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "Log.h"

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

/////////////////////////////////////////////////////////////////////////////////////////////
//	Setters: Set light direction, ambient and diffuse color, and toggle between light colors
/////////////////////////////////////////////////////////////////////////////////////////////

	void SetLightDirection(float, float, float);

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	void SetLightToggle(int);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Getters: Returns the value of the light direction, ambient and diffuse color, and the currently toggled light color
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR3 GetLightDirection();

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();

	int GetLightToggle();
	
	//Shadow helpers
	D3DXVECTOR3 GetPosition();
	void SetPosition(float, float, float);
	void SetLookAt(float, float, float);
	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float, float);
	void GetViewMatrix(D3DXMATRIX&);
	void GetProjectionMatrix(D3DXMATRIX&);

private:

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Private variables: Variables containing the values for light direction, ambient and diffuse color and the current toggled light color
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR3 m_lightDirection;

	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;

	//Shadow variables
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_lookAt;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;

	int m_lightToggle;
};

#endif
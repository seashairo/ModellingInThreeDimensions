#include "lightclass.h"



LightClass::LightClass(){
}

LightClass::LightClass(const LightClass& other){
}

LightClass::~LightClass(){
}


//	Setters: Set light direction, ambient and diffuse color, and toggle between light colors
void LightClass::SetLightDirection(float x, float y, float z){
	m_lightDirection = D3DXVECTOR3(x, y, z);
	return;
}

void LightClass::SetAmbientColor(float r, float g, float b, float a){
	m_ambientColor = D3DXVECTOR4(r, g, b, a);
	return;
}

void LightClass::SetDiffuseColor(float r, float g, float b, float a){
	m_diffuseColor = D3DXVECTOR4(r, g, b, a);
	Log::COut("Diffuse Light Colour set to " + to_string(r) + " " + to_string(g) + " " + to_string(b) + " " + to_string(a));
	return;
}

void LightClass::SetSpecularColor(float r, float g, float b, float a){
	m_specularColor = D3DXVECTOR4(r, g, b, a);
	Log::COut("Specular Light Colour set to " + to_string(r) + " " + to_string(g) + " " + to_string(b) + " " + to_string(a));
	return;
}

void LightClass::SetSpecularPower(float power){
	m_specularPower = power;
	Log::COut("Specular Power set to " + to_string(power));
	return;
}

void LightClass::SetLightToggle(int x){
	m_lightToggle = x;
	return;
}

//	Getters: Returns the value of the light direction, ambient and diffuse color, and the currently toggled light color
D3DXVECTOR3 LightClass::GetLightDirection(){
	return m_lightDirection;
}

D3DXVECTOR4 LightClass::GetAmbientColor(){
	return m_ambientColor;
}

D3DXVECTOR4 LightClass::GetDiffuseColor(){
	return m_diffuseColor;
}

D3DXVECTOR4 LightClass::GetSpecularColor(){
	return m_specularColor;
}

float LightClass::GetSpecularPower(){
	return m_specularPower;
}

int LightClass::GetLightToggle(){
	return m_lightToggle;
}

//Shadow 
void LightClass::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR3(x, y, z);
	return;
}

D3DXVECTOR3 LightClass::GetPosition()
{
	return m_position;
}

void LightClass::SetLookAt(float x, float y, float z)
{
	m_lookAt.x = x;
	m_lookAt.y = y;
	m_lookAt.z = z;
	return;
}

void LightClass::GenerateViewMatrix()
{
	D3DXVECTOR3 up;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Create the view matrix from the three vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &up);
	
	return;
}

void LightClass::GenerateProjectionMatrix(float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;


	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)D3DX_PI / 2.0f;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	return;
}


void LightClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void LightClass::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}


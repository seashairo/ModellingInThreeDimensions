#include "lightshaderclass.h"


// Initialize the variables. Set all the pointers to 0 to initialize them.
LightShaderClass::LightShaderClass(){
	m_effect = 0;
	m_technique = 0;
	m_layout = 0;

	m_worldMatrixPtr = 0;
	m_viewMatrixPtr = 0;
	m_projectionMatrixPtr = 0;
	m_textureArrayPtr = 0;

	m_ambientColorPtr = 0;
	m_diffuseColorPtr = 0;
	m_lightDirectionPtr = 0;

	cameraPositionPtr = 0;
	specularColorPtr = 0;
	specularPowerPtr = 0;
}

LightShaderClass::LightShaderClass(const LightShaderClass& other){
}

LightShaderClass::~LightShaderClass(){
}

// Initializes the light.fx shader file
bool LightShaderClass::Initialize(ID3D10Device* device, HWND hwnd){
	bool result;

	result = InitializeShader(device, hwnd, L"../ModellingInThreeDimensions/data/light.fx");
	if(!result)
	{
		return false;
	}

	return true;
}

// Shutsdown the shader
void LightShaderClass::Shutdown(){
	ShutdownShader();
	return;
}

// Takes the required variables to set the shader parameters and render the buffers using the shader file
void LightShaderClass::Render(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
							  ID3D10ShaderResourceView** textureArray, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition,
								D3DXVECTOR4 specularColor, float specularPower){
	
	SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, textureArray, lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
	RenderShader(device, indexCount, vertexCount, instanceCount);
	return;
}

// Loads the shader in from the file and gets the pointers to the variables within the shader
// Complete with error feedback and debugging
bool LightShaderClass::InitializeShader(ID3D10Device* device, HWND hwnd, WCHAR* filename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[6];
	unsigned int numElements;
    D3D10_PASS_DESC passDesc;

	// Initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	result = D3DX10CreateEffectFromFile(filename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
										device, NULL, NULL, &m_effect, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			Log::COut("Shader failed to compile");
			Log::COut((char*)(errorMessage->GetBufferPointer()));

			// Release the error message.
			errorMessage->Release();
			errorMessage = 0;
		}
		
		else
		{
			Log::COut("Missing shader file");
		}

		return false;
	}

	// Get a pointer to the technique inside the shader.
	m_technique = m_effect->GetTechniqueByName("LightTechnique");
	if(!m_technique)
	{
		return false;
	}

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TESTCOORD";
	polygonLayout[3].SemanticIndex = 1;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[3].InputSlot = 1;
	polygonLayout[3].AlignedByteOffset = 0;
	polygonLayout[3].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[3].InstanceDataStepRate = 1;

	polygonLayout[4].SemanticName = "TANGENT";
	polygonLayout[4].SemanticIndex = 0;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[4].InputSlot = 0;
	polygonLayout[4].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[4].InstanceDataStepRate = 0;

	polygonLayout[5].SemanticName = "BINORMAL";
	polygonLayout[5].SemanticIndex = 0;
	polygonLayout[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[5].InputSlot = 0;
	polygonLayout[5].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[5].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[5].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
    numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Get the description of the first pass described in the shader technique.
    m_technique->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
    result = device->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_layout);
	if(FAILED(result))
	{
		return false;
	}

	// Get pointers to the variables within the shader
    m_worldMatrixPtr = m_effect->GetVariableByName("worldMatrix")->AsMatrix();
	m_viewMatrixPtr = m_effect->GetVariableByName("viewMatrix")->AsMatrix();
    m_projectionMatrixPtr = m_effect->GetVariableByName("projectionMatrix")->AsMatrix();

	m_textureArrayPtr = m_effect->GetVariableByName("shaderTexture")->AsShaderResource();

	m_lightDirectionPtr = m_effect->GetVariableByName("lightDirection")->AsVector();

	m_ambientColorPtr = m_effect->GetVariableByName("ambientColor")->AsVector();
	m_diffuseColorPtr = m_effect->GetVariableByName("diffuseColor")->AsVector();

	cameraPositionPtr = m_effect->GetVariableByName("cameraPosition")->AsVector();
	specularColorPtr = m_effect->GetVariableByName("specularColor")->AsVector();
	specularPowerPtr = m_effect->GetVariableByName("specularPower")->AsScalar();

	return true;
}

// Shutdowns the shader by releasing all the pointers
void LightShaderClass::ShutdownShader()
{
	m_worldMatrixPtr = 0;
	m_viewMatrixPtr = 0;
	m_projectionMatrixPtr = 0;

	m_textureArrayPtr = 0;

	m_lightDirectionPtr = 0;

	m_ambientColorPtr = 0;
	m_diffuseColorPtr = 0;

	cameraPositionPtr = 0;
	specularColorPtr = 0;
	specularPowerPtr = 0;

	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	m_technique = 0;

	if(m_effect)
	{
		m_effect->Release();
		m_effect = 0;
	}

	return;
}

// Sets the required variables within the shader
void LightShaderClass::SetShaderParameters(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
										   ID3D10ShaderResourceView** textureArray, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
										   D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower){

	m_worldMatrixPtr->SetMatrix((float*)&worldMatrix);
	m_viewMatrixPtr->SetMatrix((float*)&viewMatrix);
    m_projectionMatrixPtr->SetMatrix((float*)&projectionMatrix);

	m_textureArrayPtr->SetResourceArray(textureArray, 0, 2);

	m_lightDirectionPtr->SetFloatVector((float*)&lightDirection);

	m_ambientColorPtr->SetFloatVector((float*)&ambientColor);
	m_diffuseColorPtr->SetFloatVector((float*)&diffuseColor);

	cameraPositionPtr->SetFloatVector((float*)&cameraPosition);
	specularColorPtr->SetFloatVector((float*)&specularColor);
	specularPowerPtr->SetFloat(specularPower);

	return;
}

// Runs through each pass in the technique to render the scene using the shader
void LightShaderClass::RenderShader(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount){

	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;
	device->IASetInputLayout(m_layout);
	m_technique->GetDesc(&techniqueDesc);

	for(i=0; i<techniqueDesc.Passes; ++i)
    {
        m_technique->GetPassByIndex(i)->Apply(0);
        device->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
    }

	return;
}
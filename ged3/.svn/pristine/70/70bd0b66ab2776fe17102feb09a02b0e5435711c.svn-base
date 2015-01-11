#include "GlassShaderClass.h"

// Initialize the variables. Set all the pointers to 0 to initialize them.
GlassShaderClass::GlassShaderClass(){
}

GlassShaderClass::GlassShaderClass(const GlassShaderClass& other){
}

GlassShaderClass::~GlassShaderClass(){
}

// Shutsdown the shader
void GlassShaderClass::ShutdownShader(){
	m_effects = 0;

	m_worldMatrixPtr = 0;
	m_viewMatrixPtr = 0;
	m_projectionMatrixPtr = 0;
	m_texturePtr = 0;

	m_ambientColorPtr = 0;
	m_diffuseColorPtr = 0;
	m_lightDirectionPtr = 0;

	m_cameraPositionPtr = 0;
	m_specularColorPtr = 0;
	m_specularPowerPtr = 0;
}

// Shutsdown the shader
void GlassShaderClass::Shutdown(){
	ShutdownShader();
	return;
}

void GlassShaderClass::Initialize(ID3D10Device* device){
	HRESULT result;
	ID3D10Blob* errorMessage;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[5];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;


	// Initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	result = D3DX10CreateEffectFromFile(L"../ModellingInThreeDimensions/data/glass.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
		device, NULL, NULL, &m_effects, &errorMessage, NULL);
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
	}

	// Get a pointer to the technique inside the shader.
	m_techniques = m_effects->GetTechniqueByName("GlassTechnique");
	if(!m_techniques)
	{
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

	polygonLayout[3].SemanticName = "TANGENT";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[3].InputSlot = 0;
	polygonLayout[3].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[3].InstanceDataStepRate = 0;

	polygonLayout[4].SemanticName = "BINORMAL";
	polygonLayout[4].SemanticIndex = 0;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[4].InputSlot = 0;
	polygonLayout[4].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[4].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
    numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Get the description of the first pass described in the shader technique.
	m_techniques->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_Layouts);

	// Get pointers to the three matrices inside the shader so they can be updated from this class.
	m_worldMatrixPtr = m_effects->GetVariableByName("worldMatrix")->AsMatrix();
	m_viewMatrixPtr = m_effects->GetVariableByName("viewMatrix")->AsMatrix();
	m_projectionMatrixPtr = m_effects->GetVariableByName("projectionMatrix")->AsMatrix();

	// Get pointers to the texture resources inside the shader.
	m_texturePtr = m_effects->GetVariableByName("shaderTexture")->AsShaderResource();
	m_refractionTexturePtr =  m_effects->GetVariableByName("refractionTexture")->AsShaderResource();

	// Get a pointer to the refraction scale variable inside the shader.
	m_refractionScalePtr = m_effects->GetVariableByName("refractionScale")->AsScalar();

}

//Render generally
void GlassShaderClass::RenderGlass(ID3D10Device* device, int indexCount, int vertexCount, int instanceCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
							  ID3D10ShaderResourceView** textures,ID3D10ShaderResourceView* refractionTexture, float refractionScale)
{
	// Set the world matrix variable inside the shader.
	m_worldMatrixPtr->SetMatrix((float*)&worldMatrix);

	// Set the view matrix variable inside the shader.
	m_viewMatrixPtr->SetMatrix((float*)&viewMatrix);

	// Set the projection matrix variable inside the shader.
	m_projectionMatrixPtr->SetMatrix((float*)&projectionMatrix);

	m_texturePtr->SetResourceArray(textures, 0, 2);

	m_refractionTexturePtr->SetResource(refractionTexture);

		// Set the refraction scale variable inside the shader.
	m_refractionScalePtr->SetFloat(refractionScale);

	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;
	device->IASetInputLayout(m_Layouts);
	m_techniques->GetDesc(&techniqueDesc);
	for(i=0; i<techniqueDesc.Passes; ++i)
    {
        m_techniques->GetPassByIndex(i)->Apply(0);
        device->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
    }

	return;
}


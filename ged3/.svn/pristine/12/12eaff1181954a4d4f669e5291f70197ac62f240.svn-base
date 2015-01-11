////////////////////////////////////////////////////////////////////////////////
// Filename: foliageshaderclass.cpp
//http://www.rastertek.com/terdx10tut19.html Used for Reference.
////////////////////////////////////////////////////////////////////////////////
#include "FoliageShaderClass.h"


FoliageShaderClass::FoliageShaderClass(void)
{
	m_effect = 0;
	m_technique = 0;
	m_layout = 0;

	m_viewMatrixPtr = 0;
	m_projectionMatrixPtr = 0;
	m_texturePtr = 0;
}


FoliageShaderClass::FoliageShaderClass(const FoliageShaderClass& other)
{
}

FoliageShaderClass::~FoliageShaderClass(void)
{
}

bool FoliageShaderClass::Initialize(ID3D10Device* device)
{
	bool result;

	result = InitializeShader(device, L"../ModellingInThreeDimensions/data/foliage/foliage.fx");

	return true;
}

void FoliageShaderClass::Shutdown()
{
	ShutdownShader();

	return;
}

void FoliageShaderClass::Render(ID3D10Device* device, int vertexCount, int instanceCount, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D10ShaderResourceView* texture)
{
	SetShaderParameters(viewMatrix, projectionMatrix, texture);
	RenderShader(device, vertexCount, instanceCount);

	return;
}

bool FoliageShaderClass::InitializeShader(ID3D10Device* device, WCHAR* filename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[7];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;

	errorMessage = 0;

	result = D3DX10CreateEffectFromFile(filename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, device, NULL, NULL, &m_effect, &errorMessage, NULL);

	if(FAILED(result))
	{
		
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, filename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			
		}

		return false;

	}

	// Get a pointer to the technique inside the shader.
	m_technique = m_effect->GetTechniqueByName("FoliageTechnique");
	if(!m_technique)
	{
		return false;
	}

	// Now setup the layout of the data that goes into the shader.
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

	polygonLayout[2].SemanticName = "WORLD";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = 0;
	polygonLayout[2].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	polygonLayout[3].SemanticName = "WORLD";
	polygonLayout[3].SemanticIndex = 1;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[3].InputSlot = 1;
	polygonLayout[3].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[3].InstanceDataStepRate = 1;

	polygonLayout[4].SemanticName = "WORLD";
	polygonLayout[4].SemanticIndex = 2;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[4].InputSlot = 1;
	polygonLayout[4].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[4].InstanceDataStepRate = 1;

	polygonLayout[5].SemanticName = "WORLD";
	polygonLayout[5].SemanticIndex = 3;
	polygonLayout[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[5].InputSlot = 1;
	polygonLayout[5].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[5].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[5].InstanceDataStepRate = 1;

	polygonLayout[6].SemanticName = "TEXCOORD";
	polygonLayout[6].SemanticIndex = 1;
	polygonLayout[6].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[6].InputSlot = 1;
	polygonLayout[6].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[6].InputSlotClass = D3D10_INPUT_PER_INSTANCE_DATA;
	polygonLayout[6].InstanceDataStepRate = 1;

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

	// Get pointers to the matrices inside the shader so we can update them from this class.
	m_viewMatrixPtr = m_effect->GetVariableByName("viewMatrix")->AsMatrix();
	m_projectionMatrixPtr = m_effect->GetVariableByName("projectionMatrix")->AsMatrix();

	// Get pointer to the texture resource inside the shader.
	m_texturePtr = m_effect->GetVariableByName("shaderTexture")->AsShaderResource();

	return true;
}

void FoliageShaderClass::ShutdownShader()
{
	// Release the pointer to the texture in the shader file.
	m_texturePtr = 0;

	// Release the pointers to the matrices inside the shader.
	m_viewMatrixPtr = 0;
	m_projectionMatrixPtr = 0;

	// Release the pointer to the shader layout.
	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pointer to the shader technique.
	m_technique = 0;

	// Release the pointer to the shader.
	if(m_effect)
	{
		m_effect->Release();
		m_effect = 0;
	}

	return;
}

void FoliageShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;
	
	return;
}

void FoliageShaderClass::SetShaderParameters(D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D10ShaderResourceView* texture)
{
	// Set the view matrix variable inside the shader.
	m_viewMatrixPtr->SetMatrix((float*)&viewMatrix);

	// Set the projection matrix variable inside the shader.
	m_projectionMatrixPtr->SetMatrix((float*)&projectionMatrix);

	// Bind the texture.
	m_texturePtr->SetResource(texture);

	return;
}

void FoliageShaderClass::RenderShader(ID3D10Device* device, int vertexCount, int instanceCount)
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;
	

	// Set the input layout.
	device->IASetInputLayout(m_layout);

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	m_technique->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just one currently) and render the triangles.
	for(i=0; i<techniqueDesc.Passes; ++i)
	{
		m_technique->GetPassByIndex(i)->Apply(0);
		device->DrawInstanced(vertexCount, instanceCount, 0, 0);
	}

	return;
}
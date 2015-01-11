#include "textureclass.h"

TextureClass::TextureClass(){
	//Our texture class only supports up to 4 textures per entity
	m_textures[0] = 0;
	m_textures[1] = 0;
	m_textures[2] = 0;
	m_textures[3] = 0;
}

TextureClass::TextureClass(const TextureClass& other){
}

TextureClass::~TextureClass(){
}

bool TextureClass::InitTexture(ID3D10Device* device, WCHAR* filename){
	HRESULT result;

	// Load the first texture in.
	result = D3DX10CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_textures[0], NULL);
	if(FAILED(result))
	{
		return false;
	}
	return true;
}

bool TextureClass::InitTexture(ID3D10Device* device, WCHAR* f1, WCHAR* f2){
	HRESULT result;

	// Load the first texture in.
	result = D3DX10CreateShaderResourceViewFromFile(device, f1, NULL, NULL, &m_textures[0], NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	if(!f2 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f2, NULL, NULL, &m_textures[1], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}

	return true;
}

bool TextureClass::InitTexture(ID3D10Device* device, WCHAR* f1, WCHAR* f2, WCHAR* f3){
	HRESULT result;

	// Load the first texture in.
	result = D3DX10CreateShaderResourceViewFromFile(device, f1, NULL, NULL, &m_textures[0], NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	if(!f2 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f2, NULL, NULL, &m_textures[1], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}
	// Load the third texture in.
	if(!f3 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f3, NULL, NULL, &m_textures[2], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}

	return true;
}

bool TextureClass::InitTexture(ID3D10Device* device, WCHAR* f1, WCHAR* f2
									   , WCHAR* f3, WCHAR* f4){
	HRESULT result;

	// Load the first texture in.
	result = D3DX10CreateShaderResourceViewFromFile(device, f1, NULL, NULL, &m_textures[0], NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Load the second texture in.
	if(!f2 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f2, NULL, NULL, &m_textures[1], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}
		// Load the third texture in.
	if(!f3 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f3, NULL, NULL, &m_textures[2], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}
		// Load the third texture in.
	if(!f4 == NULL){
		result = D3DX10CreateShaderResourceViewFromFile(device, f4, NULL, NULL, &m_textures[3], NULL);
		if(FAILED(result))
		{
			return false;
		}
	}

	return true;
}

bool TextureClass::InitCubeTexture(ID3D10Device* device, WCHAR* f1)
{
	HRESULT result;

	D3DX10_IMAGE_LOAD_INFO loadInfo;
	loadInfo.MiscFlags = D3D10_RESOURCE_MISC_TEXTURECUBE;

	ID3D10Texture2D* tex = 0;
	result = D3DX10CreateTextureFromFile(device, f1, 
	&loadInfo, 0, (ID3D10Resource**)&tex, 0);

	if(FAILED(result))
	{
		MessageBox(0, L"Load cube texture - Failed",
			L"Error", MB_OK);
		return false;
	}

	D3D10_TEXTURE2D_DESC SMTextureDesc;
	tex->GetDesc(&SMTextureDesc);

	D3D10_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	result = device->CreateShaderResourceView(tex, &SMViewDesc, &m_textures[0]);

	if(FAILED(result))
	{
		MessageBox(0, L"Create Cube Texture RV - Failed",
			L"Error", MB_OK);
		return false;
	}
	tex->Release();
}

void TextureClass::Shutdown(){
	// Release the texture resources.
	if(m_textures[0])
	{
		m_textures[0]->Release();
		m_textures[0] = 0;
	}
	if(m_textures[1])
	{
		m_textures[1]->Release();
		m_textures[1] = 0;
	}
	if(m_textures[2])
	{
		m_textures[2]->Release();
		m_textures[2] = 0;
	}
	if(m_textures[3])
	{
		m_textures[2]->Release();
		m_textures[2] = 0;
	}
	return;
}

ID3D10ShaderResourceView** TextureClass::GetTextureArray(){
	return m_textures;
}
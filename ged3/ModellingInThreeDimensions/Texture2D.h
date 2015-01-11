#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

// Includes
#include <d3dx10.h>
#include <d3dx10math.h>

// My Includes
#include "TextureClass.h"

// Class
class Texture2D{
public:
	struct TextureVertex{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	Texture2D();

	bool Initialize(ID3D10Device*, int, int, TextureClass*, int, int);
	void Shutdown();
	bool Render(ID3D10Device*, int, int);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(int, int);
	void RenderBuffers(ID3D10Device*);

private:
	ID3D10Buffer *m_vertexBuffer;
	ID3D10Buffer *m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	TextureClass* m_Texture;

	int m_screenWidth;
	int m_screenHeight;
	int m_textureWidth;
	int m_textureHeight;
	int m_previousPosX;
	int m_previousPosY;
};

#endif
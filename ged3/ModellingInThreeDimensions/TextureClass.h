////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d10.h>
#include <d3dx10.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool InitTexture(ID3D10Device*, WCHAR*);
	bool InitTexture(ID3D10Device*, WCHAR*, WCHAR*);
	bool InitTexture(ID3D10Device*, WCHAR*, WCHAR*, WCHAR*);
	bool InitTexture(ID3D10Device*, WCHAR*, WCHAR*, WCHAR*, WCHAR*);
	bool InitCubeTexture(ID3D10Device*, WCHAR*);
	void Shutdown();

	ID3D10ShaderResourceView** GetTextureArray();

private:
	ID3D10ShaderResourceView* m_textures[3];
};

#endif
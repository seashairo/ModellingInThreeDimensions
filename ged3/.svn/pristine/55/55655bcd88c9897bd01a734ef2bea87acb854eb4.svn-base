// Much of the content and design of this code is based upon Rastertek's DirectX Tutorials, particularly http://www.rastertek.com/dx11tut14.html and http://www.rastertek.com/dx11tut31.html

#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "InputClass.h"
#include "GraphicsClass.h"

class SoundClass
{
private:


	struct position
	{
		float x;
		float y;
		float z;
	};

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:
	SoundClass(InputClass* m_Input, GraphicsClass* graphicsReference);
	SoundClass(const SoundClass&);
	~SoundClass();
	bool Initialize(HWND);
	void Shutdown();
	void PlayFromEntity(string soundName, GraphicsClass::position entityPosition);
	bool PlayMusic();
	bool Frame();
	void CheckFlags();
 
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
	bool Play(int m_volume, IDirectSoundBuffer8** m_buffer, IDirectSound3DBuffer8** m_3DBuffer, GraphicsClass::position m_position, 
			  bool isMusic, bool isLooping);
	bool Load(char*, IDirectSoundBuffer8**, IDirectSound3DBuffer8**, bool isMusic);
	void Shutdown(IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**, 
				  IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**, IDirectSoundBuffer8**,
				  IDirectSound3DBuffer8**, IDirectSound3DBuffer8**, IDirectSound3DBuffer8**, IDirectSound3DBuffer8**, 
				  IDirectSound3DBuffer8**, IDirectSound3DBuffer8**);
	bool SetEffect(string effectName);
	
 
private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_musicBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	IDirectSoundBuffer8* m_secondaryBuffer2;
	IDirectSoundBuffer8* m_secondaryBuffer3;
	IDirectSoundBuffer8* m_secondaryBuffer4;
	IDirectSoundBuffer8* m_secondaryBuffer5;
	IDirectSoundBuffer8* m_secondaryBuffer6;
	IDirectSoundBuffer8* m_secondaryBuffer7;
	IDirectSoundBuffer8* m_secondaryBuffer8;
	IDirectSoundBuffer8* m_secondaryBuffer9;

	IDirectSound3DBuffer8* m_secondary3DBuffer1;
	IDirectSound3DBuffer8* m_secondary3DBuffer2;
	IDirectSound3DBuffer8* m_secondary3DBuffer3;
	IDirectSound3DBuffer8* m_secondary3DBuffer4;
	IDirectSound3DBuffer8* m_secondary3DBuffer5;
	IDirectSound3DBuffer8* m_music3DBuffer;

	IDirectSound3DListener8* m_listener;

	int m_volume;
	long m_pan;
	GraphicsClass::position m_position;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	string m_effectName;
	GraphicsClass::position m_ListenerPos;
	bool m_musicToggle;
	bool m_previouslyUnderwater;
	bool m_currentlyUnderwater;
	bool m_musicPlaying;
	GraphicsClass::position m_motorPosition;

	D3DXVECTOR3 m_cameraRotation;
	D3DXVECTOR3 m_rotatedVector;
	D3DXMATRIX m_rotationMatrix;
};
 
#endif
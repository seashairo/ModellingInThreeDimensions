#include "soundclass.h"

// Much of the content and design of this code is based upon Rastertek's DirectX Tutorials, particularly http://www.rastertek.com/dx11tut14.html and http://www.rastertek.com/dx11tut31.html

SoundClass::SoundClass(InputClass* input, GraphicsClass* gReference)
{

	//Master Settings
	m_volume = 0;
	m_pan = 0;
	m_musicToggle = true;	
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	//Pointers to required Classes
	m_Input = input;
	m_Graphics = gReference;

	//Position of the motor sound effect
	m_motorPosition.x = 12;
	m_motorPosition.y = 17;
	m_motorPosition.z = 8;

	//Initialize Variabes for Listener Orientation

	m_cameraRotation;
	m_rotatedVector;
	m_rotatedVector.x = 0;
	m_rotatedVector.y = 0;
	m_rotatedVector.z = 1;
	m_rotationMatrix;
	
}
 
 
SoundClass::SoundClass(const SoundClass& other)
{

}
 
 
SoundClass::~SoundClass()
{
}
 
 
bool SoundClass::Initialize(HWND hwnd)
{

	
	bool result;
	// Initialize direct sound and the primary sound buffer.
	result = InitializeDirectSound(hwnd);
	if(!result)
	{
		return false;
	}


	// Load audio files into buffers
	Load("../ModellingInThreeDimensions/data/sound/ambientWater_uw.wav", &m_secondaryBuffer1, &m_music3DBuffer, true);
	Load("../ModellingInThreeDimensions/data/sound/music.wav", &m_musicBuffer, &m_music3DBuffer, true);
	Load("../ModellingInThreeDimensions/data/sound/motor_uw.wav", &m_secondaryBuffer2, &m_secondary3DBuffer1, false);
	Load("../ModellingInThreeDimensions/data/sound/motor.wav", &m_secondaryBuffer3, &m_secondary3DBuffer1, false);
	Load("../ModellingInThreeDimensions/data/sound/splashFromWater.wav", &m_secondaryBuffer4, &m_music3DBuffer, true);
	Load("../ModellingInThreeDimensions/data/sound/splashToWater.wav", &m_secondaryBuffer5, &m_music3DBuffer, true);
	Load("../ModellingInThreeDimensions/data/sound/fishSwim_uw.wav", &m_secondaryBuffer6, &m_secondary3DBuffer2, false);
	Load("../ModellingInThreeDimensions/data/sound/fishSwim2_uw.wav", &m_secondaryBuffer7, &m_secondary3DBuffer3, false);
	Load("../ModellingInThreeDimensions/data/sound/manyFishSwim_uw.wav", &m_secondaryBuffer8, &m_secondary3DBuffer4, false);
	Load("../ModellingInThreeDimensions/data/sound/JawsSound.wav", &m_secondaryBuffer9, &m_secondary3DBuffer5, false);
	
	//Start Playing Music
	Play(m_volume-2000, &m_musicBuffer, &m_music3DBuffer, m_position,true, true);

	//Determine if initial state is underwater and play sounds
	m_currentlyUnderwater = m_Graphics->CheckUnderwater();

	if(m_currentlyUnderwater){
		Play(m_volume-1000, &m_secondaryBuffer1, &m_music3DBuffer, m_position, true, true);
		Play(m_volume, &m_secondaryBuffer2, &m_secondary3DBuffer1, m_motorPosition, false, true);
	}

	else{
		Play(m_volume, &m_secondaryBuffer3, &m_secondary3DBuffer1, m_motorPosition, false, true);
	}

	return true;
	
	
}

bool SoundClass::Frame()
{
	//Set The orientation and position of the listener
	m_cameraRotation = m_Graphics->m_Camera->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&m_rotationMatrix, m_cameraRotation.y, m_cameraRotation.x, m_cameraRotation.z);
	D3DXVec3TransformCoord(&m_rotatedVector, &m_rotatedVector, &m_rotationMatrix);
	m_listener->SetOrientation(m_rotatedVector.x, m_rotatedVector.y, m_rotatedVector.z, 0, 0, 0, DS3D_IMMEDIATE);
	m_ListenerPos = m_Graphics->GetCameraPosition();
	m_listener->SetPosition(m_ListenerPos.x, m_ListenerPos.y, m_ListenerPos.z, DS3D_IMMEDIATE);
	m_position = m_Graphics->GetCameraPosition();

	//set uderwater state
	m_previouslyUnderwater = m_currentlyUnderwater;
	m_currentlyUnderwater = m_Graphics->CheckUnderwater();

	//Check for change in underwater state
	if(!m_previouslyUnderwater && m_currentlyUnderwater){
		
		m_secondaryBuffer3->Stop();

		Play(m_volume, &m_secondaryBuffer5, &m_music3DBuffer, m_position, true, false);
		Play(m_volume-1000, &m_secondaryBuffer1, &m_music3DBuffer, m_position, true, true);
		Play(m_volume, &m_secondaryBuffer2, &m_secondary3DBuffer1, m_motorPosition, false, true);
	}

	if(m_previouslyUnderwater && !m_currentlyUnderwater){ 
		
		m_secondaryBuffer2->Stop();
		m_secondaryBuffer1->Stop();

		Play(m_volume, &m_secondaryBuffer4, &m_music3DBuffer, m_position, true, false);
		Play(m_volume, &m_secondaryBuffer3, &m_secondary3DBuffer1, m_motorPosition, false, true);
	}

	if(m_Input->KeyJustDown(DIK_F5) == true){
		m_secondaryBuffer3->Stop();
	}
	

	//Check for music toggle
	if(m_Input->KeyJustDown(DIK_R) == true){
		m_musicToggle = !m_musicToggle;}

	if(!m_musicToggle){
		m_musicBuffer->Stop();
		m_musicPlaying = false;
	}

	if(m_musicToggle && !m_musicPlaying){
		Play(m_volume-2000, &m_musicBuffer, &m_music3DBuffer, m_position,true, true);
		m_musicPlaying = true;
	}

	CheckFlags();

	return true;
}

//Used to play sounds from other classes
void SoundClass::PlayFromEntity(string soundName, GraphicsClass::position entityPosition)
{
	if(soundName == "jaws")
	{
		Play(m_volume, &m_secondaryBuffer9, &m_secondary3DBuffer5, entityPosition, false, false);
	}

	else if(soundName == "fishSwim")
	{
		Play(m_volume, &m_secondaryBuffer6, &m_secondary3DBuffer2, entityPosition, false, false);
	}

	else if(soundName == "fishSwimShort")
	{
		Play(m_volume, &m_secondaryBuffer7, &m_secondary3DBuffer3, entityPosition, false, false);
	}

	else if(soundName == "manyFishSwim")
	{
		Play(m_volume, &m_secondaryBuffer8, &m_secondary3DBuffer4, entityPosition, false, false);
	}
}

void SoundClass::Shutdown()
{
	// Release the secondary buffers.
	Shutdown(&m_secondaryBuffer1, &m_secondaryBuffer2, &m_secondaryBuffer3, &m_secondaryBuffer4, &m_secondaryBuffer5,
			 &m_secondaryBuffer6, &m_secondaryBuffer7, &m_secondaryBuffer8, &m_secondaryBuffer9, &m_musicBuffer,
			 &m_secondary3DBuffer1, &m_secondary3DBuffer2, &m_secondary3DBuffer3, &m_secondary3DBuffer4,
			 &m_secondary3DBuffer5, &m_music3DBuffer);

	// Shutdown the Direct Sound API.
	ShutdownDirectSound();
 
	return;
}

bool SoundClass::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
 
 
	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if(FAILED(result))
	{
		return false;
	}
 
	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
 
	// Get control of the primary sound buffer on the default sound device.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the format of the primary sound bufffer.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if(FAILED(result))
	{
		return false;
	}

	// Obtain a listener interface.
	result = m_primaryBuffer->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&m_listener);
	if(FAILED(result))
	{
		return false;
	}

	// Set the initial position of the listener to be in the middle of the scene.
	m_listener->SetPosition(0.0f, 0.0f, 0.0f, DS3D_IMMEDIATE);
 
	return true;
}

void SoundClass::ShutdownDirectSound()
{
	// Release the listener interface.
	if(m_listener)
	{
		m_listener->Release();
		m_listener = 0;
	}

	// Release the primary sound buffer pointer.
	if(m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}
 
	// Release the direct sound interface pointer.
	if(m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}
 
	return;
}

bool SoundClass::Load(char* filename, IDirectSoundBuffer8** secondaryBuffer, IDirectSound3DBuffer8** secondary3DBuffer, bool isMusic)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}
 
	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if(count != 1)
	{
		return false;
	}
 
	// Check that the chunk ID is the RIFF format.
	if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') || 
	   (waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}
 
	// Check that the file format is the WAVE format.
	if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
	   (waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}
 
	// Check that the sub chunk ID is the fmt format.
	if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
	   (waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}
 
	// Check that the audio format is WAVE_FORMAT_PCM.
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}
 
	// Check that the wave file was recorded in mono format.
	if(waveFileHeader.numChannels != 1)
	{
		return false;
	}
 
	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if(waveFileHeader.sampleRate != 44100)
	{
		return false;
	}
 
	// Ensure that the wave file was recorded in 16 bit format.
	if(waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}
 
	// Check for the data chunk header.
	if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
	   (waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 1;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	if(!isMusic){
		bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;} //| DSBCAPS_CTRLPAN | DSBCAPS_CTRLFX 
	else { bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;}
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	//SOUND02 FAILING HERE
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}
 
	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if(FAILED(result))
	{
		return false;
	}
 
	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);
 
	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if(!waveData)
	{
		return false;
	}
 
	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if(count != waveFileHeader.dataSize)
	{
		return false;
	}
 
	// Close the file once done reading.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}
 
	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		return false;
	}
 
	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);
 
	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		return false;
	}
	
	// Release the wave data since it was copied into the secondary buffer.
	delete [] waveData;
	waveData = 0;
 
	// Get the 3D interface to the secondary sound buffer.
	result = (*secondaryBuffer)->QueryInterface(IID_IDirectSound3DBuffer8, (void**)&*secondary3DBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void SoundClass::Shutdown(IDirectSoundBuffer8** secondary1, IDirectSoundBuffer8** secondary2, IDirectSoundBuffer8** secondary3, IDirectSoundBuffer8** secondary4, 
						  IDirectSoundBuffer8** secondary5, IDirectSoundBuffer8** secondary6, IDirectSoundBuffer8** secondary7, IDirectSoundBuffer8** secondary8, 
						  IDirectSoundBuffer8** secondary9, IDirectSoundBuffer8** secondary10,
						  IDirectSound3DBuffer8** secondary3d1, IDirectSound3DBuffer8** secondary3d2, IDirectSound3DBuffer8** secondary3d3, 
						  IDirectSound3DBuffer8** secondary3d4, IDirectSound3DBuffer8** secondary3d5, IDirectSound3DBuffer8** secondary3d6)
{

	// Release the 3D interfaces to the secondary sound buffers.
		
	if(*secondary3d1){
		(*secondary3d1)->Release();
		*secondary3d1 = 0;}
	if(*secondary3d2){
		(*secondary3d2)->Release();
		*secondary3d2 = 0;}
	if(*secondary3d3){
		(*secondary3d3)->Release();
		*secondary3d3 = 0;}
	if(*secondary3d4){
		(*secondary3d4)->Release();
		*secondary3d4 = 0;}
	if(*secondary3d5){
		(*secondary3d5)->Release();
		*secondary3d5 = 0;}
	if(*secondary3d6){
		(*secondary3d6)->Release();
		*secondary3d6 = 0;}

	// Release the secondary sound buffer.
	if(*secondary1){
		(*secondary1)->Release();
		*secondary1 = 0;}
	if(*secondary2){
		(*secondary2)->Release();
		*secondary2 = 0;}
	if(*secondary3){
		(*secondary3)->Release();
		*secondary3 = 0;}
	if(*secondary4){
		(*secondary4)->Release();
		*secondary4 = 0;}
	if(*secondary5){
		(*secondary5)->Release();
		*secondary5 = 0;}
	if(*secondary6){
		(*secondary6)->Release();
		*secondary6 = 0;}
	if(*secondary7){
		(*secondary7)->Release();
		*secondary7 = 0;}
	if(*secondary8){
		(*secondary8)->Release();
		*secondary8 = 0;}
	if(*secondary9){
		(*secondary9)->Release();
		*secondary9 = 0;}
	if(*secondary10){
		(*secondary10)->Release();
		*secondary10 = 0;}

	return;
}

bool SoundClass::Play(int m_volume, IDirectSoundBuffer8** m_buffer, IDirectSound3DBuffer8** m_3DBuffer, GraphicsClass::position m_position, bool isMusic, bool isLooping)
{
	HRESULT result;
 
	float positionX, positionY, positionZ;

	// Set the 3D position of where the sound should be located
	
	positionX = m_position.x;
	positionY = m_position.y;
	positionZ = m_position.z;

	// Set position at the beginning of the sound buffer.
	result = (*m_buffer)->SetCurrentPosition(0);
	if(FAILED(result))
	{
		return false;
	}
 
	// Set volume of the buffer to m_volume.
	result = (*m_buffer)->SetVolume(m_volume);
	if(FAILED(result))
	{
		return false;
	}

	// Set the 3D position of the sound if it is not music; music has no 3D location
	if(!isMusic){
		(*m_3DBuffer)->SetPosition(positionX, positionY, positionZ, DS3D_IMMEDIATE);}

	// Unlike 3D sound, music may be panned
	if(isMusic){
	result = (*m_buffer)->SetPan(m_pan);
	if(FAILED(result))
	{
		return false;
	}
	}

	// Set effects if passed in
	result = SetEffect(m_effectName);
	if(FAILED(result))
	{
		return false;
	}
 
	// Play the contents of the secondary sound buffer.
	if(!isLooping){
		result = (*m_buffer)->Play(0, 0, 0);}
	else{ result = (*m_buffer)->Play(0,0, DSBPLAY_LOOPING);}
	if(FAILED(result))
	{
		return false;
	}
 
	return true;
}

bool SoundClass::SetEffect(string effectName)
{
	// Applies an effect 

	if (effectName == "reverb")
	{
	// Describe the effect buffer.
	DWORD dwResults[1];
	DSEFFECTDESC reverbEffect;
	memset(&reverbEffect, 0, sizeof(DSEFFECTDESC));
	reverbEffect.dwSize = sizeof(DSEFFECTDESC);
	reverbEffect.dwFlags = 0;
	reverbEffect.guidDSFXClass = GUID_DSFX_WAVES_REVERB;

	// Set the effect
 
	 m_secondaryBuffer1->SetFX(1, &reverbEffect, dwResults);
	}

	else if(effectName == "EQ")
	{

	DWORD dwResults[1];
	DSEFFECTDESC eqEffect;
	memset(&eqEffect, 0, sizeof(DSEFFECTDESC));
	eqEffect.dwSize = sizeof(DSEFFECTDESC);
	eqEffect.dwFlags = 0;
	eqEffect.guidDSFXClass = GUID_DSFX_STANDARD_PARAMEQ;

	eqEffect.guidDSFXClass.Data1 = 100;
	eqEffect.guidDSFXClass.Data2 = 100;
	eqEffect.guidDSFXClass.Data3 = -100;

	m_secondaryBuffer1->SetFX(1, &eqEffect, dwResults);
	}

	else
	{
		return false;
	}

	return true;
};


void SoundClass::CheckFlags(){
	if(m_Graphics->soundFlags[0] == true){
		PlayFromEntity("jaws", m_Graphics->GetEntityPosition(0));
	}

	if(m_Graphics->soundFlags[1] == true){
		PlayFromEntity("fishSwim", m_Graphics->GetEntityPosition(0));
	}

	if(m_Graphics->soundFlags[2] == true){
		PlayFromEntity("manyFishSwim", m_Graphics->GetEntityPosition(0));
	}

	for(int i = 0; i < 5; i++){
		m_Graphics->soundFlags[i] = false;
	}
}
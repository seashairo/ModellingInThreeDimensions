////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

// Direct Input version
#define DIRECTINPUT_VERSION 0x0800

// Required libraries
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include "Log.h"
#include <dinput.h>
#include "3DManagerClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsKeyPressed(int key);
	bool KeyJustDown(int key);
	bool KeyJustUp(int ket);

	bool IsMouseDown(int button);
	bool MouseJustDown(int button);
	bool MouseJustUp(int button);
	D3DXVECTOR2 GetMousePosition();

private:
	int m_screenWidth;
	int m_screenHeight;

	// Keyboard attributes.
	bool ReadKeyboard();
	unsigned char m_keyboardState[256];
	unsigned char m_keyboardStatePrev[256];

	// Mouse attributes.
	bool ReadMouse();
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_mouseStatePrev; 
	D3DXVECTOR2 m_mousePos;
	D3DXVECTOR2 m_mousePosPrev;

	// The input devices
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
};

#endif
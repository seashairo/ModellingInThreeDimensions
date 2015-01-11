#include "inputclass.h"

InputClass::InputClass(){
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;

	m_mousePos = D3DXVECTOR2(0, 0);
}

InputClass::InputClass(const InputClass& other){
}

InputClass::~InputClass(){
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight){
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the direct input interface
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the keyboard devices format to keyboard
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}

	// Set the keyboard to only accept input from this application (DISCL_EXCLUSIVE)
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard for use
	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	// Create a direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if(FAILED(result)){
		return false;
	}

	// Set the device format to mouse.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result)){
		return false;
	}

	// Set the cooperative level for the device.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if(FAILED(result)){
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if(FAILED(result)){
		return false;
	}

	return true;
}

void InputClass::Shutdown(){
	// Release the keyboard
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the mouse.
	if(m_mouse){
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release direct input
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}

bool InputClass::Frame(){
	bool result;

	// Read from the keyboard.
	if(!ReadKeyboard())
	{
		return false;
	}

	// Read from the mouse.
	if(!ReadMouse()){
		return false;
	}

	return true;
}

#pragma region Keyboard
bool InputClass::ReadKeyboard(){
	HRESULT result;

	// Get the keyboard state
	memcpy(&m_keyboardStatePrev, m_keyboardState, sizeof(char)*256);
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	
	if(FAILED(result))
	{
		// If for some reason we don't have the keyboard, get it again.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}

bool InputClass::IsKeyPressed(int key){
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[key]  & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::KeyJustDown(int key){
	if((m_keyboardState[key] & 0x80) && !(m_keyboardStatePrev[key] & 0x80)){
		return true;
	}

	return false;
}

bool InputClass::KeyJustUp(int key){
	if(!(m_keyboardState[key] & 0x80) && (m_keyboardStatePrev[key] & 0x80)){
		return true;
	}

	return false;
}
#pragma endregion

#pragma region Mouse
// Update the mouse states.
bool InputClass::ReadMouse(){
	HRESULT result;

	memcpy(&m_mouseStatePrev, &m_mouseState, sizeof(DIMOUSESTATE));
	result = m_mouse->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState);

	if(FAILED(result))
	{
		// If for some reason we don't have the mouse, get it again.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	// Update previous mouse state.
	m_mousePosPrev.x = m_mousePos.x;
	m_mousePosPrev.y = m_mousePos.y;

	// Update new mouse state.
	m_mousePos.x += m_mouseState.lX;
	m_mousePos.y += m_mouseState.lY;

	// Lock mousePos to the available window space.
	if(m_mousePos.x < 0) m_mousePos.x = 0;
	if(m_mousePos.y < 0) m_mousePos.y = 0;
	if(m_mousePos.x > m_screenWidth) m_mousePos.x = m_screenWidth;
	if(m_mousePos.y > m_screenHeight) m_mousePos.y = m_screenHeight;

	//Log::COut("Mouse is currently at: " + to_string(m_mousePos.x) + ", " + to_string(m_mousePos.y) + ".");
		
	return true;
}

// Check if a mouse button is down.
bool InputClass::IsMouseDown(int button)
{
	if(m_mouseState.rgbButtons[button] & 0x80)
	{
		return true;
	}
}

// Check if a mouse button has just been pressed.
bool InputClass::MouseJustDown(int button){
	if((m_mouseState.rgbButtons[button] & 0x80) && !(m_mouseStatePrev.rgbButtons[button] & 0x80)){
		return true;
	}

	return false;
}

// Check if a mouse button has just been released.
bool InputClass::MouseJustUp(int button){
	if(!(m_mouseState.rgbButtons[button] & 0x80) && (m_mouseStatePrev.rgbButtons[button] & 0x80)){
		return true;
	}

	return false;
}

// Return the mouse position as a Vec2
D3DXVECTOR2 InputClass::GetMousePosition(){
	return m_mousePos;
}
#pragma endregion
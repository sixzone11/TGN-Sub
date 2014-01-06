#pragma once

#include <InitGuid.h>

#define DIRECTINPUT_VERSION		0x0800

#pragma comment(lib, "dinput8.lib")

#include <dinput.h>

class Window;

class CInput
{
public:
	CInput(void);
	CInput(const CInput& other);
	~CInput(void);


public:
	bool Initialize(Window* window);
    void Shutdown();
    bool Frame();
 

public:
    bool IsEscapePressed() const;
	inline bool IsKeyPressed(int keyID) const
	{
		return (_keyboardState[keyID] & 0x80);
	}
    void GetMouseLocation(int&, int&) const;
 

private:
    bool ReadKeyboard();
    bool ReadMouse();
    void ProcessInput();


private:
	IDirectInput8*			_directInput;
	IDirectInputDevice8*	_keyboard;
	IDirectInputDevice8*	_mouse;

	unsigned char			_keyboardState[256];
    DIMOUSESTATE			_mouseState;
 
    int			_screenWidth;
	int			_screenHeight;
    int			_mouseX;
	int			_mouseY;
};
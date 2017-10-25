#include "stdafx.h"
#include "KeyManager.h"

KeyManager * KeyManager::ms_pInstance = NULL;
int KeyManager::s_keyPressed = S_KEY_NONE;

KeyManager::KeyManager(){}
KeyManager::~KeyManager(){}

void KeyManager::Init()
{

}
void KeyManager::SetKeyPress(const int keyCode)
{
	s_keyPressed |= keyCode;
}
void KeyManager::SetKeyPress(const unsigned char keyChar)
{
	//esLogMessage("%c is press.\n", keyChar);
	switch (keyChar)
	{
	case S_CHAR_UP:
		SetKeyPress(S_KEY_UP);
		//esLogMessage("Key Arrow Up.\n");
		break;

	case S_CHAR_DOWN:
		SetKeyPress(S_KEY_DOWN);
		//esLogMessage("Key Arrow Down.\n");
		break;

	case S_CHAR_LEFT:
		SetKeyPress(S_KEY_LEFT);
		//esLogMessage("Key Left.\n");
		break;

	case S_CHAR_RIGHT:
		SetKeyPress(S_KEY_RIGHT);
		//esLogMessage("Right Left.\n");
		break;

	case S_CHAR_1:
		SetKeyPress(S_KEY_1);
		break;

	case S_CHAR_2:
		SetKeyPress(S_KEY_2);
		break;

	case S_CHAR_3:
		SetKeyPress(S_KEY_3);
		break;
	case S_CHAR_ESC:
		SetKeyPress(S_KEY_ESC);
		break;
	case S_CHAR_P:
		SetKeyPress(S_KEY_P);
		break;
	case S_CHAR_CTRL:
		SetKeyPress(S_KEY_CTRL);
		break;
	case S_CHAR_S:
		SetKeyPress(S_KEY_S);
		break;
	case S_CHAR_L:
		SetKeyPress(S_KEY_L);
		break;
	case S_CHAR_A:
		SetKeyPress(S_KEY_A);
		break;
	case S_CHAR_D:
		SetKeyPress(S_KEY_D);
		break;
	case S_CHAR_W:
		SetKeyPress(S_KEY_W);
		break;
	case S_CHAR_E:
		SetKeyPress(S_KEY_E);
		break;
	case S_CHAR_F:
		SetKeyPress(S_KEY_F);
		break;
	case S_CHAR_R:
		SetKeyPress(S_KEY_R);
		break;
	case S_CHAR_Q:
		SetKeyPress(S_KEY_Q);
		break;
	default:
		SetKeyPress(S_KEY_OTHER);
		break;
	}
}
bool KeyManager::IsKeyPressed(const int keyCode)
{
	return s_keyPressed & keyCode;
}
bool KeyManager::IsAnyKeyPressed()
{
	return s_keyPressed;
}
bool KeyManager::IsKeyUpPressed()
{
	return IsKeyPressed(S_KEY_UP);
}
bool KeyManager::IsKeyDownPressed()
{
	return IsKeyPressed(S_KEY_DOWN);
}
bool KeyManager::IsKeyLeftPressed()
{
	return IsKeyPressed(S_KEY_LEFT);
}
bool KeyManager::IsKeyRightPressed()
{
	return IsKeyPressed(S_KEY_RIGHT);
}
bool KeyManager::UnAllKeyPress()
{
	if(s_keyPressed != S_KEY_NONE)
	{
		s_keyPressed = S_KEY_NONE;
		return true;
	}
	return false;
}
bool KeyManager::UnKeyPress(const int keyCode)
{
	if(s_keyPressed & keyCode)
	{
		s_keyPressed ^= keyCode;
		return true;
	}
	return false;
}
bool KeyManager::UnKeyPress(const unsigned char keyChar)
{
	//esLogMessage("%c [%d] is unpressed.\n", keyChar, keyChar);
	switch (keyChar)
	{
	case S_CHAR_UP:
		return UnKeyPress(S_KEY_UP);
		//esLogMessage("Key Arrow Up.\n");
		break;

	case S_CHAR_DOWN:
		return UnKeyPress(S_KEY_DOWN);
		//esLogMessage("Key Arrow Down.\n");
		break;

	case S_CHAR_LEFT:
		return UnKeyPress(S_KEY_LEFT);
		//esLogMessage("Key Left.\n");
		break;

	case S_CHAR_RIGHT:
		return UnKeyPress(S_KEY_RIGHT);
		//esLogMessage("Right Left.\n");
		break;

	case S_CHAR_1:
		return UnKeyPress(S_KEY_1);
		break;

	case S_CHAR_2:
		return UnKeyPress(S_KEY_2);
		break;

	case S_CHAR_3:
		return UnKeyPress(S_KEY_3);
		break;
	case S_CHAR_ESC:
		return UnKeyPress(S_KEY_ESC);
		break;
	case S_CHAR_P:
		return UnKeyPress(S_KEY_P);
		break;
	case S_CHAR_CTRL:
		return UnKeyPress(S_KEY_CTRL);
		break;
	case S_CHAR_S:
		return UnKeyPress(S_KEY_S);
		break;
	case S_CHAR_L:
		return UnKeyPress(S_KEY_L);
		break;
	case S_CHAR_A:
		return UnKeyPress(S_KEY_A);
		break;
	case S_CHAR_D:
		return UnKeyPress(S_KEY_D);
		break;
	case S_CHAR_W:
		return UnKeyPress(S_KEY_W);
		break;
	case S_CHAR_E:
		return UnKeyPress(S_KEY_E);
		break;
	case S_CHAR_F:
		return UnKeyPress(S_KEY_F);
		break;
	case S_CHAR_R:
		return UnKeyPress(S_KEY_R);
		break;
	case S_CHAR_Q:
		return UnKeyPress(S_KEY_Q);
		break;
	default:
		return UnKeyPress(S_KEY_OTHER);
		break;
	}
}
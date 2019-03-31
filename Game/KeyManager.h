#pragma once

class KeyManager
{
public:
	static const int S_KEY_NONE				= 0;
	static const int S_KEY_LEFT_FLIPPER		= 1 << 0;
	static const int S_KEY_RIGHT_FLIPPER	= 1 << 1;
	static const int S_KEY_SELECT			= 1 << 2;
	static const int S_KEY_SPACE			= 1 << 3;
	static const int S_KEY_UP				= 1 << 4;
	static const int S_KEY_DOWN				= 1 << 5;
	static const int S_KEY_LEFT				= 1 << 6;
	static const int S_KEY_RIGHT			= 1 << 7;
	static const int S_KEY_ESC				= 1 << 8;
	static const int S_KEY_OTHER			= 1 << 9;
	static const int S_KEY_P				= 1 << 10;
	static const int S_KEY_1				= 1 << 11;
	static const int S_KEY_2				= 1 << 12;
	static const int S_KEY_3				= 1 << 13;
	static const int S_KEY_CTRL				= 1 << 14;
	static const int S_KEY_S				= 1 << 15;
	static const int S_KEY_L				= 1 << 16;
	static const int S_KEY_A				= 1 << 17;
	static const int S_KEY_D				= 1 << 18;
	static const int S_KEY_W				= 1 << 19;
	static const int S_KEY_C				= 1 << 20;
	static const int S_KEY_V				= 1 << 21;
	static const int S_KEY_E				= 1 << 22;
	static const int S_KEY_F				= 1 << 23;
	static const int S_KEY_R				= 1 << 24;
	static const int S_KEY_Q				= 1 << 25;
	static const int S_KEY_X				= 1 << 26;

	//static const unsigned char S_CHAR_NONE			= 0;
	static const unsigned char S_CHAR_LEFT_FLIPPER	= 1;
	static const unsigned char S_CHAR_RIGHT_FLIPPER	= 2;
	static const unsigned char S_CHAR_SELECT		= 3;
	static const unsigned char S_CHAR_SPACE			= ' ';
	static const unsigned char S_CHAR_UP			= '&';
	static const unsigned char S_CHAR_DOWN			= '(';
	static const unsigned char S_CHAR_LEFT			= '%';
	static const unsigned char S_CHAR_RIGHT			= '\'';
	static const unsigned char S_CHAR_ESC			= 27;
	//static const unsigned char S_CHAR_OTHER		= '.';
	static const unsigned char S_CHAR_P				= 'P';
	static const unsigned char S_CHAR_1				= '1';
	static const unsigned char S_CHAR_2				= '2';
	static const unsigned char S_CHAR_3				= '3';
	static const unsigned char S_CHAR_CTRL			= 17;
	static const unsigned char S_CHAR_S				= 'S';
	static const unsigned char S_CHAR_L				= 'L';
	static const unsigned char S_CHAR_A				= 'A';
	static const unsigned char S_CHAR_D				= 'D';
	static const unsigned char S_CHAR_W				= 'W';
	static const unsigned char S_CHAR_C				= 'C';
    static const unsigned char S_CHAR_V             = 'V';
	static const unsigned char S_CHAR_E				= 'E';
	static const unsigned char S_CHAR_F				= 'F';
	static const unsigned char S_CHAR_R				= 'R';
	static const unsigned char S_CHAR_Q				= 'Q';
    static const unsigned char S_CHAR_X             = 'X';

	static int s_keyPressed;

	void Init();
	
	void SetKeyPress(const int keyCode);
	void SetKeyPress(const unsigned char keyChar);
	bool IsKeyPressed(const int keyCode);
	bool IsAnyKeyPressed();
	bool IsKeyUpPressed();
	bool IsKeyDownPressed();
	bool IsKeyLeftPressed();
	bool IsKeyRightPressed();
	bool UnKeyPress(const int keyCode);
	bool UnAllKeyPress();
	bool UnKeyPress(const unsigned char keyChar);

	
#pragma region "Singleton"
private:
	KeyManager();
	~KeyManager();
	static void CreateInstance()
	{
		ms_pInstance = new KeyManager();
	}

public:

	static KeyManager * GetInstance() 
	{
        if (!ms_pInstance) CreateInstance();
        return ms_pInstance;
	}

	static void DestroyInstance() 
	{
		if ( ms_pInstance )
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

protected:
	static KeyManager * ms_pInstance;

#pragma endregion
};
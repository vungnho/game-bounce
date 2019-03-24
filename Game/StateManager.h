#pragma once

enum typeStates {STATE_LOAD, STATE_MAINMENU, STATE_PAUSE, STATE_PLAY, STATE_GAME_OVER, STATE_MAP_EDITOR, STATE_LOADING, STATE_LV_SELECT};
class StateManager
{
private:
	typeStates m_state;
public:
	void Init();
	void SetCurrentState(typeStates newState);
	typeStates GetCurrentState();

#pragma region "Singleton"
private:
	StateManager();
	~StateManager();
	static void CreateInstance()
	{
		ms_pInstance = new StateManager();
	}

public:

	static StateManager * GetInstance() 
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
	static StateManager * ms_pInstance;

#pragma endregion
};
#include "StdAfx.h"
#include "StateManager.h"

StateManager * StateManager::ms_pInstance = NULL;

StateManager::StateManager():m_state(STATE_PAUSE){}
StateManager::~StateManager(){}

void StateManager::Init()
{
	m_state = STATE_LOAD;
}

void StateManager::SetCurrentState(typeStates newState)
{
	m_state = newState;
}
typeStates StateManager::GetCurrentState()
{
	return m_state;
}

//// NewTrainingFramework.cpp : Defines the entry point for the console application.
////
//
//
//#include "stdafx.h"
//
//#include "../Game/Globals.h"
//
//#include "../Game/ResourceManager.h"
//#include "../Game/SceneManager.h"
//#include "../Game/KeyManager.h"
//#include "../Game/TextManager.h"
//#include "../Game/StateManager.h"
//
//
//#include <conio.h>
//
//
//
//
//int Init ( ESContext *esContext )
//{
//
//	//Màu sau khi xoá hết màn hình
//	glViewport(0, 0, esContext->width, esContext->height);
//	glClearColor ( 1.0, 1.0, 1.0, 0 ); //RGBA
//
//
//	KeyManager::CreateInstance();
//	KeyManager::GetInstance()->Init();
//
//	ResourceManager::CreateInstance();
//	ResourceManager::GetInstance()->Init();
//
//	TextManager::CreateInstance();
//	TextManager::GetInstance()->Init();
//
//	SceneManager::CreateInstance();
//	SceneManager::GetInstance()->Init();
//
//
//	StateManager::CreateInstance();
//	StateManager::GetInstance()->Init();
//
//
//	return 0;
//
//}
//
//
//
//void Draw ( ESContext *esContext )
//{
//
//
//	
//	SceneManager::GetInstance()->Draw();
//
//
//
//}
//
//void Update ( ESContext *esContext, float deltaTime )
//{
//	SceneManager::GetInstance()->Update(deltaTime);
//}
//
//void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
//{
//	if(bIsPressed)
//	{
//		SceneManager::GetInstance()->OnKeyDown(key);
//	}
//	else
//	{
//		SceneManager::GetInstance()->OnKeyUp(key);
//	}
//}
//
//void CleanUp()
//{
//    
//	ResourceManager::DestroyInstance();
//	KeyManager::DestroyInstance();
//	SceneManager::DestroyInstance();
//	TextManager::DestroyInstance();
//	StateManager::DestroyInstance();
//}
//
////convert to bottom left
//int Invert(int y, int height)
//{
//	return (height - y);
//}
//
//
//void TouchActionDown(ESContext *esContext, int x, int y)
//{
//
//	y = Invert(y, esContext->height);
//	SceneManager::GetInstance()->OnTourchDown(x, y);
//
//}
//
//void TouchActionUp(ESContext *esContext, int x, int y)
//{
//	y = Invert(y, esContext->height);
//	SceneManager::GetInstance()->OnTourchUp(x, y);
//}
//
//void TouchActionMove(ESContext *esContext, int x, int y)
//{
//
//	y = Invert(y, esContext->height);
//	SceneManager::GetInstance()->OnTourchMove(x, y);
//
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	ESContext esContext;
//
//    esInitContext ( &esContext );
//	SceneManager::GetInstance()->esContext = &esContext;
//
//	esCreateWindow ( &esContext, "3D Trainning", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
//
//	if ( Init ( &esContext ) != 0 )
//		return 0;
//
//	esRegisterDrawFunc ( &esContext, Draw );
//	esRegisterUpdateFunc ( &esContext, Update );
//	esRegisterKeyFunc ( &esContext, Key);
//	esRegisterMouseDownFunc(&esContext, TouchActionDown);
//	esRegisterMouseUpFunc(&esContext, TouchActionUp);
//	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
//
//	esMainLoop ( &esContext );
//
//
//
//	//releasing OpenGL resources
//	CleanUp();
//
//
//
//	//identifying memory leaks
//	MemoryDump();
//	//Console::log("Press any key...\n");
//	_getch();
//
//	return 0;
//}
//

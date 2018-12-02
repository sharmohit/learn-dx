#include <memory>

#include "SceneManager.h"
#include "MainScene.h"

SceneManager::SceneManager()
{
	currentScene = 0;
	currentState = Running;
	isGameQuit = false;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	//loadScene(Menu_Scene);
}

void SceneManager::Input()
{
	currentScene->Input();
}

void SceneManager::Update(float dt)
{
	currentScene->Update(dt);
}

void SceneManager::Render()
{
	currentScene->Render();
}

void SceneManager::Quit()
{
	currentScene->Quit();
	delete currentScene;
	currentScene = 0;
}

void SceneManager::LoadScene(GameScene scene)
{
	if (currentScene != 0)
	{
		Quit();
	}

	currentState = Running;

	switch (scene)
	{
	case Main_Scene:
	{
					   //std::shared_ptr<MainScene> mainScene = std::shared_ptr<MainScene>(new MainScene());
					   currentScene = new MainScene();
					   currentScene->Init();
					   break;
	}
	default:
		currentScene = 0;
		break;
	}
}
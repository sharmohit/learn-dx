#pragma once

#include"Scene.h"

enum GameScene
{
	Main_Scene
};

enum GameState
{
	Running,
	Pause,
	Won,
	Lose
};

class SceneManager{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Input();
	void Update(float dt);
	void Render();
	void Quit();
	void LoadScene(GameScene scene);
	GameScene loadedScene;
	GameState currentState;
	bool isGameQuit;
private:
	Scene* currentScene;
};
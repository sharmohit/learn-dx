#pragma once

#include "Scene.h"

class MainScene : public Scene{
public:
	MainScene();
	~MainScene();

	void Init();
	void Input();
	void Update(float dt);
	void Render();
	void Quit();
};
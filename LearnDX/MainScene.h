#pragma once

#include "Scene.h"
#include "Cube.h"

class MainScene : public Scene{
public:
	MainScene();
	~MainScene();

	void Init();
	void Input();
	void Update(float dt);
	void Render();
	void Quit();
private:
	std::shared_ptr<Cube> m_pCube;
};
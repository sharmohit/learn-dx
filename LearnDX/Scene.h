#pragma once

class Scene{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Input();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Quit();
};
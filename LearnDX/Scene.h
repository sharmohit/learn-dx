#pragma once

class Scene{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Input() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;
};
#pragma once

#include <memory>
#include "Transform.h"

class Entity {
public:
	Entity();
	virtual ~Entity();
	std::shared_ptr<Transform> GetTransform(){ return m_pTransform; };
	void SetTransform(std::shared_ptr<Transform> transform);
private:
	std::shared_ptr<Transform> m_pTransform;
};
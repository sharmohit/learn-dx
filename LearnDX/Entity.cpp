#include "Entity.h"

Entity::Entity()
{
	m_pTransform = std::shared_ptr<Transform>(new Transform());
}

Entity::~Entity()
{
}

void Entity::SetTransform(std::shared_ptr<Transform> pTransform)
{
	m_pTransform = pTransform;
}
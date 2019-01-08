#include "Scene.h"
#include <stdio.h>

Scene::Scene()
{
	printf("Scene Base Constructor");
}

Scene::~Scene()
{
	printf("\nScene Base Destructor");
}

void Scene::Init()
{
	printf("\nScene Base Init()");
}

void Scene::Input()
{
	printf("\nScene Base Input()");
}

void Scene::Update(float dt)
{
	printf("\nScene Base Update");
}

void Scene::Render()
{
	printf("\nScene Base Render");
}

void Scene::Quit()
{
	printf("\nScene Base Quit");
}
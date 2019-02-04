#include <memory>

#include "dxstdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	printf("\n MainMenu Init()");
	m_pCube = std::shared_ptr<Cube>(new Cube());
	printf("\n Cube Scale X:%f", m_pCube->GetTransform()->GetScale().x);
}

void MainScene::Input()
{
	printf("\n MainMenu Input()");
}

void MainScene::Update(float dt)
{
	//printf("\n MainMenu Update");
}

void MainScene::Render()
{
	//printf("\n MainMenu Render");
}

void MainScene::Quit()
{
	printf("\n MainMenu Quit");
}
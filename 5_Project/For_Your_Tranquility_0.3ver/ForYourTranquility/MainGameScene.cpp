#include "pch.h"
#include "MainGameScene.h"

MainGameScene::MainGameScene()
{
	m_MainGameState = eSceneStateAll::MAIN_OFFICE;
}

MainGameScene::~MainGameScene()
{

}

void MainGameScene::Initialize(JJEngine* pJJEngine)
{

}

void MainGameScene::Update()
{
	SceneManager::GetInstance()->SceneFSM(eSceneState::OUTRO);

	// ���������� �̷��� ����..
	SceneManager::ChangeScene(eSceneStateAll::OUTRO_RESULT);
}

void MainGameScene::Render()
{

}

void MainGameScene::Finalize()
{

}
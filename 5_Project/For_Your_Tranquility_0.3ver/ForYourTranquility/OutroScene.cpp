#include "pch.h"
#include "OutroScene.h"

OutroScene::OutroScene()
	:m_pOutroResult(nullptr), m_pOutroEnding(nullptr)
{
	m_OutroState = eSceneStateAll::OUTRO_RESULT;
}

OutroScene::~OutroScene()
{

}

void OutroScene::Initialize(JJEngine* pJJEngine)
{

}

void OutroScene::Update()
{
	SceneManager::GetInstance()->SceneFSM(eSceneState::INTRO);
}

void OutroScene::Render()
{

}

void OutroScene::Finalize()
{

}
#include "pch.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	m_IntroState = eSceneStateAll::INTRO_TITLE;
}

IntroScene::~IntroScene()
{

}

void IntroScene::Initialize(JJEngine* pJJEngine)
{
	/*
	// IntroScene에서 사용하는 이미지 생성
	ImageResource bgImage = new ImageResource;
	bgImage->Initialize(100, 100);

	// 게임 오브젝트 매니저를 통한 게임 오브젝트 추가
	m_pGameObjectManager->AddGameObject(GameLayer::BACKGROUND, bgImage);
	*/
}

void IntroScene::Update()
{
	// TITLE 씬 이후 ANIMATION 씬으로 전환
	SceneManager::GetInstance()->SceneFSM(eSceneState::MAINGAME);
}

void IntroScene::Render()
{

}

void IntroScene::Finalize()
{

}
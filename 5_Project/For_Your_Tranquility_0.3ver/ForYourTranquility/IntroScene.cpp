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
	// IntroScene���� ����ϴ� �̹��� ����
	ImageResource bgImage = new ImageResource;
	bgImage->Initialize(100, 100);

	// ���� ������Ʈ �Ŵ����� ���� ���� ������Ʈ �߰�
	m_pGameObjectManager->AddGameObject(GameLayer::BACKGROUND, bgImage);
	*/
}

void IntroScene::Update()
{
	// TITLE �� ���� ANIMATION ������ ��ȯ
	SceneManager::GetInstance()->SceneFSM(eSceneState::MAINGAME);
}

void IntroScene::Render()
{

}

void IntroScene::Finalize()
{

}
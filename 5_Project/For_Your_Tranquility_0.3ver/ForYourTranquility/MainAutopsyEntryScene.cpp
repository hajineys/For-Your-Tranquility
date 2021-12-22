#include "pch.h"

#include "MainAutopsyEntryScene.h"
#include "MainAutopsyRoomScene.h"
#include "ObjectManager.h"
#include "Button.h"
#include "ColliderBox.h"

bool MainAutopsyEntryScene::IsFirstPlay = false;

MainAutopsyEntryScene::MainAutopsyEntryScene()
	:m_pFrog(nullptr)
{

}

MainAutopsyEntryScene::~MainAutopsyEntryScene()
{

}

void MainAutopsyEntryScene::Initialize()
{
	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	m_pObjectManager->CreateObject_Image(JVector(0, 0), L"AutopsyRoom_Background", 1, UISortLayer::BACKGROUND);
	m_pFrog = m_pObjectManager->CreateObject_Button(JVector(741, 562), L"AutopsyRoom_FrogOnly", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);
	m_pFrog->AddSprite(L"AutopsyRoom_FrogHighlight", 1);
	m_pFrog->GetColliderBox()->SetSize(JVector(530, 132));
}

void MainAutopsyEntryScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pObjectManager->UpdateAll(dTime);
	m_pObjectManager->CheckButtonClicked(this);

	// ������ �ý� ���̶���Ʈ
	if (m_pFrog->GetColliderBox()->IsCollided)
	{
		m_pFrog->ChangeSprite(1);

		if (IsFirstPlay == false)
		{
			SoundManager::GetInstance()->Play(1, L"Orgen_01");
			IsFirstPlay = true;
		}
	}
	else
	{
		m_pFrog->ChangeSprite(0);
		IsFirstPlay = false;
	}

	switch (m_NowSceneState)
	{
	case eNowSceneState::NONE:
		break;

	case eNowSceneState::GO_TO_NEXT_SCENE:
	{
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY);
		}
	}
	break;
	}
}

void MainAutopsyEntryScene::Draw()
{
	m_pObjectManager->DrawAll();

	SceneManager::DrawBlackScreen();

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	//ShowDebug();
}

void MainAutopsyEntryScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Main_AutopsyEntryScene ��");
}

void MainAutopsyEntryScene::Release()
{
	m_pObjectManager->Release();
	Scene::Release();
}
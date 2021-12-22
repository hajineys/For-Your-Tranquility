#include "pch.h"
#include "IntroAnimationScene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "TextBox.h"
#include "Button.h"
#include "ColliderBox.h"

IntroAnimationScene::IntroAnimationScene()
	:m_pBackgroundIMG(nullptr)
{

}

IntroAnimationScene::~IntroAnimationScene()
{

}

void IntroAnimationScene::Initialize()
{
	SoundManager::GetInstance()->Play(0, L"BGM_Intro");

	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	//���ȭ��
	m_pBackgroundIMG = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Intro_Background", 1, UISortLayer::BACKGROUND);

	m_pTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(20, 700), L"Intro", UISortLayer::ENDLAYER);
	m_pTextBox->On();
	m_pTextBox->SetStartEndIndex(0, m_pTextBox->GetScriptTextCount());
}

void IntroAnimationScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pObjectManager->UpdateAll(dTime);

	// ��ȭ���ڰ� �������� ��츸 ������Ʈ ���ش�.
	m_pTextBox->Update(dTime);

	// ��ũ��Ʈ�� ��� ������ �� ���콺 ������ ���� ������ �̵�
	if (InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->IsAllTextEnd())
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}

	switch (m_NowSceneState)
	{
	case eNowSceneState::NONE:
		break;
	case eNowSceneState::GO_TO_NEXT_SCENE:
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
			SceneManager::ChangeScene(eSceneStateAll::MAIN_OFFICE);

		return;
	case eNowSceneState::GO_TO_PREV_SCENE:
		break;
	case eNowSceneState::POPUP_SHOW:
		break;
	default:
		break;
	}
}

void IntroAnimationScene::Draw()
{
	m_pObjectManager->DrawAll();

	SceneManager::DrawBlackScreen();

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;
	
	// �ӽ� ĳ����
	if (m_pTextBox->GetKeyIndex() < 28)
	{
		m_pTextBox->DrawCharacter(false);
	}
	else
	{
		m_pTextBox->DrawCharacter(true);
	}

	m_pTextBox->Draw(1.0f);

	//JJEngine::GetInstance()->DrawText(700, 500, 1000, 500, 35, ColorF(ColorF::White), L"�׽�Ʈ ���� ver0.3, ��Ʈ�� �ִϸ��̼� ��ŵ\n �� ���� ����");
}

void IntroAnimationScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Animation ��");
}

void IntroAnimationScene::Release()
{
	m_pObjectManager->Release();

	Scene::Release();

	SoundManager::GetInstance()->Stop(0, L"BGM_Intro");
}

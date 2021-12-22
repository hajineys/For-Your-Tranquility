#include "pch.h"

#include "IntroTitleScene.h"
#include "ObjectManager.h"
#include "Button.h"
#include "Object.h"
#include "ColliderBox.h"
#include <stdlib.h>

bool IntroTitleScene::m_IsFirstPlay[2] = { false, };

IntroTitleScene::IntroTitleScene()
	:m_pBackGround(nullptr),
	m_pLightAnimation(nullptr),
	m_pTitleBar(nullptr),
	m_pStartButton(nullptr),
	m_pExitButton(nullptr),
	m_pNowSceneState(eSceneStateAll::INTRO_TITLE)
{

}

IntroTitleScene::~IntroTitleScene()
{

}

void IntroTitleScene::Initialize()
{
	Scene::Initialize();
	InputManager::GetInstance()->Reset();

	// ��׶����̹���
	m_pObjectManager->CreateObject_Image(JVector(0, 0), L"NewTitle_background", 1, UISortLayer::BACKGROUND);
	m_pLightAnimation = m_pObjectManager->CreateObject_Image(JVector(629, 260), L"NewTitle_lightcolor_ani", 8, UISortLayer::BUTTON);

	// Ÿ��Ʋ��
	m_pTitleBar = m_pObjectManager->CreateObject_Image(JVector(246, 326), L"NewTitle_ani", 8, UISortLayer::BUTTON);

	m_pObjectManager->CreateObject_Image(JVector(246, 634), L"NewTitle_english", 1, UISortLayer::BACKGROUND);

	// ���ӽ��۹�ư
	m_pStartButton = m_pObjectManager->CreateObject_Button(JVector(250, 814), L"NewTitle_StartButton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);
	// ���������ư
	m_pExitButton = m_pObjectManager->CreateObject_Button(JVector(250, 867), L"NewTitle_ExitButton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);

	SoundManager::GetInstance()->Play(0, L"BGM_Main");		// BGM����

	// ����ö �ʱ�ȭ
	FileFolder::GetInstance()->Initialize();
}

void IntroTitleScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	// ���콺�� �ö��ֳ� �ȿö��ֳ�?
	m_pObjectManager->UpdateAll(dTime);
	//FileFolder::GetInstance()->Update(dTime);

	m_pObjectManager->CheckButtonClicked(this);

	m_pTitleBar->UpdateAnimation(dTime);
	m_pLightAnimation->UpdateAnimation(dTime);

	/// ���۹�ư�� �÷��ξ��� ��
	if (m_pStartButton->GetColliderBox()->IsCollided)
	{
		m_pStartButton->ChangeFrame(1);

		if (m_IsFirstPlay[0] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_01");
			m_IsFirstPlay[0] = true;
		}
	}
	else
	{
		m_pStartButton->ChangeFrame(0);
		m_IsFirstPlay[0] = false;
	}

	// ����
	/// �����ư�� �÷��ξ��� �� 
	if (m_pExitButton->GetColliderBox()->IsCollided)
	{
		m_pExitButton->ChangeFrame(1);

		if (m_IsFirstPlay[1] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_01");
			m_IsFirstPlay[1] = true;
		}
	}
	else
	{
		m_pExitButton->ChangeFrame(0);
		m_IsFirstPlay[1] = false;
	}

	switch (m_NowSceneState)
	{
	case eNowSceneState::NONE:
		break;

	case eNowSceneState::GO_TO_NEXT_SCENE:

		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");	// ��ư�� ������ ����ȴ�.
			SceneManager::ChangeScene(eSceneStateAll::INTRO_ANIMATION);
		}
		return;

	case eNowSceneState::GO_TO_PREV_SCENE:
		SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");	// ��ư�� ������ ����ȴ�.
		exit(0);
		return;

	case eNowSceneState::POPUP_SHOW:
		break;
	}
}

void IntroTitleScene::Draw()
{
	m_pObjectManager->DrawAll();

	//FileFolder::GetInstance()->Draw();

	SceneManager::DrawBlackScreen();
	
	

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;
}


void IntroTitleScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Title ��");
}

void IntroTitleScene::Release()
{
	Scene::Release();

	SoundManager::GetInstance()->Stop(0, L"BGM_Intro");
}
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

	// 백그라운드이미지
	m_pObjectManager->CreateObject_Image(JVector(0, 0), L"NewTitle_background", 1, UISortLayer::BACKGROUND);
	m_pLightAnimation = m_pObjectManager->CreateObject_Image(JVector(629, 260), L"NewTitle_lightcolor_ani", 8, UISortLayer::BUTTON);

	// 타이틀바
	m_pTitleBar = m_pObjectManager->CreateObject_Image(JVector(246, 326), L"NewTitle_ani", 8, UISortLayer::BUTTON);

	m_pObjectManager->CreateObject_Image(JVector(246, 634), L"NewTitle_english", 1, UISortLayer::BACKGROUND);

	// 게임시작버튼
	m_pStartButton = m_pObjectManager->CreateObject_Button(JVector(250, 814), L"NewTitle_StartButton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);
	// 게임종료버튼
	m_pExitButton = m_pObjectManager->CreateObject_Button(JVector(250, 867), L"NewTitle_ExitButton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);

	SoundManager::GetInstance()->Play(0, L"BGM_Main");		// BGM사운드

	// 파일철 초기화
	FileFolder::GetInstance()->Initialize();
}

void IntroTitleScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	// 마우스가 올라가있냐 안올라가있냐?
	m_pObjectManager->UpdateAll(dTime);
	//FileFolder::GetInstance()->Update(dTime);

	m_pObjectManager->CheckButtonClicked(this);

	m_pTitleBar->UpdateAnimation(dTime);
	m_pLightAnimation->UpdateAnimation(dTime);

	/// 시작버튼에 올려두었을 때
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

	// 생성
	/// 종료버튼에 올려두었을 때 
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
			SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");	// 버튼업 했을때 실행된다.
			SceneManager::ChangeScene(eSceneStateAll::INTRO_ANIMATION);
		}
		return;

	case eNowSceneState::GO_TO_PREV_SCENE:
		SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");	// 버튼업 했을때 실행된다.
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
	
	

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;
}


void IntroTitleScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Title 씬");
}

void IntroTitleScene::Release()
{
	Scene::Release();

	SoundManager::GetInstance()->Stop(0, L"BGM_Intro");
}
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

	//배경화면
	m_pBackgroundIMG = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Intro_Background", 1, UISortLayer::BACKGROUND);

	m_pTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(20, 700), L"Intro", UISortLayer::ENDLAYER);
	m_pTextBox->On();
	m_pTextBox->SetStartEndIndex(0, m_pTextBox->GetScriptTextCount());
}

void IntroAnimationScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pObjectManager->UpdateAll(dTime);

	// 대화상자가 켜져있을 경우만 업데이트 해준다.
	m_pTextBox->Update(dTime);

	// 스크립트가 모두 끝났을 때 마우스 누르면 다음 씬으로 이동
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

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;
	
	// 임시 캐릭터
	if (m_pTextBox->GetKeyIndex() < 28)
	{
		m_pTextBox->DrawCharacter(false);
	}
	else
	{
		m_pTextBox->DrawCharacter(true);
	}

	m_pTextBox->Draw(1.0f);

	//JJEngine::GetInstance()->DrawText(700, 500, 1000, 500, 35, ColorF(ColorF::White), L"테스트 버전 ver0.3, 인트로 애니메이션 스킵\n 두 마디만 나옴");
}

void IntroAnimationScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Animation 씬");
}

void IntroAnimationScene::Release()
{
	m_pObjectManager->Release();

	Scene::Release();

	SoundManager::GetInstance()->Stop(0, L"BGM_Intro");
}

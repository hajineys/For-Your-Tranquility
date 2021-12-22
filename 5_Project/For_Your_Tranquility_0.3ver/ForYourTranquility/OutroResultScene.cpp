#include "pch.h"

#include "OutroResultScene.h"
#include "ObjectManager.h"
#include "TextBox.h"
#include "IntroTitleScene.h"
#include "IntroAnimationScene.h"
#include "MainAutopsyRoomScene.h"
#include "MainDissectingRoomScene.h"

OutroResultScene::OutroResultScene()
	:m_pBackgroundIMG(nullptr),
	m_pTextBox(nullptr)
{

}

OutroResultScene::~OutroResultScene()
{

}

void OutroResultScene::Initialize()
{
	// BGM
	SoundManager::GetInstance()->Play(0, L"BGM_Outro");

	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	m_pTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(0, 0), L"Outro", UISortLayer::BUTTON);
	m_pTextBox->SetStartEndIndex(0, m_pTextBox->GetScriptTextCount());

	switch (FileFolder::EndingState)
	{
		case eEnding::None:
			break;
		case eEnding::HeartAttackEnding:			// 심장마비 병사
			m_pTextBox->SetStartEndIndex(0, 10);
			break;
		case eEnding::AlcoholEnding:				// 자살
			m_pTextBox->SetStartEndIndex(11, 22);
			break;
		case eEnding::CirrhosisEnding:				// 간경화 병사
			m_pTextBox->SetStartEndIndex(23, 34);
			break;
		default:
			break;
	}

	// 아웃트로 배경
	m_pBackgroundIMG = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Intro_Background", 1, UISortLayer::BACKGROUND);
}

void OutroResultScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pObjectManager->UpdateAll(dTime);

	/// 대화상자가 켜져 있을 경우만 업데이트 해준다.
	m_pTextBox->Update(dTime);

	// 스크립트가 모두 끝났을 때 마우스 누르면 다음 씬으로 이동

	// 심장마비 엔딩일 때
	if (FileFolder::EndingState == eEnding::HeartAttackEnding && InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->GetKeyIndex() > 10)
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}

	// 알코올중독 엔딩일 때
	if (FileFolder::EndingState == eEnding::AlcoholEnding && InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->GetKeyIndex() > 22)
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}

	// 간경화 엔딩일 때
	if (FileFolder::EndingState == eEnding::CirrhosisEnding && InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->GetKeyIndex() > 34)
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}


	if (m_NowSceneState == eNowSceneState::GO_TO_NEXT_SCENE)
	{
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			SceneManager::ChangeScene(eSceneStateAll::OUTRO_ENDING);
		}
	}
}

void OutroResultScene::Draw()
{
	m_pObjectManager->DrawAll();

	SceneManager::DrawBlackScreen();

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pTextBox->DrawCharacter(false);
	m_pTextBox->Draw(1.0f);

	//ShowDebug();
}

void OutroResultScene::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 40, L"Outro_Result 씬");
}

void OutroResultScene::Release()
{
	m_pObjectManager->Release();

	Scene::Release();

}
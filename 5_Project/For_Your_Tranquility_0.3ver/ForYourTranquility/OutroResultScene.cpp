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
		case eEnding::HeartAttackEnding:			// ���帶�� ����
			m_pTextBox->SetStartEndIndex(0, 10);
			break;
		case eEnding::AlcoholEnding:				// �ڻ�
			m_pTextBox->SetStartEndIndex(11, 22);
			break;
		case eEnding::CirrhosisEnding:				// ����ȭ ����
			m_pTextBox->SetStartEndIndex(23, 34);
			break;
		default:
			break;
	}

	// �ƿ�Ʈ�� ���
	m_pBackgroundIMG = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Intro_Background", 1, UISortLayer::BACKGROUND);
}

void OutroResultScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pObjectManager->UpdateAll(dTime);

	/// ��ȭ���ڰ� ���� ���� ��츸 ������Ʈ ���ش�.
	m_pTextBox->Update(dTime);

	// ��ũ��Ʈ�� ��� ������ �� ���콺 ������ ���� ������ �̵�

	// ���帶�� ������ ��
	if (FileFolder::EndingState == eEnding::HeartAttackEnding && InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->GetKeyIndex() > 10)
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}

	// ���ڿ��ߵ� ������ ��
	if (FileFolder::EndingState == eEnding::AlcoholEnding && InputManager::GetInstance()->CheckLeftButtonUp() && m_pTextBox->GetKeyIndex() > 22)
	{
		m_NowSceneState = eNowSceneState::GO_TO_NEXT_SCENE;
	}

	// ����ȭ ������ ��
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

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	m_pTextBox->DrawCharacter(false);
	m_pTextBox->Draw(1.0f);

	//ShowDebug();
}

void OutroResultScene::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 40, L"Outro_Result ��");
}

void OutroResultScene::Release()
{
	m_pObjectManager->Release();

	Scene::Release();

}
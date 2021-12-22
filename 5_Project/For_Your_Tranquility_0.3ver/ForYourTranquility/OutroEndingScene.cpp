#include "pch.h"

#include "OutroEndingScene.h"
#include "IntroTitleScene.h"
#include "MainOfficeScene.h"
#include "MainIncidentScene.h"
#include "MainAutopsyEntryScene.h"
#include "MainAutopsyRoomScene.h"
#include "MainDissectingRoomScene.h"
#include "Button.h"
#include "Object.h"
#include "ColliderBox.h"
#include "ObjectManager.h"

bool OutroEndingScene::m_IsFirst = false;
bool OutroEndingScene::m_IsFirstPlay[2] = { false, };

OutroEndingScene::OutroEndingScene()
	:m_pBackgroundIMG(nullptr),
	m_pFileIMG(nullptr),
	m_pThankyou(nullptr),
	m_pGoTitle(nullptr),
	m_pExitGame(nullptr),
	m_FirstChoiceStr(L""),
	m_SecondChoiceStr(L""),
	m_ThirdChoiceStr(L"")
{

}

OutroEndingScene::~OutroEndingScene()
{

}

void OutroEndingScene::Initialize()
{
	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	m_pBackgroundIMG = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"ending_background", 1, UISortLayer::BACKGROUND);

	m_pFileIMG = m_pObjectManager->CreateObject_Image(JVector(220, 0), L"ending_page", 1, UISortLayer::BUTTON);

	m_pThankyou = m_pObjectManager->CreateObject_Image(JVector(1125, 338), L"ending_thankyou", 1, UISortLayer::BUTTON);

	m_pGoTitle = m_pObjectManager->CreateObject_Button(JVector(1125, 700), L"ending_ReturnButton", 2, UISortLayer::POPUPWINDOW_OBJECT, eNowSceneState::GO_TO_NEXT_SCENE);
	m_pExitGame = m_pObjectManager->CreateObject_Button(JVector(1122, 750), L"ending_ExitButton", 2, UISortLayer::POPUPWINDOW_OBJECT, eNowSceneState::GO_TO_PREV_SCENE);

	switch (FileFolder::m_FirstChoiceState)
	{
	case eFirstChoiceState::None:
		break;
	case eFirstChoiceState::HeartDisease:
		m_FirstChoiceStr = L"���� ��ȯ���� ����";
		break;
	case eFirstChoiceState::Cirrhosis:
		m_FirstChoiceStr = L"�� ��ȭ�� ����";
		break;
	case eFirstChoiceState::A_Large_Intake_Of_Alcohol:
		m_FirstChoiceStr = L"�ٷ��� ���ڿ� ����� ����";
		break;
	default:
		break;
	}

	switch (FileFolder::m_SecondChoiceState)
	{
	case eSecondChoiceState::None:
		break;
	case eSecondChoiceState::AcuteHeartAttack:
		m_SecondChoiceStr = L"�޼� ���帶���";
		break;
	case eSecondChoiceState::Abnormal_State_Of_Consciousness:
		m_SecondChoiceStr = L"���������� �ǽ� ���·�";
		break;
	case eSecondChoiceState::AlcoholShock:
		m_SecondChoiceStr = L"���ڿ� ��ũ��";
		break;
	default:
		break;
	}

	switch (FileFolder::m_ThirdChoiceState)
	{
	case eThirdChoiceState::None:
		break;
	case eThirdChoiceState::Suicide:
		m_ThirdChoiceStr = L"�ڻ�";
		break;
	case eThirdChoiceState::Murder:
		m_ThirdChoiceStr = L"Ÿ��";
		break;
	case eThirdChoiceState::Death_From_Disease:
		m_ThirdChoiceStr = L"����";
		break;
	default:
		break;
	}
}

void OutroEndingScene::Update(float dTime)
{
	m_pObjectManager->UpdateAll(dTime);
	m_pObjectManager->CheckButtonClicked(this);

	if (m_pGoTitle->GetColliderBox()->IsCollided)
	{
		m_pGoTitle->ChangeFrame(1);

		if (m_IsFirstPlay[0] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			m_IsFirstPlay[0] = true;
		}
	}
	else
	{
		m_pGoTitle->ChangeFrame(0);
		m_IsFirstPlay[0] = false;
	}

	if (m_pExitGame->GetColliderBox()->IsCollided)
	{
		m_pExitGame->ChangeFrame(1);

		if (m_IsFirstPlay[1] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			m_IsFirstPlay[1] = true;
		}
	}
	else
	{
		m_pExitGame->ChangeFrame(0);
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
			SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");		// ��ư�� ������ ����ȴ�.

			/*
			FileFolder::EndingState = eEnding::None;
			FileFolder::m_FirstChoiceState = eFirstChoiceState::None;
			FileFolder::m_SecondChoiceState = eSecondChoiceState::None;
			FileFolder::m_ThirdChoiceState = eThirdChoiceState::None;
			*/

			SceneManager::ChangeScene(eSceneStateAll::INTRO_TITLE);
		}
		return;

	case eNowSceneState::GO_TO_PREV_SCENE:
		SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");			// ��ư�� ������ ����ȴ�.
		exit(0);
		return;

	case eNowSceneState::POPUP_SHOW:
		break;
	}
}

void OutroEndingScene::Draw()
{
	m_pObjectManager->DrawAll();

	// ������ 3
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 575, m_pFileIMG->Transform()->Pos.y + 325, L"����", 45, ColorF(ColorF::DarkRed), m_ThirdChoiceStr.c_str());

	// ������ 1
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 470, L"����", 25, ColorF(ColorF::DarkSlateGray), m_FirstChoiceStr.c_str());

	// ������ 2
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 570, L"����", 25, ColorF(ColorF::DarkSlateGray), m_SecondChoiceStr.c_str());

	// ������ 3
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 840, L"����", 25, ColorF(ColorF::DarkSlateGray), m_ThirdChoiceStr.c_str());

	//ShowDebug();
}

void OutroEndingScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Outro_Ending ��");
}

void OutroEndingScene::Release()
{
	AllStaticFinalize();
	Scene::Release();
	SoundManager::GetInstance()->Stop(0, L"BGM_Outro");
	FileFolder::GetInstance()->Release();
}

void OutroEndingScene::AllStaticFinalize()
{
	// ��Ʈ�� Ÿ��Ʋ ��
	IntroTitleScene::m_IsFirstPlay[0] = false;
	IntroTitleScene::m_IsFirstPlay[1] = false;

	// ���� ���ǽ� ��
	for (int i = 0; i < 22; i++)
	{
		MainOfficeScene::IsPlaying[i] = false;
	}

	MainOfficeScene::m_OnlyOnce = false;

	// ���� ��� �Խ��� ��
	for (int i = 0; i < 5; i++)
	{
		MainIncidentScene::IsPlaying[i] = false;
	}

	// �ΰ˽� ��Ʈ�� ��
	MainAutopsyEntryScene::IsFirstPlay = false;

	// �ΰ˽� ��
	MainAutopsyRoomScene::m_CutFrogHeart = false;
	MainAutopsyRoomScene::m_CutFrogLiver = false;
	MainAutopsyRoomScene::m_CutFrogLungs = false;
	MainAutopsyRoomScene::m_CutFrogStomach01 = false;
	MainAutopsyRoomScene::m_CutFrogStomach02 = false;
	MainAutopsyRoomScene::m_CutFrogStomachFin = false;

	MainAutopsyRoomScene::_OnlyOncePlay = false;

	MainAutopsyRoomScene::CutOrganGuideCollided = false;
	MainAutopsyRoomScene::FrogBodyOpen = false;
	MainAutopsyRoomScene::TrayInOrganState = OrganState::NONE;
	MainAutopsyRoomScene::TrayHadOrgan = 0;

	MainAutopsyRoomScene::m_CutFrogLiverAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogLungAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogStomachAndNextScene = false;

	// �ؽ�Ʈ �ڽ� �ѹ� �÷��̿�
	for (int i = 0; i < 6; i++)
	{
		MainAutopsyRoomScene::m_InOncePlay[i] = false;
	}

	// ���� 
	for (int i = 0; i < 11; i++)
	{
		MainAutopsyRoomScene::IsPlayingAutopsyRoom[i] = false;
	}

	MainAutopsyRoomScene::m_CutFrogLiverAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogLungAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogStomachAndNextScene = false;

	// �غν� ��
	MainDissectingRoomScene::DissectStart = false;

	MainDissectingRoomScene::FrogHeartOpen = false;
	MainDissectingRoomScene::FrogHeartDetailOpen = false;
	MainDissectingRoomScene::FrogLiverOpen = false;
	MainDissectingRoomScene::FrogLungsOpen = false;
	MainDissectingRoomScene::FrogStomach01Open = false;
	MainDissectingRoomScene::FrogStomach02Open = false;
	MainDissectingRoomScene::FrogStomach03Open = false;

	MainDissectingRoomScene::DetailOpenHeartFatCollided = false;

	MainDissectingRoomScene::CutFrogStomach02GuideCollided = false;

	// ��� ���� ä��Ϸ�
	MainDissectingRoomScene::PetrischaleHadHeartPiece = false;
	MainDissectingRoomScene::PetrischaleHadLiverPiece = false;
	MainDissectingRoomScene::PetrischaleHadLungsPiece = false;
	MainDissectingRoomScene::PetrischaleHadStomachPiece = false;

	for (int i = 0; i < 11; i++)
	{
		MainDissectingRoomScene::IsOncePlay[i] = false;
	}

	for (int i = 0; i < 13; i++)
	{
		MainDissectingRoomScene::m_IsFirstPlay[i] = false;
	}

	// ����ö �ʱ�ȭ
	FileFolder::EndingState = eEnding::None;
	FileFolder::m_FirstChoiceState = eFirstChoiceState::None;
	FileFolder::m_SecondChoiceState = eSecondChoiceState::None;
	FileFolder::m_ThirdChoiceState = eThirdChoiceState::None;
}
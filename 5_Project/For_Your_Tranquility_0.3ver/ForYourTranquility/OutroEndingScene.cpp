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
		m_FirstChoiceStr = L"심장 질환으로 인해";
		break;
	case eFirstChoiceState::Cirrhosis:
		m_FirstChoiceStr = L"간 경화로 인해";
		break;
	case eFirstChoiceState::A_Large_Intake_Of_Alcohol:
		m_FirstChoiceStr = L"다량의 알코올 섭취로 인해";
		break;
	default:
		break;
	}

	switch (FileFolder::m_SecondChoiceState)
	{
	case eSecondChoiceState::None:
		break;
	case eSecondChoiceState::AcuteHeartAttack:
		m_SecondChoiceStr = L"급성 심장마비로";
		break;
	case eSecondChoiceState::Abnormal_State_Of_Consciousness:
		m_SecondChoiceStr = L"비정상적인 의식 상태로";
		break;
	case eSecondChoiceState::AlcoholShock:
		m_SecondChoiceStr = L"알코올 쇼크로";
		break;
	default:
		break;
	}

	switch (FileFolder::m_ThirdChoiceState)
	{
	case eThirdChoiceState::None:
		break;
	case eThirdChoiceState::Suicide:
		m_ThirdChoiceStr = L"자살";
		break;
	case eThirdChoiceState::Murder:
		m_ThirdChoiceStr = L"타살";
		break;
	case eThirdChoiceState::Death_From_Disease:
		m_ThirdChoiceStr = L"병사";
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
			SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");		// 버튼업 했을때 실행된다.

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
		SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");			// 버튼업 했을때 실행된다.
		exit(0);
		return;

	case eNowSceneState::POPUP_SHOW:
		break;
	}
}

void OutroEndingScene::Draw()
{
	m_pObjectManager->DrawAll();

	// 선택지 3
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 575, m_pFileIMG->Transform()->Pos.y + 325, L"바탕", 45, ColorF(ColorF::DarkRed), m_ThirdChoiceStr.c_str());

	// 선택지 1
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 470, L"바탕", 25, ColorF(ColorF::DarkSlateGray), m_FirstChoiceStr.c_str());

	// 선택지 2
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 570, L"바탕", 25, ColorF(ColorF::DarkSlateGray), m_SecondChoiceStr.c_str());

	// 선택지 3
	JJEngine::GetInstance()->DrawText(m_pFileIMG->Transform()->Pos.x + 480, m_pFileIMG->Transform()->Pos.y + 840, L"바탕", 25, ColorF(ColorF::DarkSlateGray), m_ThirdChoiceStr.c_str());

	//ShowDebug();
}

void OutroEndingScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Outro_Ending 씬");
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
	// 인트로 타이틀 씬
	IntroTitleScene::m_IsFirstPlay[0] = false;
	IntroTitleScene::m_IsFirstPlay[1] = false;

	// 메인 오피스 씬
	for (int i = 0; i < 22; i++)
	{
		MainOfficeScene::IsPlaying[i] = false;
	}

	MainOfficeScene::m_OnlyOnce = false;

	// 메인 사고 게시판 씬
	for (int i = 0; i < 5; i++)
	{
		MainIncidentScene::IsPlaying[i] = false;
	}

	// 부검실 엔트리 씬
	MainAutopsyEntryScene::IsFirstPlay = false;

	// 부검실 씬
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

	// 텍스트 박스 한번 플레이용
	for (int i = 0; i < 6; i++)
	{
		MainAutopsyRoomScene::m_InOncePlay[i] = false;
	}

	// 사운드 
	for (int i = 0; i < 11; i++)
	{
		MainAutopsyRoomScene::IsPlayingAutopsyRoom[i] = false;
	}

	MainAutopsyRoomScene::m_CutFrogLiverAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogLungAndNextScene = false;
	MainAutopsyRoomScene::m_CutFrogStomachAndNextScene = false;

	// 해부실 씬
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

	// 장기 조각 채취완료
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

	// 파일철 초기화
	FileFolder::EndingState = eEnding::None;
	FileFolder::m_FirstChoiceState = eFirstChoiceState::None;
	FileFolder::m_SecondChoiceState = eSecondChoiceState::None;
	FileFolder::m_ThirdChoiceState = eThirdChoiceState::None;
}
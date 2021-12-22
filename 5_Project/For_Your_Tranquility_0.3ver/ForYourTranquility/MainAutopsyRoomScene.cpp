#include "pch.h"

#include "MainAutopsyRoomScene.h"
#include "MainDissectingRoomScene.h"
#include "Organ.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "ColliderBox.h"
#include "Player.h"
#include "Button.h"
#include "TextBox.h"


// static 멤버 변수 초기화
bool MainAutopsyRoomScene::m_CutFrogHeart = false;
bool MainAutopsyRoomScene::m_CutFrogLiver = false;
bool MainAutopsyRoomScene::m_CutFrogLungs = false;
bool MainAutopsyRoomScene::m_CutFrogStomach01 = false;
bool MainAutopsyRoomScene::m_CutFrogStomach02 = false;
bool MainAutopsyRoomScene::m_CutFrogStomachFin = false;

bool MainAutopsyRoomScene::_OnlyOncePlay = false;

bool MainAutopsyRoomScene::CutOrganGuideCollided = false;
bool MainAutopsyRoomScene::FrogBodyOpen = false;
OrganState MainAutopsyRoomScene::TrayInOrganState = OrganState::NONE;
int MainAutopsyRoomScene::TrayHadOrgan = 0;

bool MainAutopsyRoomScene::m_InOncePlay[11] = { false, };			// 텍스트 박스용
bool MainAutopsyRoomScene::IsPlayingAutopsyRoom[11] = { false, };	// 사운드용

bool MainAutopsyRoomScene::m_CutFrogLiverAndNextScene = false;
bool MainAutopsyRoomScene::m_CutFrogLungAndNextScene = false;
bool MainAutopsyRoomScene::m_CutFrogStomachAndNextScene = false;

MainAutopsyRoomScene::MainAutopsyRoomScene()
	:m_pBakcgorund(nullptr),
	m_pTray(nullptr),
	m_pPrevScene(nullptr),
	m_pMagnifyingGlassButton(nullptr),
	m_pMagnifyingGlassResetButton(nullptr),
	m_pScalpelButton(nullptr),
	m_pScalpelResetButton(nullptr),
	m_pScissorsButton(nullptr),
	m_ppScissorsResetButton(nullptr),
	m_pFrogBody(nullptr),
	m_pFrogBodyCutGuide(nullptr),
	m_pFrogCutBody01(nullptr),
	m_pFrogCutBodyFin(nullptr),
	m_pFrogHead(nullptr),
	m_pFrogHeadImage(nullptr),
	m_pFrogRightArm(nullptr),
	m_pFrogRightArmImage(nullptr),
	m_pFrogRightHand(nullptr),
	m_pFrogRightHandImage(nullptr),
	m_pFrogRightLeg(nullptr),
	m_pFrogRightLegImage(nullptr),
	m_pFrogLeftLeg(nullptr),
	m_pFrogLeftLegImage(nullptr),
	m_pFrogHeartCutGuide(nullptr),
	m_pFrogLiverCutGuide(nullptr),
	m_pFrogLungsCutGuide(nullptr),
	m_pFrogStomachCutGuide01(nullptr),
	m_pFrogStomachCutGuide02(nullptr),
	m_pOrgan(nullptr),
	m_pPlayer(nullptr),
	m_UseMagnifying_Glass(false),
	m_UseScalpel(false),
	m_UseScissors(false),
	m_ClickFrogHead(false),
	m_ClickFrogRightArm(false),
	m_ClickFrogRightHand(false),
	m_ClickFrogRightLeg(false),
	m_ClickFrogLeftLeg(false),
	m_FrogBodyCutPointCollided(0),
	m_PickFrogHeart(false),
	m_PickFrogLiver(false),
	m_PickFrogLungs(false),
	m_PickFrogStomach(false),
	m_OrganInTray(false),
	m_MainAutopsyRoomTextBox(nullptr)
{

}

MainAutopsyRoomScene::~MainAutopsyRoomScene()
{

}

void MainAutopsyRoomScene::Initialize()
{
	Scene::Initialize();
	InputManager::GetInstance()->Reset();

	/// 대화상자
	m_MainAutopsyRoomTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(20, 700), L"MainAutopsyRoomScene", UISortLayer::ENDLAYER);

	// 플레이어
	m_pPlayer = new Player();
	m_pPlayer->Initialize();

	// 배경이미지
	m_pBakcgorund = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"AutopsyRoom_TableBackground", 1, UISortLayer::BACKGROUND);

	// 버튼
	m_pPrevScene = m_pObjectManager->CreateObject_Button(JVector(10, 1000), L"icon_backtoOffice", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);
	m_pTray = m_pObjectManager->CreateObject_Button(JVector(533, 779), L"Tray_Ani", 10, UISortLayer::PLAYER, eNowSceneState::GO_TO_NEXT_SCENE);

	// 파일철 버튼
	m_pFileFolderButton = m_pObjectManager->CreateObject_Button(JVector(1625, 780), L"Note", 1, UISortLayer::BUTTON, eNowSceneState::NONE);

	// 도구 선택 버튼
	m_pMagnifyingGlassButton = m_pObjectManager->CreateObject_Button(JVector(1126, 816), L"MagnifyingGlass", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMagnifyingGlassButton->GetColliderBox()->SetSize(JVector(110, 130));
	m_pMagnifyingGlassResetButton = m_pObjectManager->CreateObject_Button(JVector(1146, 850), L"TrayReset", { 110, 130 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	m_pScalpelButton = m_pObjectManager->CreateObject_Button(JVector(1275, 815), L"Scalpel", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pScalpelButton->GetColliderBox()->SetSize(JVector(110, 130));
	m_pScalpelResetButton = m_pObjectManager->CreateObject_Button(JVector(1295, 850), L"TrayReset", { 110, 130 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	m_pScissorsButton = m_pObjectManager->CreateObject_Button(JVector(1408, 814), L"Scissors", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pScissorsButton->GetColliderBox()->SetSize(JVector(110, 130));
	m_ppScissorsResetButton = m_pObjectManager->CreateObject_Button(JVector(1428, 850), L"TrayReset", { 110, 130 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	// 개구리 시신 버튼
	m_pFrogBody = m_pObjectManager->CreateObject_Button(JVector(439, -28), L"Autopsy_frog_normal", 1, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogBody->GetColliderBox()->SetSize(JVector(900, 400));
	m_pFrogBodyCutGuide = m_pObjectManager->OnlyCreateObject_Image(JVector(703, 354), L"frog_line", 3, UISortLayer::POPUPWINDOW);

	m_pFrogBodyCutPoint[0] = m_pObjectManager->CreateObject_Button(JVector(697, 350), L"Cut00Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[1] = m_pObjectManager->CreateObject_Button(JVector(720, 370), L"Cut01Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[2] = m_pObjectManager->CreateObject_Button(JVector(735, 390), L"Cut02Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[3] = m_pObjectManager->CreateObject_Button(JVector(695, 465), L"Cut03Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[4] = m_pObjectManager->CreateObject_Button(JVector(718, 442), L"Cut04Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[5] = m_pObjectManager->CreateObject_Button(JVector(740, 423), L"Cut05Point", { 30, 30 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[6] = m_pObjectManager->CreateObject_Button(JVector(767, 395), L"Cut06Point", { 50, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[7] = m_pObjectManager->CreateObject_Button(JVector(813, 398), L"Cut07Point", { 50, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[8] = m_pObjectManager->CreateObject_Button(JVector(861, 397), L"Cut08Point", { 50, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[9] = m_pObjectManager->CreateObject_Button(JVector(907, 399), L"Cut09Point", { 50, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[10] = m_pObjectManager->CreateObject_Button(JVector(954, 397), L"Cut10Point", { 50, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogBodyCutPoint[11] = m_pObjectManager->CreateObject_Button(JVector(1000, 397), L"Cut10Point", { 30, 35 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogBodyCutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 12; i++)
	{
		bool _false = false;
		m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] = false;
	}

	m_pFrogCutBodyFin = m_pObjectManager->OnlyCreateObject_Button(JVector(439, -28), L"Autopsy_frogCut_Ani4", 4, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	// 돋보기 확대 버튼
	m_pFrogHead = m_pObjectManager->CreateObject_Button(JVector(430, 313), L"FrogHead", { 250, 250 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogHeadImage = m_pObjectManager->OnlyCreateObject_Button(JVector(320, 320), L"MagnifyingGlass_Face", 1, UISortLayer::POPUPWINDOWBUTTON);

	m_pFrogRightArm = m_pObjectManager->CreateObject_Button(JVector(680, 540), L"FrogRightArm", { 160, 160 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogRightArmImage = m_pObjectManager->OnlyCreateObject_Button(JVector(610, 480), L"MagnifyingGlass_Arm", 1, UISortLayer::POPUPWINDOWBUTTON);

	m_pFrogRightHand = m_pObjectManager->CreateObject_Button(JVector(840, 680), L"FrogRightHand", { 130, 130 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogRightHandImage = m_pObjectManager->OnlyCreateObject_Button(JVector(750, 610), L"MagnifyingGlass_Hand", 1, UISortLayer::POPUPWINDOWBUTTON);

	m_pFrogRightLeg = m_pObjectManager->CreateObject_Button(JVector(1130, 485), L"pFrogRightLeg", { 300, 160 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogRightLegImage = m_pObjectManager->OnlyCreateObject_Button(JVector(1080, 450), L"MagnifyingGlass_RightLeg", 1, UISortLayer::POPUPWINDOWBUTTON);

	m_pFrogLeftLeg = m_pObjectManager->CreateObject_Button(JVector(1130, 150), L"FrogLeftLeg", { 300, 155 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);
	m_pFrogLeftLegImage = m_pObjectManager->OnlyCreateObject_Button(JVector(1080, 80), L"MagnifyingGlass_LeftLeg", 1, UISortLayer::POPUPWINDOWBUTTON);

	// 개구리 장기 버튼
	m_pFrogOrgan[static_cast<int>(OrganState::ECT3)] = m_pObjectManager->OnlyCreateObject_Button(JVector(868, 300), L"Autopsy_ect3", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::POPUP_SHOW);
	m_pFrogOrgan[static_cast<int>(OrganState::BONE)] = m_pObjectManager->OnlyCreateObject_Button(JVector(750, 330), L"Autopsy_bone", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::POPUP_SHOW);
	m_pFrogOrgan[static_cast<int>(OrganState::ECT4)] = m_pObjectManager->OnlyCreateObject_Button(JVector(855, 442), L"Autopsy_ect4", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::POPUP_SHOW);
	m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)] = m_pObjectManager->OnlyCreateObject_Button(JVector(737, 266), L"Autopsy_stomach", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->GetColliderBox()->SetSize(JVector(300, 300));
	m_pFrogStomachCutGuide01 = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"organs_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogStomachCutGuide01->GetColliderBox()->SetSize(JVector(20, 80));
	m_pFrogStomachCutGuide02 = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"organs_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogStomachCutGuide02->GetColliderBox()->SetSize(JVector(20, 80));

	m_pFrogOrgan[static_cast<int>(OrganState::ECT2)] = m_pObjectManager->OnlyCreateObject_Button(JVector(953, 387), L"Autopsy_ect2", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)] = m_pObjectManager->OnlyCreateObject_Button(JVector(841, 348), L"Autopsy_lungs", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogLungsCutGuide = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"organs_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogLungsCutGuide->GetColliderBox()->SetSize(JVector(20, 80));

	m_pFrogOrgan[static_cast<int>(OrganState::LIVER)] = m_pObjectManager->OnlyCreateObject_Button(JVector(745, 305), L"Autopsy_liver", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogLiverCutGuide = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"organs_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogLiverCutGuide->GetColliderBox()->SetSize(JVector(20, 80));

	m_pFrogOrgan[static_cast<int>(OrganState::HEART)] = m_pObjectManager->OnlyCreateObject_Button(JVector(698, 364), L"Autopsy_heart", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogHeartCutGuide = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"organs_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogHeartCutGuide->GetColliderBox()->SetSize(JVector(20, 80));

	// 상호작용 객체
	m_pOrgan = new Organ(UISortLayer::POPUPWINDOW);
	m_pOrgan->Initialize(JVector(0, 0), L"Organ");

	if (_OnlyOncePlay)
		m_pFrogCutBodyFin->ChangeFrame(3);

	// 버그를 잡자...........
	if (m_CutFrogLiver)
		m_CutFrogLiverAndNextScene = true;
	if (m_CutFrogLungs)
		m_CutFrogLungAndNextScene = true;
	if (m_CutFrogStomach01)	// 위장이 다 잘렸을 때
		m_CutFrogStomachAndNextScene = true;
}

void MainAutopsyRoomScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	if (m_pPrevScene->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Button_Door");
	}

	/// 대화상자가 켜져 있을 경우만 업데이트 해준다.
	m_MainAutopsyRoomTextBox->Update(dTime);

	/// 대화상자가 올라와져 있으면 다른곳 클릭안됨
	if (m_MainAutopsyRoomTextBox->GetState())
		return;

	switch (m_NowSceneState)
	{
	case eNowSceneState::NONE:
		break;

	case eNowSceneState::GO_TO_NEXT_SCENE:
	{
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			if (m_IsGameEnd)
			{
				SoundManager::GetInstance()->Stop(2, L"BGM_Office");
				SoundManager::GetInstance()->Stop(3, L"BGM_Room");
				SceneManager::ChangeScene(eSceneStateAll::OUTRO_RESULT);
				return;
			}
			else
			{
				SceneManager::ChangeScene(eSceneStateAll::MAIN_DISSECTING);
				return;
			}
		}
	}
	break;

	case eNowSceneState::GO_TO_PREV_SCENE:
	{
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			SceneManager::ChangeScene(eSceneStateAll::MAIN_OFFICE);
			return;
		}
	}
	break;

	case eNowSceneState::POPUP_SHOW:
		break;
	}

	FileFolder::GetInstance()->Update(dTime, this);

	if (FileFolder::GetInstance()->GetNowState())
	{
		return;
	}

	if (m_pFileFolderButton->GetColliderBox()->IsClicked)
	{
		FileFolder::GetInstance()->On();
	}

	m_pObjectManager->CheckButtonClicked(this);

	m_pTray->Update(dTime);

	m_pObjectManager->UpdateAll(dTime);

	/// 해부실 입장시 나오는 대화상자.
	if (m_InOncePlay[0] == false)
	{
		m_MainAutopsyRoomTextBox->SetStartEndIndex(5, 5);
		m_InOncePlay[0] = true;
	}
	// 트레이 상태에 따라 다르게 이미지 출력
	if (m_pTray->GetColliderBox()->IsCollided)
	{
		if (TrayHadOrgan == 1)
		{
			m_pTray->ChangeFrame(3);
		}
		else if (TrayHadOrgan == 2)
		{
			m_pTray->ChangeFrame(5);
		}
		else if (TrayHadOrgan == 3)
		{
			m_pTray->ChangeFrame(7);
		}
		else if (TrayHadOrgan == 4)
		{
			m_pTray->ChangeFrame(9);
		}
		else
		{
			m_pTray->ChangeFrame(1);
		}
	}
	else
	{
		if (TrayHadOrgan == 1)
		{
			m_pTray->ChangeFrame(2);
		}
		else if (TrayHadOrgan == 2)
		{
			m_pTray->ChangeFrame(4);
		}
		else if (TrayHadOrgan == 3)
		{
			m_pTray->ChangeFrame(6);
		}
		else if (TrayHadOrgan == 4)
		{
			m_pTray->ChangeFrame(8);
		}
		else
		{
			m_pTray->ChangeFrame(0);
		}
	}

	// 장기들을 업데이트한다.
	for (int i = 0; i < static_cast<int>(OrganState::NONE); i++)
	{
		m_pFrogOrgan[i]->Update(dTime);
	}

	m_pPlayer->Update(dTime);

	POINT _mousePos = InputManager::GetInstance()->GetMousePos();

	/// 도구 선택 및 제자리 돌려놓기
	// 부검실 돋보기
	if (m_pMagnifyingGlassButton->GetColliderBox()->IsClicked || m_pMagnifyingGlassResetButton->GetColliderBox()->IsClicked)
	{
		if (m_UseMagnifying_Glass == true && m_pMagnifyingGlassResetButton->GetColliderBox()->IsClicked)
		{
			m_UseMagnifying_Glass = false;
			m_pMagnifyingGlassButton->Transform()->Pos = { 1126, 816 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
			SoundManager::GetInstance()->Play(1, L"Button_Down");				// 집을때 사운드
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::AUTOPSY_MAGNIFYING_GLASS);
			m_pPlayer->SetHadToolState(true);

			m_UseMagnifying_Glass = true;
			m_UseScalpel = false;
			m_UseScissors = false;

			m_pMagnifyingGlassButton->Transform()->Pos = { -1126, -816 };
			m_pScalpelButton->Transform()->Pos = { 1275, 815 };
			m_pScissorsButton->Transform()->Pos = { 1408, 814 };
			SoundManager::GetInstance()->Play(1, L"Button_Down");				// 내려놓을때 사운드
		}
	}
	// 부검실 메스
	else if (m_pScalpelButton->GetColliderBox()->IsClicked || m_pScalpelResetButton->GetColliderBox()->IsClicked)
	{
		if (m_UseScalpel == true && m_pScalpelResetButton->GetColliderBox()->IsClicked)
		{
			m_UseScalpel = false;
			m_pScalpelButton->Transform()->Pos = { 1275, 815 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
			SoundManager::GetInstance()->Play(1, L"Button_Down"); // 집을때 사운드
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::AUTOPSY_SCALPEL);
			m_pPlayer->SetHadToolState(true);

			m_UseMagnifying_Glass = false;
			m_UseScalpel = true;
			m_UseScissors = false;

			m_pMagnifyingGlassButton->Transform()->Pos = { 1126, 816 };
			m_pScalpelButton->Transform()->Pos = { -1275, -815 };
			m_pScissorsButton->Transform()->Pos = { 1408, 814 };
			SoundManager::GetInstance()->Play(1, L"Button_Down"); // 내려놓을때 사운드
		}
	}
	// 부검실 가위
	else if (m_pScissorsButton->GetColliderBox()->IsClicked || m_ppScissorsResetButton->GetColliderBox()->IsClicked)
	{
		if (m_UseScissors == true && m_ppScissorsResetButton->GetColliderBox()->IsClicked)
		{
			m_UseScissors = false;
			m_pScissorsButton->Transform()->Pos = { 1408, 814 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
			SoundManager::GetInstance()->Play(1, L"Button_Down"); // 집을때 사운드
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::AUTOPSY_SCISSORS);
			m_pPlayer->SetHadToolState(true);

			m_UseMagnifying_Glass = false;
			m_UseScalpel = false;
			m_UseScissors = true;

			m_pMagnifyingGlassButton->Transform()->Pos = { 1126, 816 };
			m_pScalpelButton->Transform()->Pos = { 1275, 815 };
			m_pScissorsButton->Transform()->Pos = { -1408, -814 };
			SoundManager::GetInstance()->Play(1, L"Button_Down"); // 내려놓을때 사운드
		}
	}

	if (m_pPlayer->GetHadToolState() == true)
	{
		m_pPlayer->GetTools(ToolType::AUTOPSY_MAGNIFYING_GLASS)->Transform()->SetPos(_mousePos.x, _mousePos.y);
		m_pPlayer->GetTools(ToolType::AUTOPSY_SCALPEL)->Transform()->SetPos(_mousePos.x, _mousePos.y);
		m_pPlayer->GetTools(ToolType::AUTOPSY_SCISSORS)->Transform()->SetPos(_mousePos.x, _mousePos.y);
	}

	/// 돋보기로 시신 부분 확대 버튼
	if (m_UseMagnifying_Glass == true && m_pFrogHead->GetColliderBox()->IsClicked)
	{
		if (FrogBodyOpen == true) {}

		else
		{
			m_ClickFrogHead = true;

			// 파일철 상태 최신화
			FileFolder::GetInstance()->IsCheckHead = true;
			SoundManager::GetInstance()->Play(1, L"Tool_Magnifier_Use.wav"); // 시신확인 사운드
		}
	}
	else if (m_UseMagnifying_Glass == true && m_pFrogRightArm->GetColliderBox()->IsClicked)
	{
		if (FrogBodyOpen == true) {}
		else
		{
			m_ClickFrogRightArm = true;

			// 파일철 상태 최신화
			FileFolder::GetInstance()->IsCheckArm = true;
			SoundManager::GetInstance()->Play(1, L"Tool_Magnifier_Use.wav"); // 시신확인 사운드
		}
	}
	else if (m_UseMagnifying_Glass == true && m_pFrogRightHand->GetColliderBox()->IsClicked)
	{
		if (FrogBodyOpen == true) {}
		else
		{
			m_ClickFrogRightHand = true;

			// 파일철 상태 최신화
			FileFolder::GetInstance()->IsCheckHand = true;
			SoundManager::GetInstance()->Play(1, L"Tool_Magnifier_Use.wav"); // 시신확인 사운드
		}
	}
	else if (m_UseMagnifying_Glass == true && m_pFrogRightLeg->GetColliderBox()->IsClicked)
	{
		if (FrogBodyOpen == true) {}
		else
		{
			m_ClickFrogRightLeg = true;

			// 파일철 상태 최신화
			FileFolder::GetInstance()->IsCheckLeg = true;
			SoundManager::GetInstance()->Play(1, L"Tool_Magnifier_Use.wav"); // 시신확인 사운드
		}
	}
	else if (m_UseMagnifying_Glass == true && m_pFrogLeftLeg->GetColliderBox()->IsClicked)
	{
		if (FrogBodyOpen == true) {}
		else
		{
			m_ClickFrogLeftLeg = true;

			// 파일철 상태 최신화
			FileFolder::GetInstance()->IsCheckLeg = true;
			SoundManager::GetInstance()->Play(1, L"Tool_Magnifier_Use.wav"); // 시신확인 사운드
		}
	}
	else if (m_pBakcgorund->GetColliderBox()->IsClicked || m_UseMagnifying_Glass == false)
	{
		m_ClickFrogHead = false;
		m_ClickFrogRightArm = false;
		m_ClickFrogRightHand = false;
		m_ClickFrogRightLeg = false;
		m_ClickFrogLeftLeg = false;
	}

	// 배 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 12; i++)
	{
		m_pFrogBodyCutPoint[i]->Update(dTime);
	}

	// 메스로 배 가르는 상호작용
	if (m_UseScalpel)
	{
		// CutPoint에 맞춰 변경되는 부검실 메스 이미지
		for (int i = 0; i < 3; i++)
		{
			if (m_pFrogBodyCutPoint[i]->GetColliderBox()->IsCollided)
			{
				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{
						// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogBodyCutPointCollided++;
						m_pPlayer->GetTools(ToolType::AUTOPSY_SCALPEL)->ChangeMotionFrame(2);
					}
					m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] = true;
				}
			}
		}

		for (int i = 3; i < 6; i++)
		{
			if (m_pFrogBodyCutPoint[i]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
			{
				m_pPlayer->GetTools(ToolType::AUTOPSY_SCALPEL)->ChangeMotionFrame(1);

				if (m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] == false)
				{
					m_FrogBodyCutPointCollided++;
				}

				m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] = true;
			}
		}

		for (int i = 6; i < 12; i++)
		{
			if (m_pFrogBodyCutPoint[i]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
			{
				m_pPlayer->GetTools(ToolType::AUTOPSY_SCALPEL)->ChangeMotionFrame(3);

				if (m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] == false)
				{
					m_FrogBodyCutPointCollided++;
				}
				m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[i]] = true;
			}
		}
	}

	// 11번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (배를 다 쨌음)
	if (m_FrogBodyCutPointCollided == 12 && m_IsFrogBodyCutPointDownMap[m_pFrogBodyCutPoint[11]] == true)
	{
		FrogBodyOpen = true;
		if (IsPlayingAutopsyRoom[0] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting"); // 시신확인 사운드
			IsPlayingAutopsyRoom[0] = true;
		}
	}
	if (FrogBodyOpen)
	{
		if (_OnlyOncePlay == false)
		{
			if (m_pFrogCutBodyFin->PlayAnimation(dTime, 0.6f))
			{
				_OnlyOncePlay = true;
			}
		}
		else
		{
			m_pFrogCutBodyFin->ChangeFrame(3);

			if (m_InOncePlay[1] == false)
			{
				m_MainAutopsyRoomTextBox->SetStartEndIndex(4, 4);
				m_InOncePlay[1] = true;
			}
		}
	}

	// 장기 컷팅 관련 객체 업데이트
	m_pFrogHeartCutGuide->Update(dTime);
	m_pFrogLiverCutGuide->Update(dTime);
	m_pFrogLungsCutGuide->Update(dTime);
	m_pFrogStomachCutGuide01->Update(dTime);
	m_pFrogStomachCutGuide02->Update(dTime);

	// 장기 자르기
	if (m_UseScissors)
	{
		if (m_pFrogHeartCutGuide->GetColliderBox()->IsCollided
			|| m_pFrogLiverCutGuide->GetColliderBox()->IsCollided
			|| m_pFrogLungsCutGuide->GetColliderBox()->IsCollided
			|| m_pFrogStomachCutGuide01->GetColliderBox()->IsCollided
			|| m_pFrogStomachCutGuide02->GetColliderBox()->IsCollided)
		{
			CutOrganGuideCollided = true;
		}
		else CutOrganGuideCollided = false;

		if (FrogBodyOpen == true && m_InOncePlay[6] == false)
		{
			m_pFrogHeartCutGuide->Transform()->Pos = { 725, 382 };
			m_InOncePlay[6] = true;
		}

		if (m_CutFrogHeart == true && FrogBodyOpen == true)
		{
			m_pFrogLiverCutGuide->Transform()->Pos = { 910, 385 };
		}

		if (m_CutFrogLiverAndNextScene == true && FrogBodyOpen == true && m_InOncePlay[8] == false)
		{
			m_pFrogLungsCutGuide->Transform()->Pos = { 875, 380 };
			m_InOncePlay[8] = true;
		}

		if (m_CutFrogLungAndNextScene == true && FrogBodyOpen == true && m_InOncePlay[9] == false)
		{
			m_pFrogStomachCutGuide01->Transform()->Pos = { 804, 373 };
			m_InOncePlay[9] = true;
		}

		if (m_CutFrogLungAndNextScene == true && FrogBodyOpen == true && m_InOncePlay[10] == false)
		{
			m_pFrogStomachCutGuide02->Transform()->Pos = { 860, 420 };
			m_InOncePlay[10] = true;
		}

		if (m_pFrogHeartCutGuide->GetColliderBox()->IsClicked)
		{
			if (IsPlayingAutopsyRoom[1] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");
				IsPlayingAutopsyRoom[1] = true;
			}

			m_CutFrogHeart = true;
			m_pPlayer->GetTools(ToolType::AUTOPSY_SCISSORS)->ChangeMotionFrame(2);
			m_pFrogHeartCutGuide->Transform()->Pos = { -500, -500 };
		}
		// 가위로 자르는 부분
		else if (m_CutFrogHeart == true && m_pFrogLiverCutGuide->GetColliderBox()->IsClicked)
		{
			if (IsPlayingAutopsyRoom[2] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");
				IsPlayingAutopsyRoom[2] = true;
				/// 심장 & 간
				m_MainAutopsyRoomTextBox->SetStartEndIndex(6, 6);
			}

			m_CutFrogLiver = true;
			m_pFrogLiverCutGuide->Transform()->Pos = { -500, -500 };
		}
		// 폐를 자른다.
		else if (m_CutFrogHeart == true && m_CutFrogLiver == true && m_pFrogLungsCutGuide->GetColliderBox()->IsClicked)
		{
			if (IsPlayingAutopsyRoom[3] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");
				IsPlayingAutopsyRoom[3] = true;
			}

			m_CutFrogLungs = true;
			m_pFrogLungsCutGuide->Transform()->Pos = { -500, -500 };
		}
		else if (m_CutFrogHeart == true && m_CutFrogLiver == true && m_CutFrogLungs == true && m_pFrogStomachCutGuide01->GetColliderBox()->IsClicked)
		{
			if (IsPlayingAutopsyRoom[4] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");
				IsPlayingAutopsyRoom[4] = true;
			}

			m_CutFrogStomach01 = true;
			m_pFrogStomachCutGuide01->Transform()->Pos = { -500, -500 };
		}
		else if (m_CutFrogHeart == true && m_CutFrogLiver == true && m_CutFrogLungs == true && m_CutFrogStomach01 == true
			&& m_pFrogStomachCutGuide02->GetColliderBox()->IsClicked)
		{
			if (IsPlayingAutopsyRoom[5] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");
				IsPlayingAutopsyRoom[5] = true;
			}

			m_CutFrogStomach02 = true;
			m_pFrogStomachCutGuide02->Transform()->Pos = { -500, -500 };
		}
	}

	if (m_CutFrogStomach01 && m_CutFrogStomach02)
	{
		m_CutFrogStomachFin = true;
	}

	/// 장기 드래그해서 트레이에 옮기기
	if (m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && m_CutFrogHeart == true)
	{
		if (m_UseMagnifying_Glass == true || m_UseScalpel == true || m_UseScissors == true) {}
		else
		{
			m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Transform()->Pos.x = _mousePos.x - m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Transform()->Size.x / 2;
			m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Transform()->Pos.y = _mousePos.y - m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Transform()->Size.y / 2;

			m_PickFrogHeart = true;

			if (IsPlayingAutopsyRoom[6] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Orgen_01");
				IsPlayingAutopsyRoom[6] = true;
			}
		}

		TrayInOrganState = OrganState::HEART;
	}
	else if (m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && m_CutFrogLiver == true
		&& MainAutopsyRoomScene::TrayHadOrgan == 1)
	{
		if (m_UseMagnifying_Glass == true || m_UseScalpel == true || m_UseScissors == true) {}
		else
		{
			m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Transform()->Pos.x = _mousePos.x - m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Transform()->Size.x / 2;
			m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Transform()->Pos.y = _mousePos.y - m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Transform()->Size.y / 2;

			m_PickFrogLiver = true;

			if (IsPlayingAutopsyRoom[7] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Orgen_01");
				IsPlayingAutopsyRoom[7] = true;
			}
		}

		TrayInOrganState = OrganState::LIVER;
	}
	else if (m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && m_CutFrogLungs == true
		&& MainAutopsyRoomScene::TrayHadOrgan == 2)
	{
		if (m_UseMagnifying_Glass == true || m_UseScalpel == true || m_UseScissors == true) {}
		else
		{
			m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Transform()->Pos.x = _mousePos.x - m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Transform()->Size.x / 2;
			m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Transform()->Pos.y = _mousePos.y - m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Transform()->Size.y / 2;

			m_PickFrogLungs = true;

			if (IsPlayingAutopsyRoom[8] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Orgen_01");
				IsPlayingAutopsyRoom[8] = true;
			}
		}

		TrayInOrganState = OrganState::LUNGS;
	}
	else if (m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && m_CutFrogStomachFin == true
		&& MainAutopsyRoomScene::TrayHadOrgan == 3)
	{
		if (m_UseMagnifying_Glass == true || m_UseScalpel == true || m_UseScissors == true) {}
		else
		{
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Transform()->Pos.x = _mousePos.x - m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Transform()->Size.x / 2;
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Transform()->Pos.y = _mousePos.y - m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Transform()->Size.y / 2;

			m_PickFrogStomach = true;

			if (IsPlayingAutopsyRoom[9] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Orgen_01");
				IsPlayingAutopsyRoom[9] = true;
			}
		}

		TrayInOrganState = OrganState::STOMACH;
	}
	else
	{
		m_PickFrogHeart = false;
		m_PickFrogLiver = false;
		m_PickFrogLungs = false;
		m_PickFrogStomach = false;
	}

	/// 트레이에 장기 옮길때마다 TrayHadOrgan++;
	for (int i = 0; i < static_cast<int>(OrganState::NONE); i++)
	{
		if (m_pTray->GetColliderBox()->CheckCollidedObject(m_pFrogOrgan[i]) && InputManager::GetInstance()->CheckLeftButtonUp())
		{
			if (m_OrganInTray == false)
				TrayHadOrgan++;

			m_OrganInTray = true;

			if (IsPlayingAutopsyRoom[10] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Orgen_01");
				IsPlayingAutopsyRoom[10] = true;
			}
		}
		else
		{
			IsPlayingAutopsyRoom[10] = false;
		}
	}

	if (m_OrganInTray == true || MainDissectingRoomScene::DissectStart == true)
	{
		m_pTray->SetStateForClicked(eNowSceneState::GO_TO_NEXT_SCENE);
	}
	else m_pTray->SetStateForClicked(eNowSceneState::NONE);

	/// 다른 장기 집을때 트레이에 들어간 장기는 사라지게 만듬
	if (m_PickFrogHeart == false && m_PickFrogLiver == true)
	{
		m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Transform()->Pos = { 699, -363 };
		m_OrganInTray = false;
	}
	else if (m_PickFrogHeart == false && m_PickFrogLiver == false && m_PickFrogLungs == true)
	{
		m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Transform()->Pos = { 745, -305 };
		m_OrganInTray = false;
	}
	else if (m_PickFrogHeart == false && m_PickFrogLiver == false && m_PickFrogLungs == false && m_PickFrogStomach == true)
	{
		m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Transform()->Pos = { 840, -346 };
		m_OrganInTray = false;
	}
}

void MainAutopsyRoomScene::Draw()
{
	m_pObjectManager->DrawAll();

	if (FrogBodyOpen)
	{
		m_pFrogCutBodyFin->Draw();
	}

	if (TrayHadOrgan == 1)
	{
		m_pTray->ChangeFrame(2);
	}
	else if (TrayHadOrgan == 2)
	{
		m_pTray->ChangeFrame(4);
	}
	else if (TrayHadOrgan == 3)
	{
		m_pTray->ChangeFrame(6);
	}
	else if (TrayHadOrgan == 4)
	{
		m_pTray->ChangeFrame(8);
	}

	// 부검실 메스 선택 시 개봉가이드 선 표시
	if (m_UseScalpel == true && !FrogBodyOpen)
	{
		m_pFrogBodyCutGuide->Draw(0.7f);
	}

	if (FrogBodyOpen && m_pFrogCutBodyFin->GetNowFrame() >= 3)
	{
		switch (TrayHadOrgan)
		{
		case 0:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::HEART)]->Draw();
			break;

		case 1:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::LIVER)]->Draw();
			break;

		case 2:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::LUNGS)]->Draw();
			break;

		case 3:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::STOMACH)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			break;

		case 4:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			break;

		case 5:
			m_pFrogOrgan[static_cast<int>(OrganState::ECT3)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::BONE)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT4)]->Draw();
			m_pFrogOrgan[static_cast<int>(OrganState::ECT2)]->Draw();
			break;
		}
	}

	/// 장기 컷 점선 표시
	if (m_UseScissors == true && FrogBodyOpen && TrayHadOrgan == 3
		&& MainDissectingRoomScene::FrogStomach01Open == false && MainDissectingRoomScene::FrogStomach02Open == false && MainDissectingRoomScene::FrogStomach03Open == false)
	{
		m_pFrogStomachCutGuide02->Draw(0.7f);
	}

	if (m_UseScissors == true && FrogBodyOpen && TrayHadOrgan == 3
		&& MainDissectingRoomScene::FrogStomach01Open == false && MainDissectingRoomScene::FrogStomach02Open == false && MainDissectingRoomScene::FrogStomach03Open == false)
	{
		m_pFrogStomachCutGuide01->Draw(0.7f);
	}

	if (m_UseScissors == true && FrogBodyOpen && TrayHadOrgan == 2 && MainDissectingRoomScene::FrogLungsOpen == false)
	{
		m_pFrogLungsCutGuide->Draw(0.7f);
	}

	if (m_UseScissors == true && FrogBodyOpen && m_CutFrogLiver == false && MainDissectingRoomScene::FrogLiverOpen == false)
	{
		m_pFrogLiverCutGuide->Draw(0.7f);
	}

	if (m_UseScissors == true && FrogBodyOpen && m_CutFrogHeart == false && MainDissectingRoomScene::FrogHeartOpen == false)
	{
		m_pFrogHeartCutGuide->Draw(0.7f);
	}

	// 돋보기 확대 이미지 출력
	if (m_ClickFrogHead)
	{
		m_pFrogHeadImage->Draw();
		if (m_InOncePlay[2] == false)
		{
			m_MainAutopsyRoomTextBox->SetStartEndIndex(0, 0);
			m_InOncePlay[2] = true;
		}
	}
	else if (m_ClickFrogRightArm)
	{
		m_pFrogRightArmImage->Draw();
		if (m_InOncePlay[3] == false)
		{
			m_MainAutopsyRoomTextBox->SetStartEndIndex(1, 1);
			m_InOncePlay[3] = true;
		}
	}
	else if (m_ClickFrogRightHand)
	{
		m_pFrogRightHandImage->Draw();
		if (m_InOncePlay[4] == false)
		{
			m_MainAutopsyRoomTextBox->SetStartEndIndex(2, 2);
			m_InOncePlay[4] = true;
		}
	}
	else if (m_ClickFrogRightLeg)
	{
		m_pFrogRightLegImage->Draw();
		if (m_InOncePlay[5] == false)
		{
			m_MainAutopsyRoomTextBox->SetStartEndIndex(3, 3);
			m_InOncePlay[5] = true;
		}
	}
	else if (m_ClickFrogLeftLeg)
	{
		m_pFrogLeftLegImage->Draw();
	}

	m_pPlayer->Draw();

	// 파일철 그리기
	if (FileFolder::GetInstance()->GetNowState())
		FileFolder::GetInstance()->Draw();

	// 페이드 아웃
	SceneManager::DrawBlackScreen();

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	// 텍스트 박스 드로우
	m_MainAutopsyRoomTextBox->Draw();

	//ShowDebug();
}

void MainAutopsyRoomScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Main_AutopsyRoom 씬");
	JJEngine::GetInstance()->DrawText(0, 60, L"Use Magnifying_Glass : %d", m_UseMagnifying_Glass);
	JJEngine::GetInstance()->DrawText(0, 80, L"Use Scalpel : %d", m_UseScalpel);
	JJEngine::GetInstance()->DrawText(0, 100, L"Use Scissors : %d", m_UseScissors);
	JJEngine::GetInstance()->DrawText(0, 120, L"Tray Organ Count : %d", TrayHadOrgan);
	JJEngine::GetInstance()->DrawText(0, 140, L"Cut Frog Heart : %d", m_CutFrogHeart);
	JJEngine::GetInstance()->DrawText(0, 160, L"Cut Frog Liver : %d", m_CutFrogLiver);
	JJEngine::GetInstance()->DrawText(0, 180, L"Cut Frog Lung : %d", m_CutFrogLungs);
	JJEngine::GetInstance()->DrawText(0, 200, L"Cut Frog Stomach01 : %d", m_CutFrogStomach01);
	JJEngine::GetInstance()->DrawText(0, 220, L"Cut Frog Stomach02 : %d", m_CutFrogStomach02);
	JJEngine::GetInstance()->DrawText(0, 240, L"Cut Frog Stomach Fin : %d", m_CutFrogStomachFin);
	JJEngine::GetInstance()->DrawText(0, 280, L"Cut Organ Guide Collided : %d", CutOrganGuideCollided);

	JJEngine::GetInstance()->DrawText(300, 140, L"Frog Body Cut PointCollided : %d", m_FrogBodyCutPointCollided);
}

void MainAutopsyRoomScene::Release()
{
	Scene::Release();
}
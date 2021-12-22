#include "pch.h"

#include "MainDissectingRoomScene.h"
#include "MainAutopsyRoomScene.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "ColliderBox.h"
#include "Player.h"
#include "Button.h"
#include "Organ.h"
#include "TextBox.h"

// static 멤버 변수 초기화
bool MainDissectingRoomScene::DissectStart = false;

bool MainDissectingRoomScene::FrogHeartOpen = false;
bool MainDissectingRoomScene::FrogHeartDetailOpen = false;
bool MainDissectingRoomScene::FrogLiverOpen = false;
bool MainDissectingRoomScene::FrogLungsOpen = false;
bool MainDissectingRoomScene::FrogStomach01Open = false;
bool MainDissectingRoomScene::FrogStomach02Open = false;
bool MainDissectingRoomScene::FrogStomach03Open = false;

bool MainDissectingRoomScene::DetailOpenHeartFatCollided = false;

bool MainDissectingRoomScene::CutFrogStomach02GuideCollided = false;

bool MainDissectingRoomScene::PetrischaleHadHeartPiece = false;
bool MainDissectingRoomScene::PetrischaleHadLiverPiece = false;
bool MainDissectingRoomScene::PetrischaleHadLungsPiece = false;
bool MainDissectingRoomScene::PetrischaleHadStomachPiece = false;

bool MainDissectingRoomScene::IsOncePlay[11] = { false, };
bool MainDissectingRoomScene::m_IsFirstPlay[13] = { false, };

MainDissectingRoomScene::MainDissectingRoomScene()
	:m_pPrevScene(nullptr),
	m_pOrganLeftButton(nullptr),
	m_pOrganRightButton(nullptr),
	m_pFrogHeartCutGuide01(nullptr),
	m_pFrogHeartCutGuide02(nullptr),
	m_pFrogLiverCutGuide(nullptr),
	m_pFrogLungCutGuide(nullptr),
	m_pFrogStomachCutGuide01(nullptr),
	m_pFrogStomachCutGuide02(nullptr),
	m_pFrogStomachCutGuide03(nullptr),
	m_pFrogHeartPiece(nullptr),
	m_pFrogLiverPiece(nullptr),
	m_pFrogLungsPiece(nullptr),
	m_pFrogStomachPiece(nullptr),
	m_pHeartFatCheck01(nullptr),
	m_pHeartFatCheck02(nullptr),
	m_pPincetteButton(nullptr),
	m_pPincetteResetButton(nullptr),
	m_pScissorsButton(nullptr),
	m_pScissorsResetButton(nullptr),
	m_pScalpelButton(nullptr),
	m_pScalpelResetButton(nullptr),
	m_pPetrischaleButton(nullptr),
	m_pFileButton(nullptr),
	m_pOrgan(nullptr),
	m_pPlayer(nullptr),
	m_pTextBox(nullptr),
	m_UsePincette(false),
	m_UseScissors(false),
	m_UseScalpel(false),
	m_FrogHeartCutPointCollided(0),
	m_FrogHeartDetailCutPointCollided(0),
	m_FrogLiverCutPointCollided(0),
	m_FrogLungsCutPointCollided(0),
	m_FrogStomach01CutPointCollided(0),
	m_FrogStomach02CutPointCollided(0),
	m_FrogStomach03CutPointCollided(0),
	m_PickFrogHeartPiece(false),
	m_PickFrogLiverPiece(false),
	m_PickFrogLungsPiece(false),
	m_PickFrogStomachPiece(false),
	m_NowPickOrganPiece(PickOrganPiece::NONE)
{

}

MainDissectingRoomScene::~MainDissectingRoomScene()
{

}

void MainDissectingRoomScene::Initialize()
{
	Scene::Initialize();
	InputManager::GetInstance()->Reset();

	// 플레이어
	m_pPlayer = new Player();
	m_pPlayer->Initialize();

	// 배경 이미지
	m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Dissecting_Background2", 1, UISortLayer::BACKGROUND);

	// 버튼
	m_pPrevScene = m_pObjectManager->CreateObject_Button(JVector(893, 35), L"Dissecting_ReturnButton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);
	m_pOrganLeftButton = m_pObjectManager->CreateObject_Button(JVector(516, 490), L"Dissecting_TrayButton_left", 2, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pOrganRightButton = m_pObjectManager->CreateObject_Button(JVector(1364, 490), L"Dissecting_TrayButton_right", 2, UISortLayer::BUTTON, eNowSceneState::NONE);

	m_pFileFolderButton = m_pObjectManager->CreateObject_Button(JVector(1843, 1005), L"icon_file", 1, UISortLayer::TOPUI, eNowSceneState::NONE);
	
	// 도구 버튼
	m_pPincetteButton = m_pObjectManager->CreateObject_Button(JVector(1477, 242), L"DissectingRoom_Forceps", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPincetteButton->GetColliderBox()->SetSize(JVector(295, 160));
	m_pPincetteResetButton = m_pObjectManager->CreateObject_Button(JVector(1500, 296), L"TrayReset", { 295, 160 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	m_pScissorsButton = m_pObjectManager->CreateObject_Button(JVector(1474, 445), L"DissectingRoom_Scissors2", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pScissorsButton->GetColliderBox()->SetSize(JVector(295, 160));
	m_pScissorsResetButton = m_pObjectManager->CreateObject_Button(JVector(1486, 476), L"TrayReset", { 295, 160 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	m_pScalpelButton = m_pObjectManager->CreateObject_Button(JVector(1472, 613), L"Dissecting_Scalpel", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pScalpelButton->GetColliderBox()->SetSize(JVector(295, 160));
	m_pScalpelResetButton = m_pObjectManager->CreateObject_Button(JVector(1495, 667), L"TrayReset", { 295, 160 }, UISortLayer::POPUPWINDOW, eNowSceneState::NONE);

	m_pPetrischaleButton = m_pObjectManager->CreateObject_Button(JVector(119, 375), L"Dissecting_Petrischale", 1, UISortLayer::BUTTON, eNowSceneState::NONE);

	// 상호작용 객체
	m_pOrgan = new Organ(UISortLayer::POPUPWINDOW);
	m_pOrgan->Initialize(JVector(0, 0), L"Organ");
	m_pOrgan->SetOrganState(MainAutopsyRoomScene::TrayInOrganState);

	// 심장 컷
	m_pFrogHeartCutGuide01 = m_pObjectManager->OnlyCreateObject_Button(JVector(841, 395), L"heart_line01", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogHeartCutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(955, 371), L"Cut00Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(997, 382), L"Cut01Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1047, 399), L"Cut02Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1053, 447), L"Cut03Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[4] = m_pObjectManager->OnlyCreateObject_Button(JVector(1057, 494), L"Cut04Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[5] = m_pObjectManager->OnlyCreateObject_Button(JVector(1059, 533), L"Cut05Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[6] = m_pObjectManager->OnlyCreateObject_Button(JVector(1051, 579), L"Cut06Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[7] = m_pObjectManager->OnlyCreateObject_Button(JVector(1039, 623), L"Cut07Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[8] = m_pObjectManager->OnlyCreateObject_Button(JVector(1023, 664), L"Cut08Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[9] = m_pObjectManager->OnlyCreateObject_Button(JVector(989, 700), L"Cut09Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[10] = m_pObjectManager->OnlyCreateObject_Button(JVector(938, 703), L"Cut10Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[11] = m_pObjectManager->OnlyCreateObject_Button(JVector(896, 680), L"Cut11Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[12] = m_pObjectManager->OnlyCreateObject_Button(JVector(867, 649), L"Cut12Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[13] = m_pObjectManager->OnlyCreateObject_Button(JVector(829, 610), L"Cut13Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartCutPoint[14] = m_pObjectManager->OnlyCreateObject_Button(JVector(815, 562), L"Cut14Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogHeartCutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 15; i++)
	{
		bool _false = false;
		m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] = false;
		m_pFrogHeartCutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 심장 디테일 컷
	m_pFrogHeartCutGuide02 = m_pObjectManager->OnlyCreateObject_Button(JVector(1025, 495), L"heart_line02", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogHeartDetailCutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Cut00Point", { 40, 40 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartDetailCutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Cut01Point", { 45, 45 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogHeartDetailCutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Cut02Point", { 40, 40 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogHeartDetailCutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 3; i++)
	{
		bool _false = false;
		m_IsFrogHeartDetailCutPointDownMap[m_pFrogHeartDetailCutPoint[i]] = false;
		m_pFrogHeartDetailCutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 심장 조직
	m_pFrogHeartPiece = m_pObjectManager->OnlyCreateObject_Button(JVector(757, 587), L"tissue_piece_heart", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	// 심장 이물질
	m_pHeartFatCheck01 = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"Dissecting_heart_fat_c", 2, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pHeartFatCheck01->GetColliderBox()->SetSize(JVector(100, 100));
	m_pHeartFatCheck02 = m_pObjectManager->OnlyCreateObject_Button(JVector(-500, -500), L"Dissecting_heart_fat_o", 2, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pHeartFatCheck02->GetColliderBox()->SetSize(JVector(100, 100));

	// 간 절취선
	m_pFrogLiverCutGuide = m_pObjectManager->OnlyCreateObject_Button(JVector(712, 403), L"liver_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogLiverCutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(843, 390), L"Cut00Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(890, 385), L"Cut01Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(936, 380), L"Cut02Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(983, 395), L"Cut03Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[4] = m_pObjectManager->OnlyCreateObject_Button(JVector(1032, 410), L"Cut04Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[5] = m_pObjectManager->OnlyCreateObject_Button(JVector(1075, 440), L"Cut05Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[6] = m_pObjectManager->OnlyCreateObject_Button(JVector(1115, 475), L"Cut06Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[7] = m_pObjectManager->OnlyCreateObject_Button(JVector(1160, 510), L"Cut07Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[8] = m_pObjectManager->OnlyCreateObject_Button(JVector(1163, 557), L"Cut08Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[9] = m_pObjectManager->OnlyCreateObject_Button(JVector(1127, 587), L"Cut09Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[10] = m_pObjectManager->OnlyCreateObject_Button(JVector(1082, 607), L"Cut10Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[11] = m_pObjectManager->OnlyCreateObject_Button(JVector(1040, 633), L"Cut11Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[12] = m_pObjectManager->OnlyCreateObject_Button(JVector(990, 643), L"Cut12Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[13] = m_pObjectManager->OnlyCreateObject_Button(JVector(940, 627), L"Cut13Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[14] = m_pObjectManager->OnlyCreateObject_Button(JVector(893, 622), L"Cut14Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[15] = m_pObjectManager->OnlyCreateObject_Button(JVector(850, 580), L"Cut15Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[16] = m_pObjectManager->OnlyCreateObject_Button(JVector(813, 544), L"Cut16Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[17] = m_pObjectManager->OnlyCreateObject_Button(JVector(767, 510), L"Cut17Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[18] = m_pObjectManager->OnlyCreateObject_Button(JVector(722, 524), L"Cut18Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[19] = m_pObjectManager->OnlyCreateObject_Button(JVector(670, 493), L"Cut19Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[20] = m_pObjectManager->OnlyCreateObject_Button(JVector(705, 447), L"Cut20Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[21] = m_pObjectManager->OnlyCreateObject_Button(JVector(746, 413), L"Cut21Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLiverCutPoint[22] = m_pObjectManager->OnlyCreateObject_Button(JVector(793, 392), L"Cut22Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogLiverCutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 23; i++)
	{
		bool _false = false;
		m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = false;
		m_pFrogLiverCutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 간 조직
	m_pFrogLiverPiece = m_pObjectManager->OnlyCreateObject_Button(JVector(893, 411), L"tissue_piece_liver", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	// 폐 절취선
	m_pFrogLungCutGuide = m_pObjectManager->OnlyCreateObject_Button(JVector(967, 414), L"lung_line", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogLungsCutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(978, 398), L"Cut00Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1019, 411), L"Cut01Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1051, 439), L"Cut02Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1091, 476), L"Cut03Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[4] = m_pObjectManager->OnlyCreateObject_Button(JVector(1127, 516), L"Cut04Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[5] = m_pObjectManager->OnlyCreateObject_Button(JVector(1138, 555), L"Cut05Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[6] = m_pObjectManager->OnlyCreateObject_Button(JVector(1150, 605), L"Cut06Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[7] = m_pObjectManager->OnlyCreateObject_Button(JVector(1152, 640), L"Cut07Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[8] = m_pObjectManager->OnlyCreateObject_Button(JVector(1138, 678), L"Cut08Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[9] = m_pObjectManager->OnlyCreateObject_Button(JVector(1106, 711), L"Cut09Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[10] = m_pObjectManager->OnlyCreateObject_Button(JVector(1067, 748), L"Cut10Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[11] = m_pObjectManager->OnlyCreateObject_Button(JVector(1016, 773), L"Cut11Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[12] = m_pObjectManager->OnlyCreateObject_Button(JVector(971, 752), L"Cut12Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[13] = m_pObjectManager->OnlyCreateObject_Button(JVector(949, 714), L"Cut13Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogLungsCutPoint[14] = m_pObjectManager->OnlyCreateObject_Button(JVector(953, 678), L"Cut14Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogLungsCutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 15; i++)
	{
		bool _false = false;
		m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = false;
		m_pFrogLungsCutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 폐 조직
	m_pFrogLungsPiece = m_pObjectManager->OnlyCreateObject_Button(JVector(1000, 616), L"tissue_piece_lung", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	// 위장 가운데 절취선
	m_pFrogStomachCutGuide01 = m_pObjectManager->OnlyCreateObject_Button(JVector(805, 332), L"stomach_line01", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogStomach01CutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(840, 321), L"Cut00Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(889, 339), L"Cut01Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(926, 360), L"Cut02Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(966, 381), L"Cut03Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[4] = m_pObjectManager->OnlyCreateObject_Button(JVector(1000, 400), L"Cut04Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[5] = m_pObjectManager->OnlyCreateObject_Button(JVector(1022, 433), L"Cut05Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[6] = m_pObjectManager->OnlyCreateObject_Button(JVector(1000, 465), L"Cut06Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[7] = m_pObjectManager->OnlyCreateObject_Button(JVector(960, 465), L"Cut07Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[8] = m_pObjectManager->OnlyCreateObject_Button(JVector(913, 456), L"Cut08Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[9] = m_pObjectManager->OnlyCreateObject_Button(JVector(873, 435), L"Cut09Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[10] = m_pObjectManager->OnlyCreateObject_Button(JVector(842, 416), L"Cut10Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[11] = m_pObjectManager->OnlyCreateObject_Button(JVector(815, 390), L"Cut11Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[12] = m_pObjectManager->OnlyCreateObject_Button(JVector(789, 353), L"Cut12Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach01CutPoint[13] = m_pObjectManager->OnlyCreateObject_Button(JVector(793, 318), L"Cut13Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogStomach01CutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 14; i++)
	{
		bool _false = false;
		m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = false;
		m_pFrogStomach01CutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 위장 왼쪽 절취선
	m_pFrogStomachCutGuide02 = m_pObjectManager->OnlyCreateObject_Button(JVector(-300, -300), L"stomach_line02", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);
	m_pFrogStomachCutGuide02->GetColliderBox()->SetSize(JVector(145, 60));

	// 위장 오른쪽 절취선
	m_pFrogStomachCutGuide03 = m_pObjectManager->OnlyCreateObject_Button(JVector(1058, 394), L"stomach_line03", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	m_pFrogStomach03CutPoint[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(1045, 414), L"Cut00Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1077, 386), L"Cut01Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1117, 384), L"Cut02Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1138, 416), L"Cut03Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[4] = m_pObjectManager->OnlyCreateObject_Button(JVector(1144, 459), L"Cut04Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[5] = m_pObjectManager->OnlyCreateObject_Button(JVector(1156, 500), L"Cut05Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[6] = m_pObjectManager->OnlyCreateObject_Button(JVector(1169, 538), L"Cut06Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[7] = m_pObjectManager->OnlyCreateObject_Button(JVector(1193, 572), L"Cut07Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);
	m_pFrogStomach03CutPoint[8] = m_pObjectManager->OnlyCreateObject_Button(JVector(1203, 610), L"Cut08Point", { 50, 50 }, UISortLayer::PLAYER, eNowSceneState::NONE);

	// IsFrogStomach03CutPointDownMap을 초기화한다. <Button*, bool>
	for (int i = 0; i < 9; i++)
	{
		bool _false = false;
		m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[i]] = false;
		m_pFrogStomach03CutPoint[i]->Transform()->Pos = { -300, -300 };
	}

	// 위장 조직
	m_pFrogStomachPiece = m_pObjectManager->OnlyCreateObject_Button(JVector(911, 366), L"tissue_piece_stomach", 1, UISortLayer::POPUPWINDOWBUTTON, eNowSceneState::NONE);

	if (PetrischaleHadHeartPiece == true)
	{
		m_pFrogHeartPiece->Transform()->Pos = { 255, 500 };
	}

	if (PetrischaleHadLiverPiece == true)
	{
		m_pFrogLiverPiece->Transform()->Pos = { 245, 500 };
	}

	if (PetrischaleHadLungsPiece == true)
	{
		m_pFrogLungsPiece->Transform()->Pos = { 255, 500 };
	}

	if (PetrischaleHadStomachPiece == true)
	{
		m_pFrogStomachPiece->Transform()->Pos = { 255, 500 };
	}

	/// 이미 장기를 잘랐다면 잘린 이미지로 출력되어야함
	if (FrogHeartOpen)
	{
		m_pOrgan->GetOrgans(OrganState::HEART)->ChangeFrame(1);

		if (FrogHeartDetailOpen)
		{
			m_pOrgan->GetOrgans(OrganState::HEART)->Transform()->Pos = { 672,282 };
			m_pOrgan->GetOrgans(OrganState::HEART)->ChangeFrame(4);
		}
	}

	if (FrogLiverOpen)
	{
		m_pOrgan->GetOrgans(OrganState::LIVER)->ChangeFrame(2);
	}

	if (FrogLungsOpen)
	{
		m_pOrgan->GetOrgans(OrganState::LUNGS)->ChangeFrame(4);
	}

	if (FrogStomach01Open)
	{
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(1);
	}

	if (FrogStomach02Open)
	{
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(2);
	}

	if (FrogStomach03Open)
	{
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(3);
	}

	// 텍스트박스 이니셜라이즈 할 때 스크립트의 이름을 넣어준다. (아마도 씬의 이름)
	m_pTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(0, 0), L"MainDissectingRoomScene", UISortLayer::TOPUI);
}

void MainDissectingRoomScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	/// 대화상자가 켜져 있을 경우만 업데이트 해준다.
	m_pTextBox->Update(dTime);

	if (m_pTextBox->GetState())
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
		}
	}
	break;

	case eNowSceneState::GO_TO_PREV_SCENE:
	{
		SceneManager::FadeIn(dTime);

		if (SceneManager::IsFadeInEnd)
		{
			SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY);
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

	m_pObjectManager->UpdateAll(dTime);
	m_pObjectManager->CheckButtonClicked(this);

	DissectStart = true;

	// 이전 씬으로 가는 버튼 마우스 상호작용 애니메이션
	if (m_pPrevScene->GetColliderBox()->IsCollided)
	{
		if (m_IsFirstPlay[0] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_01");
			m_IsFirstPlay[0] = true;
		}
		m_pPrevScene->ChangeFrame(1);
	}
	else
	{
		m_IsFirstPlay[0] = false;
		m_pPrevScene->ChangeFrame(0);
	}

	m_pPlayer->Update(dTime);

	POINT _mousePos = InputManager::GetInstance()->GetMousePos();

	// 장기 변경 버튼
	if (m_pOrganLeftButton->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Button_Down");
		m_pOrganLeftButton->ChangeFrame(1);
	}
	else m_pOrganLeftButton->ChangeFrame(0);

	if (m_pOrganRightButton->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Button_Down");
		m_pOrganRightButton->ChangeFrame(1);
	}
	else m_pOrganRightButton->ChangeFrame(0);

	/// 도구 선택 및 제자리 돌려놓기
	// 해부실 핀셋
	if (m_pPincetteButton->GetColliderBox()->IsClicked || m_pPincetteResetButton->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Tool_Forceps");
		if (m_UsePincette == true && m_pPincetteResetButton->GetColliderBox()->IsClicked)
		{
			m_UsePincette = false;
			m_pPincetteButton->Transform()->Pos = { 1477, 242 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::DISSECT_PINCETTE);
			m_pPlayer->SetHadToolState(true);

			m_UsePincette = true;
			m_UseScissors = false;
			m_UseScalpel = false;

			m_pPincetteButton->Transform()->Pos = { 1477, -300 };
			m_pScissorsButton->Transform()->Pos = { 1474, 445 };
			m_pScalpelButton->Transform()->Pos = { 1472, 613 };
		}
	}
	// 해부실 가위
	else if (m_pScissorsButton->GetColliderBox()->IsClicked || m_pScissorsResetButton->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Tool_Pickup");
		if (m_UseScissors == true && m_pScissorsResetButton->GetColliderBox()->IsClicked)
		{
			m_UseScissors = false;
			m_pScissorsButton->Transform()->Pos = { 1474, 445 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::DISSECT_SCISSORS);
			m_pPlayer->SetHadToolState(true);

			m_UsePincette = false;
			m_UseScissors = true;
			m_UseScalpel = false;

			m_pPincetteButton->Transform()->Pos = { 1477, 242 };
			m_pScissorsButton->Transform()->Pos = { 1474, -300 };
			m_pScalpelButton->Transform()->Pos = { 1472, 613 };
		}
	}
	// 해부실 메스
	else if (m_pScalpelButton->GetColliderBox()->IsClicked || m_pScalpelResetButton->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Tool_Pickup");
		if (m_UseScalpel == true && m_pScalpelResetButton->GetColliderBox()->IsClicked)
		{
			m_UseScalpel = false;
			m_pScalpelButton->Transform()->Pos = { 1472, 613 };
			m_pPlayer->SetToolType(ToolType::NONE);
			m_pPlayer->SetHadToolState(false);
		}
		else
		{
			m_pPlayer->SetToolType(ToolType::DISSECT_SCALPEL);
			m_pPlayer->SetHadToolState(true);

			m_UsePincette = false;
			m_UseScissors = false;
			m_UseScalpel = true;

			m_pPincetteButton->Transform()->Pos = { 1477, 242 };
			m_pScissorsButton->Transform()->Pos = { 1474, 445 };
			m_pScalpelButton->Transform()->Pos = { 1472, -300 };
		}
	}

	if (m_pPlayer->GetHadToolState() == true)
	{
		m_pPlayer->GetTools(ToolType::DISSECT_PINCETTE)->Transform()->SetPos(_mousePos.x, _mousePos.y);
		m_pPlayer->GetTools(ToolType::DISSECT_SCISSORS)->Transform()->SetPos(_mousePos.x, _mousePos.y);
		m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->Transform()->SetPos(_mousePos.x, _mousePos.y);
	}

	// 장기 변경 버튼에 따른 장기 상태 변화
	m_pOrgan->Update(dTime);

	switch (MainAutopsyRoomScene::TrayHadOrgan)
	{
		case 1:
			if (m_pOrganLeftButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
			}
			else if (m_pOrganRightButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
			}
			break;

		case 2:
			if (m_pOrganLeftButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
			}
			else if (m_pOrganRightButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
			}
			break;

		case 3:
			if (m_pOrganLeftButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::LUNGS)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::LUNGS);
				}
			}
			else if (m_pOrganRightButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::LUNGS)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::LUNGS);
				}
			}
			break;

		case 4:
			if (m_pOrganLeftButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::STOMACH)
				{
					m_pOrgan->SetOrganState(OrganState::LUNGS);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LUNGS)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::STOMACH);
				}
			}
			else if (m_pOrganRightButton->GetColliderBox()->IsClicked)
			{
				if (m_pOrgan->GetOrganState() == OrganState::STOMACH)
				{
					m_pOrgan->SetOrganState(OrganState::HEART);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::HEART)
				{
					m_pOrgan->SetOrganState(OrganState::LIVER);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LIVER)
				{
					m_pOrgan->SetOrganState(OrganState::LUNGS);
				}
				else if (m_pOrgan->GetOrganState() == OrganState::LUNGS)
				{
					m_pOrgan->SetOrganState(OrganState::STOMACH);
				}
			}
			break;
	}

	/// 심장 혈관 속 이물질 확인
	m_pHeartFatCheck01->Update(dTime);
	m_pHeartFatCheck02->Update(dTime);

	if (m_UsePincette)
	{
		m_pHeartFatCheck01->Transform()->Pos = { 801, 297 };

		if (FrogHeartDetailOpen)
		{
			m_pHeartFatCheck02->Transform()->Pos = { 846, 282 };
		}
	}
	else if (m_UsePincette && m_pOrgan->GetOrganState() == OrganState::LIVER || m_pOrgan->GetOrganState() == OrganState::LUNGS || m_pOrgan->GetOrganState() == OrganState::STOMACH)
	{
		m_pHeartFatCheck01->Transform()->Pos = { -300, -300 };
		m_pHeartFatCheck02->Transform()->Pos = { -300, -300 };
	}

	// 핀셋으로 심장 혈관 확인
	if (m_pHeartFatCheck01->GetColliderBox()->IsHolding && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		if (m_IsFirstPlay[1] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Forceps");
			m_IsFirstPlay[1] = true;
		}

		if (!IsOncePlay[0])
		{
			m_pTextBox->SetStartEndIndex(1, 1);
			IsOncePlay[0] = true;
		}

		m_pHeartFatCheck01->ChangeFrame(1);
	}
	else m_pHeartFatCheck01->ChangeFrame(0);

	if (m_pHeartFatCheck02->GetColliderBox()->IsCollided && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		DetailOpenHeartFatCollided = true;
	}
	else DetailOpenHeartFatCollided = false;

	if (m_pHeartFatCheck02->GetColliderBox()->IsHolding && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		if (m_IsFirstPlay[2] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Forceps");
			m_IsFirstPlay[2] = true;
		}

		if (!IsOncePlay[1])
		{
			m_pTextBox->SetStartEndIndex(1, 1);
			IsOncePlay[1] = true;
		}

		m_pPlayer->GetTools(ToolType::DISSECT_PINCETTE)->ChangeMotionFrame(2);
		m_pHeartFatCheck02->ChangeFrame(1);
	}
	else
	{
		m_pHeartFatCheck02->ChangeFrame(0);
	}

	/// 장기 컷 점선 표시
	m_pFrogHeartCutGuide01->Update(dTime);
	m_pFrogHeartCutGuide02->Update(dTime);
	m_pFrogLiverCutGuide->Update(dTime);
	m_pFrogLungCutGuide->Update(dTime);
	m_pFrogStomachCutGuide01->Update(dTime);
	m_pFrogStomachCutGuide02->Update(dTime);
	m_pFrogStomachCutGuide03->Update(dTime);

	/// 심장 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 15; i++)
	{
		m_pFrogHeartCutPoint[i]->Update(dTime);
	}

	for (int i = 0; i < 3; i++)
	{
		m_pFrogHeartDetailCutPoint[i]->Update(dTime);
	}

	if (m_UseScalpel)
	{
		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (m_pOrgan->GetOrganState() == OrganState::HEART)
		{
			m_pFrogHeartCutPoint[0]->Transform()->Pos = { 955, 371 };
			m_pFrogHeartCutPoint[1]->Transform()->Pos = { 997, 382 };
			m_pFrogHeartCutPoint[2]->Transform()->Pos = { 1047, 399 };
			m_pFrogHeartCutPoint[3]->Transform()->Pos = { 1053, 447 };
			m_pFrogHeartCutPoint[4]->Transform()->Pos = { 1057, 494 };
			m_pFrogHeartCutPoint[5]->Transform()->Pos = { 1059, 533 };
			m_pFrogHeartCutPoint[6]->Transform()->Pos = { 1051, 579 };
			m_pFrogHeartCutPoint[7]->Transform()->Pos = { 1039, 623 };
			m_pFrogHeartCutPoint[8]->Transform()->Pos = { 1023, 664 };
			m_pFrogHeartCutPoint[9]->Transform()->Pos = { 989, 700 };
			m_pFrogHeartCutPoint[10]->Transform()->Pos = { 938, 703 };
			m_pFrogHeartCutPoint[11]->Transform()->Pos = { 896, 680 };
			m_pFrogHeartCutPoint[12]->Transform()->Pos = { 867, 649 };
			m_pFrogHeartCutPoint[13]->Transform()->Pos = { 829, 610 };
			m_pFrogHeartCutPoint[14]->Transform()->Pos = { 815, 562 };
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_pFrogHeartCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(8);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogHeartCutPointCollided++;
					}

					m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] = true;
				}
			}
		}

		for (int i = 3; i < 8; i++)
		{
			if (m_pFrogHeartCutPoint[i]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(9);

				if (m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] == false)
					m_FrogHeartCutPointCollided++;

				m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] = true;
			}
		}

		for (int i = 8; i < 12; i++)
		{
			if (m_pFrogHeartCutPoint[i]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(2);

				if (m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] == false)
					m_FrogHeartCutPointCollided++;

				m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] = true;
			}
		}

		for (int i = 11; i < 15; i++)
		{
			if (m_pFrogHeartCutPoint[i]->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(4);

				if (m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] == false)
					m_FrogHeartCutPointCollided++;

				m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[i]] = true;
			}
		}

		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (FrogHeartOpen == true)
		{
			m_pFrogHeartDetailCutPoint[0]->Transform()->Pos = { 1043, 495 };
			m_pFrogHeartDetailCutPoint[1]->Transform()->Pos = { 1035, 540 };
			m_pFrogHeartDetailCutPoint[2]->Transform()->Pos = { 1021, 583 };
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_pFrogHeartDetailCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(0);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogHeartDetailCutPointDownMap[m_pFrogHeartDetailCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																						// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogHeartDetailCutPointCollided++;
					}

					m_IsFrogHeartDetailCutPointDownMap[m_pFrogHeartDetailCutPoint[i]] = true;
				}
			}
		}
	}

	// 14번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (심장 자름)
	if (m_FrogHeartCutPointCollided == 15 && m_IsFrogHeartCutPointDownMap[m_pFrogHeartCutPoint[14]] == true)
	{
		FrogHeartOpen = true;
		m_pOrgan->GetOrgans(OrganState::HEART)->ChangeFrame(1);

		if (m_IsFirstPlay[3] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[3] = true;
		}

		for (int i = 0; i < 15; i++)
		{
			m_pFrogHeartCutPoint[i]->Transform()->Pos = { -300, -300 };
		}
	}

	// 2번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (심장 디테일 자름)
	if (m_FrogHeartDetailCutPointCollided == 3 && m_IsFrogHeartDetailCutPointDownMap[m_pFrogHeartDetailCutPoint[2]] == true && FrogHeartOpen == true)
	{
		FrogHeartDetailOpen = true;
		m_pOrgan->GetOrgans(OrganState::HEART)->ChangeFrame(2);

		if (m_IsFirstPlay[4] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[4] = true;
		}

		if (m_pOrgan->GetOrgans(OrganState::HEART)->GetNowFrame() < 3 && FrogHeartDetailOpen == true)
		{
			m_pOrgan->GetOrgans(OrganState::HEART)->ChangeFrame(4);
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		for (int i = 0; i < 3; i++)
		{
			m_pFrogHeartDetailCutPoint[i]->Transform()->Pos = { -300, -300 };
		}

		if (!IsOncePlay[2])
		{
			m_pTextBox->SetStartEndIndex(0, 0);
			FileFolder::GetInstance()->HeartState = eHeartState::Cuted;
			IsOncePlay[2] = true;
		}
	}

	// 심장 다 자르면 위치 오른쪽으로 이동
	if (FrogHeartDetailOpen)
	{
		m_pOrgan->GetOrgans(OrganState::HEART)->Transform()->Pos = { 672,282 };
	}

	m_pFrogHeartPiece->Update(dTime);

	// 심장 조직 옮기기
	if (m_pFrogHeartPiece->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && FrogHeartOpen == true)
	{
		m_NowPickOrganPiece = PickOrganPiece::HEART;

		if (m_UsePincette == true)
		{
			m_pFrogHeartPiece->Transform()->Pos.x = _mousePos.x - m_pFrogHeartPiece->Transform()->Size.x / 2;
			m_pFrogHeartPiece->Transform()->Pos.y = _mousePos.y - m_pFrogHeartPiece->Transform()->Size.y / 2;

			m_PickFrogHeartPiece = true;
		}

		else if (m_UseScissors == true || m_UseScalpel == true) {}
	}

	if (m_pFrogHeartPiece->GetColliderBox()->CheckCollidedObject(m_pPetrischaleButton))
	{
		PetrischaleHadHeartPiece = true;

		if (m_IsFirstPlay[5] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Glass_01");
			m_IsFirstPlay[5] = true;
		}

		if (!IsOncePlay[3])
		{
			m_pTextBox->SetStartEndIndex(3, 3);

			FileFolder::GetInstance()->HeartState = eHeartState::SampleMoved;
			IsOncePlay[3] = true;
		}
	}

	/// 간 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 23; i++)
	{
		m_pFrogLiverCutPoint[i]->Update(dTime);
	}

	if (m_UseScalpel)
	{
		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (FrogLiverOpen == false)
		{
			m_pFrogLiverCutPoint[0]->Transform()->Pos = { 843, 390 };
			m_pFrogLiverCutPoint[1]->Transform()->Pos = { 890, 385 };
			m_pFrogLiverCutPoint[2]->Transform()->Pos = { 936, 380 };
			m_pFrogLiverCutPoint[3]->Transform()->Pos = { 983, 395 };
			m_pFrogLiverCutPoint[4]->Transform()->Pos = { 1032, 410 };
			m_pFrogLiverCutPoint[5]->Transform()->Pos = { 1075, 440 };
			m_pFrogLiverCutPoint[6]->Transform()->Pos = { 1115, 475 };
			m_pFrogLiverCutPoint[7]->Transform()->Pos = { 1160, 510 };
			m_pFrogLiverCutPoint[8]->Transform()->Pos = { 1163, 557 };
			m_pFrogLiverCutPoint[9]->Transform()->Pos = { 1127, 587 };
			m_pFrogLiverCutPoint[10]->Transform()->Pos = { 1082, 607 };
			m_pFrogLiverCutPoint[11]->Transform()->Pos = { 1040, 633 };
			m_pFrogLiverCutPoint[12]->Transform()->Pos = { 990, 643 };
			m_pFrogLiverCutPoint[13]->Transform()->Pos = { 940, 627 };
			m_pFrogLiverCutPoint[14]->Transform()->Pos = { 893, 622 };
			m_pFrogLiverCutPoint[15]->Transform()->Pos = { 850, 580 };
			m_pFrogLiverCutPoint[16]->Transform()->Pos = { 813, 544 };
			m_pFrogLiverCutPoint[17]->Transform()->Pos = { 767, 510 };
			m_pFrogLiverCutPoint[18]->Transform()->Pos = { 722, 524 };
			m_pFrogLiverCutPoint[19]->Transform()->Pos = { 670, 493 };
			m_pFrogLiverCutPoint[20]->Transform()->Pos = { 705, 447 };
			m_pFrogLiverCutPoint[21]->Transform()->Pos = { 746, 413 };
			m_pFrogLiverCutPoint[22]->Transform()->Pos = { 793, 392 };
		}

		for (int i = 0; i < 5; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(7);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 5; i < 8; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(8);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 8; i < 12; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(1);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 12; i < 14; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(2);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 14; i < 17; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(4);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 17; i < 19; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(2);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 19; i < 21; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(5);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}

		for (int i = 20; i < 23; i++)
		{
			if (m_pFrogLiverCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(6);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLiverCutPointCollided++;
					}

					m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[i]] = true;
				}
			}
		}
	}

	// 22번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (폐 자름)
	if (m_FrogLiverCutPointCollided == 23 && m_IsFrogLiverCutPointDownMap[m_pFrogLiverCutPoint[22]] == true)
	{
		FrogLiverOpen = true;
		m_pOrgan->GetOrgans(OrganState::LIVER)->ChangeFrame(2);

		if (m_IsFirstPlay[6] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[6] = true;
		}

		if (!IsOncePlay[4])
		{
			// 스크립트 출력
			m_pTextBox->SetStartEndIndex(2, 2);

			FileFolder::GetInstance()->LiverState = eLiverState::Cuted;
			IsOncePlay[4] = true;
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		for (int i = 0; i < 23; i++)
		{
			m_pFrogLiverCutPoint[i]->Transform()->Pos = { -300, -300 };
		}
	}

	m_pFrogLiverPiece->Update(dTime);

	// 간 조직 옮기기
	if (m_pFrogLiverPiece->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && FrogLiverOpen == true)
	{
		m_NowPickOrganPiece = PickOrganPiece::LIVER;

		if (m_UsePincette == true)
		{
			m_pFrogLiverPiece->Transform()->Pos.x = _mousePos.x - m_pFrogLiverPiece->Transform()->Size.x / 2;
			m_pFrogLiverPiece->Transform()->Pos.y = _mousePos.y - m_pFrogLiverPiece->Transform()->Size.y / 2;

			m_PickFrogLiverPiece = true;
		}

		else if (m_UseScissors == true || m_UseScalpel == true) {}
	}

	if (m_pFrogLiverPiece->GetColliderBox()->CheckCollidedObject(m_pPetrischaleButton))
	{
		PetrischaleHadLiverPiece = true;

		if (m_IsFirstPlay[7] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Glass_01");
			m_IsFirstPlay[7] = true;
		}

		if (!IsOncePlay[5])
		{
			m_pTextBox->SetStartEndIndex(3, 3);

			FileFolder::GetInstance()->LiverState = eLiverState::SampleMoved;
			IsOncePlay[5] = true;
		}
	}

	/// 폐 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 15; i++)
	{
		m_pFrogLungsCutPoint[i]->Update(dTime);
	}

	if (m_UseScalpel)
	{
		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (FrogLungsOpen == false)
		{
			m_pFrogLungsCutPoint[0]->Transform()->Pos = { 978, 398 };
			m_pFrogLungsCutPoint[1]->Transform()->Pos = { 1019, 411 };
			m_pFrogLungsCutPoint[2]->Transform()->Pos = { 1051, 439 };
			m_pFrogLungsCutPoint[3]->Transform()->Pos = { 1091, 476 };
			m_pFrogLungsCutPoint[4]->Transform()->Pos = { 1127, 516 };
			m_pFrogLungsCutPoint[5]->Transform()->Pos = { 1138, 555 };
			m_pFrogLungsCutPoint[6]->Transform()->Pos = { 1150, 605 };
			m_pFrogLungsCutPoint[7]->Transform()->Pos = { 1152, 640 };
			m_pFrogLungsCutPoint[8]->Transform()->Pos = { 1138, 678 };
			m_pFrogLungsCutPoint[9]->Transform()->Pos = { 1106, 711 };
			m_pFrogLungsCutPoint[10]->Transform()->Pos = { 1067, 748 };
			m_pFrogLungsCutPoint[11]->Transform()->Pos = { 1016, 773 };
			m_pFrogLungsCutPoint[12]->Transform()->Pos = { 971, 752 };
			m_pFrogLungsCutPoint[13]->Transform()->Pos = { 949, 714 };
			m_pFrogLungsCutPoint[14]->Transform()->Pos = { 953, 678 };
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_pFrogLungsCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(7);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLungsCutPointCollided++;
					}

					m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = true;
				}
			}
		}

		for (int i = 3; i < 7; i++)
		{
			if (m_pFrogLungsCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(9);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLungsCutPointCollided++;
					}

					m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = true;
				}
			}
		}

		for (int i = 7; i < 12; i++)
		{
			if (m_pFrogLungsCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(0);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLungsCutPointCollided++;
					}

					m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = true;
				}
			}
		}

		for (int i = 11; i < 13; i++)
		{
			if (m_pFrogLungsCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(2);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLungsCutPointCollided++;
					}

					m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = true;
				}
			}
		}

		for (int i = 13; i < 15; i++)
		{
			if (m_pFrogLungsCutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(4);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																			// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogLungsCutPointCollided++;
					}

					m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[i]] = true;
				}
			}
		}

	}

	// 15번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (폐 자름)
	if (m_FrogLungsCutPointCollided == 15 && m_IsFrogLungsCutPointDownMap[m_pFrogLungsCutPoint[14]] == true)
	{
		FrogLungsOpen = true;
		m_pOrgan->GetOrgans(OrganState::LUNGS)->PlayAnimation(dTime);
		m_pOrgan->GetOrgans(OrganState::LUNGS)->Transform()->Pos = { 718, 255 };

		if (m_IsFirstPlay[8] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[8] = true;
		}

		if (!IsOncePlay[6])
		{
			FileFolder::GetInstance()->LungState = eLungState::Cuted;

			// 스크립트 출력
			if (m_pOrgan->GetOrgans(OrganState::LUNGS)->GetNowFrame() == 4)
			{
				m_pTextBox->SetStartEndIndex(4, 4);

				IsOncePlay[6] = true;
			}
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		for (int i = 0; i < 15; i++)
		{
			m_pFrogLungsCutPoint[i]->Transform()->Pos = { -300, -300 };
		}
	}

	m_pFrogLungsPiece->Update(dTime);

	// 폐 조직 옮기기
	if (m_pFrogLungsPiece->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold() && FrogLungsOpen == true)
	{
		m_NowPickOrganPiece = PickOrganPiece::LUNGS;

		if (m_UsePincette == true)
		{
			m_pFrogLungsPiece->Transform()->Pos.x = _mousePos.x - m_pFrogLungsPiece->Transform()->Size.x / 2;
			m_pFrogLungsPiece->Transform()->Pos.y = _mousePos.y - m_pFrogLungsPiece->Transform()->Size.y / 2;

			m_PickFrogLungsPiece = true;
		}

		else if (m_UseScissors == true || m_UseScalpel == true) {}
	}

	if (m_pFrogLungsPiece->GetColliderBox()->CheckCollidedObject(m_pPetrischaleButton))
	{
		if (m_IsFirstPlay[9] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Glass_01");
			m_IsFirstPlay[9] = true;
		}

		if (!IsOncePlay[7])
		{
			m_pTextBox->SetStartEndIndex(3, 3);

			FileFolder::GetInstance()->LungState = eLungState::SampleMoved;
			IsOncePlay[7] = true;
		}

		PetrischaleHadLungsPiece = true;
	}

	/// 위장01 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 14; i++)
	{
		m_pFrogStomach01CutPoint[i]->Update(dTime);
	}

	if (m_UseScalpel)
	{
		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (m_pOrgan->GetOrganState() == OrganState::STOMACH)
		{
			m_pFrogStomach01CutPoint[0]->Transform()->Pos = { 840, 321 };
			m_pFrogStomach01CutPoint[1]->Transform()->Pos = { 889, 339 };
			m_pFrogStomach01CutPoint[2]->Transform()->Pos = { 926, 360 };
			m_pFrogStomach01CutPoint[3]->Transform()->Pos = { 966, 381 };
			m_pFrogStomach01CutPoint[4]->Transform()->Pos = { 1000, 400 };
			m_pFrogStomach01CutPoint[5]->Transform()->Pos = { 1022, 433 };
			m_pFrogStomach01CutPoint[6]->Transform()->Pos = { 1000, 465 };
			m_pFrogStomach01CutPoint[7]->Transform()->Pos = { 960, 465 };
			m_pFrogStomach01CutPoint[8]->Transform()->Pos = { 913, 456 };
			m_pFrogStomach01CutPoint[9]->Transform()->Pos = { 873, 435 };
			m_pFrogStomach01CutPoint[10]->Transform()->Pos = { 842, 416 };
			m_pFrogStomach01CutPoint[11]->Transform()->Pos = { 815, 390 };
			m_pFrogStomach01CutPoint[12]->Transform()->Pos = { 789, 353 };
			m_pFrogStomach01CutPoint[13]->Transform()->Pos = { 793, 318 };
		}

		for (int i = 0; i < 4; i++)
		{
			if (m_pFrogStomach01CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(7);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach01CutPointCollided++;
					}

					m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = true;
				}
			}
		}

		for (int i = 4; i < 6; i++)
		{
			if (m_pFrogStomach01CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(9);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach01CutPointCollided++;
					}

					m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = true;
				}
			}
		}

		for (int i = 6; i < 9; i++)
		{
			if (m_pFrogStomach01CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(2);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach01CutPointCollided++;
					}

					m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = true;
				}
			}
		}

		for (int i = 9; i < 12; i++)
		{
			if (m_pFrogStomach01CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(3);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach01CutPointCollided++;
					}

					m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = true;
				}
			}
		}

		for (int i = 12; i < 14; i++)
		{
			if (m_pFrogStomach01CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(5);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach01CutPointCollided++;
					}

					m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[i]] = true;
				}
			}
		}

		if (m_pFrogStomach01CutPoint[13]->GetColliderBox()->IsCollided)
		{
			m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(7);

			if (InputManager::GetInstance()->CheckLeftButtonHold())
			{
				if (m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[13]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
				{																						// 2 : true  if( == false) -> ++ 안된다 -> true
					m_FrogStomach01CutPointCollided++;
				}

				m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[13]] = true;
			}
		}
	}

	// 13번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (위장01 자름)
	if (m_FrogStomach01CutPointCollided == 14 && m_IsFrogStomach01CutPointDownMap[m_pFrogStomach01CutPoint[13]] == true)
	{
		FrogStomach01Open = true;
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(1);

		if (m_IsFirstPlay[10] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[10] = true;
		}

		if (!IsOncePlay[8])
		{
			FileFolder::GetInstance()->StomachState = eStomachState::Cuted;

			// 스크립트 출력
			m_pTextBox->SetStartEndIndex(5, 5);

			IsOncePlay[8] = true;
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		for (int i = 0; i < 14; i++)
		{
			m_pFrogStomach01CutPoint[i]->Transform()->Pos = { -300, -300 };
		}

		m_pFrogStomachCutGuide02->Transform()->Pos = { 653, 340 };
	}

	/// 위장02 자르기용 충돌체크 배열 업데이트
	if (m_UseScissors && m_pOrgan->GetOrganState() == OrganState::STOMACH)
	{
		if (m_pFrogStomachCutGuide02->GetColliderBox()->IsCollided)
		{
			CutFrogStomach02GuideCollided = true;
		}
		else CutFrogStomach02GuideCollided = false;

		if (m_pFrogStomachCutGuide02->GetColliderBox()->IsClicked)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scissor_Cuting");

			m_FrogStomach02CutPointCollided++;
		}
	}

	// 3번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (위장02 자름)
	if (m_FrogStomach02CutPointCollided == 1)
	{
		FrogStomach02Open = true;
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(2);

		if (!IsOncePlay[9])
		{
			// 스크립트 출력
			m_pTextBox->SetStartEndIndex(6, 6);

			IsOncePlay[9] = true;
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		m_pFrogStomachCutGuide02->Transform()->Pos = { -300, -300 };
	}

	/// 위장03 자르기용 충돌체크 배열 업데이트
	for (int i = 0; i < 9; i++)
	{
		m_pFrogStomach03CutPoint[i]->Update(dTime);
	}

	if (m_UseScalpel)
	{
		// 버튼 충돌을 막기 위해 { -300, -300 }으로 했던 충돌체크 배열 원래 자리로 변경
		if (m_pOrgan->GetOrganState() == OrganState::STOMACH)
		{
			m_pFrogStomach03CutPoint[0]->Transform()->Pos = { 1045, 414 };
			m_pFrogStomach03CutPoint[1]->Transform()->Pos = { 1077, 386 };
			m_pFrogStomach03CutPoint[2]->Transform()->Pos = { 1117, 384 };
			m_pFrogStomach03CutPoint[3]->Transform()->Pos = { 1138, 416 };
			m_pFrogStomach03CutPoint[4]->Transform()->Pos = { 1144, 459 };
			m_pFrogStomach03CutPoint[5]->Transform()->Pos = { 1156, 500 };
			m_pFrogStomach03CutPoint[6]->Transform()->Pos = { 1169, 538 };
			m_pFrogStomach03CutPoint[7]->Transform()->Pos = { 1193, 572 };
			m_pFrogStomach03CutPoint[8]->Transform()->Pos = { 1203, 610 };
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_pFrogStomach03CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(7);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach03CutPointCollided++;
					}

					m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[i]] = true;
				}
			}
		}

		for (int i = 3; i < 9; i++)
		{
			if (m_pFrogStomach03CutPoint[i]->GetColliderBox()->IsCollided)
			{
				m_pPlayer->GetTools(ToolType::DISSECT_SCALPEL)->ChangeMotionFrame(9);

				if (InputManager::GetInstance()->CheckLeftButtonHold())
				{
					if (m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[i]] == false)			// 1 : false 상태에서 -> 카운트++ -> true
					{																					// 2 : true  if( == false) -> ++ 안된다 -> true
						m_FrogStomach03CutPointCollided++;
					}

					m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[i]] = true;
				}
			}
		}
	}

	// 8번째 컷포인트 컬라이더 박스 친구가 마우스에 눌림당했음 (위장03 자름)
	if (m_FrogStomach03CutPointCollided == 9 && m_IsFrogStomach03CutPointDownMap[m_pFrogStomach03CutPoint[8]] == true)
	{
		FrogStomach03Open = true;
		m_pOrgan->GetOrgans(OrganState::STOMACH)->ChangeFrame(4);
		m_pOrgan->GetOrgans(OrganState::STOMACH)->Transform()->Pos = { 636, 300 };

		if (m_IsFirstPlay[11] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Tool_Scalpel_Cuting");
			m_IsFirstPlay[11] = true;
		}

		// 다 잘랐으면 다른 버튼 충돌체크에 방해되지 않게 치워버리기
		for (int i = 0; i < 9; i++)
		{
			m_pFrogStomach03CutPoint[i]->Transform()->Pos = { -300, -300 };
		}
	}

	m_pFrogStomachPiece->Update(dTime);

	// 위장 조직 옮기기
	if (m_pFrogStomachPiece->GetColliderBox()->IsCollided && InputManager::GetInstance()->CheckLeftButtonHold()
		&& FrogStomach01Open == true)
	{
		m_NowPickOrganPiece = PickOrganPiece::STOMACH;

		if (m_UsePincette == true)
		{
			m_pFrogStomachPiece->Transform()->Pos.x = _mousePos.x - m_pFrogStomachPiece->Transform()->Size.x / 2;
			m_pFrogStomachPiece->Transform()->Pos.y = _mousePos.y - m_pFrogStomachPiece->Transform()->Size.y / 2;

			m_PickFrogStomachPiece = true;
		}

		else if (m_UseScissors == true || m_UseScalpel == true) {}
	}

	if (m_pFrogStomachPiece->GetColliderBox()->CheckCollidedObject(m_pPetrischaleButton))
	{
		if (m_IsFirstPlay[12] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Glass_01");
			m_IsFirstPlay[12] = true;
		}

		if (!IsOncePlay[10])
		{
			m_pTextBox->SetStartEndIndex(3, 3);

			FileFolder::GetInstance()->StomachState = eStomachState::SampleMoved;
			IsOncePlay[10] = true;
		}

		PetrischaleHadStomachPiece = true;
	}
}

void MainDissectingRoomScene::Draw()
{
	m_pObjectManager->DrawAll();

	m_pOrgan->Draw();

	if (m_UseScalpel && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		if (FrogHeartOpen == false)
		{
			for (int i = 0; i < 15; i++)
			{
				m_pFrogHeartCutPoint[i]->Draw();
			}

			m_pFrogHeartCutGuide01->Draw(0.7f);
		}
		else if (FrogHeartOpen && FrogHeartDetailOpen == false)
		{
			m_pFrogHeartCutGuide02->Draw(0.7f);

			for (int i = 0; i < 3; i++)
			{
				m_pFrogHeartDetailCutPoint[i]->Draw();
			}
		}
		else
		{
			m_pFrogHeartPiece->Draw();
		}
	}
	else if (m_UseScalpel && m_pOrgan->GetOrganState() == OrganState::LIVER)
	{
		if (FrogLiverOpen == false)
		{
			for (int i = 0; i < 23; i++)
			{
				m_pFrogLiverCutPoint[i]->Draw();
			}

			m_pFrogLiverCutGuide->Draw(0.7f);
		}
		else
		{
			m_pFrogLiverPiece->Draw();
		}
	}
	else if (m_UseScalpel && m_pOrgan->GetOrganState() == OrganState::LUNGS)
	{
		if (FrogLungsOpen == false)
		{
			for (int i = 0; i < 15; i++)
			{
				m_pFrogLungsCutPoint[i]->Draw();
			}

			m_pFrogLungCutGuide->Draw(0.7f);
		}
	}

	if (FrogStomach01Open == true && FrogStomach02Open == true && FrogStomach03Open == false && m_pOrgan->GetOrganState() == OrganState::STOMACH)
	{
		for (int i = 0; i < 9; i++)
		{
			m_pFrogStomach03CutPoint[i]->Draw();
		}

		m_pFrogStomachCutGuide03->Draw(0.7f);
	}

	if ((m_UseScissors && m_pOrgan->GetOrganState() == OrganState::STOMACH) || (m_UseScalpel && m_pOrgan->GetOrganState() == OrganState::STOMACH))
	{
		if (FrogStomach01Open == false)
		{
			for (int i = 0; i < 14; i++)
			{
				m_pFrogStomach01CutPoint[i]->Draw();
			}

			m_pFrogStomachCutGuide01->Draw(0.7f);
		}

		if (FrogStomach01Open == true && FrogStomach02Open == false)
		{
			m_pFrogStomachCutGuide02->Draw(0.7f);
		}
	}

	// 장기 조직 그리기
	if (FrogHeartDetailOpen == true && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		m_pFrogHeartPiece->Draw();
	}

	if (FrogLiverOpen == true && m_pOrgan->GetOrganState() == OrganState::LIVER)
	{
		m_pFrogLiverPiece->Draw();
	}

	if (FrogLungsOpen == true && m_pOrgan->GetOrganState() == OrganState::LUNGS && m_pOrgan->GetOrgans(OrganState::LUNGS)->GetNowFrame() >= 3)
	{
		m_pFrogLungsPiece->Draw();
	}

	if (FrogStomach01Open == true && m_pOrgan->GetOrganState() == OrganState::STOMACH)
	{
		m_pFrogStomachPiece->Draw();
	}

	if (m_UsePincette && FrogHeartOpen == false && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		m_pHeartFatCheck01->Draw();
	}

	if (m_UsePincette && FrogHeartDetailOpen == true && m_pOrgan->GetOrganState() == OrganState::HEART)
	{
		m_pHeartFatCheck02->Draw();
	}

	if (FileFolder::GetInstance()->GetNowState())
	{
		FileFolder::GetInstance()->Draw();
	}

	m_pPlayer->Draw();
	m_pTextBox->Draw();

	// 페이드 아웃
	SceneManager::DrawBlackScreen();

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	//ShowDebug();
}

void MainDissectingRoomScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 40, L"Main_DissectingRoom 씬");
	JJEngine::GetInstance()->DrawText(0, 60, L"Tray Had Organ : %d", MainAutopsyRoomScene::TrayHadOrgan);
	JJEngine::GetInstance()->DrawText(0, 80, L"Frog Heart Cut Point Collided : %d", m_FrogHeartCutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 100, L"Frog Heart Detail Cut Point Collided : %d", m_FrogHeartDetailCutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 120, L"Frog Liver Cut Point Collided : %d", m_FrogLiverCutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 140, L"Frog Lung Cut Point Collided : %d", m_FrogLungsCutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 160, L"Frog Stomach01 Cut Point Collided : %d", m_FrogStomach01CutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 180, L"Frog Stomach02 Cut Point Collided : %d", m_FrogStomach02CutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 200, L"Frog Stomach03 Cut Point Collided : %d", m_FrogStomach03CutPointCollided);
	JJEngine::GetInstance()->DrawText(0, 240, L"Frog Stomach Cut Point Collided : %d", CutFrogStomach02GuideCollided);
	JJEngine::GetInstance()->DrawText(0, 280, L"Heart Fat Collided : %d", DetailOpenHeartFatCollided);
	JJEngine::GetInstance()->DrawText(0, 360, L"Now Pick Organ Piece : %d", m_NowPickOrganPiece);
}

void MainDissectingRoomScene::Release()
{
	Scene::Release();
}
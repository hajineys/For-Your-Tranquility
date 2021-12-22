#include "pch.h"

#include "MainOfficeScene.h"
#include "MainDissectingRoomScene.h"
#include "ObjectManager.h"
#include "TextBox.h"
#include "Button.h"
#include "ColliderBox.h"

bool MainOfficeScene::IsPlaying[22] = { false, };
bool MainOfficeScene::m_OnlyOnce;

MainOfficeScene::MainOfficeScene()
	:m_pPopupWindowBackgroundImg(nullptr),
	m_pNextScene(nullptr),
	m_NowState(eState::NONE),
	m_pIncidentBtn(nullptr),
	m_pIncidentBtnOn(nullptr),
	m_pMicroscopeBtn(nullptr),
	m_pMicroscopeBtnOn(nullptr),
	m_pMicroscope_PopupBackground(nullptr),
	m_pMicroscope_lens(nullptr),
	m_SchaleState(4),
	m_pPhoneBtn(nullptr),
	m_pPhoneBtnOn(nullptr),
	m_MonitorImage(nullptr),
	m_pMonitorBtnOn(nullptr),
	m_IsMonitorClicked(false),
	m_pPhone0Key(nullptr),
	m_pPhone1Key(nullptr),
	m_pPhone2Key(nullptr),
	m_pPhone3Key(nullptr),
	m_pPhone4Key(nullptr),
	m_pPhone5Key(nullptr),
	m_pPhone6Key(nullptr),
	m_pPhone7Key(nullptr),
	m_pPhone8Key(nullptr),
	m_pPhone9Key(nullptr),
	m_pPhoneHashKey(nullptr),
	m_pPhoneStarKey(nullptr),
	m_pFileBtn(nullptr),
	m_pFileBtnOn(nullptr),
	m_pAutopsyBtn(nullptr),
	m_pIncidentScreen(nullptr),
	m_pPhoneScreen(nullptr),
	m_pFileScreen(nullptr),
	m_pInvestigationCompleteBtn(nullptr),
	m_InputNumberStr(L""),
	m_Action1(L"12*"),
	m_Action2(L"10*"),
	m_Action3(L"13*"),
	m_pOfficeTextBox(nullptr)
{

}

MainOfficeScene::~MainOfficeScene()
{

}

void MainOfficeScene::Initialize()
{
	SoundManager::GetInstance()->VolumeUp(2);						// 다시 넘어올 때 볼륨 크게해준다.
	SoundManager::GetInstance()->VolumeDown(3);						// 다시 넘어올 때 부검실 볼륨을 작게해준다.

	// 처음 들어올때만 사운드를 실행한다.
	if (IsPlaying[0] == false)										// IsPlaying의 첫번째 칸이 false라면
	{
		SoundManager::GetInstance()->Play(2, L"BGM_Office");		// 오피스 음악을 재생시킨다.
		SoundManager::GetInstance()->Play(3, L"BGM_Room");			// 부검실 음악을 재생시킨다.
		SoundManager::GetInstance()->VolumeDown(3);					// 부검실 음악을 음소거 시킨다.
		IsPlaying[0] = true;										// IsPlaying의 첫번째 칸을 true 바꾼다.
	}

	//  다른씬으로 갔다가 다시 돌아올때 멈추었던 음악을 다시 재생시킨다.

	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	/// 대화상자
	m_pOfficeTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(20, 700), L"MainOfficeScene", UISortLayer::ENDLAYER);

	// 팝업 켜졌을때 버튼
	//m_PopupStateButton = true;

	// 배경 이미지
	m_pBackgroundImg = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Office2_background", 1, UISortLayer::BACKGROUND);
	m_pPopupWindowBackgroundImg = m_pObjectManager->OnlyCreateObject_Image(JVector(0, 0), L"Microscope_backgraound", 1, UISortLayer::BACKGROUND);

	// 씬 이동 버튼
	m_pNextScene = m_pObjectManager->CreateObject_Button(JVector(1774, 1003), L"icon_backtoOffice2", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);

	/// 오피스 씬 하이라이팅
	// 사건 현장 버튼 하이라이팅 
	m_pIncidentBtnOn = m_pObjectManager->CreateObject_Button(JVector(284, 7), L"Office2_board2", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);
	m_pIncidentBtnOn->AddSprite(L"Office2_board1", 1);
	m_pIncidentBtnOn->GetColliderBox()->SetSize(JVector(800, 530));

	// 현미경 버튼 하이라이팅
	m_pMicroscopeBtnOn = m_pObjectManager->CreateObject_Button(JVector(382, 549), L"Office2_microscope1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMicroscopeBtnOn->AddSprite(L"Office2_microscope", 1);
	m_pMicroscopeBtnOn->GetColliderBox()->SetSize(JVector(180, 230));

	// 전화기 버튼 하이라이팅
	m_pPhoneBtnOn = m_pObjectManager->CreateObject_Button(JVector(1044, 610), L"Office2_telephone1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPhoneBtnOn->AddSprite(L"Office2_telephone", 1);
	m_pPhoneBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// 파일철 버튼 하이라이팅
	m_pFileBtnOn = m_pObjectManager->CreateObject_Button(JVector(810, 722), L"Office2_file1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pFileBtnOn->AddSprite(L"Office2_file", 1);
	m_pFileBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// 모니터 버튼 하이라이팅
	m_pMonitorBtnOn = m_pObjectManager->CreateObject_Button(JVector(1277, 377), L"Office2_Monitor1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMonitorBtnOn->AddSprite(L"Office2_Monitor", 1);
	m_pMonitorBtnOn->GetColliderBox()->SetSize(JVector(200, 200));

	m_MonitorImage = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"egg02", 1, UISortLayer::POPUPWINDOW);
	m_MonitorImage->GetColliderBox()->SetSize(JVector(1920, 1080));

	// 전화기 팝업 화면 버튼
	m_pPhoneScreen = m_pObjectManager->OnlyCreateObject_Button(JVector(520, 202), L"telephone", 1, UISortLayer::POPUPWINDOW);

	/// 현미경 팝업 후
	// 팝업 후 현미경 팝업창 이미지
	m_pMicroscope_PopupBackground = m_pObjectManager->OnlyCreateObject_Image(JVector(380, 135), L"Microscope_PopupBackground", 1, UISortLayer::POPUPWINDOW);

	// 샬레에 담긴 샘플
	m_pMicroscope_schale[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_heart", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_liver", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_lung", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_stomach", 1, UISortLayer::POPUPWINDOWBUTTON);

	//현미경으로 본 샘플그림
	m_pMicroscope_lens_schale[0] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_heart2", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[1] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_liver1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[2] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_lung1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[3] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_stomach1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[4] = m_pObjectManager->OnlyCreateObject_Image(JVector(462, 280), L"Microscope_lens_background", 1, UISortLayer::POPUPWINDOW_UP);

	// 팝업후 렌즈 그림
	m_pMicroscope_lens = m_pObjectManager->OnlyCreateObject_Image(JVector(427, 210), L"Left_Microscope", 1, UISortLayer::POPUPWINDOW_OBJECT);
	m_pMicroscope_lens->AddSprite(L"Microscope_lens", 1);
	m_pMicroscope_lens->GetColliderBox()->SetSize(JVector(547, 564));

	/// 전화기 숫자버튼
	// 0-Key
	m_pPhone0Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_0key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone0Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 661;
	m_pPhone0Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 474;

	// 1-key
	m_pPhone1Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_1key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone1Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 567;
	m_pPhone1Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 185;

	// 2-key
	m_pPhone2Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_2key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone2Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 661;
	m_pPhone2Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 185;

	// 3-key
	m_pPhone3Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_3key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone3Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 753;
	m_pPhone3Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 185;

	// 4-key
	m_pPhone4Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_4key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone4Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 567;
	m_pPhone4Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 278;

	// 5-key
	m_pPhone5Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_5key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone5Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 661;
	m_pPhone5Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 278;

	// 6-key
	m_pPhone6Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_6key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone6Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 753;
	m_pPhone6Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 278;

	// 7-key
	m_pPhone7Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_7key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone7Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 567;
	m_pPhone7Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 374;

	// 8-key
	m_pPhone8Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_8key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone8Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 661;
	m_pPhone8Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 374;

	// 9-key
	m_pPhone9Key = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_9key", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhone9Key->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 753;
	m_pPhone9Key->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 374;

	// hash-key
	m_pPhoneHashKey = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_hashkey", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhoneHashKey->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 753;
	m_pPhoneHashKey->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 474;

	// star-key
	m_pPhoneStarKey = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"telephone_starkey", 2, UISortLayer::POPUPWINDOWBUTTON);
	m_pPhoneStarKey->Transform()->Pos.x = m_pPhoneScreen->Transform()->Pos.x + 567;
	m_pPhoneStarKey->Transform()->Pos.y = m_pPhoneScreen->Transform()->Pos.y + 474;
}

void MainOfficeScene::Update(float dTime)
{
	SceneManager::FadeOut(dTime);

	// 페이드 아웃이 끝났을 경우만 씬 업데이트 (오작동 방지)
	if (!SceneManager::IsFadeOutEnd)
		return;

	/// 씬의 공통적인 버튼들(eNowSceneState 참고)만 Check 함
	m_pObjectManager->CheckButtonClicked(this);

	if (m_pNextScene->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Button_Door");
	}

	/// 전화기 숫자버튼 업데이트
	m_pPhone0Key->Update(dTime);
	m_pPhone1Key->Update(dTime);
	m_pPhone2Key->Update(dTime);
	m_pPhone3Key->Update(dTime);
	m_pPhone4Key->Update(dTime);
	m_pPhone5Key->Update(dTime);
	m_pPhone6Key->Update(dTime);
	m_pPhone7Key->Update(dTime);
	m_pPhone8Key->Update(dTime);
	m_pPhone9Key->Update(dTime);
	m_pPhoneHashKey->Update(dTime);
	m_pPhoneStarKey->Update(dTime);

	m_pPopupWindowBackgroundImg->Update(dTime);

	m_pMicroscope_PopupBackground->Update(dTime);

	// 씬 이동
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

			/*SoundManager::GetInstance()->Pause(3, L"BGM_Office");*/
			if (m_OnlyOnce == false)
			{
				SoundManager::GetInstance()->VolumeDown(2); // 씬 넘어갈 때 오피스 볼륨을 최소화 시킨다.
				SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY_ENTRY); //딱한번만 부검실 엔트리로 간다.
				SoundManager::GetInstance()->VolumeUp(3); // 씬 넘어갈 때 부검실 볼륨을 키워준다.
				m_OnlyOnce = true;
				return;
			}
			else
			{
				SoundManager::GetInstance()->VolumeDown(2); // 씬 넘어갈 때 오피스 볼륨을 최소화 시킨다.
				SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY); //  부검실로 간다
				SoundManager::GetInstance()->VolumeUp(3); // 씬 넘어갈 때 부검실 볼륨을 키워준다.
				return;
			}
		}
	}
	break;

	case eNowSceneState::GO_TO_PREV_SCENE:
		SceneManager::ChangeScene(eSceneStateAll::MAIN_INCIDENT);
		return;
	case eNowSceneState::POPUP_SHOW:
		break;
	}

	if (m_pFileBtnOn->GetColliderBox()->IsClicked)
	{
		FileFolder::GetInstance()->On();
	}

	FileFolder::GetInstance()->Update(dTime, this);

	if (FileFolder::GetInstance()->GetNowState())
	{
		return;
	}

	if (m_NowState == eState::NONE)
	{
		m_pObjectManager->UpdateAll(dTime);
	}

	POINT _mousePos = InputManager::GetInstance()->GetMousePos();

	if (InputManager::GetInstance()->CheckLeftButtonUp()
		&& m_pOfficeTextBox->GetState() == false
		&& m_NowState == eState::POPUP_MICROSCOPE)
	{
		SoundManager::GetInstance()->Play(1, L"Glass_01");

		// 눌러진 샬레에 따라 스크립트 출력
		if (m_pMicroscope_schale[0]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))			// 심장
		{
			m_pOfficeTextBox->SetStartEndIndex(165, 165);
		}
		else if (m_pMicroscope_schale[1]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// 간
		{
			m_pOfficeTextBox->SetStartEndIndex(166, 166);
		}
		else if (m_pMicroscope_schale[2]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// 폐
		{
			m_pOfficeTextBox->SetStartEndIndex(167, 167);
		}
		else if (m_pMicroscope_schale[3]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// 위
		{
			m_pOfficeTextBox->SetStartEndIndex(168, 168);
		}
	}

	/// 대화상자가 켜져 있을 경우만 업데이트 해준다.
	m_pOfficeTextBox->Update(dTime);

	if (m_pOfficeTextBox->GetState())
		return;

	// 사건현장 이미지 위에 올렸을때 하이라이팅
	if (m_pIncidentBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[1] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[1] = true;
		}

		m_pIncidentBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pIncidentBtnOn->ChangeSprite(0);
		IsPlaying[1] = false;
	}

	// 현미경 하이라이팅
	if (m_pMicroscopeBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[2] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[2] = true;
		}

		m_pMicroscopeBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pMicroscopeBtnOn->ChangeSprite(0);
		IsPlaying[2] = false;
	}

	m_pMicroscope_lens->Update(dTime);

	// 충돌체크를 하기 위해 샘플 버튼을 업데이트해준다.
	for (int i = 0; i < 4; i++)
	{
		m_pMicroscope_schale[i]->Update(dTime);
	}

	for (int i = 0; i < 5; i++)
	{
		m_pMicroscope_lens_schale[i]->Update(dTime);
	}

	if (MainDissectingRoomScene::PetrischaleHadHeartPiece)
	{
		m_pMicroscope_schale[0]->Transform()->Pos = { 1050, 285 };
	}

	if (MainDissectingRoomScene::PetrischaleHadLiverPiece)
	{
		m_pMicroscope_schale[1]->Transform()->Pos = { 1300, 285 };
	}

	if (MainDissectingRoomScene::PetrischaleHadLungsPiece)
	{
		m_pMicroscope_schale[2]->Transform()->Pos = { 1050, 535 };
	}

	if (MainDissectingRoomScene::PetrischaleHadStomachPiece)
	{
		m_pMicroscope_schale[3]->Transform()->Pos = { 1300, 535 };
	}

	// 현미경 렌즈에 어떤 조직이 들어갔냐에 따라 다른 상태 변경
	if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[3]))		//위
	{
		m_SchaleState = 3;

		if (!IsPlaying[3])
		{
			FileFolder::GetInstance()->StomachState = eStomachState::UseMicroScope;
			IsPlaying[3] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[2])) // 폐
	{
		m_SchaleState = 2;

		if (!IsPlaying[4])
		{
			FileFolder::GetInstance()->LungState = eLungState::UseMicroScope;
			IsPlaying[4] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[1])) // 간
	{
		m_SchaleState = 1;

		if (!IsPlaying[5])
		{
			FileFolder::GetInstance()->LiverState = eLiverState::UseMicroScope;
			IsPlaying[5] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[0])) //심장
	{
		m_SchaleState = 0;

		if (!IsPlaying[6])
		{
			FileFolder::GetInstance()->HeartState = eHeartState::UseMicroScope;
			IsPlaying[6] = true;
		}
	}
	else
	{
		m_SchaleState = 4;
	}

	// 샬렛 드래그
	if (m_pMicroscope_schale[3]->GetColliderBox()->IsHolding)
	{
		m_pMicroscope_schale[3]->Transform()->Pos.x = _mousePos.x - m_pMicroscope_schale[3]->Transform()->Size.x / 2;
		m_pMicroscope_schale[3]->Transform()->Pos.y = _mousePos.y - m_pMicroscope_schale[3]->Transform()->Size.y / 2;
	}
	else if (m_pMicroscope_schale[2]->GetColliderBox()->IsHolding)
	{
		m_pMicroscope_schale[2]->Transform()->Pos.x = _mousePos.x - m_pMicroscope_schale[2]->Transform()->Size.x / 2;
		m_pMicroscope_schale[2]->Transform()->Pos.y = _mousePos.y - m_pMicroscope_schale[2]->Transform()->Size.y / 2;
	}
	else if (m_pMicroscope_schale[1]->GetColliderBox()->IsHolding)
	{
		m_pMicroscope_schale[1]->Transform()->Pos.x = _mousePos.x - m_pMicroscope_schale[1]->Transform()->Size.x / 2;
		m_pMicroscope_schale[1]->Transform()->Pos.y = _mousePos.y - m_pMicroscope_schale[1]->Transform()->Size.y / 2;
	}
	else if (m_pMicroscope_schale[0]->GetColliderBox()->IsHolding)
	{
		m_pMicroscope_schale[0]->Transform()->Pos.x = _mousePos.x - m_pMicroscope_schale[0]->Transform()->Size.x / 2;
		m_pMicroscope_schale[0]->Transform()->Pos.y = _mousePos.y - m_pMicroscope_schale[0]->Transform()->Size.y / 2;
	}

	// 전화기 하이라이팅
	if (m_pPhoneBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[7] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[7] = true;
		}

		m_pPhoneBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pPhoneBtnOn->ChangeSprite(0);
		IsPlaying[7] = false;
	}

	// 파일 하이라이팅
	if (m_pFileBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[8] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[8] = true;
		}

		m_pFileBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pFileBtnOn->ChangeSprite(0);
		IsPlaying[8] = false;
	}

	// 모니터 하이라이팅
	if (m_pMonitorBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[9] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[9] = true;
		}

		m_pMonitorBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pMonitorBtnOn->ChangeSprite(0);
		IsPlaying[9] = false;
	}

	// 현며경 열림
	if (m_NowState == eState::NONE && m_pMicroscopeBtnOn->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::POPUP_MICROSCOPE;
	}

	// 현미경 누르면 닫힘
	if (m_NowState == eState::POPUP_MICROSCOPE
		&& m_pMicroscope_PopupBackground->GetColliderBox()->CheckOutSideCollided()
		&& m_pMicroscope_PopupBackground->GetColliderBox()->CheckOutSideClicked()
		&& m_pOfficeTextBox->GetState() == false)
	{
		m_NowState = eState::NONE;
	}

	static bool _0keyClicked = false;
	static bool _1keyClicked = false;
	static bool _2keyClicked = false;
	static bool _3keyClicked = false;
	static bool _4keyClicked = false;
	static bool _5keyClicked = false;
	static bool _6keyClicked = false;
	static bool _7keyClicked = false;
	static bool _8keyClicked = false;
	static bool _9keyClicked = false;
	static bool _hashkeyClicked = false;
	static bool _starkeyClicked = false;

	/// 전화기 숫자 버튼 관련
	if (m_NowState == eState::POPUP_PHONE && m_pOfficeTextBox->GetState() == false)
	{
		// 전화기 0버튼 프레임
		if (m_pPhone0Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[10] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[10] = true;
			}

			_0keyClicked = true;
			m_pPhone0Key->ResetAnimation();
			m_InputNumberStr += L"0";
		}
		else
		{
			IsPlaying[10] = false;
		}

		// 전화기 0번 키 애니메이션 리셋
		if (_0keyClicked)
		{
			m_pPhone0Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 1버튼 프레임
		if (m_pPhone1Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[11] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[11] = true;
			}

			_1keyClicked = true;
			m_pPhone1Key->ResetAnimation();
			m_InputNumberStr += L"1";
		}
		else
		{
			IsPlaying[11] = false;
		}

		// 전화기 1번 키 애니메이션 리셋
		if (_1keyClicked)
		{
			m_pPhone1Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 2버튼 프레임
		if (m_pPhone2Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[12] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[12] = true;
			}

			_2keyClicked = true;
			m_pPhone2Key->ResetAnimation();
			m_InputNumberStr += L"2";
		}
		else
		{
			IsPlaying[12] = false;
		}

		// 전화기 2번 키 애니메이션 리셋
		if (_2keyClicked)
		{
			m_pPhone2Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 3버튼 프레임
		if (m_pPhone3Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[13] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[13] = true;
			}

			_3keyClicked = true;
			m_pPhone3Key->ResetAnimation();
			m_InputNumberStr += L"3";

		}
		else
		{
			IsPlaying[13] = false;
		}

		// 전화기 3번 키 애니메이션 리셋
		if (_3keyClicked)
		{
			m_pPhone3Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 4버튼 프레임
		if (m_pPhone4Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[14] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[14] = true;
			}

			_4keyClicked = true;
			m_pPhone4Key->ResetAnimation();
			m_InputNumberStr += L"4";
		}
		else
		{
			IsPlaying[14] = false;
		}

		// 전화기 4번 키 애니메이션 리셋
		if (_4keyClicked)
		{
			m_pPhone4Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 5버튼 프레임
		if (m_pPhone5Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[15] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[15] = true;
			}

			_5keyClicked = true;
			m_pPhone5Key->ResetAnimation();
			m_InputNumberStr += L"5";
		}
		else
		{
			IsPlaying[15] = false;
		}

		// 전화기 5번 키 애니메이션 리셋
		if (_5keyClicked)
		{
			m_pPhone5Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 6버튼 프레임
		if (m_pPhone6Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[16] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[16] = true;
			}

			_6keyClicked = true;
			m_pPhone6Key->ResetAnimation();
			m_InputNumberStr += L"6";
		}
		else
		{
			IsPlaying[16] = false;
		}

		// 전화기 6번 키 애니메이션 리셋
		if (_6keyClicked)
		{
			m_pPhone6Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 7버튼 프레임
		if (m_pPhone7Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[17] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[17] = true;
			}

			_7keyClicked = true;
			m_pPhone7Key->ResetAnimation();
			m_InputNumberStr += L"7";
		}
		else
		{
			IsPlaying[17] = false;
		}

		// 전화기 7번 키 애니메이션 리셋
		if (_7keyClicked)
		{
			m_pPhone7Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 8버튼 프레임
		if (m_pPhone8Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[18] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[18] = true;
			}

			_8keyClicked = true;
			m_pPhone8Key->ResetAnimation();
			m_InputNumberStr += L"8";
		}
		else
		{
			IsPlaying[18] = false;
		}

		// 전화기 8번 키 애니메이션 리셋
		if (_8keyClicked)
		{
			m_pPhone8Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 9버튼 프레임
		if (m_pPhone9Key->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[19] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[19] = true;
			}

			_9keyClicked = true;
			m_pPhone9Key->ResetAnimation();
			m_InputNumberStr += L"9";
		}
		else
		{
			IsPlaying[19] = false;
		}

		// 전화기 9번 키 애니메이션 리셋
		if (_9keyClicked)
		{
			m_pPhone9Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 hash 버튼 프레임
		if (m_pPhoneHashKey->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[20] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[20] = true;
			}

			_hashkeyClicked = true;
			m_pPhoneHashKey->ResetAnimation();
			m_InputNumberStr = L"";
		}
		else
		{
			IsPlaying[20] = false;
		}

		// 전화기 hash 번 키 애니메이션 리셋
		if (_hashkeyClicked)
		{

			m_pPhoneHashKey->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 전화기 Star 버튼 프레임
		if (m_pPhoneStarKey->GetColliderBox()->IsClicked)
		{
			if (IsPlaying[21] == false)
			{
				SoundManager::GetInstance()->Play(1, L"Button_Down_PhonePad");
				IsPlaying[21] = true;
			}

			_starkeyClicked = true;
			m_pPhoneStarKey->ResetAnimation();
			m_InputNumberStr += L"*";

			/// 전화기 번호 비교
			if (m_InputNumberStr == m_Action1)                    /// 형사과
			{
				/// 돋보기로 머리 & 돋보기로 팔
				if (FileFolder::GetInstance()->IsCheckHead == true && FileFolder::GetInstance()->IsCheckArm == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(145, 164);
				}
				/// 돋보기로 머리 조사 했을때 대화상자 
				else if (FileFolder::GetInstance()->IsCheckHead == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(121, 131);
				}
				/// 돋보기로 팔 조사 했을때 대화상자
				else if (FileFolder::GetInstance()->IsCheckArm == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(132, 144);
				}
				else
				{
					/// 위에 조건이 만족 안했을때 기본 멘트
					m_pOfficeTextBox->SetStartEndIndex(118, 120);
				}
			}
			else if (m_InputNumberStr == m_Action2)                /// 병리조직과
			{
				/// 심장 병리과 멘트 출력 확인용
				//FileFolder::GetInstance()->HeartState = eHeartState::UseMicroScope;

				/// 심장 & 간 & 폐
				if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope
					&& FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope
					&& FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(93, 117);
				}
				/// 심장과 간
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope && FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					m_pOfficeTextBox->SetStartEndIndex(38, 56);
				}
				/// 심장과 폐
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope && FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(57, 75);
				}
				/// 간과 폐 
				else if (FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope && FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(76, 92);
				}
				/// 심장 병리과 멘트
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					m_pOfficeTextBox->SetStartEndIndex(3, 15);
				}
				/// 간 병리과 멘트 출력
				else if (FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope)
				{
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					m_pOfficeTextBox->SetStartEndIndex(16, 26);
				}
				/// 폐 병리과 멘트 출력
				else if (FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(27, 37);
				}
				/// 아무조건도 안했을때
				else
				{
					m_pOfficeTextBox->SetStartEndIndex(0, 2);
				}
			}
			else if (m_InputNumberStr == m_Action3)                ///  보호관찰과
			{
				// 기본멘트만
				m_pOfficeTextBox->SetStartEndIndex(169, 171);
			}
		}
		else
		{
			IsPlaying[21] = false;
		}

		// 전화기 Star 번 키 애니메이션 리셋
		if (_starkeyClicked)
		{
			m_pPhoneStarKey->PlayAndResetAnimation(dTime, 2.5f);
		}

		// 숫자가 3개를 초과해서 입력되었을 때
		if (m_InputNumberStr.size() > 3)
			m_InputNumberStr = L"";
	}

	// 전화기 버튼 눌렀을 때 전화기 팝업이 뜬다.
	if (m_NowState == eState::NONE && m_pPhoneBtnOn->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::POPUP_PHONE;
	}

	// 전화기 팝업이 떠있고, 전화기 팝업 이외의 부분을 누르면 팝업이 닫힌다. = m_NowState = eState::None;
	if (m_NowState == eState::POPUP_PHONE
		&& m_pPhoneScreen->GetColliderBox()->CheckOutSideCollided()
		&& m_pPhoneScreen->GetColliderBox()->CheckOutSideClicked()
		&& m_pOfficeTextBox->GetState() == false)
	{
		m_NowState = eState::NONE;
		m_InputNumberStr = L"";
	}

	m_MonitorImage->Update(dTime);

	// 모니터 창 활성화(이스터에그)
	if (m_pMonitorBtnOn->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::POPUP_MONITOR;
		m_IsMonitorClicked = true;
		m_MonitorImage->Transform()->Pos = { 624, 301 };
	}

	if (m_MonitorImage->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::NONE;
		m_MonitorImage->Transform()->Pos = { -500, -500 };
	}
}

void MainOfficeScene::Draw()
{
	// 모든 오브젝트 그리기
	m_pObjectManager->DrawAll();

	if (m_NowState == eState::POPUP_MICROSCOPE)
	{
		m_pPopupWindowBackgroundImg->Draw();
		m_pMicroscope_PopupBackground->Draw();						// 현미경 배경그린다

		if (FileFolder::GetInstance()->HeartState == eHeartState::SampleMoved || FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope)
		{
			m_pMicroscope_schale[0]->Draw();
		}

		if (FileFolder::GetInstance()->LiverState == eLiverState::SampleMoved || FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope)
		{
			m_pMicroscope_schale[1]->Draw();
		}

		if (FileFolder::GetInstance()->LungState == eLungState::SampleMoved || FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
		{
			m_pMicroscope_schale[2]->Draw();
		}

		if (FileFolder::GetInstance()->StomachState == eStomachState::SampleMoved || FileFolder::GetInstance()->StomachState == eStomachState::UseMicroScope)
		{
			m_pMicroscope_schale[3]->Draw();
		}

		switch (m_SchaleState)
		{
		case 0:
			m_pMicroscope_lens_schale[0]->Draw();
			break;

		case 1:
			m_pMicroscope_lens_schale[1]->Draw();
			break;

		case 2:
			m_pMicroscope_lens_schale[2]->Draw();
			break;

		case 3:
			m_pMicroscope_lens_schale[3]->Draw();
			break;

		case 4:
			m_pMicroscope_lens_schale[4]->Draw();
			break;
		}

		m_pMicroscope_lens->Draw();									// 샘플 위에 렌즈를 그린다.
	}

	if (m_NowState == eState::POPUP_PHONE)
	{
		m_pPopupWindowBackgroundImg->Draw();
		m_pPhoneScreen->Draw();
		m_pPhone0Key->Draw();
		m_pPhone1Key->Draw();
		m_pPhone2Key->Draw();
		m_pPhone3Key->Draw();
		m_pPhone4Key->Draw();
		m_pPhone5Key->Draw();
		m_pPhone6Key->Draw();
		m_pPhone7Key->Draw();
		m_pPhone8Key->Draw();
		m_pPhone9Key->Draw();
		m_pPhoneHashKey->Draw();
		m_pPhoneStarKey->Draw();

		// 전화기 번호 찍었을때 나옴
		JJEngine::GetInstance()->DrawText(1130, 300, 35, ColorF(ColorF::LightGray), m_InputNumberStr.c_str());
	}

	if (m_NowState == eState::POPUP_MONITOR)
	{
		m_pPopupWindowBackgroundImg->Draw();
		m_MonitorImage->Draw();
	}

	m_pOfficeTextBox->Draw();

	if (FileFolder::GetInstance()->GetNowState())
	{
		FileFolder::GetInstance()->Draw();
	}

	//ShowDebug();

	SceneManager::DrawBlackScreen();
}

void MainOfficeScene::ShowDebug()
{
	Scene::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 120, L"TextBox X : %f", m_pOfficeTextBox->Transform()->Pos.x);
	JJEngine::GetInstance()->DrawText(0, 150, L"TextBox Y : %f", m_pOfficeTextBox->Transform()->Pos.y);

	JJEngine::GetInstance()->DrawText(0, 40, L"Main_Office 씬");

	wstring _nowState;

	switch (m_NowState)
	{
	case MainOfficeScene::eState::POPUP_INCIDENT:
		_nowState = L"POPUP_INCIDENT";
		break;

	case MainOfficeScene::eState::POPUP_MICROSCOPE:
		_nowState = L"POPUP_MICROSCOPE";
		break;

	case MainOfficeScene::eState::POPUP_PHONE:
		_nowState = L"POPUP_PHONE";
		break;

	case MainOfficeScene::eState::POPUP_FILE:
		_nowState = L"POPUP_FILE";
		break;

	case MainOfficeScene::eState::POPUP_STATE_COUNT:
		_nowState = L"POPUP_STATE_COUNT";
		break;

	case MainOfficeScene::eState::NONE:
		_nowState = L"NONE";
		break;
	}
}

void MainOfficeScene::Release()
{
	m_pObjectManager->Release();
	Scene::Release();
}
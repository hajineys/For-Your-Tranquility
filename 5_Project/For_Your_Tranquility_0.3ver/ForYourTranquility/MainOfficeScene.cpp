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
	SoundManager::GetInstance()->VolumeUp(2);						// �ٽ� �Ѿ�� �� ���� ũ�����ش�.
	SoundManager::GetInstance()->VolumeDown(3);						// �ٽ� �Ѿ�� �� �ΰ˽� ������ �۰����ش�.

	// ó�� ���ö��� ���带 �����Ѵ�.
	if (IsPlaying[0] == false)										// IsPlaying�� ù��° ĭ�� false���
	{
		SoundManager::GetInstance()->Play(2, L"BGM_Office");		// ���ǽ� ������ �����Ų��.
		SoundManager::GetInstance()->Play(3, L"BGM_Room");			// �ΰ˽� ������ �����Ų��.
		SoundManager::GetInstance()->VolumeDown(3);					// �ΰ˽� ������ ���Ұ� ��Ų��.
		IsPlaying[0] = true;										// IsPlaying�� ù��° ĭ�� true �ٲ۴�.
	}

	//  �ٸ������� ���ٰ� �ٽ� ���ƿö� ���߾��� ������ �ٽ� �����Ų��.

	Scene::Initialize();

	InputManager::GetInstance()->Reset();

	/// ��ȭ����
	m_pOfficeTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(20, 700), L"MainOfficeScene", UISortLayer::ENDLAYER);

	// �˾� �������� ��ư
	//m_PopupStateButton = true;

	// ��� �̹���
	m_pBackgroundImg = m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Office2_background", 1, UISortLayer::BACKGROUND);
	m_pPopupWindowBackgroundImg = m_pObjectManager->OnlyCreateObject_Image(JVector(0, 0), L"Microscope_backgraound", 1, UISortLayer::BACKGROUND);

	// �� �̵� ��ư
	m_pNextScene = m_pObjectManager->CreateObject_Button(JVector(1774, 1003), L"icon_backtoOffice2", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);

	/// ���ǽ� �� ���̶�����
	// ��� ���� ��ư ���̶����� 
	m_pIncidentBtnOn = m_pObjectManager->CreateObject_Button(JVector(284, 7), L"Office2_board2", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);
	m_pIncidentBtnOn->AddSprite(L"Office2_board1", 1);
	m_pIncidentBtnOn->GetColliderBox()->SetSize(JVector(800, 530));

	// ���̰� ��ư ���̶�����
	m_pMicroscopeBtnOn = m_pObjectManager->CreateObject_Button(JVector(382, 549), L"Office2_microscope1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMicroscopeBtnOn->AddSprite(L"Office2_microscope", 1);
	m_pMicroscopeBtnOn->GetColliderBox()->SetSize(JVector(180, 230));

	// ��ȭ�� ��ư ���̶�����
	m_pPhoneBtnOn = m_pObjectManager->CreateObject_Button(JVector(1044, 610), L"Office2_telephone1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPhoneBtnOn->AddSprite(L"Office2_telephone", 1);
	m_pPhoneBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// ����ö ��ư ���̶�����
	m_pFileBtnOn = m_pObjectManager->CreateObject_Button(JVector(810, 722), L"Office2_file1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pFileBtnOn->AddSprite(L"Office2_file", 1);
	m_pFileBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// ����� ��ư ���̶�����
	m_pMonitorBtnOn = m_pObjectManager->CreateObject_Button(JVector(1277, 377), L"Office2_Monitor1", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMonitorBtnOn->AddSprite(L"Office2_Monitor", 1);
	m_pMonitorBtnOn->GetColliderBox()->SetSize(JVector(200, 200));

	m_MonitorImage = m_pObjectManager->OnlyCreateObject_Button(JVector(0, 0), L"egg02", 1, UISortLayer::POPUPWINDOW);
	m_MonitorImage->GetColliderBox()->SetSize(JVector(1920, 1080));

	// ��ȭ�� �˾� ȭ�� ��ư
	m_pPhoneScreen = m_pObjectManager->OnlyCreateObject_Button(JVector(520, 202), L"telephone", 1, UISortLayer::POPUPWINDOW);

	/// ���̰� �˾� ��
	// �˾� �� ���̰� �˾�â �̹���
	m_pMicroscope_PopupBackground = m_pObjectManager->OnlyCreateObject_Image(JVector(380, 135), L"Microscope_PopupBackground", 1, UISortLayer::POPUPWINDOW);

	// ������ ��� ����
	m_pMicroscope_schale[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_heart", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_liver", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[2] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_lung", 1, UISortLayer::POPUPWINDOWBUTTON);
	m_pMicroscope_schale[3] = m_pObjectManager->OnlyCreateObject_Button(JVector(-100, -100), L"Microscope_schale_stomach", 1, UISortLayer::POPUPWINDOWBUTTON);

	//���̰����� �� ���ñ׸�
	m_pMicroscope_lens_schale[0] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_heart2", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[1] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_liver1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[2] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_lung1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[3] = m_pObjectManager->OnlyCreateObject_Image(JVector(482, 295), L"frog_cell_stomach1", 1, UISortLayer::POPUPWINDOW_UP);
	m_pMicroscope_lens_schale[4] = m_pObjectManager->OnlyCreateObject_Image(JVector(462, 280), L"Microscope_lens_background", 1, UISortLayer::POPUPWINDOW_UP);

	// �˾��� ���� �׸�
	m_pMicroscope_lens = m_pObjectManager->OnlyCreateObject_Image(JVector(427, 210), L"Left_Microscope", 1, UISortLayer::POPUPWINDOW_OBJECT);
	m_pMicroscope_lens->AddSprite(L"Microscope_lens", 1);
	m_pMicroscope_lens->GetColliderBox()->SetSize(JVector(547, 564));

	/// ��ȭ�� ���ڹ�ư
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

	// ���̵� �ƿ��� ������ ��츸 �� ������Ʈ (���۵� ����)
	if (!SceneManager::IsFadeOutEnd)
		return;

	/// ���� �������� ��ư��(eNowSceneState ����)�� Check ��
	m_pObjectManager->CheckButtonClicked(this);

	if (m_pNextScene->GetColliderBox()->IsClicked)
	{
		SoundManager::GetInstance()->Play(1, L"Button_Door");
	}

	/// ��ȭ�� ���ڹ�ư ������Ʈ
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

	// �� �̵�
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
				SoundManager::GetInstance()->VolumeDown(2); // �� �Ѿ �� ���ǽ� ������ �ּ�ȭ ��Ų��.
				SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY_ENTRY); //���ѹ��� �ΰ˽� ��Ʈ���� ����.
				SoundManager::GetInstance()->VolumeUp(3); // �� �Ѿ �� �ΰ˽� ������ Ű���ش�.
				m_OnlyOnce = true;
				return;
			}
			else
			{
				SoundManager::GetInstance()->VolumeDown(2); // �� �Ѿ �� ���ǽ� ������ �ּ�ȭ ��Ų��.
				SceneManager::ChangeScene(eSceneStateAll::MAIN_AUTOPSY); //  �ΰ˽Ƿ� ����
				SoundManager::GetInstance()->VolumeUp(3); // �� �Ѿ �� �ΰ˽� ������ Ű���ش�.
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

		// ������ ������ ���� ��ũ��Ʈ ���
		if (m_pMicroscope_schale[0]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))			// ����
		{
			m_pOfficeTextBox->SetStartEndIndex(165, 165);
		}
		else if (m_pMicroscope_schale[1]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// ��
		{
			m_pOfficeTextBox->SetStartEndIndex(166, 166);
		}
		else if (m_pMicroscope_schale[2]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// ��
		{
			m_pOfficeTextBox->SetStartEndIndex(167, 167);
		}
		else if (m_pMicroscope_schale[3]->GetColliderBox()->CheckCollidedObject(m_pMicroscope_lens))	// ��
		{
			m_pOfficeTextBox->SetStartEndIndex(168, 168);
		}
	}

	/// ��ȭ���ڰ� ���� ���� ��츸 ������Ʈ ���ش�.
	m_pOfficeTextBox->Update(dTime);

	if (m_pOfficeTextBox->GetState())
		return;

	// ������� �̹��� ���� �÷����� ���̶�����
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

	// ���̰� ���̶�����
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

	// �浹üũ�� �ϱ� ���� ���� ��ư�� ������Ʈ���ش�.
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

	// ���̰� ��� � ������ ���Ŀ� ���� �ٸ� ���� ����
	if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[3]))		//��
	{
		m_SchaleState = 3;

		if (!IsPlaying[3])
		{
			FileFolder::GetInstance()->StomachState = eStomachState::UseMicroScope;
			IsPlaying[3] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[2])) // ��
	{
		m_SchaleState = 2;

		if (!IsPlaying[4])
		{
			FileFolder::GetInstance()->LungState = eLungState::UseMicroScope;
			IsPlaying[4] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[1])) // ��
	{
		m_SchaleState = 1;

		if (!IsPlaying[5])
		{
			FileFolder::GetInstance()->LiverState = eLiverState::UseMicroScope;
			IsPlaying[5] = true;
		}
	}
	else if (m_pMicroscope_lens->GetColliderBox()->CheckCollidedObject(m_pMicroscope_schale[0])) //����
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

	// ���� �巡��
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

	// ��ȭ�� ���̶�����
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

	// ���� ���̶�����
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

	// ����� ���̶�����
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

	// ����� ����
	if (m_NowState == eState::NONE && m_pMicroscopeBtnOn->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::POPUP_MICROSCOPE;
	}

	// ���̰� ������ ����
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

	/// ��ȭ�� ���� ��ư ����
	if (m_NowState == eState::POPUP_PHONE && m_pOfficeTextBox->GetState() == false)
	{
		// ��ȭ�� 0��ư ������
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

		// ��ȭ�� 0�� Ű �ִϸ��̼� ����
		if (_0keyClicked)
		{
			m_pPhone0Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 1��ư ������
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

		// ��ȭ�� 1�� Ű �ִϸ��̼� ����
		if (_1keyClicked)
		{
			m_pPhone1Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 2��ư ������
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

		// ��ȭ�� 2�� Ű �ִϸ��̼� ����
		if (_2keyClicked)
		{
			m_pPhone2Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 3��ư ������
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

		// ��ȭ�� 3�� Ű �ִϸ��̼� ����
		if (_3keyClicked)
		{
			m_pPhone3Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 4��ư ������
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

		// ��ȭ�� 4�� Ű �ִϸ��̼� ����
		if (_4keyClicked)
		{
			m_pPhone4Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 5��ư ������
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

		// ��ȭ�� 5�� Ű �ִϸ��̼� ����
		if (_5keyClicked)
		{
			m_pPhone5Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 6��ư ������
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

		// ��ȭ�� 6�� Ű �ִϸ��̼� ����
		if (_6keyClicked)
		{
			m_pPhone6Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 7��ư ������
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

		// ��ȭ�� 7�� Ű �ִϸ��̼� ����
		if (_7keyClicked)
		{
			m_pPhone7Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 8��ư ������
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

		// ��ȭ�� 8�� Ű �ִϸ��̼� ����
		if (_8keyClicked)
		{
			m_pPhone8Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� 9��ư ������
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

		// ��ȭ�� 9�� Ű �ִϸ��̼� ����
		if (_9keyClicked)
		{
			m_pPhone9Key->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� hash ��ư ������
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

		// ��ȭ�� hash �� Ű �ִϸ��̼� ����
		if (_hashkeyClicked)
		{

			m_pPhoneHashKey->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ��ȭ�� Star ��ư ������
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

			/// ��ȭ�� ��ȣ ��
			if (m_InputNumberStr == m_Action1)                    /// �����
			{
				/// ������� �Ӹ� & ������� ��
				if (FileFolder::GetInstance()->IsCheckHead == true && FileFolder::GetInstance()->IsCheckArm == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(145, 164);
				}
				/// ������� �Ӹ� ���� ������ ��ȭ���� 
				else if (FileFolder::GetInstance()->IsCheckHead == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(121, 131);
				}
				/// ������� �� ���� ������ ��ȭ����
				else if (FileFolder::GetInstance()->IsCheckArm == true)
				{
					m_pOfficeTextBox->SetStartEndIndex(132, 144);
				}
				else
				{
					/// ���� ������ ���� �������� �⺻ ��Ʈ
					m_pOfficeTextBox->SetStartEndIndex(118, 120);
				}
			}
			else if (m_InputNumberStr == m_Action2)                /// ����������
			{
				/// ���� ������ ��Ʈ ��� Ȯ�ο�
				//FileFolder::GetInstance()->HeartState = eHeartState::UseMicroScope;

				/// ���� & �� & ��
				if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope
					&& FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope
					&& FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(93, 117);
				}
				/// ����� ��
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope && FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					m_pOfficeTextBox->SetStartEndIndex(38, 56);
				}
				/// ����� ��
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope && FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(57, 75);
				}
				/// ���� �� 
				else if (FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope && FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(76, 92);
				}
				/// ���� ������ ��Ʈ
				else if (FileFolder::GetInstance()->HeartState == eHeartState::UseMicroScope)
				{
					FileFolder::GetInstance()->HeartState = eHeartState::Call;
					m_pOfficeTextBox->SetStartEndIndex(3, 15);
				}
				/// �� ������ ��Ʈ ���
				else if (FileFolder::GetInstance()->LiverState == eLiverState::UseMicroScope)
				{
					FileFolder::GetInstance()->LiverState = eLiverState::Call;
					m_pOfficeTextBox->SetStartEndIndex(16, 26);
				}
				/// �� ������ ��Ʈ ���
				else if (FileFolder::GetInstance()->LungState == eLungState::UseMicroScope)
				{
					FileFolder::GetInstance()->LungState = eLungState::Call;
					m_pOfficeTextBox->SetStartEndIndex(27, 37);
				}
				/// �ƹ����ǵ� ��������
				else
				{
					m_pOfficeTextBox->SetStartEndIndex(0, 2);
				}
			}
			else if (m_InputNumberStr == m_Action3)                ///  ��ȣ������
			{
				// �⺻��Ʈ��
				m_pOfficeTextBox->SetStartEndIndex(169, 171);
			}
		}
		else
		{
			IsPlaying[21] = false;
		}

		// ��ȭ�� Star �� Ű �ִϸ��̼� ����
		if (_starkeyClicked)
		{
			m_pPhoneStarKey->PlayAndResetAnimation(dTime, 2.5f);
		}

		// ���ڰ� 3���� �ʰ��ؼ� �ԷµǾ��� ��
		if (m_InputNumberStr.size() > 3)
			m_InputNumberStr = L"";
	}

	// ��ȭ�� ��ư ������ �� ��ȭ�� �˾��� ���.
	if (m_NowState == eState::NONE && m_pPhoneBtnOn->GetColliderBox()->IsClicked)
	{
		m_NowState = eState::POPUP_PHONE;
	}

	// ��ȭ�� �˾��� ���ְ�, ��ȭ�� �˾� �̿��� �κ��� ������ �˾��� ������. = m_NowState = eState::None;
	if (m_NowState == eState::POPUP_PHONE
		&& m_pPhoneScreen->GetColliderBox()->CheckOutSideCollided()
		&& m_pPhoneScreen->GetColliderBox()->CheckOutSideClicked()
		&& m_pOfficeTextBox->GetState() == false)
	{
		m_NowState = eState::NONE;
		m_InputNumberStr = L"";
	}

	m_MonitorImage->Update(dTime);

	// ����� â Ȱ��ȭ(�̽��Ϳ���)
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
	// ��� ������Ʈ �׸���
	m_pObjectManager->DrawAll();

	if (m_NowState == eState::POPUP_MICROSCOPE)
	{
		m_pPopupWindowBackgroundImg->Draw();
		m_pMicroscope_PopupBackground->Draw();						// ���̰� ���׸���

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

		m_pMicroscope_lens->Draw();									// ���� ���� ��� �׸���.
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

		// ��ȭ�� ��ȣ ������� ����
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

	JJEngine::GetInstance()->DrawText(0, 40, L"Main_Office ��");

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
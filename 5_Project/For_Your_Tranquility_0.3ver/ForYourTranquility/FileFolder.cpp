#include "pch.h"
#include "FileFolder.h"
#include "ColliderBox.h"
#include "ObjectManager.h"
#include "Button.h"
#include "TextBox.h"

FileFolder* FileFolder::m_Instance = nullptr;
eEnding FileFolder::EndingState = eEnding::None;
eFirstChoiceState FileFolder::m_FirstChoiceState = eFirstChoiceState::None;
eSecondChoiceState FileFolder::m_SecondChoiceState = eSecondChoiceState::None;
eThirdChoiceState FileFolder::m_ThirdChoiceState = eThirdChoiceState::None;

FileFolder::FileFolder(UISortLayer layer)
	:Object(layer), m_NowState(false),
	HeartState(eHeartState::None), LiverState(eLiverState::None), LungState(eLungState::None), StomachState(eStomachState::None),
	IsCheckHead(false), IsCheckArm(false), IsCheckHand(false), IsCheckLeg(false), m_pObjectManager(nullptr),
	IsCheckSchaleHeart(false), IsCheckSchaleLiver(false), IsCheckSchaleLung(false), IsCheckSchaleStomach(false)
	, m_IsPolaroidPopupOn(false), m_CheckPolaroidCount(0), m_PolaroidImageIndex(0), m_NotCloseFileFolder(false)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_IsChoiceOpen[i][j] = false;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		m_IsDrawPolaroid[i] = false;
	}
}

FileFolder::~FileFolder()
{

}

FileFolder* FileFolder::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new FileFolder(UISortLayer::TOPUI);
	}
	return m_Instance;
}

void FileFolder::DeleteInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

void FileFolder::Initialize()
{
	m_Transform = new JTransform();

	for (int i = 0; i < 3; i++)
	{
		m_ShowButtonList[i] = false;
	}

	// ������ �������� ����
	for (int i = 0; i < 4; i++)
	{
		m_IsChoiceOpen[2][i] = true;
	}
	
	// Trnasform �ʱ�ȭ
	m_Transform->Pos = JVector(0, 0);
	// ������Ʈ �̸� �ʱ�ȭ
	m_ObjectName = L"FileFolder";

	m_ColliderBox = new ColliderBox(m_Transform->Pos, m_ObjectName);

	m_pObjectManager = new ObjectManager;

	// ���ҽ� �̹��� �ε� ���� ����;
	AddSprite(L"file_clip", 1);
	AddSprite(L"file_clipper", 1);
	AddSprite(L"file_papers", 1);
	AddSprite(L"file_poket", 1);
	AddSprite(L"file_polaroid", 1);
	AddSprite(L"frog_cell_heart2_polaroid1", 1);
	AddSprite(L"frog_cell_liver_polaroid1", 1);
	AddSprite(L"frog_cell_lung_polaroid1", 1);
	AddSprite(L"frog_cell_stomach_polaroid2", 1);
	AddSprite(L"polaroid_arm_big", 1);
	AddSprite(L"polaroid_hand_big", 1);
	AddSprite(L"polaroid_head_big", 1);
	AddSprite(L"polaroid_leg_big", 1);
	AddSprite(L"polaroid_liver_big", 1);
	AddSprite(L"polaroid_lung_big", 1);
	AddSprite(L"polaroid_stomach_big", 1);
	AddSprite(L"polaroid_heart_big", 1);
	AddSprite(L"frog_cell_heart2_small", 1);
	AddSprite(L"frog_cell_liver_small", 1);
	AddSprite(L"frog_cell_lung_small", 1);
	AddSprite(L"frog_cell_stomach_small2", 1);
	AddSprite(L"polaroid_arm_small", 1);
	AddSprite(L"polaroid_hand_small", 1);
	AddSprite(L"polaroid_head_small", 1);
	AddSprite(L"polaroid_heart_small", 1);
	AddSprite(L"polaroid_leg_small", 1);
	AddSprite(L"polaroid_liver_small", 1);
	AddSprite(L"polaroid_lung_small", 1);
	AddSprite(L"polaroid_stomach_small", 1);

	// �ؽ�Ʈ ��ư ����
	m_SelectTextButton[0][0] = m_pObjectManager->OnlyCreateObject_Button(JVector(1354, 569), L"File_Selection1_normal1", 2, UISortLayer::BUTTON, eFirstChoiceState::None);
	// Ŭ���Ǹ� ������ ���̵�		
	m_SelectTextButton[0][1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1354, m_Transform->Pos.y + 185), L"File_Selection1_heart", 2, UISortLayer::BUTTON, eFirstChoiceState::HeartDisease);
	m_SelectTextButton[0][2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1354, m_Transform->Pos.y + 240), L"File_Selection1_liver", 2, UISortLayer::BUTTON, eFirstChoiceState::Cirrhosis);
	m_SelectTextButton[0][3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1354, m_Transform->Pos.y + 295), L"File_Selection1_Alcohol", 2, UISortLayer::BUTTON, eFirstChoiceState::A_Large_Intake_Of_Alcohol);

	m_SelectTextButton[1][0] = m_pObjectManager->OnlyCreateObject_Button(JVector(1081, 642), L"File_Selection2_normal1", 2, UISortLayer::BUTTON, eSecondChoiceState::None);
	// Ŭ���Ǹ� ������ ���̵�		
	m_SelectTextButton[1][1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1081, m_Transform->Pos.y + 455), L"File_Selection2_heart", 2, UISortLayer::BUTTON, eSecondChoiceState::AcuteHeartAttack);
	m_SelectTextButton[1][2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1081, m_Transform->Pos.y + 510), L"File_Selection2_brain", 2, UISortLayer::BUTTON, eSecondChoiceState::Abnormal_State_Of_Consciousness);
	m_SelectTextButton[1][3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1081, m_Transform->Pos.y + 565), L"File_Selection2_liver", 2, UISortLayer::BUTTON, eSecondChoiceState::AlcoholShock);

	m_SelectTextButton[2][0] = m_pObjectManager->OnlyCreateObject_Button(JVector(1126, 779), L"File_Selection3_normal1", 2, UISortLayer::BUTTON, eThirdChoiceState::None);
	// Ŭ���Ǹ� ������ ���̵�		
	m_SelectTextButton[2][1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1126, 779 + 32 * 1), L"File_Selection3_suiside", 2, UISortLayer::BUTTON, eThirdChoiceState::Suicide);
	m_SelectTextButton[2][2] = m_pObjectManager->OnlyCreateObject_Button(JVector(1126, 779 + 32 * 2), L"File_Selection3_accidental", 2, UISortLayer::BUTTON, eThirdChoiceState::Murder);
	m_SelectTextButton[2][3] = m_pObjectManager->OnlyCreateObject_Button(JVector(1126, 779 + 32 * 3), L"File_Selection3_disease", 2, UISortLayer::BUTTON, eThirdChoiceState::Death_From_Disease);

	// ������̵� â ���� ��ư ����
	m_PolaroidPopupOnButton = m_pObjectManager->OnlyCreateObject_Button(JVector(m_Transform->Pos.x + 330, m_Transform->Pos.y + 90), L"PolaroidButton", JVector(500, 500), UISortLayer::BUTTON, eThirdChoiceState::None);

	// ������̵� �˾����� �¿� ��ư ����
	m_PolaroidPrevNextButton[0] = m_pObjectManager->OnlyCreateObject_Button(JVector(600, 550), L"polaroid_button_left", 2, UISortLayer::BUTTON);
	m_PolaroidPrevNextButton[1] = m_pObjectManager->OnlyCreateObject_Button(JVector(1300, 550), L"polaroid_button_right", 2, UISortLayer::BUTTON);

	// ������̵� �˾��� �ݱ� ���� ��ư
	m_PolaroidPopupOffButton = m_pObjectManager->OnlyCreateObject_Button(JVector(550, 300), L"Popup Close Button", JVector(900, 550), UISortLayer::BUTTON, eNowSceneState::NONE);

	// �ΰ˿Ϸ� ��ư
	m_CompleteButton = m_pObjectManager->OnlyCreateObject_Button(JVector(1380, 890), L"File_completebutton", 2, UISortLayer::BUTTON, eNowSceneState::GO_TO_NEXT_SCENE);

	m_pTextBox = m_pObjectManager->OnlyCreateObject_TextBox(JVector(0, 0), L"FileIron", UISortLayer::TOPUI);

	AddSprite(L"file", 1);
	
	// �ݶ��̴� ������ ����
	m_ColliderBox->SetTransform.Pos = { 200, 200 };
	m_ColliderBox->SetSize(JVector(1260, 950));
}

void FileFolder::Release()
{
	Object::Release();

	if (m_pObjectManager != nullptr)
	{
		m_pObjectManager->Release();
		delete m_pObjectManager;
		m_pObjectManager = nullptr;
	}

	DeleteInstance();
}

void FileFolder::Update(float dTime, Scene* scene)
{
	/// ��ȭ���ڰ� ���� ���� ��츸 ������Ʈ ���ش�.
	m_pTextBox->Update(dTime);

	if (m_pTextBox->GetState())
		return;

	CheckState();
	CheckChoiceButtonOpenState();

	// ���� ���� ���� ���°� Off �̸� ������Ʈ ���� ����
	if (!GetNowState())
		return;

	m_ColliderBox->Update(dTime, m_Transform);

	m_PolaroidPopupOnButton->Update(dTime);
	m_PolaroidPopupOffButton->Update(dTime);

	m_CompleteButton->Update(dTime);

	/// �� �������� �ƴ��� üũ
	if (m_CompleteButton->GetColliderBox()->IsClicked)
	{
		// 1��° ��������
		if (m_FirstChoiceState == eFirstChoiceState::HeartDisease
			&& m_SecondChoiceState == eSecondChoiceState::AcuteHeartAttack
			&& m_ThirdChoiceState == eThirdChoiceState::Death_From_Disease)
		{
			EndingState = eEnding::HeartAttackEnding;
			scene->SetNowSceneState(eNowSceneState::GO_TO_NEXT_SCENE);
			scene->SetIsGameEnd(true);
		}
		// 2��° ��������
		else if (m_FirstChoiceState == eFirstChoiceState::A_Large_Intake_Of_Alcohol
			&& m_SecondChoiceState == eSecondChoiceState::Abnormal_State_Of_Consciousness
			&& m_ThirdChoiceState == eThirdChoiceState::Suicide)
		{
			EndingState = eEnding::AlcoholEnding;
			scene->SetNowSceneState(eNowSceneState::GO_TO_NEXT_SCENE);
			scene->SetIsGameEnd(true);
		}
		// 3��° ��������
		else if (m_FirstChoiceState == eFirstChoiceState::Cirrhosis
			&& m_SecondChoiceState == eSecondChoiceState::AlcoholShock
			&& m_ThirdChoiceState == eThirdChoiceState::Death_From_Disease)
		{
			EndingState = eEnding::CirrhosisEnding;
			scene->SetNowSceneState(eNowSceneState::GO_TO_NEXT_SCENE);
			scene->SetIsGameEnd(true);
		}
		else
		{
			m_pTextBox->SetStartEndIndex(0, 0);
		}
	}
	
	// ������̵� ��ư�� ������ �˾��� ����.
	if (m_PolaroidPopupOnButton->GetColliderBox()->IsClicked)
	{
		if (IsCheckHead)
			m_CheckPolaroidCount++;
		if (IsCheckArm)
			m_CheckPolaroidCount++;
		if (IsCheckHand)
			m_CheckPolaroidCount++;
		if (IsCheckLeg)
			m_CheckPolaroidCount++;

		for (int i = 0; i < Polaroid_End_Count; i++)
		{
			if (m_IsDrawPolaroid[i] == true)
				m_CheckPolaroidCount++;
		}

		if (m_CheckPolaroidCount > 0)
		{
			m_IsPolaroidPopupOn = true;
			m_NotCloseFileFolder = true;
		}

		m_CheckPolaroidCount = 0;
	}

	// �˾��� �ݴ´�.
	if (m_PolaroidPopupOffButton->GetColliderBox()->IsOutSideClicked && m_IsPolaroidPopupOn
		&& !m_PolaroidPopupOnButton->GetColliderBox()->IsClicked)
	{
		m_IsPolaroidPopupOn = false;
		return;
	}

	// ����ö�� �ݴ´�.
	if (m_ColliderBox->IsOutSideClicked && !m_NotCloseFileFolder)
	{
		Off();
	}

	if (m_IsPolaroidPopupOn == false)
		m_NotCloseFileFolder = false;

	// �¿� ��ư
	if (m_IsPolaroidPopupOn)
	{
		m_PolaroidPrevNextButton[0]->Update(dTime);
		m_PolaroidPrevNextButton[1]->Update(dTime);
	}

	m_PolaroidImageVec.clear();

	if (IsCheckHead)
		m_PolaroidImageVec.push_back(m_SpriteVec[Polaroid_head_big]->Bitmap);
	if (IsCheckArm)
		m_PolaroidImageVec.push_back(m_SpriteVec[Polaroid_arm_big]->Bitmap);
	if (IsCheckHand)
		m_PolaroidImageVec.push_back(m_SpriteVec[Polaroid_hand_big]->Bitmap);
	if (IsCheckLeg)
		m_PolaroidImageVec.push_back(m_SpriteVec[Polaroid_leg_big]->Bitmap);

	for (int i = 0; i < Polaroid_End_Count; i++)
	{
		if (m_IsDrawPolaroid[i] == true)
		{
			if (i < 4)
				m_PolaroidImageVec.push_back(m_SpriteVec[i + 5]->Bitmap);
			else
				m_PolaroidImageVec.push_back(m_SpriteVec[i + 9]->Bitmap);
		}
	}

	if (m_PolaroidPrevNextButton[0]->GetColliderBox()->IsClicked)
	{
		m_PolaroidImageIndex--;

		if (m_PolaroidImageIndex < 0)
			m_PolaroidImageIndex = m_PolaroidImageVec.size() - 1;
	}

	if (m_PolaroidPrevNextButton[1]->GetColliderBox()->IsClicked)
	{
		m_PolaroidImageIndex++;

		if (m_PolaroidImageIndex >= m_PolaroidImageVec.size())
			m_PolaroidImageIndex = 0;
	}

	if (m_IsPolaroidPopupOn)
		return;

	// ���̽� ��ư�� ������Ʈ ���ش�;
	for (int i = 0; i < 3; i++)
	{
		m_SelectTextButton[i][0]->Update(dTime);

		if (m_SelectTextButton[i][0]->GetColliderBox()->IsClicked)
		{
			if (m_ShowButtonList[i] == false && m_ChoiceButtonVec[i].size() > 0)
			{
				m_ShowButtonList[i] = true;									// ��ư����Ʈ�� ����
			}
			/// �� ������ �̷��.... 
			//else
				//m_ShowButtonList[i] = false;
		}

		for (int j = 1; j < 4; j++)
		{
			if (m_ShowButtonList[i] == true)
				m_SelectTextButton[i][j]->Update(dTime);

			if (m_SelectTextButton[i][j]->GetColliderBox()->IsClicked)
			{
				m_ShowButtonList[i] = false;							// ���̽���ư�� ������ ��ư�� Ŭ���Ѵٸ� ������.

				// ��ư�� ���¸� ����
				CheckChoiceState(i, m_SelectTextButton[i][j]);
			}
		}
	}

	CheckFrame();
}

void FileFolder::CheckFrame()
{
	if (m_CompleteButton->GetColliderBox()->IsCollided)
		m_CompleteButton->ChangeFrame(1);
	else
		m_CompleteButton->ChangeFrame(0);

	for (int i = 0; i < 3; i++)
	{
		// ���̽� ��ư�� �׸���.
		if (m_SelectTextButton[i][0]->GetColliderBox()->IsCollided)
		{
			m_SelectTextButton[i][0]->ChangeFrame(1);
		}
		else
		{
			m_SelectTextButton[i][0]->ChangeFrame(0);
		}

		if (m_ShowButtonList[i] == true)
		{
			for (int j = 0; j < m_ChoiceButtonVec[i].size(); j++)
			{
				// ���ǿ� ���� ������ư�� �׷��ش�.

				if (m_ChoiceButtonVec[i][j]->GetColliderBox()->IsCollided)
					m_ChoiceButtonVec[i][j]->ChangeFrame(1);
				else
					m_ChoiceButtonVec[i][j]->ChangeFrame(0);
			}
		}
	}

	if (m_PolaroidPrevNextButton[0]->GetColliderBox()->IsCollided)
		m_PolaroidPrevNextButton[0]->ChangeFrame(1);
	else
		m_PolaroidPrevNextButton[0]->ChangeFrame(0);

	if (m_PolaroidPrevNextButton[1]->GetColliderBox()->IsCollided)
		m_PolaroidPrevNextButton[1]->ChangeFrame(1);
	else
		m_PolaroidPrevNextButton[1]->ChangeFrame(0);
}

void FileFolder::CheckState()
{
	/*
	m_IsChoiceOpen[0][1] = true;
	m_IsChoiceOpen[0][2] = true;

	m_IsChoiceOpen[1][1] = true;
	m_IsChoiceOpen[1][3] = true;
	m_IsChoiceOpen[1][2] = true;
	*/

	switch (HeartState)
	{
	case eHeartState::Cuted:
		m_IsDrawPolaroid[Polaroid_Organ_Heart] = true;
		m_IsChoiceOpen[0][1] = true;
		break;
	case eHeartState::SampleMoved:
		break;
	case eHeartState::UseMicroScope:
		m_IsDrawPolaroid[Polaroid_Frog_cell_Heart2] = true;
		break;
	case eHeartState::Call:
		m_IsChoiceOpen[1][1] = true;
		break;
	}

	switch (LiverState)
	{
	case eLiverState::Cuted:
		m_IsDrawPolaroid[Polaroid_Organ_Liver] = true;
		m_IsChoiceOpen[0][2] = true;
		break;
	case eLiverState::SampleMoved:
		break;
	case eLiverState::UseMicroScope:
		m_IsDrawPolaroid[Polaroid_Frog_cell_Liver] = true;
		break;
	case eLiverState::Call:
		m_IsChoiceOpen[0][3] = true;	// �ٷ��� ���ڿ� ����  = true;
		m_IsChoiceOpen[1][3] = true;	// ���ڿ� ��ũ
		m_IsChoiceOpen[1][2] = true;	// �� �������� �ǽ� ����
		break;
	}

	switch (LungState)
	{
	case eLungState::Cuted:
		m_IsDrawPolaroid[Polaroid_Organ_Lung] = true;
		break;
	case eLungState::SampleMoved:
		break;
	case eLungState::UseMicroScope:
		m_IsDrawPolaroid[Polaroid_Frog_cell_Lung] = true;
		break;
	case eLungState::Call:
		break;
	}

	switch (StomachState)
	{
	case eStomachState::Cuted:
		m_IsDrawPolaroid[Polaroid_Organ_Stomach] = true;
		break;
	case eStomachState::SampleMoved:
		break;
	case eStomachState::UseMicroScope:
		m_IsDrawPolaroid[Polaroid_Frog_cell_Stomach] = true;
		break;
	case eStomachState::Call:
		break;
	}
}

void FileFolder::CheckChoiceButtonOpenState()
{
	int offsetX = 0;
	int offsetY = 0;

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			offsetX = 1354;
			offsetY = 569;
			break;
		case 1:
			offsetX = 1081;
			offsetY = 642;
			break;
		case 2:
			offsetX = 1126;
			offsetY = 779;
		}

		for (int j = 1; j < 4; j++)
		{
			if (m_IsChoiceOpen[i][j])
			{
				offsetY += 32;
				m_SelectTextButton[i][j]->Transform()->SetPos(offsetX, offsetY);
				m_ChoiceButtonVec[i].push_back(m_SelectTextButton[i][j]);
			}
		}
	}
}

void FileFolder::CheckChoiceState(int i, Button* stateButton)
{
	switch (i)
	{
	case 0:
		m_FirstChoiceState = stateButton->GetFirstChoiceState();
		break;
	case 1:
		m_SecondChoiceState = stateButton->GetSecondChoiceState();
		break;
	case 2:
		m_ThirdChoiceState = stateButton->GetThirdChoiceState();
		break;
	}
}

void FileFolder::DrawPolaroid()
{
	// ���¿����� ������̵带 �׸���.
	if (IsCheckHead || IsCheckArm || IsCheckHand || IsCheckLeg)
	{
		if (IsCheckHead)
			JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_head_small], m_Transform->Pos.x + 380, m_Transform->Pos.y + 100);
		if (IsCheckArm)
			JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_arm_small], m_Transform->Pos.x + 390, m_Transform->Pos.y + 100);
		if (IsCheckHand)
			JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_hand_small], m_Transform->Pos.x + 400, m_Transform->Pos.y + 100);
		if (IsCheckLeg)
			JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_leg_small], m_Transform->Pos.x + 410, m_Transform->Pos.y + 100);

	}
	if (m_IsDrawPolaroid[Polaroid_Frog_cell_Liver])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[frog_cell_liver_small], m_Transform->Pos.x + 430, m_Transform->Pos.y + 150);
	if (m_IsDrawPolaroid[Polaroid_Frog_cell_Heart2])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[frog_cell_heart2_small], m_Transform->Pos.x + 440, m_Transform->Pos.y + 150);
	if (m_IsDrawPolaroid[Polaroid_Frog_cell_Lung])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[frog_cell_lung_small], m_Transform->Pos.x + 450, m_Transform->Pos.y + 150);
	if (m_IsDrawPolaroid[Polaroid_Frog_cell_Stomach])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[frog_cell_stomach_small], m_Transform->Pos.x + 460, m_Transform->Pos.y + 150);
	
	if (m_IsDrawPolaroid[Polaroid_Organ_Lung])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_lung_small], m_Transform->Pos.x + 480, m_Transform->Pos.y + 200);
	if (m_IsDrawPolaroid[Polaroid_Organ_Liver])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_liver_small], m_Transform->Pos.x + 490, m_Transform->Pos.y + 200);
	if (m_IsDrawPolaroid[Polaroid_Organ_Stomach])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_stomach_small], m_Transform->Pos.x + 500, m_Transform->Pos.y + 200);
	if (m_IsDrawPolaroid[Polaroid_Organ_Heart])
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[polaroid_heart_small], m_Transform->Pos.x + 510, m_Transform->Pos.y + 200);
}

void FileFolder::Draw(float opacity/*= 1.0f*/)
{
	// ���� ���� ���� ���°� Off �̸� �׸��� ����
	if (!GetNowState())
		return;
	
	// 1. ���� �� �׸��� �׸���.
	JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File], m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	// 2. ������ �׸���. (���� �Ʒ�)
	//JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_poket], m_Transform->Pos.x + 15, m_Transform->Pos.y + 632, opacity);

	// 3. ���̸� �׸���. (������ ������)
	//JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_papers], m_Transform->Pos.x + m_Transform->Size.x / 2 + 50, m_Transform->Pos.y + 100, opacity);

	// 4. ������̵带 �׸���. (���� ��)
	//JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_polaroid], m_Transform->Pos.x + 130, m_Transform->Pos.y + 50, opacity);

	// ...
	DrawPolaroid();

	// 5. ���� Ŭ���� �׸���. (������̵� ��)
	JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_clip], m_Transform->Pos.x + 528, m_Transform->Pos.y + 37, opacity);

	// 6. ���� Ŭ���۸� �׸���. (���� ��)
	JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_clipper], m_Transform->Pos.x + m_Transform->Size.x / 2 + 200, m_Transform->Pos.y + 90, opacity);

	// 7. ������ ��ư ���
	for (int i = 0; i < 3; i++)
	{
		// ���̽� ��ư�� �׸���.
		m_SelectTextButton[i][0]->Draw();

		if (m_ShowButtonList[i] == true)
		{
			for (int j = 0; j < m_ChoiceButtonVec[i].size(); j++)
			{
				// ���ǿ� ���� ������ư�� �׷��ش�.
				m_ChoiceButtonVec[i][j]->Draw();
			}
		}
	}

	switch (m_FirstChoiceState)
	{
	case eFirstChoiceState::None:
		break;
	case eFirstChoiceState::HeartDisease:
		m_SelectTextButton[0][1]->Transform()->SetPos(1354, 569);
		m_SelectTextButton[0][1]->Draw();
		break;
	case eFirstChoiceState::Cirrhosis:
		m_SelectTextButton[0][2]->Transform()->SetPos(1354, 569);
		m_SelectTextButton[0][2]->Draw();
		break;
	case eFirstChoiceState::A_Large_Intake_Of_Alcohol:
		m_SelectTextButton[0][3]->Transform()->SetPos(1354, 569);
		m_SelectTextButton[0][3]->Draw();
		break;
	default:
		break;
	}

	switch (m_SecondChoiceState)
	{
	case eSecondChoiceState::None:
		break;
	case eSecondChoiceState::AcuteHeartAttack:
		m_SelectTextButton[1][1]->Transform()->SetPos(1081, 642);
		m_SelectTextButton[1][1]->ChangeFrame(0);
		m_SelectTextButton[1][1]->Draw();
		break;
	case eSecondChoiceState::Abnormal_State_Of_Consciousness:
		m_SelectTextButton[1][2]->Transform()->SetPos(1081, 642);
		m_SelectTextButton[1][2]->ChangeFrame(0);
		m_SelectTextButton[1][2]->Draw();
		break;
	case eSecondChoiceState::AlcoholShock:
		m_SelectTextButton[1][3]->Transform()->SetPos(1081, 642);
		m_SelectTextButton[1][3]->ChangeFrame(0);
		m_SelectTextButton[1][3]->Draw();
		break;
	default:
		break;
	}

	switch (m_ThirdChoiceState)
	{
	case eThirdChoiceState::None:
		break;
	case eThirdChoiceState::Suicide:
		m_SelectTextButton[2][1]->Transform()->SetPos(1126, 779);
		m_SelectTextButton[2][1]->ChangeFrame(0);
		m_SelectTextButton[2][1]->Draw();
		break;
	case eThirdChoiceState::Murder:
		m_SelectTextButton[2][2]->Transform()->SetPos(1126, 779);
		m_SelectTextButton[2][2]->ChangeFrame(0);
		m_SelectTextButton[2][2]->Draw();
		break;
	case eThirdChoiceState::Death_From_Disease:
		m_SelectTextButton[2][3]->Transform()->SetPos(1126, 779);
		m_SelectTextButton[2][3]->ChangeFrame(0);
		m_SelectTextButton[2][3]->Draw();
		break;
	default:
		break;
	}

	// �ΰ˿Ϸ� ��ư
	m_CompleteButton->Draw();

	m_PolaroidPopupOnButton->Draw();
	DrawPolaroidPopup();

	m_pTextBox->Draw();

	

	// ���� �ʱ�ȭ
	for (int i = 0; i < 3; i++)
	{
		m_ChoiceButtonVec[i].clear();
	}

	//ShowDebug();
}

void FileFolder::DrawPolaroidPopup()
{
	if (!m_IsPolaroidPopupOn)
		return;

	if (IsCheckHead)
		m_CheckPolaroidCount++;
	if (IsCheckArm)
		m_CheckPolaroidCount++;
	if (IsCheckHand)
		m_CheckPolaroidCount++;
	if (IsCheckLeg)
		m_CheckPolaroidCount++;

	for (int i = 0; i < Polaroid_End_Count; i++)
	{
		if (m_IsDrawPolaroid[i] == true)
			m_CheckPolaroidCount++;
	}

	if (m_CheckPolaroidCount <= 0)
	{
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[File_polaroid], m_Transform->Pos.x + m_Transform->Size.x / 2 - 200, m_Transform->Pos.y + m_Transform->Size.y / 2 - 200);
	}
	else
	{
		if (m_PolaroidImageVec.size() > 0)
			JJEngine::GetInstance()->DrawSprite(m_PolaroidImageVec[m_PolaroidImageIndex], m_Transform->Pos.x + m_Transform->Size.x / 2 - 200, m_Transform->Pos.y + m_Transform->Size.y / 2 - 200);

		m_PolaroidPrevNextButton[0]->Draw();
		m_PolaroidPrevNextButton[1]->Draw();
	}

	m_PolaroidPopupOffButton->Draw();

	m_PolaroidImageVec.clear();
	m_CheckPolaroidCount = 0;
}

void FileFolder::ShowDebug()
{
	Object::ShowDebug();

	JJEngine::GetInstance()->DrawText(0, 490, L"ChoiceVec[0] : %d", m_ChoiceButtonVec[0].size());
	JJEngine::GetInstance()->DrawText(0, 520, L"ChoiceVec[1] : %d", m_ChoiceButtonVec[1].size());

	JJEngine::GetInstance()->DrawText(0, 400, L"FirstChoiceState : %d", m_FirstChoiceState);
	JJEngine::GetInstance()->DrawText(0, 430, L"SecondChoiceState : %d", m_SecondChoiceState);
	JJEngine::GetInstance()->DrawText(0, 460, L"ThirdChoiceState : %d", m_ThirdChoiceState);
}

void FileFolder::On()
{
	m_NowState = true;
}

void FileFolder::Off()
{
	m_NowState = false;

	// �˾��� �̹��� ���ʹ� ����ش�.
	m_PolaroidImageVec.clear();
}

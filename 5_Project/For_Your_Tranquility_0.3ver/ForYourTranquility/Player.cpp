#include "pch.h"

#include "Player.h"
#include "MainAutopsyRoomScene.h"
#include "MainDissectingRoomScene.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Button.h"
#include "ColliderBox.h"

Player::Player()
	:m_ToolType(ToolType::NONE), m_HadTool(false), m_UseTool(false), m_pMainDissectingRoomScene(nullptr)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	m_pObjectManager = new ObjectManager;

	// ToolType 0 : 부검실 돋보기
	m_Tools[static_cast<int>(ToolType::AUTOPSY_MAGNIFYING_GLASS)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"MagnifyingGlass", UISortLayer::PLAYER);

	// ToolType 1 : 부검실 메스
	m_Tools[static_cast<int>(ToolType::AUTOPSY_SCALPEL)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"Scalpel_anim", UISortLayer::PLAYER);

	// ToolType 2 : 부검실 가위
	m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"Scissors_anim", UISortLayer::PLAYER);

	// ToolType 3 : 해부실 메스
	m_Tools[static_cast<int>(ToolType::DISSECT_SCALPEL)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"Dissecting_Scalpel2", UISortLayer::PLAYER);

	// ToolType 4 : 해부실 가위
	m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"DissectingRoom_Scissors_Anim", UISortLayer::PLAYER);

	// ToolType 5 : 해부실 집게
	m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"DissectingRoom_Forceps_default", UISortLayer::PLAYER);

	// ToolType 6 : 해부실 조직 집게
	m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)] = m_pObjectManager->OnlyCreateObject_Animation(JVector(0, 0), L"DissectingRoom_Forceps_five", UISortLayer::PLAYER);

	m_pMainDissectingRoomScene = new MainDissectingRoomScene;
}

void Player::Update(float dTime)
{
	if (MainDissectingRoomScene::DetailOpenHeartFatCollided)
	{
		m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->ChangeMotionFrame(3);
	}
	else
	{
		m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->ChangeMotionFrame(1);
	}

	if (MainAutopsyRoomScene::CutOrganGuideCollided == true)
	{
		m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)]->ChangeMotionFrame(3);
	}
	else
	{
		m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)]->ChangeMotionFrame(1);
	}

	if (MainDissectingRoomScene::CutFrogStomach02GuideCollided == true)
	{
		m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(3);
	}
	else
	{
		m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(1);
	}

	if (InputManager::GetInstance()->CheckLeftButtonHold())
	{
		m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->ChangeMotionFrame(0);

		if (MainAutopsyRoomScene::CutOrganGuideCollided == true)
		{
			m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)]->ChangeMotionFrame(2);
		}
		else if (MainAutopsyRoomScene::CutOrganGuideCollided == false)
		{
			m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)]->ChangeMotionFrame(0);
		}

		if (MainDissectingRoomScene::CutFrogStomach02GuideCollided == true)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(2);
		}
		else if (MainDissectingRoomScene::CutFrogStomach02GuideCollided == false)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(0);
		}

		// 장기조직 조직 집었을때
		if (m_pMainDissectingRoomScene->GetNowPickOrganPiece() == PickOrganPiece::HEART)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->ChangeMotionFrame(1);
		}
		else if (m_pMainDissectingRoomScene->GetNowPickOrganPiece() == PickOrganPiece::LIVER)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->ChangeMotionFrame(2);
		}
		else if (m_pMainDissectingRoomScene->GetNowPickOrganPiece() == PickOrganPiece::LUNGS)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->ChangeMotionFrame(3);
		}
		else if (m_pMainDissectingRoomScene->GetNowPickOrganPiece() == PickOrganPiece::STOMACH)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->ChangeMotionFrame(4);
		}
		else
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->ChangeMotionFrame(0);
		}
	}
	else if (InputManager::GetInstance()->CheckLeftButtonUp())
	{
		if (MainDissectingRoomScene::CutFrogStomach02GuideCollided == true)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(3);
		}
		else if (MainDissectingRoomScene::CutFrogStomach02GuideCollided == false)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->ChangeMotionFrame(1);
		}

		if (MainDissectingRoomScene::DetailOpenHeartFatCollided)
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->ChangeMotionFrame(2);
		}
		else
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->ChangeMotionFrame(1);
		}
	}
}

void Player::Draw()
{
	POINT _mousePos = InputManager::GetInstance()->GetMousePos();

	switch (m_ToolType)
	{
		case ToolType::AUTOPSY_MAGNIFYING_GLASS:
		{
			m_Tools[static_cast<int>(ToolType::AUTOPSY_MAGNIFYING_GLASS)]->Draw();
		}
		break;

		case ToolType::AUTOPSY_SCALPEL:
		{
			m_Tools[static_cast<int>(ToolType::AUTOPSY_SCALPEL)]->Draw();
		}
		break;

		case ToolType::AUTOPSY_SCISSORS:
		{
			m_Tools[static_cast<int>(ToolType::AUTOPSY_SCISSORS)]->Draw();
		}
		break;

		case ToolType::DISSECT_SCALPEL:
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCALPEL)]->Draw();
		}
		break;

		case ToolType::DISSECT_SCISSORS:
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_SCISSORS)]->Draw();
		}
		break;

		case ToolType::DISSECT_PINCETTE:
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE)]->Draw();
		}
		break;

		case ToolType::DISSECT_PINCETTE_PIECE:
		{
			m_Tools[static_cast<int>(ToolType::DISSECT_PINCETTE_PIECE)]->Draw();
		}
		break;

		case ToolType::NONE:
		{
			// 아무것도 안뜸!
		}
		break;
	}
}

void Player::Release()
{
	//m_Tools->Release();

	if (m_pObjectManager != nullptr)
	{
		m_pObjectManager->Release();
		delete m_pObjectManager;
		m_pObjectManager = nullptr;
	}

	// 툴 제거
	for (int i = 0; i < static_cast<int>(ToolType::NONE); i++)
	{
		if (m_Tools[i] != nullptr)
		{
			delete m_Tools[i];
			m_Tools[i] = nullptr;
		}
	}
}
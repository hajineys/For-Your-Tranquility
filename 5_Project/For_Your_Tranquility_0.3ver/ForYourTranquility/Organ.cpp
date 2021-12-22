#include "pch.h"
#include "Organ.h"
#include "GameObject.h"
#include "ObjectManager.h"

Organ::Organ(UISortLayer layer)
	:Object(layer), m_NowOrganState(OrganState::NONE), m_pObjectManager(nullptr)
{

}

Organ::~Organ()
{

}

void Organ::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);

	m_pObjectManager = new ObjectManager;

	// OrganState 0 : ��
	m_Organs[static_cast<int>(OrganState::ECT3)] = m_pObjectManager->OnlyCreateObject_Image(JVector(637, 300), L"Autopsy_ect3", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 1 : ��
	m_Organs[static_cast<int>(OrganState::BONE)] = m_pObjectManager->OnlyCreateObject_Image(JVector(637, 300), L"Autopsy_bone", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 2 : ����
	m_Organs[static_cast<int>(OrganState::STOMACH)] = m_pObjectManager->OnlyCreateObject_Image(JVector(637, 300), L"Dissecting_stomach", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 3 : ��� ���
	m_Organs[static_cast<int>(OrganState::ECT4)] = m_pObjectManager->OnlyCreateObject_Image(JVector(637, 300), L"Autopsy_ect4", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 4 : �������� ���
	m_Organs[static_cast<int>(OrganState::ECT2)] = m_pObjectManager->OnlyCreateObject_Image(JVector(637, 300), L"Autopsy_ect2", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 5 : ��
	m_Organs[static_cast<int>(OrganState::LUNGS)] = m_pObjectManager->OnlyCreateObject_Image(JVector(717, 255), L"Dissecting_lung", 5, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 6 : ��
	m_Organs[static_cast<int>(OrganState::LIVER)] = m_pObjectManager->OnlyCreateObject_Image(JVector(670, 377), L"Dissecting_liver", 3, UISortLayer::POPUPWINDOWBUTTON);

	// OrganState 7 : ����
	m_Organs[static_cast<int>(OrganState::HEART)] = m_pObjectManager->OnlyCreateObject_Image(JVector(552, 282), L"Dissecting_Heart", 5, UISortLayer::POPUPWINDOWBUTTON);
}

void Organ::Update(float dTime)
{
	Object::Update(dTime);
}

void Organ::Draw(float opacity/*=1.0f*/)
{
	switch (m_NowOrganState)
	{
		case OrganState::ECT3:
		{
			m_Organs[static_cast<int>(OrganState::ECT3)]->Draw();
		}
		break;

		case OrganState::BONE:
		{
			m_Organs[static_cast<int>(OrganState::BONE)]->Draw();
		}
		break;

		case OrganState::STOMACH:
		{
			m_Organs[static_cast<int>(OrganState::STOMACH)]->Draw();
		}
		break;

		case OrganState::ECT4:
		{
			m_Organs[static_cast<int>(OrganState::ECT4)]->Draw();
		}
		break;

		case OrganState::ECT2:
		{
			m_Organs[static_cast<int>(OrganState::ECT2)]->Draw();
		}
		break;

		case OrganState::LUNGS:
		{
			m_Organs[static_cast<int>(OrganState::LUNGS)]->Draw();
		}
		break;

		case OrganState::LIVER:
		{
			m_Organs[static_cast<int>(OrganState::LIVER)]->Draw();
		}
		break;

		case OrganState::HEART:
		{
			m_Organs[static_cast<int>(OrganState::HEART)]->Draw();
		}
		break;

		case OrganState::NONE:
		{
			// �ƹ��͵� �ȶ�!
		}
		break;
	}
}

void Organ::Release()
{
	Object::Release();

	if (m_pObjectManager != nullptr)
	{
		m_pObjectManager->Release();
		delete m_pObjectManager;
		m_pObjectManager = nullptr;
	}
}
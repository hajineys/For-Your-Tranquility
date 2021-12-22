#include "pch.h"

#include "MainIncidentScene.h"
#include "ObjectManager.h"
#include "Button.h"
#include "ColliderBox.h"

bool MainIncidentScene::IsPlaying[5] = { false, };

MainIncidentScene::MainIncidentScene()
	:m_pPolaroidDeadBtnOn(nullptr),
	m_pPolaroidShelterBtnOn(nullptr),
	m_pPolaroidShoesBtnOn(nullptr),
	m_pPolaroidSojuBtnOn(nullptr),
	m_pMapBtnOn(nullptr),
	m_pPolaroidDeadBtn(nullptr),
	m_pPolaroidShelterBtn(nullptr),
	m_pPolaroidShoesBtn(nullptr),
	m_pPolaroidSojuBtn(nullptr),
	m_pMapBtn(nullptr)
{

}

MainIncidentScene::~MainIncidentScene()
{

}

void MainIncidentScene::Initialize()
{
	Scene::Initialize();
	InputManager::GetInstance()->Reset();

	// 씬 이동 버튼
	//m_ChangeSceneButton[PREV] = m_pObjectManager->CreateObject_Button(JVector(10, 970), L"PrevButton", { 100 , 100 }, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);
	m_pObjectManager->CreateObject_Button(JVector(10, 1000), L"icon_backtoOffice", 1, UISortLayer::BUTTON, eNowSceneState::GO_TO_PREV_SCENE);

	// 배경 이미지
	m_pObjectManager->CreateObject_Image(JVector(0, 0), L"Board2_background", 1, UISortLayer::BACKGROUND);

	// Dead 폴라로이드 하이라이팅
	m_pPolaroidDeadBtnOn = m_pObjectManager->CreateObject_Button(JVector(380, 683), L"polaroid_deadbody_mini", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPolaroidDeadBtnOn->AddSprite(L"polaroid_deadbody_mini_light", 1);
	m_pPolaroidDeadBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// Shelter 폴라 하이라이팅
	m_pPolaroidShelterBtnOn = m_pObjectManager->CreateObject_Button(JVector(291, 158), L"polaroid_shelter_mini", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPolaroidShelterBtnOn->AddSprite(L"polaroid_shelter_mini_light", 1);
	m_pPolaroidShelterBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// Shoes 폴라 하이라이팅
	m_pPolaroidShoesBtnOn = m_pObjectManager->CreateObject_Button(JVector(220, 585), L"polaroid_shoes_mini", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPolaroidShoesBtnOn->AddSprite(L"polaroid_shoes_mini_light", 1);
	m_pPolaroidShoesBtnOn->GetColliderBox()->SetSize(JVector(150, 150));

	// 소주 폴라 하이라이팅
	m_pPolaroidSojuBtnOn = m_pObjectManager->CreateObject_Button(JVector(237, 319), L"polaroid_soju_mini", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pPolaroidSojuBtnOn->AddSprite(L"polaroid_soju_mini_light", 1);
	m_pPolaroidSojuBtnOn->GetColliderBox()->SetSize(JVector(120, 120));

	// 맵 하이라이팅
	m_pMapBtnOn = m_pObjectManager->CreateObject_Button(JVector(387, 130), L"map", 1, UISortLayer::BUTTON, eNowSceneState::NONE);
	m_pMapBtnOn->AddSprite(L"map_light", 1);
	m_pMapBtnOn->GetColliderBox()->SetSize(JVector(540, 540));

	// 보드 핀
	m_pObjectManager->CreateObject_Image(JVector(307, 162), L"board_pin", 1, UISortLayer::POPUPWINDOW);

	// Dead-big 폴라로이드 버튼
	m_pPolaroidDeadBtn = m_pObjectManager->OnlyCreateObject_Button(JVector(1100, 257), L"polaroid_deadbody_big", 1, UISortLayer::POPUPWINDOW);
	// Shelter-big 
	m_pPolaroidShelterBtn = m_pObjectManager->OnlyCreateObject_Button(JVector(1100, 257), L"polaroid_shelter_big", 1, UISortLayer::POPUPWINDOW);
	// Shoes-big
	m_pPolaroidShoesBtn = m_pObjectManager->OnlyCreateObject_Button(JVector(1100, 257), L"polaroid_shoes_big", 1, UISortLayer::POPUPWINDOW);
	// 소주-big
	m_pPolaroidSojuBtn = m_pObjectManager->OnlyCreateObject_Button(JVector(1100, 257), L"polaroid_soju_big", 1, UISortLayer::POPUPWINDOW);
	// 맵-big
	m_pMapBtn = m_pObjectManager->OnlyCreateObject_Button(JVector(1073, 280), L"map_big", 1, UISortLayer::POPUPWINDOW);
}

void MainIncidentScene::Update(float dTime)
{
	m_pObjectManager->UpdateAll(dTime);
	m_pPolaroidDeadBtn->Update(dTime);
	m_pPolaroidShelterBtn->Update(dTime);
	m_pPolaroidShoesBtn->Update(dTime);
	m_pPolaroidSojuBtn->Update(dTime);
	m_pMapBtn->Update(dTime);

	/// 씬의 공통적인 버튼들(eNowSceneState 참고)만 Check 함
	m_pObjectManager->CheckButtonClicked(this);


	// Dead 폴라로이드 하이라이팅 
	if (m_pPolaroidDeadBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[0] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[0] = true;
		}
		m_pPolaroidDeadBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pPolaroidDeadBtnOn->ChangeSprite(0);
		IsPlaying[0] = false;
	}

	// Shelter 폴라로이드 하이라이팅
	if (m_pPolaroidShelterBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[1] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[1] = true;
		}
		m_pPolaroidShelterBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pPolaroidShelterBtnOn->ChangeSprite(0);
		IsPlaying[1] = false;
	}
	// Shoes 폴라로이드 하이라이팅
	if (m_pPolaroidShoesBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[2] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[2] = true;
		}
		m_pPolaroidShoesBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pPolaroidShoesBtnOn->ChangeSprite(0);
		IsPlaying[2] = false;
	}

	// 소주 폴라로이드 하이라이팅
	if (m_pPolaroidSojuBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[3] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[3] = true;
		}
		m_pPolaroidSojuBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pPolaroidSojuBtnOn->ChangeSprite(0);
		IsPlaying[3] = false;
	}

	// 맵 하이라이팅
	if (m_pMapBtnOn->GetColliderBox()->IsCollided)
	{
		if (IsPlaying[4] == false)
		{
			SoundManager::GetInstance()->Play(1, L"Button_Over_Sample_04");
			IsPlaying[4] = true;
		}
		m_pMapBtnOn->ChangeSprite(1);
	}
	else
	{
		m_pMapBtnOn->ChangeSprite(0);
		IsPlaying[4] = false;
	}

	switch (m_NowSceneState)
	{
	case eNowSceneState::NONE:
		break;
	case eNowSceneState::GO_TO_NEXT_SCENE:
		break;
	case eNowSceneState::GO_TO_PREV_SCENE:
		SceneManager::ChangeScene(eSceneStateAll::MAIN_OFFICE);
		break;
	case eNowSceneState::POPUP_SHOW:
		break;
	}
}

void MainIncidentScene::Draw()
{
	// 모든 오브젝트 그리기
	m_pObjectManager->DrawAll();

	// big 사이즈 이미지 팝업
	if (m_pPolaroidDeadBtnOn->GetColliderBox()->IsCollided)
	{
		m_pPolaroidDeadBtn->Draw();
	}
	else if (m_pPolaroidShelterBtnOn->GetColliderBox()->IsCollided)
	{
		m_pPolaroidShelterBtn->Draw();
	}
	else if (m_pPolaroidShoesBtnOn->GetColliderBox()->IsCollided)
	{
		m_pPolaroidShoesBtn->Draw();
	}
	else if (m_pPolaroidSojuBtnOn->GetColliderBox()->IsCollided)
	{
		m_pPolaroidSojuBtn->Draw();
	}
	else if (m_pMapBtnOn->GetColliderBox()->IsCollided)
	{
		m_pMapBtn->Draw();
	}

	//ShowDebug();
}

void MainIncidentScene::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 40, L"Main_Incident 씬");
}

void MainIncidentScene::Release()
{
	m_pObjectManager->Release();
	Scene::Release();
}

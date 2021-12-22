#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;

/// <summary>
/// 메인게임 씬
/// 
/// 사건 현장 : 시체 정보 및 사건에 대한 정보 확인가능
/// 2021. 02. 19. 손광익
/// </summary>
class	MainIncidentScene : public Scene
{
public:
	MainIncidentScene();
	virtual ~MainIncidentScene();

private:
	// 멤버 변수
	// 죽어있는 폴라로이드 사진 하이라이팅
	Button* m_pPolaroidDeadBtnOn;
	// 쉘터 폴라로이드 사진 하이라이팅
	Button* m_pPolaroidShelterBtnOn;
	// 신발 폴라로이드 사진 하이라이팅
	Button* m_pPolaroidShoesBtnOn;
	// 소주 폴라로이드 사진 하이라이팅
	Button* m_pPolaroidSojuBtnOn;
	// 맵 이미지 하이라이팅
	Button* m_pMapBtnOn;

	// 팝업
	Button* m_pPolaroidDeadBtn;
	Button* m_pPolaroidShelterBtn;
	Button* m_pPolaroidShoesBtn;
	Button* m_pPolaroidSojuBtn;
	Button* m_pMapBtn;
	
public:
	// 사운드
	static bool IsPlaying[5];

public:
	// Scene 을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
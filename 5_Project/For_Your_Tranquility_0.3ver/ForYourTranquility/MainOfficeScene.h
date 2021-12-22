#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;
class TextBox;

/// <summary>
/// 메인게임 씬
/// 
/// 시체의 정보 및 사건에 대한 정보 확인 가능
/// 2021. 02. 08. Hacgeum
/// </summary>
class MainOfficeScene : public Scene
{
public:
	MainOfficeScene();
	virtual ~MainOfficeScene();

	/// MainOfficeScene의 FSM
	/// 클래스 안에 들어가있으므로 MainOfficeScene::eState 로 쓰이게 된다. -> 굳이 enum 클래스 명에 씬이름을 넣을 필요 X
	enum class eState
	{
		POPUP_INCIDENT,		// 사건현장
		POPUP_MICROSCOPE,	// 현미경
		POPUP_PHONE,		// 전화기
		POPUP_FILE,			// 파일
		POPUP_MONITOR,
		POPUP_STATE_COUNT,
		NONE
	};

private:
	Object* m_pBackgroundImg;
	Object* m_pPopupWindowBackgroundImg;

	Button* m_pNextScene;

	// 메인 오피스 씬만의 FSM
	eState m_NowState;

	///\//////////////////////////////////////////////////////////
	/// 조건이 없는 멤버 변수는 삭제(배경처럼 조건과 상관 없이 무조건 Draw되는 것)
	///\//////////////////////////////////////////////////////////

	// 사건현장 버튼
	Button* m_pIncidentBtn;
	// 사건현장 하이라이팅 on
	Button* m_pIncidentBtnOn;

	////////////////////////////////////////////////////////////////////////
	// 현미경 버튼
	Button* m_pMicroscopeBtn;
	// 현미경 하이라이팅 on
	Button* m_pMicroscopeBtnOn;

	// 현미경 팝업시
	Object* m_pMicroscope_PopupBackground;
	Object* m_pMicroscope_lens;							// 좌측 현미경 그림

	// 렌즈안에 나타날 이미지
	Object* m_pMicroscope_lens_schale[5];

	// 샬레에 담긴 샘플
	Button* m_pMicroscope_schale[4];

	// 샘플 상태
	int m_SchaleState;
	////////////////////////////////////////////////////////////////////////

	// 전화기 버튼
	Button* m_pPhoneBtn;
	// 전화기 버튼 하이라이팅 on
	Button* m_pPhoneBtnOn;

	// 모니터 하이라이팅 On
	Object* m_MonitorImage;
	Button* m_pMonitorBtnOn;
	bool m_IsMonitorClicked;

	/// 전화기 숫자버튼
	Button* m_pPhone0Key;
	Button* m_pPhone1Key;
	Button* m_pPhone2Key;
	Button* m_pPhone3Key;
	Button* m_pPhone4Key;
	Button* m_pPhone5Key;
	Button* m_pPhone6Key;
	Button* m_pPhone7Key;
	Button* m_pPhone8Key;
	Button* m_pPhone9Key;
	Button* m_pPhoneHashKey;
	Button* m_pPhoneStarKey;

	// 파일 버튼
	Button* m_pFileBtn;
	// 파일 버튼 하이라이팅 on
	Button* m_pFileBtnOn;

	// 부검실로 이동 버튼
	Button* m_pAutopsyBtn;

	// 사건현장 팝업 Screen
	Object* m_pIncidentScreen;
	// 전화기 팝업 Screen
	Object* m_pPhoneScreen;
	// 파일 팝업 Screen
	Object* m_pFileScreen;
	// 조사 완료 버튼
	Button* m_pInvestigationCompleteBtn;

	// 전화기 다이얼 숫자
	wstring m_InputNumberStr;
	wstring m_Action1;
	wstring m_Action2;
	wstring m_Action3;

	// 대화상자
	TextBox* m_pOfficeTextBox;

public:
	// 사운드
	static bool IsPlaying[22];
	static bool m_OnlyOnce;					// 딱한번만 부검실엔트리로 가기위한 변수

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
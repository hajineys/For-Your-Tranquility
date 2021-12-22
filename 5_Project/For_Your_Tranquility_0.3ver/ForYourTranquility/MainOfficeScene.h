#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;
class TextBox;

/// <summary>
/// ���ΰ��� ��
/// 
/// ��ü�� ���� �� ��ǿ� ���� ���� Ȯ�� ����
/// 2021. 02. 08. Hacgeum
/// </summary>
class MainOfficeScene : public Scene
{
public:
	MainOfficeScene();
	virtual ~MainOfficeScene();

	/// MainOfficeScene�� FSM
	/// Ŭ���� �ȿ� �������Ƿ� MainOfficeScene::eState �� ���̰� �ȴ�. -> ���� enum Ŭ���� �� ���̸��� ���� �ʿ� X
	enum class eState
	{
		POPUP_INCIDENT,		// �������
		POPUP_MICROSCOPE,	// ���̰�
		POPUP_PHONE,		// ��ȭ��
		POPUP_FILE,			// ����
		POPUP_MONITOR,
		POPUP_STATE_COUNT,
		NONE
	};

private:
	Object* m_pBackgroundImg;
	Object* m_pPopupWindowBackgroundImg;

	Button* m_pNextScene;

	// ���� ���ǽ� ������ FSM
	eState m_NowState;

	///\//////////////////////////////////////////////////////////
	/// ������ ���� ��� ������ ����(���ó�� ���ǰ� ��� ���� ������ Draw�Ǵ� ��)
	///\//////////////////////////////////////////////////////////

	// ������� ��ư
	Button* m_pIncidentBtn;
	// ������� ���̶����� on
	Button* m_pIncidentBtnOn;

	////////////////////////////////////////////////////////////////////////
	// ���̰� ��ư
	Button* m_pMicroscopeBtn;
	// ���̰� ���̶����� on
	Button* m_pMicroscopeBtnOn;

	// ���̰� �˾���
	Object* m_pMicroscope_PopupBackground;
	Object* m_pMicroscope_lens;							// ���� ���̰� �׸�

	// ����ȿ� ��Ÿ�� �̹���
	Object* m_pMicroscope_lens_schale[5];

	// ������ ��� ����
	Button* m_pMicroscope_schale[4];

	// ���� ����
	int m_SchaleState;
	////////////////////////////////////////////////////////////////////////

	// ��ȭ�� ��ư
	Button* m_pPhoneBtn;
	// ��ȭ�� ��ư ���̶����� on
	Button* m_pPhoneBtnOn;

	// ����� ���̶����� On
	Object* m_MonitorImage;
	Button* m_pMonitorBtnOn;
	bool m_IsMonitorClicked;

	/// ��ȭ�� ���ڹ�ư
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

	// ���� ��ư
	Button* m_pFileBtn;
	// ���� ��ư ���̶����� on
	Button* m_pFileBtnOn;

	// �ΰ˽Ƿ� �̵� ��ư
	Button* m_pAutopsyBtn;

	// ������� �˾� Screen
	Object* m_pIncidentScreen;
	// ��ȭ�� �˾� Screen
	Object* m_pPhoneScreen;
	// ���� �˾� Screen
	Object* m_pFileScreen;
	// ���� �Ϸ� ��ư
	Button* m_pInvestigationCompleteBtn;

	// ��ȭ�� ���̾� ����
	wstring m_InputNumberStr;
	wstring m_Action1;
	wstring m_Action2;
	wstring m_Action3;

	// ��ȭ����
	TextBox* m_pOfficeTextBox;

public:
	// ����
	static bool IsPlaying[22];
	static bool m_OnlyOnce;					// ���ѹ��� �ΰ˽ǿ�Ʈ���� �������� ����

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
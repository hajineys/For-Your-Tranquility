#pragma once
#include "Scene.h"
#include "Organ.h"

class Button;
class Object;
class Player;
class TextBox;

/// <summary>
/// ���ΰ��� ��
/// 
/// ��ü �ΰ�, �غ��� ���� �˻� ����
/// 2021. 02. 08. Hacgeum
/// </summary>
class MainAutopsyRoomScene : public Scene
{
public:
	MainAutopsyRoomScene();
	virtual ~MainAutopsyRoomScene();

private:
	// ��� ��ư
	Object* m_pBakcgorund;
	Button* m_pTray;
	Button* m_pPrevScene;

	// ����ö ��ư
	Button* m_pFileFolderButton;

	// ���� ��ư
	Button* m_pMagnifyingGlassButton;
	Button* m_pMagnifyingGlassResetButton;
	Button* m_pScalpelButton;
	Button* m_pScalpelResetButton;
	Button* m_pScissorsButton;
	Button* m_ppScissorsResetButton;

	// ������ �ý� ��ư
	Button* m_pFrogBody;
	Object* m_pFrogBodyCutGuide;
	Button* m_pFrogCutBody01;
	Button* m_pFrogCutBodyFin;

	// ������ Ȯ�� ��ư
	Button* m_pFrogHead;
	Object* m_pFrogHeadImage;
	Button* m_pFrogRightArm;
	Object* m_pFrogRightArmImage;
	Button* m_pFrogRightHand;
	Object* m_pFrogRightHandImage;
	Button* m_pFrogRightLeg;
	Object* m_pFrogRightLegImage;
	Button* m_pFrogLeftLeg;
	Object* m_pFrogLeftLegImage;

	// ������ ���
	Button* m_pFrogOrgan[8];

	// ������ ��� �� ����
	Button* m_pFrogHeartCutGuide;
	Button* m_pFrogLiverCutGuide;
	Button* m_pFrogLungsCutGuide;
	Button* m_pFrogStomachCutGuide01;
	Button* m_pFrogStomachCutGuide02;

	map<Button*, bool> m_IsFrogBodyCutPointDownMap;
	Button* m_pFrogBodyCutPoint[12];

	Organ* m_pOrgan;

	Player* m_pPlayer;

	bool m_UseMagnifying_Glass;
	bool m_UseScalpel;
	bool m_UseScissors;

	bool m_ClickFrogHead;
	bool m_ClickFrogRightArm;
	bool m_ClickFrogRightHand;
	bool m_ClickFrogRightLeg;
	bool m_ClickFrogLeftLeg;

	// ������ �ý�
	int m_FrogBodyCutPointCollided;

	bool m_PickFrogHeart;
	bool m_PickFrogLiver;
	bool m_PickFrogLungs;
	bool m_PickFrogStomach;

	bool m_OrganInTray;

	// ��ȭ����
	TextBox* m_MainAutopsyRoomTextBox;


public:
	// ���� ����
	static bool m_CutFrogLiverAndNextScene;
	static bool m_CutFrogLungAndNextScene;
	static bool m_CutFrogStomachAndNextScene;

	// ������ ���
	static bool m_CutFrogHeart;
	static bool m_CutFrogLiver;
	static bool m_CutFrogLungs;
	static bool m_CutFrogStomach01;
	static bool m_CutFrogStomach02;
	static bool m_CutFrogStomachFin;
	
	static bool _OnlyOncePlay;

	static bool CutOrganGuideCollided;
	static bool FrogBodyOpen;
	static OrganState TrayInOrganState;
	static int TrayHadOrgan;				// Ʈ���� �ȿ� ��Ⱑ � ������

public:
	// �ؽ�Ʈ �ڽ� �ѹ� �÷��̿�
	static bool m_InOncePlay[11];

	// ���� 
	static bool IsPlayingAutopsyRoom[11];

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
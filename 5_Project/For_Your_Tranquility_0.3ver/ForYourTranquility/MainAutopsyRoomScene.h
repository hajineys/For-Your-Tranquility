#pragma once
#include "Scene.h"
#include "Organ.h"

class Button;
class Object;
class Player;
class TextBox;

/// <summary>
/// 메인게임 씬
/// 
/// 시체 부검, 해부한 조직 검사 가능
/// 2021. 02. 08. Hacgeum
/// </summary>
class MainAutopsyRoomScene : public Scene
{
public:
	MainAutopsyRoomScene();
	virtual ~MainAutopsyRoomScene();

private:
	// 배경 버튼
	Object* m_pBakcgorund;
	Button* m_pTray;
	Button* m_pPrevScene;

	// 파일철 버튼
	Button* m_pFileFolderButton;

	// 도구 버튼
	Button* m_pMagnifyingGlassButton;
	Button* m_pMagnifyingGlassResetButton;
	Button* m_pScalpelButton;
	Button* m_pScalpelResetButton;
	Button* m_pScissorsButton;
	Button* m_ppScissorsResetButton;

	// 개구리 시신 버튼
	Button* m_pFrogBody;
	Object* m_pFrogBodyCutGuide;
	Button* m_pFrogCutBody01;
	Button* m_pFrogCutBodyFin;

	// 돋보기 확대 버튼
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

	// 개구리 장기
	Button* m_pFrogOrgan[8];

	// 개구리 장기 컷 점선
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

	// 개구리 시신
	int m_FrogBodyCutPointCollided;

	bool m_PickFrogHeart;
	bool m_PickFrogLiver;
	bool m_PickFrogLungs;
	bool m_PickFrogStomach;

	bool m_OrganInTray;

	// 대화상자
	TextBox* m_MainAutopsyRoomTextBox;


public:
	// 버그 방지
	static bool m_CutFrogLiverAndNextScene;
	static bool m_CutFrogLungAndNextScene;
	static bool m_CutFrogStomachAndNextScene;

	// 개구리 장기
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
	static int TrayHadOrgan;				// 트레이 안에 장기가 몇개 들어갔는지

public:
	// 텍스트 박스 한번 플레이용
	static bool m_InOncePlay[11];

	// 사운드 
	static bool IsPlayingAutopsyRoom[11];

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
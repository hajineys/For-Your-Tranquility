#pragma once
#pragma once
#include "Scene.h"

class Button;
class Organ;
class Player;
class TextBox;

enum class PickOrganPiece
{
	HEART,
	LIVER,
	LUNGS,
	STOMACH,
	NONE
};

/// <summary>
/// 메인게임 씬
/// 
/// 시체 부검, 해부한 조직 검사 가능
/// 2021. 02. 08. Hacgeum
/// </summary>
class MainDissectingRoomScene : public Scene
{
public:
	MainDissectingRoomScene();
	virtual ~MainDissectingRoomScene();

private:
	Button* m_pPrevScene;
	Button* m_pFileFolderButton;

	// 장기 버튼
	Button* m_pOrganLeftButton;
	Button* m_pOrganRightButton;

	// 장기 관련 버튼
	Button* m_pFrogHeartCutGuide01;
	Button* m_pFrogHeartCutGuide02;
	Button* m_pFrogLiverCutGuide;
	Button* m_pFrogLungCutGuide;
	Button* m_pFrogStomachCutGuide01;
	Button* m_pFrogStomachCutGuide02;
	Button* m_pFrogStomachCutGuide03;

	map<Button*, bool> m_IsFrogHeartCutPointDownMap;
	Button* m_pFrogHeartCutPoint[15];

	map<Button*, bool> m_IsFrogHeartDetailCutPointDownMap;
	Button* m_pFrogHeartDetailCutPoint[3];

	map<Button*, bool> m_IsFrogLiverCutPointDownMap;
	Button* m_pFrogLiverCutPoint[23];

	map<Button*, bool> m_IsFrogLungsCutPointDownMap;
	Button* m_pFrogLungsCutPoint[15];

	map<Button*, bool> m_IsFrogStomach01CutPointDownMap;
	Button* m_pFrogStomach01CutPoint[14];

	map<Button*, bool> m_IsFrogStomach03CutPointDownMap;
	Button* m_pFrogStomach03CutPoint[9];

	// 장기 조직
	Button* m_pFrogHeartPiece;
	Button* m_pFrogLiverPiece;
	Button* m_pFrogLungsPiece;
	Button* m_pFrogStomachPiece;

	// 심장 이물질
	Button* m_pHeartFatCheck01;
	Button* m_pHeartFatCheck02;

	// 도구 버튼
	Button* m_pPincetteButton;
	Button* m_pPincetteResetButton;
	Button* m_pScissorsButton;
	Button* m_pScissorsResetButton;
	Button* m_pScalpelButton;
	Button* m_pScalpelResetButton;
	Button* m_pPetrischaleButton;

	// 파일
	Button* m_pFileButton;

	Organ* m_pOrgan;

	Player* m_pPlayer;

	// 텍스트 박스
	TextBox* m_pTextBox;

	bool m_UsePincette;
	bool m_UseScissors;
	bool m_UseScalpel;

	// 개구리 시신
	int m_FrogHeartCutPointCollided;
	int m_FrogHeartDetailCutPointCollided;
	int m_FrogLiverCutPointCollided;
	int m_FrogLungsCutPointCollided;
	int m_FrogStomach01CutPointCollided;
	int m_FrogStomach02CutPointCollided;
	int m_FrogStomach03CutPointCollided;

	// 장기 조직
	bool m_PickFrogHeartPiece;
	bool m_PickFrogLiverPiece;
	bool m_PickFrogLungsPiece;
	bool m_PickFrogStomachPiece;

	PickOrganPiece m_NowPickOrganPiece;

public:
	static bool DissectStart;

	static bool FrogHeartOpen;
	static bool FrogHeartDetailOpen;
	static bool FrogLiverOpen;
	static bool FrogLungsOpen;
	static bool FrogStomach01Open;
	static bool FrogStomach02Open;
	static bool FrogStomach03Open;

	static bool DetailOpenHeartFatCollided;

	static bool CutFrogStomach02GuideCollided;

	// 장기 조각 채취완료
	static bool PetrischaleHadHeartPiece;
	static bool PetrischaleHadLiverPiece;
	static bool PetrischaleHadLungsPiece;
	static bool PetrischaleHadStomachPiece;

public:
	static bool IsOncePlay[11];							// 텍스트
	static bool m_IsFirstPlay[13];						// 사운드

public:
	PickOrganPiece GetNowPickOrganPiece() const { return m_NowPickOrganPiece; }

	Button* GetFatCheck02() const { return m_pHeartFatCheck02; }

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
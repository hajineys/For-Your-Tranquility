#pragma once

#include "Object.h"

class ObjectManager;
class TextBox;

enum class eFirstChoiceState
{
	None,
	HeartDisease,				// 심장질환
	Cirrhosis,					// 간경화
	A_Large_Intake_Of_Alcohol,	// 다량의 알코올 섭취
};

enum class eSecondChoiceState
{
	None,
	AcuteHeartAttack,	// 급성 심장마비
	Abnormal_State_Of_Consciousness, // 비정상적인 의식 상태
	AlcoholShock,	// 알코올 쇼크
};

enum class eThirdChoiceState
{
	None,
	Suicide,		// 자살
	Murder,			// 타살
	Death_From_Disease	//병사
};

enum class eHeartState
{
	None,
	Cuted,			// 장기를 갈랐을 때
	SampleMoved,	// 핀셋으로 조직세포를 옮겼을 때
	UseMicroScope,	// 간 표본을 현미경으로 확인했을 때
	Call			// 병리과에 전화연결
};

enum class eLiverState
{
	None,
	Cuted,			// 장기를 갈랐을 때
	SampleMoved,	// 핀셋으로 조직세포를 옮겼을 때
	UseMicroScope,	// 간 표본을 현미경으로 확인했을 때
	Call			// 병리과에 전화연결
};

enum class eLungState
{
	None,
	Cuted,			// 장기를 갈랐을 때
	SampleMoved,	// 핀셋으로 조직세포를 옮겼을 때
	UseMicroScope,	// 간 표본을 현미경으로 확인했을 때
	Call			// 병리과에 전화연결
};

enum class eStomachState
{
	None,
	Cuted,			// 장기를 갈랐을 때
	SampleMoved,	// 핀셋으로 조직세포를 옮겼을 때
	UseMicroScope,	// 간 표본을 현미경으로 확인했을 때
	Call			// 병리과에 전화연결
};

enum class eEnding
{
	None,
	HeartAttackEnding,
	AlcoholEnding,
	CirrhosisEnding
};

/// <summary>
/// 게임을 진행하면서 계속 갱신되고, 게임의 엔딩을 결정하는 파일철 클래스 -> 어느 씬에서든 불러와져야하므로 싱글톤으로 구현함
/// 2021.02.23
/// 정종영
/// </summary>
class FileFolder : public Object
{
private:
	FileFolder(UISortLayer layer);
	~FileFolder();

private:
	static FileFolder* m_Instance;
	bool m_NowState;

	ObjectManager* m_pObjectManager;

	Button* m_SelectTextButton[3][4];
	bool m_ShowButtonList[3]; // 선택버튼 리스트를 열것인지 안열것인지  true 라면 열것이다.

	bool m_IsDrawPolaroid[8];
	Button* m_PolaroidPopupOnButton;

	bool m_IsPolaroidPopupOn;
	int m_CheckPolaroidCount;
	vector<ID2D1Bitmap*> m_PolaroidImageVec;
	int m_PolaroidImageIndex;
	Button* m_PolaroidPrevNextButton[2];
	Button* m_PolaroidPopupOffButton;
	bool m_NotCloseFileFolder;

	// 선택지의 해금
	bool m_IsChoiceOpen[3][4];
	vector<Button*> m_ChoiceButtonVec[3];

	// 부검완료 버튼
	Button* m_CompleteButton;

	// 텍스트 박스
	TextBox* m_pTextBox;

public:
	eHeartState HeartState;
	eLiverState LiverState;
	eLungState LungState;
	eStomachState StomachState;

	bool IsCheckHead;
	bool IsCheckArm;
	bool IsCheckHand;
	bool IsCheckLeg;

	bool IsCheckSchaleHeart;
	bool IsCheckSchaleLiver;
	bool IsCheckSchaleLung;
	bool IsCheckSchaleStomach;

	static eFirstChoiceState m_FirstChoiceState;
	static eSecondChoiceState m_SecondChoiceState;
	static eThirdChoiceState m_ThirdChoiceState;

	// 엔딩 구분용
	static eEnding EndingState;

	static FileFolder* GetInstance();
	static void DeleteInstance();

	bool GetNowState() const { return m_NowState; }
public:
	virtual void Initialize();
	virtual void Release();

	virtual void Update(float dTime, Scene* scene);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();

	void On();
	void Off();

	void CheckFrame();
	void CheckState();
	void CheckChoiceButtonOpenState();
	void CheckChoiceState(int i, Button* stateButton);
	void DrawPolaroid();
	void DrawPolaroidPopup();
};

enum FileFolderResourceList
{
	File_clip,
	File_clipper,
	File_papers,
	File_poket,
	File_polaroid,
	Frog_cell_heart2_polaroid1,
	Frog_cell_liver_polaroid1,
	Frog_cell_lung_polaroid1,
	Frog_cell_stomach_polaroid,
	Polaroid_arm_big,
	Polaroid_hand_big,
	Polaroid_head_big,
	Polaroid_leg_big,
	Polaroid_liver_big,
	Polaroid_lung_big,
	Polaroid_stomach_big,
	Polaroid_heart_big,
	frog_cell_heart2_small,
	frog_cell_liver_small,
	frog_cell_lung_small,
	frog_cell_stomach_small,
	polaroid_arm_small,
	polaroid_hand_small,
	polaroid_head_small,
	polaroid_heart_small,
	polaroid_leg_small,
	polaroid_liver_small,
	polaroid_lung_small,
	polaroid_stomach_small,
	File,
};

enum PolaroidList
{
	Polaroid_Frog_cell_Heart2,
	Polaroid_Frog_cell_Liver,
	Polaroid_Frog_cell_Lung,
	Polaroid_Frog_cell_Stomach,
	Polaroid_Organ_Liver,
	Polaroid_Organ_Lung,
	Polaroid_Organ_Stomach,
	Polaroid_Organ_Heart,
	Polaroid_End_Count,
};
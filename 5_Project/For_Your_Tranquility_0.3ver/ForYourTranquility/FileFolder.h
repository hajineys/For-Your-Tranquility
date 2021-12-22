#pragma once

#include "Object.h"

class ObjectManager;
class TextBox;

enum class eFirstChoiceState
{
	None,
	HeartDisease,				// ������ȯ
	Cirrhosis,					// ����ȭ
	A_Large_Intake_Of_Alcohol,	// �ٷ��� ���ڿ� ����
};

enum class eSecondChoiceState
{
	None,
	AcuteHeartAttack,	// �޼� ���帶��
	Abnormal_State_Of_Consciousness, // ���������� �ǽ� ����
	AlcoholShock,	// ���ڿ� ��ũ
};

enum class eThirdChoiceState
{
	None,
	Suicide,		// �ڻ�
	Murder,			// Ÿ��
	Death_From_Disease	//����
};

enum class eHeartState
{
	None,
	Cuted,			// ��⸦ ������ ��
	SampleMoved,	// �ɼ����� ���������� �Ű��� ��
	UseMicroScope,	// �� ǥ���� ���̰����� Ȯ������ ��
	Call			// �������� ��ȭ����
};

enum class eLiverState
{
	None,
	Cuted,			// ��⸦ ������ ��
	SampleMoved,	// �ɼ����� ���������� �Ű��� ��
	UseMicroScope,	// �� ǥ���� ���̰����� Ȯ������ ��
	Call			// �������� ��ȭ����
};

enum class eLungState
{
	None,
	Cuted,			// ��⸦ ������ ��
	SampleMoved,	// �ɼ����� ���������� �Ű��� ��
	UseMicroScope,	// �� ǥ���� ���̰����� Ȯ������ ��
	Call			// �������� ��ȭ����
};

enum class eStomachState
{
	None,
	Cuted,			// ��⸦ ������ ��
	SampleMoved,	// �ɼ����� ���������� �Ű��� ��
	UseMicroScope,	// �� ǥ���� ���̰����� Ȯ������ ��
	Call			// �������� ��ȭ����
};

enum class eEnding
{
	None,
	HeartAttackEnding,
	AlcoholEnding,
	CirrhosisEnding
};

/// <summary>
/// ������ �����ϸ鼭 ��� ���ŵǰ�, ������ ������ �����ϴ� ����ö Ŭ���� -> ��� �������� �ҷ��������ϹǷ� �̱������� ������
/// 2021.02.23
/// ������
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
	bool m_ShowButtonList[3]; // ���ù�ư ����Ʈ�� �������� �ȿ�������  true ��� �����̴�.

	bool m_IsDrawPolaroid[8];
	Button* m_PolaroidPopupOnButton;

	bool m_IsPolaroidPopupOn;
	int m_CheckPolaroidCount;
	vector<ID2D1Bitmap*> m_PolaroidImageVec;
	int m_PolaroidImageIndex;
	Button* m_PolaroidPrevNextButton[2];
	Button* m_PolaroidPopupOffButton;
	bool m_NotCloseFileFolder;

	// �������� �ر�
	bool m_IsChoiceOpen[3][4];
	vector<Button*> m_ChoiceButtonVec[3];

	// �ΰ˿Ϸ� ��ư
	Button* m_CompleteButton;

	// �ؽ�Ʈ �ڽ�
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

	// ���� ���п�
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
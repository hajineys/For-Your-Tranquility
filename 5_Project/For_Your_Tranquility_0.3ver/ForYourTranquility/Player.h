#pragma once

class GameObject;
class MainDissectingRoomScene;

enum class ToolType
{
	AUTOPSY_MAGNIFYING_GLASS,
	AUTOPSY_SCALPEL,
	AUTOPSY_SCISSORS,
	DISSECT_SCALPEL,
	DISSECT_SCISSORS,
	DISSECT_PINCETTE,
	DISSECT_PINCETTE_PIECE,
	NONE
};

/// <summary>
/// 유저가 조종하는 Player
/// 
/// 마우스를 이용하여 게임을 진행한다, 부검실에서 사용하는 의학도구들 포함
/// 2021. 02. 14 Hacgeum
/// </summary>
class Player
{
public:
	Player();
	~Player();

private:
	GameObject* m_Tools[static_cast<int>(ToolType::NONE)];
	ObjectManager* m_pObjectManager;

	ToolType m_ToolType;
	bool m_HadTool;
	bool m_UseTool;

	MainDissectingRoomScene* m_pMainDissectingRoomScene;

	// Getter / Setter
public:
	ToolType GetToolType() const { return m_ToolType; }
	void SetToolType(ToolType toolType) { m_ToolType = toolType; }

	bool GetUseToolState() const { return m_UseTool; }
	void SetUseToolState(bool value) { m_UseTool = value; }

	bool GetHadToolState() const { return m_HadTool; }
	void SetHadToolState(bool state) { m_HadTool = state; }

	GameObject* GetTools(ToolType type) const { return m_Tools[static_cast<int>(type)]; }

public:
	void Initialize();
	void Update(float dTime);
	void Draw();
	void Release();
};
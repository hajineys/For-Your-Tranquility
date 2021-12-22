#pragma once

class Button;
class ObjectManager;

enum class eSceneStateAll
{
	INTRO_TITLE,
	INTRO_ANIMATION,
	MAIN_OFFICE,
	MAIN_AUTOPSY_ENTRY,
	MAIN_AUTOPSY,
	MAIN_DISSECTING,
	OUTRO_RESULT,
	OUTRO_ENDING,
	MAIN_INCIDENT,
	NONE
};

/// 모든 씬에 공통되는 씬의 상태 (더 있으면 추가바람)
enum class eNowSceneState
{
	NONE,
	GO_TO_NEXT_SCENE,
	GO_TO_PREV_SCENE,
	POPUP_SHOW,
};

/// ChangeSceneButton 배열을 명시적으로 관리하기 위한 enum
enum PrevNextButton
{
	PREV,
	NEXT
};

/// <summary>
/// 씬 인터페이스
/// 
/// 각 게임 씬의 부모 클래스
/// 2021. 02. 06. Hacgeum
/// (수정)2021. 02. 18. 정종영
/// </summary>
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// 초기화
	virtual void Initialize();
	virtual void Update(float dTime) abstract;
	virtual void Draw() abstract;
	virtual void ShowDebug();
	virtual void Release();

protected:
	ObjectManager* m_pObjectManager;
	eNowSceneState m_NowSceneState;		// 현재 씬의 상태
	
	bool m_IsGameEnd;

public:
	void SetIsGameEnd(bool val) { m_IsGameEnd = val; }
	void SetNowSceneState(eNowSceneState val) { m_NowSceneState = val; }
};
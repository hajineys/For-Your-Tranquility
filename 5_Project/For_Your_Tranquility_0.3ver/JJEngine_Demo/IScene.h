#pragma once

enum class eSceneStateAll
{
	INTRO_TITLE,
	INTRO_ANIMATION,
	MAIN_OFFICE,
	MAIN_AUTOPSY,
	MAIN_DISSECTING,
	OUTRO_RESULT,
	OUTRO_ENDING
};

/// <summary>
/// 씬 인터페이스
/// 
/// 각 게임 씬의 부모 추상 클래스
/// 2021. 02. 06. Hacgeum
/// </summary>
class IScene /*abstract*/
{
public:
	// 초기화
	virtual void Initialize() abstract;
	virtual void Update(float dTime) abstract;
	virtual void Render() abstract;
	virtual void ShowDebug() abstract;
	virtual void Finalize() abstract;
};
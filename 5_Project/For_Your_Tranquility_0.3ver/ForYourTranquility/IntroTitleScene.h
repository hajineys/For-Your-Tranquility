#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;

/// <summary>
/// 타이틀 씬
/// 
/// 타이틀, 게임시작, 게임종료 등 선택지 존재
/// 2021. 02. 08. Hacgeum
/// 
/// 임시버튼 및 클릭시 씬 전환, 게임종료
/// 2021. 02. 15. JJun
/// </summary>

class IntroTitleScene : public Scene
{
public:
	IntroTitleScene();
	virtual ~IntroTitleScene();

private:
	Object* m_pBackGround;						// 배경 화면

	Object* m_pLightAnimation;					// 배경 화면 전등 애니메이션
	Object* m_pTitleBar;						// 타이틀 이미지

	Button* m_pStartButton;						// 게임 시작 버튼 

	Button* m_pExitButton;						// 게임 종료 버튼 

	eSceneStateAll m_pNowSceneState;			// 디버그용
	
public:
	static bool m_IsFirstPlay[2];

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
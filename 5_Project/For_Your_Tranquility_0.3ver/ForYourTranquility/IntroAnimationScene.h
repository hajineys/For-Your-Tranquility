#pragma once
#include "Scene.h"

enum SceneCharacter
{
	Elder,
	Junior,
	PoliceMan,
	SuperIntendent,
};

class ObjectManager;
class Object;
class TextBox;

/// <summary>
/// 타이틀 씬
/// 
/// 게임 시작 후 플레이어 캐릭터와 주변 캐릭터와의 간단한 대화 애니메이션
/// 2021. 02. 08. Hacgeum
/// </summary>
class IntroAnimationScene : public Scene
{
public:
	IntroAnimationScene();
	virtual ~IntroAnimationScene();

	// 배경화면
	Object* m_pBackgroundIMG;

	// 대화상자
	TextBox* m_pTextBox;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
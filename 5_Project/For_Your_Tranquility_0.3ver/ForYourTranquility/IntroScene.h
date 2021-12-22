#pragma once
#include "IScene.h"

/// <summary>
/// 인트로 씬
/// 
/// 타이틀, 대화 애니메이션 씬 존재
/// 2021. 02. 06. Hacgeum
/// </summary>
class IntroScene : public IScene
{
public:
	IntroScene();
	virtual ~IntroScene();

	eSceneStateAll m_IntroState;
	IScene* m_pNowScene;
	IScene* m_pIntroTitle;
	IScene* m_pIntroAnimation;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};
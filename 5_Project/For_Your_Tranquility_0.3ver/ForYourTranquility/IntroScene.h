#pragma once
#include "IScene.h"

/// <summary>
/// ��Ʈ�� ��
/// 
/// Ÿ��Ʋ, ��ȭ �ִϸ��̼� �� ����
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
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};
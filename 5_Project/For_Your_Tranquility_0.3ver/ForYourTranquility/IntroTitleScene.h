#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;

/// <summary>
/// Ÿ��Ʋ ��
/// 
/// Ÿ��Ʋ, ���ӽ���, �������� �� ������ ����
/// 2021. 02. 08. Hacgeum
/// 
/// �ӽù�ư �� Ŭ���� �� ��ȯ, ��������
/// 2021. 02. 15. JJun
/// </summary>

class IntroTitleScene : public Scene
{
public:
	IntroTitleScene();
	virtual ~IntroTitleScene();

private:
	Object* m_pBackGround;						// ��� ȭ��

	Object* m_pLightAnimation;					// ��� ȭ�� ���� �ִϸ��̼�
	Object* m_pTitleBar;						// Ÿ��Ʋ �̹���

	Button* m_pStartButton;						// ���� ���� ��ư 

	Button* m_pExitButton;						// ���� ���� ��ư 

	eSceneStateAll m_pNowSceneState;			// ����׿�
	
public:
	static bool m_IsFirstPlay[2];

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
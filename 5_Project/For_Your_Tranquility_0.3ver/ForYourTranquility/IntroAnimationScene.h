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
/// Ÿ��Ʋ ��
/// 
/// ���� ���� �� �÷��̾� ĳ���Ϳ� �ֺ� ĳ���Ϳ��� ������ ��ȭ �ִϸ��̼�
/// 2021. 02. 08. Hacgeum
/// </summary>
class IntroAnimationScene : public Scene
{
public:
	IntroAnimationScene();
	virtual ~IntroAnimationScene();

	// ���ȭ��
	Object* m_pBackgroundIMG;

	// ��ȭ����
	TextBox* m_pTextBox;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};
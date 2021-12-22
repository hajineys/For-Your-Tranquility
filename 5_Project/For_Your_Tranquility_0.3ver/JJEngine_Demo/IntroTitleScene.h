#pragma once
#include "IScene.h"

class ObjectManager;
class GameObject;
class Object;
class TextBox;

/// <summary>
/// Ÿ��Ʋ ��
/// 
/// Ÿ��Ʋ, ���ӽ���, �������� �� ������ ����
/// 2021. 02. 08. Hacgeum
/// </summary>
class IntroTitleScene : public IScene
{
public:
	IntroTitleScene();
	~IntroTitleScene();

private:
	ObjectManager* m_pObjectManager;

	// �׽�Ʈ�� ���ӿ�����Ʈ
	GameObject* Character;
	Object* testObject;
	TextBox* textBox;

	GameObject* testGameObject;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Render() override;
	virtual void ShowDebug() override;
	virtual void Finalize() override;
};
#pragma once
#include "IScene.h"

class tObjectManager;
class tGameObject;
class tObject;
class tTextBox;

/// <summary>
/// Ÿ��Ʋ ��
/// 
/// Ÿ��Ʋ, ���ӽ���, �������� �� ������ ����
/// 2021. 02. 08. Hacgeum
/// </summary>
class tIntroTitleScene : public IScene
{
public:
	tIntroTitleScene();
	~tIntroTitleScene();

private:
	tObjectManager* m_pObjectManager;

	// �׽�Ʈ�� ���ӿ�����Ʈ
	tGameObject* Character;
	tObject* testObject;
	tTextBox* textBox;

	tGameObject* testGameObject;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Render() override;
	virtual void ShowDebug() override;
	virtual void Finalize() override;
};
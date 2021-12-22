#pragma once
#include "Object.h"

/// <summary>
/// ���콺�� ��ȣ�ۿ��ϴ� ��ư
/// 
/// 2021.02.18 ������
/// </summary>
class Button : public Object
{
private:
	eNowSceneState m_StateForClicked;	// �� ������Ʈ�� ������ ��, �� ������Ʈ�� �ִ� ������ ����Ǿ�� �ϴ� ����
	eFirstChoiceState m_FirstChoiceState;
	eSecondChoiceState m_SecondChoiceState;
	eThirdChoiceState m_ThirdChoiceState;

public:
	eNowSceneState GetStateForClicked() const { return m_StateForClicked; }
	void SetStateForClicked(eNowSceneState val) { m_StateForClicked = val; }

	eFirstChoiceState GetFirstChoiceState() const { return m_FirstChoiceState; }
	eSecondChoiceState GetSecondChoiceState() const { return m_SecondChoiceState; }
	eThirdChoiceState GetThirdChoiceState() const { return m_ThirdChoiceState; }

public:
	Button(UISortLayer layer);
	Button(UISortLayer layer, eNowSceneState state);
	Button(UISortLayer layer, eFirstChoiceState state);
	Button(UISortLayer layer, eSecondChoiceState state);
	Button(UISortLayer layer, eThirdChoiceState state);
	virtual ~Button();

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();
};
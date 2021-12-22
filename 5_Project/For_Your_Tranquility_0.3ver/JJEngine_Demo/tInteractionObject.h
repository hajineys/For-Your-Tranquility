#pragma once

#include "tGameObject.h"

class tPlayer;

/// <summary>
/// ���콺(�÷��̾�)�� ��ȣ�ۿ��ϴ� ������Ʈ
/// 2021.02.14
/// ������
/// </summary>
class tInteractionObject : public tGameObject
{
protected:
	bool m_IsCollided;
	bool m_IsClicked;

public:
	tInteractionObject();
	~tInteractionObject();

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw();
	virtual void ShowDebug();

	/// �浹 ����
	bool CheckClicked();
};

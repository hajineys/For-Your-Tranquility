#pragma once

#include "GameObject.h"

class Player;

/// <summary>
/// ���콺(�÷��̾�)�� ��ȣ�ۿ��ϴ� ������Ʈ
/// 2021.02.14
/// ������
/// </summary>
class InteractionObject : public GameObject
{
protected:
	bool m_IsCollided;
	bool m_IsClicked;

public:
	InteractionObject();
	~InteractionObject();

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw();
	virtual void ShowDebug();

	/// �浹 ����
	bool CheckClicked();
};

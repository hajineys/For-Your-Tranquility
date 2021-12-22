#pragma once

#include "GameObject.h"

class Player;

/// <summary>
/// 마우스(플레이어)와 상호작용하는 오브젝트
/// 2021.02.14
/// 정종영
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

	/// 충돌 감지
	bool CheckClicked();
};

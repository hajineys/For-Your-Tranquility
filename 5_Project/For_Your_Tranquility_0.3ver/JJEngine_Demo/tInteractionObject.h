#pragma once

#include "tGameObject.h"

class tPlayer;

/// <summary>
/// 마우스(플레이어)와 상호작용하는 오브젝트
/// 2021.02.14
/// 정종영
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

	/// 충돌 감지
	bool CheckClicked();
};

#pragma once

#include "tObject.h"
#include "JMotion.h"

class JJEngine;

/// <summary>
/// 오브젝트를 상속받고 애니메이션 기능이 추가된 게임오브젝트 클래스
/// 2021.02.14
/// 정종영
/// </summary>
class tGameObject : public tObject
{
protected:
	/// 애니메이션 관련
	ID2D1Bitmap* m_SpriteSheet;				// 이 오브젝트의 스프라이트(애니메이션) 시트
	vector<JMotion*> m_MotionVec;			// 모든 모션들을 갖고 있는 벡터
	JMotion* m_NowMotion;					// 현재 플레이 중인 모션

	int m_MotionCount;						// 모션의 총 갯수
	int m_MotionIndex;						// 현재 플레이 중인 모션의 인덱스
	int m_PlayCount;

public:
	tGameObject();
	~tGameObject();

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();

	void UpdateAnimation(float dTime, float speed = 1.0f);
	void PlayAnimation(float dTime, float speed = 1.0f);

	void SetSpriteSheet(PCWSTR uri);
	void SetMotion();
	void SetPlayCount(int count) { m_NowMotion->PlayCount = count; }
	void ResetMotion();

	void NextMotionFrame();
	void ChangeMotionFrame(int frame);
};
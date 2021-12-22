#pragma once
#include "Object.h"

class Object;
class ObjectManager;

enum class OrganState
{
	ECT3,
	BONE,
	STOMACH,	// 위장
	ECT4,
	ECT2,
	LUNGS,		// 폐
	LIVER,		// 간
	HEART,		// 심장
	NONE
};

/// <summary>
/// 시체 속 장기
/// 
/// 부검실, 해부실에서 마우스와 상호작용 가능한 오브젝트 클래스
/// 2021. 02. 17 Hacgeum
/// </summary>
class Organ : public Object
{
public:
	Organ(UISortLayer layer);
	~Organ();

private:
	Object* m_Organs[static_cast<int>(OrganState::NONE)];
	ObjectManager* m_pObjectManager;

	OrganState m_NowOrganState;

public:
	OrganState GetOrganState() const { return m_NowOrganState; }
	void SetOrganState(OrganState organState) { m_NowOrganState = organState; }

	Object* GetOrgans(OrganState type) const { return m_Organs[static_cast<int>(type)]; }

public:
	virtual void Initialize(JVector pos, PCWSTR objectName) override;
	virtual void Update(float dTime) override;
	void Draw(float opacity = 1.0f);
	void Release();
};
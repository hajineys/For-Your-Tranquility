#pragma once
#include "Object.h"

class Object;
class ObjectManager;

enum class OrganState
{
	ECT3,
	BONE,
	STOMACH,	// ����
	ECT4,
	ECT2,
	LUNGS,		// ��
	LIVER,		// ��
	HEART,		// ����
	NONE
};

/// <summary>
/// ��ü �� ���
/// 
/// �ΰ˽�, �غνǿ��� ���콺�� ��ȣ�ۿ� ������ ������Ʈ Ŭ����
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
#pragma once

#include "Object.h"
//#include "JMotion.h"

class JJEngine;
class JMotion;

/// <summary>
/// ������Ʈ�� ��ӹް� �ִϸ��̼� ����� �߰��� ���ӿ�����Ʈ Ŭ����
/// 2021.02.14
/// ������
/// </summary>
class GameObject : public Object
{
protected:
	/// �ִϸ��̼� ����
	ID2D1Bitmap* m_SpriteSheet;				// �� ������Ʈ�� ��������Ʈ(�ִϸ��̼�) ��Ʈ
	vector<JMotion*> m_MotionVec;			// ��� ��ǵ��� ���� �ִ� ����
	JMotion* m_NowMotion;					// ���� �÷��� ���� ���

	int m_MotionCount;						// ����� �� ����
	int m_MotionIndex;						// ���� �÷��� ���� ����� �ε���

public:
	GameObject(UISortLayer layer);
	virtual ~GameObject();

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();

	/// �ִϸ��̼� ����
	virtual bool PlayAnimation(float dTime, float speed = 1.0f);
	virtual void UpdateAnimation(float dTime, float speed = 1.0f);

	void SetSpriteSheet(CString name);
	void NextMotion();

	void SetPlayCount(int count) { m_NowMotion->PlayCount = count; }
	void NextMotionFrame();
	void ChangeMotionFrame(int frame);
};
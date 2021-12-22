#pragma once

class JTransform;
class JImage;

/// <summary>
/// ������Ʈ Ŭ����, �̸��� Transform, �� ���� ��������Ʈ���� ������.
/// 2021.02.14
/// ������
/// </summary>
class Object
{
protected:
	CString m_ObjectName;				// ������Ʈ�� �̸�(���ҽ� �Ŵ����� ������ ���� �ʿ�)
	JTransform* m_Transform;			// ������Ʈ�� ��ġ, ũ��

	JImage* m_Sprite;				// ������Ʈ�� �̹���(�⺻ �� ���� ��������)

public:
	Object();
	~Object();

	JTransform* Transform() { return m_Transform; }

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();

	void SetSprite(PCWSTR uri, int frame);
	void NextFrame();
	void ChangeFrame(int frame);
};
#pragma once

class JTransform;
class JSprite;
class JImage;
class ColliderBox;

/// <summary>
/// UI Sort Layer
/// </summary>
enum class UISortLayer
{
	BACKGROUND,					// ���
	BUTTON,						// ���ϴ� ��ư
	POPUPWINDOW,				// �˾� â
	POPUPWINDOW_UP,
	POPUPWINDOW_OBJECT,
	POPUPWINDOWBUTTON,			// �˾� â�� ��ư
	PLAYER,						// �÷��̾�
	TOPUI,						// �ֻ�� UI
	ENDLAYER,
};

/// <summary>
/// ������Ʈ Ŭ����, �̸��� Transform, �� ���� ��������Ʈ���� ������.
/// 2021.02.14
/// ������
/// </summary>
class Object
{
protected:
	CString m_ObjectName;		// ������Ʈ�� �̸�(���ҽ� �Ŵ����� ������ ���� �ʿ�)
	JTransform* m_Transform;	// ������Ʈ�� ��ġ, ũ��

	vector<JImage*> m_SpriteVec;	// ������Ʈ�� �̹���(�⺻ �� ���� ��������)
	int m_SpriteIndex;				// �̹��� �ε���

	UISortLayer m_Layer;		// �� ������Ʈ�� ��ġ�� ���̾�

	ColliderBox* m_ColliderBox;

public:
	Object(UISortLayer layer);
	virtual ~Object();

	JTransform* Transform() { return m_Transform; }
	ColliderBox* GetColliderBox() { return m_ColliderBox; }
	UISortLayer GetLayer() const { return m_Layer; }
	JImage* GetNowSprite() const { return m_SpriteVec[m_SpriteIndex]; }
	int GetNowFrame() {	return m_SpriteVec[m_SpriteIndex]->DrawIndex; }

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw(float opacity = 1.0f);
	virtual void ShowDebug();

	void AddSprite(CString additionalName, int frame);
	void NextSprite();
	void ChangeSprite(int frame);

	void NextFrame();
	void ChangeFrame(int frame);

	virtual bool PlayAnimation(float dTime, float speed = 1.0f);
	virtual bool PlayAndResetAnimation(float dTime, float speed = 1.0f);
	virtual void UpdateAnimation(float dTime, float speed = 1.0f);
	virtual void ResetAnimation();
};
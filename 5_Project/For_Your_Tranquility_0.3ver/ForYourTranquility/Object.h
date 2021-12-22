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
	BACKGROUND,					// 배경
	BUTTON,						// 최하단 버튼
	POPUPWINDOW,				// 팝업 창
	POPUPWINDOW_UP,
	POPUPWINDOW_OBJECT,
	POPUPWINDOWBUTTON,			// 팝업 창의 버튼
	PLAYER,						// 플레이어
	TOPUI,						// 최상단 UI
	ENDLAYER,
};

/// <summary>
/// 오브젝트 클래스, 이름과 Transform, 한 장의 스프라이트만을 가진다.
/// 2021.02.14
/// 정종영
/// </summary>
class Object
{
protected:
	CString m_ObjectName;		// 오브젝트의 이름(리소스 매니저와 연동을 위해 필요)
	JTransform* m_Transform;	// 오브젝트의 위치, 크기

	vector<JImage*> m_SpriteVec;	// 오브젝트의 이미지(기본 한 장은 갖고있음)
	int m_SpriteIndex;				// 이미지 인덱스

	UISortLayer m_Layer;		// 이 오브젝트가 위치한 레이어

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
#pragma once

class JTransform;
class JImage;

/// <summary>
/// 오브젝트 클래스, 이름과 Transform, 한 장의 스프라이트만을 가진다.
/// 2021.02.14
/// 정종영
/// </summary>
class Object
{
protected:
	CString m_ObjectName;				// 오브젝트의 이름(리소스 매니저와 연동을 위해 필요)
	JTransform* m_Transform;			// 오브젝트의 위치, 크기

	JImage* m_Sprite;				// 오브젝트의 이미지(기본 한 장은 갖고있음)

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
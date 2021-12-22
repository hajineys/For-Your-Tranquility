#pragma once

class JTransform;
class Object;

/// <summary>
/// 마우스(플레이어)와 충돌을 감지하는 콜라이더박스
/// 2021.02.14
/// 정종영
/// </summary>
class ColliderBox
{
public:
	JTransform SetTransform;

	bool IsCollided;
	bool IsCollidedObject;
	bool IsClicked;
	bool IsHolding;

	// 콜라이더 박스의 바깥쪽 충돌 체크, 클릭 체크
	bool IsOutSideCollided;
	bool IsOutSideClicked;

	wstring Name;

public:
	ColliderBox(JVector pos, PCWSTR objectName);
	~ColliderBox();

	void SetSize(JVector size);

public:
	void Update(float dTime, JTransform* transform);
	void Draw();
	void ShowDebug();

	// 마우스와 상호작용
	bool CheckClicked();
	bool CheckCollided();
	bool CheckCollidedObject(Object* ptargetObject);
	bool CheckHolding();

	bool CheckOutSideClicked();
	bool CheckOutSideCollided();
};
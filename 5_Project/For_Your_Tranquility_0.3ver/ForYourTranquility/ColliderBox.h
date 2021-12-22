#pragma once

class JTransform;
class Object;

/// <summary>
/// ���콺(�÷��̾�)�� �浹�� �����ϴ� �ݶ��̴��ڽ�
/// 2021.02.14
/// ������
/// </summary>
class ColliderBox
{
public:
	JTransform SetTransform;

	bool IsCollided;
	bool IsCollidedObject;
	bool IsClicked;
	bool IsHolding;

	// �ݶ��̴� �ڽ��� �ٱ��� �浹 üũ, Ŭ�� üũ
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

	// ���콺�� ��ȣ�ۿ�
	bool CheckClicked();
	bool CheckCollided();
	bool CheckCollidedObject(Object* ptargetObject);
	bool CheckHolding();

	bool CheckOutSideClicked();
	bool CheckOutSideCollided();
};
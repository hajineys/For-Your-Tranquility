#include "pch.h"

#include "ColliderBox.h"
#include "Object.h"
#include "GameObject.h"
#include "JTransform.h"
#include "Player.h"

ColliderBox::ColliderBox(JVector pos, PCWSTR objectName)
	:IsCollided(false), IsClicked(false), IsHolding(false), IsOutSideClicked(false), IsOutSideCollided(false)
{
	SetTransform.Pos = pos;
	Name = objectName;
}

ColliderBox::~ColliderBox()
{

}

void ColliderBox::SetSize(JVector size)
{
	SetTransform.Size = size;
}

void ColliderBox::Update(float dTime, JTransform* transform)
{
	// �浹 �˻�
	CheckCollided();
	CheckClicked();
	CheckHolding();

	// �ٱ��� �浹�˻�
	CheckOutSideCollided();
	CheckOutSideClicked();

	if (transform->Size.x != SetTransform.Size.x && transform->Size.y != SetTransform.Size.y)
	{
		//�ǹ�O
		// �ݶ��̴� �ڽ��� ����� �E ���ΰ�? -> �ݶ��̴� �ڽ��� 
		SetTransform.Pos.x = transform->CenterPos.x - (SetTransform.Size.x / 2);
		SetTransform.Pos.y = transform->CenterPos.y - (SetTransform.Size.y / 2);
	}
	else
	{
		// ������Ʈ�� ����� �� ���ΰ�?
		SetTransform.Pos.x = transform->CenterPos.x - (transform->Size.x / 2);
		SetTransform.Pos.y = transform->CenterPos.y - (transform->Size.y / 2);
	}
}

void ColliderBox::Draw()
{
	// �浹�ڽ��� �׸���.
	if (IsCollided)
	{
		JJEngine::GetInstance()->DrawRectangle(SetTransform.Pos.x, SetTransform.Pos.y, SetTransform.Pos.x + SetTransform.Size.x, SetTransform.Pos.y + SetTransform.Size.y, ColorF(ColorF::Blue, 0.5f));
	}
	else
	{
		JJEngine::GetInstance()->DrawRectangle(SetTransform.Pos.x, SetTransform.Pos.y, SetTransform.Pos.x + SetTransform.Size.x, SetTransform.Pos.y + SetTransform.Size.y, ColorF(ColorF::LightGreen, 0.5f));
	}

	ShowDebug();
}

void ColliderBox::ShowDebug()
{
	// �ڽ��� �̸� ���
	JJEngine::GetInstance()->DrawText(SetTransform.Pos.x, SetTransform.Pos.y + SetTransform.Size.y / 2, Name.c_str());
}

bool ColliderBox::CheckClicked()
{
	// �浹�߰� ���콺��ư���� ������ ���
	if (IsCollided && InputManager::GetInstance()->CheckLeftButtonUp())
	{
		IsClicked = true;
	}
	else
		IsClicked = false;

	return IsClicked;
}

bool ColliderBox::CheckCollided()
{
	POINT _mousePos = { InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y };

	float _width = SetTransform.Size.x;
	float _height = SetTransform.Size.y;

	// �浹 �˻�
	if (_mousePos.x >= SetTransform.Pos.x &&
		_mousePos.x <= SetTransform.Pos.x + _width &&
		_mousePos.y >= SetTransform.Pos.y &&
		_mousePos.y <= SetTransform.Pos.y + _height)
	{
		// �浹
		IsCollided = true;
	}
	else
	{
		// �浹�ƴ�
		IsCollided = false;
	}

	return IsCollided;
}

bool ColliderBox::CheckCollidedObject(Object* ptargetObject)
{
	POINT _targetObjectPos = { ptargetObject->Transform()->CenterPos.x, ptargetObject->Transform()->CenterPos.y };

	float _width = SetTransform.Size.x;
	float _height = SetTransform.Size.y;

	// �浹 �˻�
	if (_targetObjectPos.x >= SetTransform.Pos.x &&
		_targetObjectPos.x <= SetTransform.Pos.x + _width &&
		_targetObjectPos.y >= SetTransform.Pos.y &&
		_targetObjectPos.y <= SetTransform.Pos.y + _height)
	{
		// �浹
		IsCollidedObject = true;
	}
	else
	{
		// �浹�ƴ�
		IsCollidedObject = false;
	}

	return IsCollidedObject;
}

bool ColliderBox::CheckHolding()
{
	// �浹�߰� ���콺�� ������ �ִ� ���
	if (IsCollided && InputManager::GetInstance()->CheckLeftButtonHold())
	{
		IsHolding = true;
	}
	else
		IsHolding = false;

	return IsHolding;
}

bool ColliderBox::CheckOutSideClicked()
{
	// �浹�߰� ���콺��ư���� ������ ���
	if (IsOutSideCollided && InputManager::GetInstance()->CheckLeftButtonUp())
	{
		IsOutSideClicked = true;
	}
	else
		IsOutSideClicked = false;

	return IsOutSideClicked;
}

bool ColliderBox::CheckOutSideCollided()
{
	POINT _mousePos = { InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y };

	float _width = SetTransform.Size.x;
	float _height = SetTransform.Size.y;

	// �浹 �˻�
	if (_mousePos.x <= SetTransform.Pos.x ||
		_mousePos.x >= SetTransform.Pos.x + _width ||
		_mousePos.y <= SetTransform.Pos.y ||
		_mousePos.y >= SetTransform.Pos.y + _height)
	{
		// �浹
		IsOutSideCollided = true;
	}
	else
	{
		// �浹�ƴ�
		IsOutSideCollided = false;
	}

	return IsOutSideCollided;
}
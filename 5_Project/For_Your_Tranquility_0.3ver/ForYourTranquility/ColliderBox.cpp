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
	// 충돌 검사
	CheckCollided();
	CheckClicked();
	CheckHolding();

	// 바깥쪽 충돌검사
	CheckOutSideCollided();
	CheckOutSideClicked();

	if (transform->Size.x != SetTransform.Size.x && transform->Size.y != SetTransform.Size.y)
	{
		//피벗O
		// 콜라이더 박스의 사이즈를 뺼 것인가? -> 콜라이더 박스는 
		SetTransform.Pos.x = transform->CenterPos.x - (SetTransform.Size.x / 2);
		SetTransform.Pos.y = transform->CenterPos.y - (SetTransform.Size.y / 2);
	}
	else
	{
		// 오브젝트의 사이즈를 뺄 것인가?
		SetTransform.Pos.x = transform->CenterPos.x - (transform->Size.x / 2);
		SetTransform.Pos.y = transform->CenterPos.y - (transform->Size.y / 2);
	}
}

void ColliderBox::Draw()
{
	// 충돌박스를 그린다.
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
	// 자신의 이름 출력
	JJEngine::GetInstance()->DrawText(SetTransform.Pos.x, SetTransform.Pos.y + SetTransform.Size.y / 2, Name.c_str());
}

bool ColliderBox::CheckClicked()
{
	// 충돌했고 마우스버튼까지 눌렸을 경우
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

	// 충돌 검사
	if (_mousePos.x >= SetTransform.Pos.x &&
		_mousePos.x <= SetTransform.Pos.x + _width &&
		_mousePos.y >= SetTransform.Pos.y &&
		_mousePos.y <= SetTransform.Pos.y + _height)
	{
		// 충돌
		IsCollided = true;
	}
	else
	{
		// 충돌아님
		IsCollided = false;
	}

	return IsCollided;
}

bool ColliderBox::CheckCollidedObject(Object* ptargetObject)
{
	POINT _targetObjectPos = { ptargetObject->Transform()->CenterPos.x, ptargetObject->Transform()->CenterPos.y };

	float _width = SetTransform.Size.x;
	float _height = SetTransform.Size.y;

	// 충돌 검사
	if (_targetObjectPos.x >= SetTransform.Pos.x &&
		_targetObjectPos.x <= SetTransform.Pos.x + _width &&
		_targetObjectPos.y >= SetTransform.Pos.y &&
		_targetObjectPos.y <= SetTransform.Pos.y + _height)
	{
		// 충돌
		IsCollidedObject = true;
	}
	else
	{
		// 충돌아님
		IsCollidedObject = false;
	}

	return IsCollidedObject;
}

bool ColliderBox::CheckHolding()
{
	// 충돌했고 마우스가 눌리고 있는 경우
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
	// 충돌했고 마우스버튼까지 눌렸을 경우
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

	// 충돌 검사
	if (_mousePos.x <= SetTransform.Pos.x ||
		_mousePos.x >= SetTransform.Pos.x + _width ||
		_mousePos.y <= SetTransform.Pos.y ||
		_mousePos.y >= SetTransform.Pos.y + _height)
	{
		// 충돌
		IsOutSideCollided = true;
	}
	else
	{
		// 충돌아님
		IsOutSideCollided = false;
	}

	return IsOutSideCollided;
}
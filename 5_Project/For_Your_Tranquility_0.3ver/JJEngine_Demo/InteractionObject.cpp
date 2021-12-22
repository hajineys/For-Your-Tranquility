#include "pch.h"

#include "Object.h"
#include "InteractionObject.h"
#include "JTransform.h"
#include "Player.h"

InteractionObject::InteractionObject()
	:m_IsCollided(false), m_IsClicked(false)
{

}

InteractionObject::~InteractionObject()
{

}

void InteractionObject::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);
}

void InteractionObject::Release()
{
	Object::Release();
}

void InteractionObject::Update(float dTime)
{
	Object::Update(dTime);
}

void InteractionObject::Draw()
{
	// 애니메이션 스프라이트를 그린다.
	Object::Draw();

	if (m_IsCollided)
	{
		if (m_IsClicked)
			JJEngine::GetInstance()->DrawFillRectangle(200, 40, 100, 100, ColorF(ColorF::Pink));
		else
			JJEngine::GetInstance()->DrawFillRectangle(200, 40, 100, 100, ColorF(ColorF::Blue));
	}
	else
	{
		JJEngine::GetInstance()->DrawFillRectangle(200, 40, 100, 100, ColorF(ColorF::Black));
	}

	ShowDebug();
}

void InteractionObject::ShowDebug()
{
	// 디버그용 충돌박스를 그린다.
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::LEFT_TOP].x, m_Transform->RectPos[JTransform::LEFT_TOP].y, m_Transform->RectPos[JTransform::RIGHT_TOP].x, m_Transform->RectPos[JTransform::RIGHT_TOP].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::RIGHT_TOP].x, m_Transform->RectPos[JTransform::RIGHT_TOP].y, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].x, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::RIGHT_BOTTOM].x, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].y, m_Transform->RectPos[JTransform::LEFT_BOTTOM].x, m_Transform->RectPos[JTransform::LEFT_BOTTOM].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::LEFT_BOTTOM].x, m_Transform->RectPos[JTransform::LEFT_BOTTOM].y, m_Transform->RectPos[JTransform::LEFT_TOP].x, m_Transform->RectPos[JTransform::LEFT_TOP].y, ColorF(ColorF::LightGreen));
}

bool InteractionObject::CheckClicked()
{
	POINT _mousePos = { InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y };

	float _width = m_Transform->RectPos[JTransform::RIGHT_TOP].x - m_Transform->RectPos[JTransform::LEFT_TOP].x;
	float _height = m_Transform->RectPos[JTransform::LEFT_BOTTOM].y - m_Transform->RectPos[JTransform::LEFT_TOP].y;

	// 충돌 검사
	if (_mousePos.x >= m_Transform->Pos.x &&
		_mousePos.x <= m_Transform->Pos.x + _width &&
		_mousePos.y >= m_Transform->Pos.y &&
		_mousePos.y <= m_Transform->Pos.y + _height)
	{
		// 충돌
		m_IsCollided = true;

		// 충돌했고 마우스버튼까지 눌렸을 경우
		if (InputManager::GetInstance()->CheckLeftButtonUp())
		{
			m_IsClicked = true;
		}
		else
			m_IsClicked = false;
	}
	else
	{
		// 충돌아님
		m_IsCollided = false;
	}

	return m_IsClicked;
}
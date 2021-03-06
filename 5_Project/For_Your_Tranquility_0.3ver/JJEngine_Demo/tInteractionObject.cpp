#include "pch.h"

#include "tObject.h"
#include "tInteractionObject.h"
#include "JTransform.h"
#include "tPlayer.h"

tInteractionObject::tInteractionObject()
	:m_IsCollided(false), m_IsClicked(false)
{

}

tInteractionObject::~tInteractionObject()
{

}

void tInteractionObject::Initialize(JVector pos, PCWSTR objectName)
{
	tObject::Initialize(pos, objectName);
}

void tInteractionObject::Release()
{
	tObject::Release();
}

void tInteractionObject::Update(float dTime)
{
	tObject::Update(dTime);
}

void tInteractionObject::Draw()
{
	// 애니메이션 스프라이트를 그린다.
	tObject::Draw();

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

void tInteractionObject::ShowDebug()
{
	// 디버그용 충돌박스를 그린다.
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::LEFT_TOP].x, m_Transform->RectPos[JTransform::LEFT_TOP].y, m_Transform->RectPos[JTransform::RIGHT_TOP].x, m_Transform->RectPos[JTransform::RIGHT_TOP].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::RIGHT_TOP].x, m_Transform->RectPos[JTransform::RIGHT_TOP].y, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].x, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::RIGHT_BOTTOM].x, m_Transform->RectPos[JTransform::RIGHT_BOTTOM].y, m_Transform->RectPos[JTransform::LEFT_BOTTOM].x, m_Transform->RectPos[JTransform::LEFT_BOTTOM].y, ColorF(ColorF::LightGreen));
	JJEngine::GetInstance()->DrawLine(m_Transform->RectPos[JTransform::LEFT_BOTTOM].x, m_Transform->RectPos[JTransform::LEFT_BOTTOM].y, m_Transform->RectPos[JTransform::LEFT_TOP].x, m_Transform->RectPos[JTransform::LEFT_TOP].y, ColorF(ColorF::LightGreen));
}

bool tInteractionObject::CheckClicked()
{
	POINT _mousePos = { tInputManager::GetInstance()->GetMousePos().x, tInputManager::GetInstance()->GetMousePos().y };

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
		if (tInputManager::GetInstance()->CheckLeftButtonUp())
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
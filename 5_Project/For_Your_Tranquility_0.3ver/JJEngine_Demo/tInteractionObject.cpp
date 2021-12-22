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
	// �ִϸ��̼� ��������Ʈ�� �׸���.
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
	// ����׿� �浹�ڽ��� �׸���.
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

	// �浹 �˻�
	if (_mousePos.x >= m_Transform->Pos.x &&
		_mousePos.x <= m_Transform->Pos.x + _width &&
		_mousePos.y >= m_Transform->Pos.y &&
		_mousePos.y <= m_Transform->Pos.y + _height)
	{
		// �浹
		m_IsCollided = true;

		// �浹�߰� ���콺��ư���� ������ ���
		if (tInputManager::GetInstance()->CheckLeftButtonUp())
		{
			m_IsClicked = true;
		}
		else
			m_IsClicked = false;
	}
	else
	{
		// �浹�ƴ�
		m_IsCollided = false;
	}

	return m_IsClicked;
}
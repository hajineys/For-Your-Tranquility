#include "pch.h"

#include "tObject.h"

tObject::tObject()
	:m_Transform(nullptr), m_ObjectName(""), m_Sprite(nullptr)
{

}

tObject::~tObject()
{

}

void tObject::Initialize(JVector pos, PCWSTR objectName)
{
	m_Transform = new JTransform();

	// Trnasform 초기화
	m_Transform->Pos = pos;

	// 오브젝트 이름 초기화
	m_ObjectName = objectName;

	m_Sprite = new JImage(1);
}

void tObject::Release()
{
	if (m_Transform != nullptr)
	{
		delete m_Transform;
		m_Transform = nullptr;
	}
}

void tObject::Update(float dTime)
{
	//m_Sprite->Update(dTime);
}

void tObject::Draw(float opacity/*=1.0f*/)
{
	JJEngine::GetInstance()->DrawSprite(m_Sprite, m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void tObject::ShowDebug()
{

}

void tObject::SetSprite(PCWSTR uri, int frame)
{
	JJEngine::GetInstance()->LoadBitmapFromFile(uri, 0, 0, &m_Sprite->Bitmap);
	m_Sprite->Frame = frame;

	// 이미지 크기에 맞게 충돌박스를 초기화
	D2D1_SIZE_F size = m_Sprite->Bitmap->GetSize();
	size.width /= frame;

	m_Transform->RectPos[m_Transform->LEFT_TOP] = { m_Transform->Pos.x, m_Transform->Pos.y };
	m_Transform->RectPos[m_Transform->RIGHT_TOP] = { m_Transform->Pos.x + size.width, m_Transform->Pos.y };
	m_Transform->RectPos[m_Transform->LEFT_BOTTOM] = { m_Transform->Pos.x, m_Transform->Pos.y + size.height };
	m_Transform->RectPos[m_Transform->RIGHT_BOTTOM] = { m_Transform->Pos.x + size.width, m_Transform->Pos.y + size.height };

	m_Transform->Size.x = size.width;
	m_Transform->Size.y = size.height;
}

void tObject::NextFrame()
{
	m_Sprite->NextFrame();
}

void tObject::ChangeFrame(int frame)
{
	m_Sprite->ChangeFrame(frame);
}

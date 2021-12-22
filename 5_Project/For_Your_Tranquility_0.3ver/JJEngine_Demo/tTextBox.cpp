#include "pch.h"
#include "tTextBox.h"


tTextBox::tTextBox()
{

}

tTextBox::~tTextBox()
{

}

void tTextBox::Initialize(JVector pos, PCWSTR objectName)
{
	tObject::Initialize(pos, objectName);

	//tResourceManager::GetInstance()->LoadScriptDataFile(m_ObjectName, m_Script.TextVec);

	JVector _size = { 1000, 400 };
	m_Transform->RectPos[JTransform::RIGHT_BOTTOM] = _size;
	m_Transform->Size = _size;
}

void tTextBox::Release()
{
	tObject::Release();
}

void tTextBox::Update(float dTime)
{
	m_Script.Update(dTime);
}

void tTextBox::Draw()
{
	/// 임시로 사각형을 그린다.
	JJEngine::GetInstance()->DrawRectangle(m_Transform->Pos.x, m_Transform->Pos.y, m_Transform->Pos.x + m_Transform->Size.x, m_Transform->Pos.y + m_Transform->Size.y);

	// 스크립트를 출력
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y + 20, m_Transform->Size.x, m_Transform->Size.y, m_Script);

	ShowDebug();
}

void tTextBox::ShowDebug()
{

}

void tTextBox::DrawNextText()
{
	m_Script.NextIndex();
}

void tTextBox::DrawAllNowText()
{
	m_Script.DrawAllNowText();
}

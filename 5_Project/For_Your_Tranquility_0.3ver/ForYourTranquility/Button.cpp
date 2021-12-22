#include "pch.h"

#include "MainOfficeScene.h"
#include "Button.h"
#include "ColliderBox.h"

Button::Button(UISortLayer layer, eNowSceneState state)
	:Object(layer), m_StateForClicked(state)
{
	
}

Button::Button(UISortLayer layer)
	:Object(layer), m_StateForClicked(eNowSceneState::NONE)
{

}

Button::Button(UISortLayer layer, eThirdChoiceState state)
	:Object(layer), m_ThirdChoiceState(state)
{

}

Button::Button(UISortLayer layer, eSecondChoiceState state)
	:Object(layer), m_SecondChoiceState(state)
{

}

Button::Button(UISortLayer layer, eFirstChoiceState state)
	:Object(layer), m_FirstChoiceState(state)
{

}

Button::~Button()
{

}

void Button::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);
}

void Button::Release()
{
	Object::Release();
}

void Button::Update(float dTime)
{
	// 부모에 있는 중점 업데이트 사용
	Object::Update(dTime);
}

void Button::Draw(float opacity/*=1.0f*/)
{
	if (m_SpriteVec.size() <= 0)
	{
// 		if (m_ColliderBox->IsCollided)
// 		{
// 			if (m_ColliderBox->IsClicked)
// 				JJEngine::GetInstance()->DrawFillRectangle(m_Transform->Pos.x, m_Transform->Pos.y, m_Transform->Pos.x + m_ColliderBox->SetTransform.Size.x, m_Transform->Pos.y + m_ColliderBox->SetTransform.Size.y, ColorF(ColorF::Pink, 0.2f));
// 			else
// 				JJEngine::GetInstance()->DrawFillRectangle(m_Transform->Pos.x, m_Transform->Pos.y, m_Transform->Pos.x + m_ColliderBox->SetTransform.Size.x, m_Transform->Pos.y + m_ColliderBox->SetTransform.Size.y, ColorF(ColorF::Blue, 0.2f));
// 		}
// 		else
// 		{
// 			JJEngine::GetInstance()->DrawFillRectangle(m_Transform->Pos.x, m_Transform->Pos.y, m_Transform->Pos.x + m_ColliderBox->SetTransform.Size.x, m_Transform->Pos.y + m_ColliderBox->SetTransform.Size.y, ColorF(ColorF::Black, 0.1f));
// 		}
	}
	else
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[m_SpriteIndex], m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void Button::ShowDebug()
{
	Object::ShowDebug();
}
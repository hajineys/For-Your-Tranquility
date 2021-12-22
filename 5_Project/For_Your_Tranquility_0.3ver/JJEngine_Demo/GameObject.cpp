#include "pch.h"

#include "GameObject.h"
#include "ResourceManager.h"

GameObject::GameObject()
	: m_SpriteSheet(nullptr)
	,m_MotionCount(0), m_MotionIndex(0)
{
	
}

GameObject::~GameObject()
{

}

void GameObject::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);

	// 애니메이션 정보 초기화
	ResourceManager::GetInstance()->LoadMotionDataFile(m_ObjectName, m_MotionVec);

	// 초기 애니메이션 설정
	m_MotionCount = m_MotionVec.size();

	// MotionVec 데이터가 있을 경우 애니메이션 O, 없을 경우 애니메이션 X
	if (m_MotionCount > 0)
	{
		m_NowMotion = m_MotionVec[m_MotionIndex];
	}
}

void GameObject::Release()
{
	Object::Release();
}

void GameObject::Update(float dTime)
{
	// 현재 모션이 무엇인가?
	m_NowMotion = m_MotionVec[m_MotionIndex];
}

void GameObject::Draw(float opacity/*=1.0f*/)
{
	JJEngine::GetInstance()->DrawSprite(m_SpriteSheet, m_NowMotion, m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void GameObject::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 800, L"x : %f", m_Transform->Pos.x);
	JJEngine::GetInstance()->DrawText(0, 840, L"y : %f", m_Transform->Pos.y);

	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 10, L"DrawIndex : %d", m_NowMotion->DrawIndex);
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 30, L"NowMotionFrame : %d", m_NowMotion->Frame);
}

void GameObject::UpdateAnimation(float dTime, float speed)
{
	// 모션 업데이트
	m_NowMotion->Update(dTime, speed);
}

void GameObject::PlayAnimation(float dTime, float speed)
{
	m_NowMotion->Play(dTime, speed);
}

void GameObject::SetSpriteSheet(PCWSTR uri)
{
	JJEngine::GetInstance()->LoadBitmapFromFile(uri, 0, 0, &m_SpriteSheet);
}

void GameObject::SetMotion()
{
	m_MotionIndex++;

	if (m_MotionIndex >= m_MotionCount)
	{
		m_MotionIndex = 0;
	}

	m_NowMotion = m_MotionVec[m_MotionIndex];
	m_NowMotion->Reset();
}

void GameObject::NextMotionFrame()
{
	m_NowMotion->NextMotionFrame();
}

void GameObject::ChangeMotionFrame(int frame)
{
	m_NowMotion->ChangeMotionFrame(frame);
}

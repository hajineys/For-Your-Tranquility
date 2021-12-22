#include "pch.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "JMotion.h"


GameObject::GameObject(UISortLayer layer)
	: Object(layer), m_SpriteSheet(nullptr)
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
	Object::Update(dTime);

	// 현재 모션이 무엇인가?
	if (m_MotionCount > 0)
		m_NowMotion = m_MotionVec[m_MotionIndex];
}

void GameObject::Draw(float opacity/*=1.0f*/)
{
	if (m_SpriteSheet != nullptr)
		JJEngine::GetInstance()->DrawSprite(m_SpriteSheet, m_NowMotion, m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	//ShowDebug();
}

void GameObject::ShowDebug()
{
	Object::ShowDebug();

	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 10, L"DrawIndex : %d", m_NowMotion->DrawIndex);
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 30, L"NowMotionFrame : %d", m_NowMotion->Frame);
}

void GameObject::UpdateAnimation(float dTime, float speed /*= 1.0f*/)
{
	// 모션 업데이트
	m_NowMotion->Update(dTime, speed);
}

bool GameObject::PlayAnimation(float dTime, float speed /*= 1.0f*/)
{
	m_NowMotion->Play(dTime, speed);
	return true;
}

void GameObject::SetSpriteSheet(CString name)
{
	m_SpriteSheet = ResourceManager::GetInstance()->GetMyImage(name);
}

void GameObject::NextMotion()
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
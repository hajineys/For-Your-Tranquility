#include "pch.h"

#include "tGameObject.h"
#include "ResourceManager.h"

tGameObject::tGameObject()
	: m_SpriteSheet(nullptr)
	,m_MotionCount(0), m_MotionIndex(0), m_PlayCount(0)
{
	
}

tGameObject::~tGameObject()
{

}

void tGameObject::Initialize(JVector pos, PCWSTR objectName)
{
	tObject::Initialize(pos, objectName);

	m_SpriteSheet = tResourceManager::GetInstance()->ImageFilesMap[m_ObjectName];

	// 애니메이션 정보 초기화
	tResourceManager::GetInstance()->LoadMotionDataFile(m_ObjectName, m_MotionVec);

	// 초기 애니메이션 설정
	m_MotionCount = m_MotionVec.size();

	// MotionVec 데이터가 있을 경우 애니메이션 O, 없을 경우 애니메이션 X
	if (m_MotionCount > 0)
	{
		m_NowMotion = m_MotionVec[m_MotionIndex];
	}
}

void tGameObject::Release()
{
	tObject::Release();
}

void tGameObject::Update(float dTime)
{
	// 현재 모션이 무엇인가?
	m_NowMotion = m_MotionVec[m_MotionIndex];
}

void tGameObject::Draw(float opacity/*=1.0f*/)
{
	JJEngine::GetInstance()->DrawSprite(m_SpriteSheet, m_NowMotion, m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void tGameObject::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 800, L"x : %f", m_Transform->Pos.x);
	JJEngine::GetInstance()->DrawText(0, 840, L"y : %f", m_Transform->Pos.y);

	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 10, L"DrawIndex : %d", m_NowMotion->DrawIndex);
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 30, L"NowMotionFrame : %d", m_NowMotion->Frame);
}

void tGameObject::UpdateAnimation(float dTime, float speed)
{
	// 모션 업데이트
	m_NowMotion->Update(dTime, speed);
}

void tGameObject::PlayAnimation(float dTime, float speed)
{
	m_NowMotion->Play(dTime, speed);
}

void tGameObject::SetSpriteSheet(PCWSTR uri)
{
	JJEngine::GetInstance()->LoadBitmapFromFile(uri, 0, 0, &m_SpriteSheet);
}

void tGameObject::SetMotion()
{
	m_MotionIndex++;

	if (m_MotionIndex >= m_MotionCount)
	{
		m_MotionIndex = 0;
	}

	m_NowMotion = m_MotionVec[m_MotionIndex];
	m_NowMotion->Reset();
}

void tGameObject::ResetMotion()
{
	m_PlayCount = 1;

	m_NowMotion = m_MotionVec[m_MotionIndex];
	m_NowMotion->Reset();
}

void tGameObject::NextMotionFrame()
{
	m_NowMotion->NextMotionFrame();
}

void tGameObject::ChangeMotionFrame(int frame)
{
	m_NowMotion->ChangeMotionFrame(frame);
}

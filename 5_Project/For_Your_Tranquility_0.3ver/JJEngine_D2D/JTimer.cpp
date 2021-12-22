#include "pch.h"

#include "JTimer.h"

JTimer::JTimer()
	: m_SecondsPerCount(0.0), m_DeltaCount(0), m_PreviousCount(0), m_CurrentCount(0)
	, m_DeltaTime(0), m_CountsPerSec(0)
{

}

JTimer::~JTimer()
{

}

float JTimer::GetDeltaTimeMS()
{
	m_DeltaTime = m_DeltaCount * m_SecondsPerCount;

	// 밀리세컨드로 변환
	return (float)m_DeltaTime * 1000.0f;
}

float JTimer::GetFPS()
{
	if (m_DeltaTime != 0)
	{
		return (float)(1.0 / m_DeltaTime);
	}
	return 0;
}

void JTimer::Initialize()
{
	// 카운터 체크. 1초당 몇 번을 세는 것인가?
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_CountsPerSec);

	// 1카운트당 몇 초나 걸리나?
	m_SecondsPerCount = 1.0 / (double)m_CountsPerSec;
}

void JTimer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentCount);

	// Time difference between this frame and the previous.
	m_DeltaCount = (m_CurrentCount - m_PreviousCount);

	// 카운트와 시간을 분리한다.
	m_DeltaTime = m_DeltaCount * m_SecondsPerCount;

	// Prepare for next frame.
	m_PreviousCount = m_CurrentCount;

	if (m_DeltaCount < 0)
	{
		m_DeltaCount = 0;
	}
}

void JTimer::Release()
{

}

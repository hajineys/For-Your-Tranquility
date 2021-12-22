#pragma once

class JTimer
{
private:
	__int64 m_CountsPerSec;
	double m_SecondsPerCount;

	__int64 m_PreviousCount;
	__int64 m_CurrentCount;
	__int64 m_DeltaCount;
	double m_DeltaTime;

public:
	JTimer();
	~JTimer();

	float GetDeltaTimeMS();
	float GetFPS();

	float GetDeltaTime() { return (float)m_DeltaTime; }
public:
	void Initialize();
	void Update();
	void Release();
};
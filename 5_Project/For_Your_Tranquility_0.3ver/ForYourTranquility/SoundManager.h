#pragma once
#include "fmod.h"

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

enum class SoundInfo
{
	None,
	Loop,
};

class JChannel
{
public:
	JChannel() : FmodChannel(nullptr), Volume(SOUND_DEFAULT), IsPlaying(false) {};
	~JChannel() {};

public:
	FMOD_CHANNEL* FmodChannel;
	float Volume;
	FMOD_BOOL IsPlaying;
};

/// <summary>
/// 사운드를 로드하고 관리하는 사운드 매니저
/// 2021.02.21
/// 라이브러리 제공 - 이우진, 손광익 / 수정, 업데이트 - 정종영
/// </summary>
class SoundManager
{
private:
	static SoundManager* m_Instance;
public:
	static SoundManager* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new SoundManager();
		}
		return m_Instance;
	}

private:
	SoundManager();
	~SoundManager();
	static FMOD_SYSTEM* FmodSoundSystem;
	
private:
	map<CString, FMOD_SOUND*> m_SoundFileMap;		// 사운드
	vector<JChannel*> m_ChannelVec;
	int m_ChannelCount;

public:
	void Initialize(int channelCount);
	void Release();

	void LoadSoundFile(CString folderPath);
	void CreateSound(PCSTR path, PCWSTR soundName, SoundInfo info);
	void CreateChannel();

	void Play(int channelNum, CString soundName);
	void Pause(int channelNum, CString soundName);
	void Resume(int channelNum, CString soundName);
	void Stop(int channelNum, CString soundName);
	void VolumeUp(int channelNum);
	void VolumeDown(int channelNum);
	void Update();

public:
	static void DeleteInstance()
	{
		if (m_Instance != nullptr)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
};

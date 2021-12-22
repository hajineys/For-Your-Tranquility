
#include "pch.h"
#include "SoundManager.h"

FMOD_SYSTEM* tSoundManager::g_sound_system;

tSoundManager* tSoundManager::m_instance = nullptr;

tSoundManager::tSoundManager(const char* path, bool loop)
	:m_bool(false)
{
	if (loop) {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
	}
	else {
		FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
	}

	m_channel = nullptr;
	m_volume = SOUND_DEFAULT;
}

tSoundManager::tSoundManager()
	:m_bool(false), m_channel(nullptr), m_volume(0), m_sound(nullptr)
{
	m_instance = GetInstance();

}

tSoundManager::~tSoundManager()
{
	FMOD_Sound_Release(m_sound);
	m_instance->FreeIntance();
}

int tSoundManager::Init() 
{
	FMOD_System_Create(&g_sound_system);
	FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, NULL);

	return 0;
}

int tSoundManager::Release() 
{
	FMOD_System_Close(g_sound_system);
	FMOD_System_Release(g_sound_system);

	return 0;
}


int tSoundManager::play() 
{
	FMOD_System_PlaySound(g_sound_system, m_sound, NULL, false, &m_channel);

	return 0;
}

int tSoundManager::pause() 
{
	FMOD_Channel_SetPaused(m_channel, true);

	return 0;
}

int tSoundManager::resume() 
{
	FMOD_Channel_SetPaused(m_channel, false);

	return 0;
}

int tSoundManager::stop() 
{
	FMOD_Channel_Stop(m_channel);

	return 0;
}

int tSoundManager::volumeUp() 
{
	if (m_volume < SOUND_MAX) 
	{
		m_volume += SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}

int tSoundManager::volumeDown() 
{
	if (m_volume > SOUND_MIN) 
	{
		m_volume -= SOUND_WEIGHT;
	}

	FMOD_Channel_SetVolume(m_channel, m_volume);

	return 0;
}


int tSoundManager::Update() 
{
	FMOD_Channel_IsPlaying(m_channel, &m_bool);

	if (m_bool) 
	{
		FMOD_System_Update(g_sound_system);
	}

	return 0;
}
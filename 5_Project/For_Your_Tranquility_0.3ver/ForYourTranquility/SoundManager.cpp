#include "pch.h"
#include "SoundManager.h"

FMOD_SYSTEM* SoundManager::FmodSoundSystem;

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
	:m_ChannelCount(0)
{

}

SoundManager::~SoundManager()
{
	// 사운드 파일들 모두 릴리즈
	for (auto it = m_SoundFileMap.begin(); it != m_SoundFileMap.end(); it++)
	{
		FMOD_Sound_Release(it->second);
	}

	m_Instance->DeleteInstance();
}

void SoundManager::Initialize(int channelCount)
{
	FMOD_System_Create(&FmodSoundSystem);
	FMOD_System_Init(FmodSoundSystem, 32, FMOD_INIT_NORMAL, NULL);

	m_ChannelCount = channelCount;

	// 채널을 생성해준다.
	for (int i = 0; i < m_ChannelCount; i++)
	{
		CreateChannel();
	}
}

void SoundManager::CreateChannel()
{
	JChannel* _channel = new JChannel();
	m_ChannelVec.push_back(_channel);
}

void SoundManager::Release()
{
	FMOD_System_Close(FmodSoundSystem);
	FMOD_System_Release(FmodSoundSystem);

// 	// 사운드를 지워준다.
// 	for (auto it = m_SoundFileMap.begin(); it != m_SoundFileMap.end(); it++)
// 	{
// 		FMOD_SOUND* _deleteObject = it->second;
// 
// 		FMOD_Sound_Release(_deleteObject);
// 		_deleteObject = nullptr;
// 	}
// 
// 	// 채널을 삭제한다.
// 	for (int i = 0; i < m_ChannelCount; i++)
// 	{
// 		delete m_ChannelVec[i];
// 		m_ChannelVec[i] = nullptr;
// 	}
// 
// 	DeleteInstance();
}

void SoundManager::LoadSoundFile(CString folderPath)
{
	CFileFind _file;

	BOOL _isOpen = _file.FindFile(folderPath + _T("\\*.*"));
	CString _fileFilter = ".WAV";

	CString _filePath, _fileExt, _fileName;

	while (_isOpen)
	{
		_isOpen = _file.FindNextFile();

		if (_file.IsDirectory() && !_file.IsDots())			// 디렉토리 발견시 
		{
			_filePath = _file.GetFilePath();

			LoadSoundFile(_filePath);						// 하위폴더를 검색하기 위해 재귀호출 발생  
		}

		_filePath = _file.GetFilePath();
		_fileExt = _filePath.Mid(_filePath.ReverseFind('.'));		// 확장자만 추출한다. 
		_fileExt.MakeUpper();										// 대문자화한다.

		if (!_file.IsDots() && _fileExt == _fileFilter)				// 파일 탐색 필터 정의에따라 해당 StringList에 추가
		{
			// 파일의 경로
			string _filePathStr = ResourceManager::CStrToStr(_filePath);

			// 파일의 이름
			_fileName = _file.GetFileName();
			// 확장자는 제거
			_fileName.Delete(_fileName.GetLength() - 4, 4);
			wstring _fileNameStr = ResourceManager::CStrToWStr(_fileName);

			// FMOD 사운드 파일 생성
			// BGM인지(Loop할 것인지) 체크
			wstring _fileAttr;
			wstring _IsBGM = L"BGM";
			_fileAttr = _fileNameStr.substr(0, 3);

			if (_file.IsDirectory()) continue;						// 폴더만 남는 경우는 넣으면 안됨

			// 사운드 파일을 생성하고 map에 넣는다.
			if (_fileAttr == _IsBGM)
				CreateSound(_filePathStr.c_str(), _fileNameStr.c_str(), SoundInfo::Loop);
			else
				CreateSound(_filePathStr.c_str(), _fileNameStr.c_str(), SoundInfo::None);
		}
	}
}

void SoundManager::CreateSound(PCSTR path, PCWSTR soundName, SoundInfo info)
{
	FMOD_SOUND* _newSound;

	if (info == SoundInfo::Loop)
	{
		FMOD_System_CreateSound(FmodSoundSystem, path, FMOD_LOOP_NORMAL, 0, &_newSound);
	}
	else
	{
		FMOD_System_CreateSound(FmodSoundSystem, path, FMOD_LOOP_OFF, 0, &_newSound);
	}

	if (_newSound != nullptr)
		m_SoundFileMap[soundName] = _newSound;
}

void SoundManager::Play(int channelNum, CString soundName)
{
	if (channelNum < m_ChannelVec.size())
		FMOD_System_PlaySound(FmodSoundSystem, m_SoundFileMap[soundName], NULL, false, &m_ChannelVec[channelNum]->FmodChannel);
}

void SoundManager::Pause(int channelNum, CString soundName)
{
	if (channelNum < m_ChannelVec.size())
		FMOD_Channel_SetPaused(m_ChannelVec[channelNum]->FmodChannel, true);
}

void SoundManager::Resume(int channelNum, CString soundName)
{
	if (channelNum < m_ChannelVec.size())
		FMOD_Channel_SetPaused(m_ChannelVec[channelNum]->FmodChannel, false);
}

void SoundManager::Stop(int channelNum, CString soundName)
{
	if (channelNum < m_ChannelVec.size())
		FMOD_Channel_Stop(m_ChannelVec[channelNum]->FmodChannel);
}

void SoundManager::VolumeUp(int channelNum)
{
	if (channelNum < m_ChannelVec.size())
	{
			m_ChannelVec[channelNum]->Volume = SOUND_DEFAULT;

		FMOD_Channel_SetVolume(m_ChannelVec[channelNum]->FmodChannel, m_ChannelVec[channelNum]->Volume);
	}
}

void SoundManager::VolumeDown(int channelNum)
{
	if (channelNum < m_ChannelVec.size())
	{
		if (m_ChannelVec[channelNum]->Volume > SOUND_MIN)
		{
			m_ChannelVec[channelNum]->Volume = SOUND_MIN;
		}

		FMOD_Channel_SetVolume(m_ChannelVec[channelNum]->FmodChannel, m_ChannelVec[channelNum]->Volume);
	}
}

void SoundManager::Update()
{
	// 채널이 플레이 중일 경우만 해당 채널을 업데이트해준다.
	for (int i = 0; i < m_ChannelVec.size(); i++)
	{
		FMOD_Channel_IsPlaying(m_ChannelVec[i]->FmodChannel, &m_ChannelVec[i]->IsPlaying);

		if (m_ChannelVec[i]->IsPlaying)
		{
			FMOD_System_Update(FmodSoundSystem);
		}
	}
}
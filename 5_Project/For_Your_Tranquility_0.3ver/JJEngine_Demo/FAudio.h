#pragma once

/*
#ifndef _CSOUND_H_
#define _CSOUND_H_

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

/// <summary>
/// 
/// FMOD용 사운드 매니저이다.
/// 채널 마다 재생되는 사운드를 하나씩 넣는다고 보면된다
/// 그렇다고 하나의 소리만 들리지는않는다 최대 몇개까지는 모르겠지만 8~12개사이 같다.
/// 채널 1 사운드 1 최대중첩 8~12개로 예상된다.
/// 
/// 다양한 효과를 더 넣을거면 추가로 넣을수 있도록하자.
/// </summary>
class FAudio 
{
	//FMOD::MAPPING
public:
	static FMOD_SYSTEM* m_sound_system;

	FMOD_BOOL m_FBool;

public:
	FAudio();
	//단일로 실행할 기본 생성자입니다. (기본 예시)
	~FAudio();
public:
	//FMOD::API
	FMOD::System* m_System;
	std::map<std::wstring, FMOD::Sound*> m_AudioMap;
	std::map<FMOD::Sound*, FMOD::Channel*> m_ChannelMap;
	std::vector<char*> m_PathList;
	FMOD_RESULT m_Result;
	bool m_FMBool;
	unsigned int m_FVolume;
	//싱글사운드용 채널
	FMOD::Channel* m_pSingleSoundCh;

	enum class SOUND_PLAY
	{
		PLAY,
		STOP,
		PAUSE,			//일시정지
		RESUME,			//일시정지된 상태에서 재시작
		VOLUME_SET,     //볼륨값을 기본으로 초기화함
		VOLUME_MIN,
		VOLUME_MAX,
		FREQUENCY_SET,    //기본 Frequency값 설정
		FREQUENCY_UP,	 //Frequency는 높을수록 가속																																				
		FREQUENCY_DOWN,	 //				낮을수록 감속 0 이후로(역재생 가능)																																			
	};
	
	* FMOD_RESULT m_Result;
	함수가 성공하면 반환 값은 FMOD_OK 입니다.
	함수가 실패하면 반환 값은 FMOD_RESULT 열거에 정의 된 값 중 하나가 됩니다.



	unsigned int m_Version;
	//FMOD 시스템을 만들어주는 함수 
	bool FCreate();
	//만들어진 시스템을 초기화 해주는함수
	bool FInit();
	//사운드를 만들어주는함수이다.
	//사용법 : 현재 이름의 사운드 등록한다
	//기본 경로는 ../../Resource/Sound/이다
	bool FCreateSound(std::wstring _name,bool _loop, FMOD::Sound** _sonund);
	//사운드를 추가해주는 함수이다. //함수이름만 입력하면된다.
	bool FAddSound(std::wstring, bool _loop);
	//현재 이름의 사운드를 재생
	bool FPlaySound(std::wstring _path);
	//종료시 제거 작업 함수
	bool FRelease();
	//등록된 파일 전부재생
	bool FSoundAllPlay(bool _start);
	//FMOD_RESULT 결과에서 메세지를 출력해주는 함수.
	bool SucceededOrWarn(const std::string& message, FMOD_RESULT result);
	//현재 이름의 사운드를 정지
	bool FStop(std::wstring _path);
	//현재 이름의 사운드를 재시작
	bool FPause(std::wstring _path);
	//현재 이름의 사운드를 재시작
	bool FResume(std::wstring _path);
	//FMod반복 재생파일 위한 업데이트 함수이다
	bool FUpdate();
	//파일 찾고 그 기능을 실행할 함수
	bool FFindChannel(std::map<std::wstring, FMOD::Sound*>& _inAudio, std::map<FMOD::Sound*, FMOD::Channel*>& _inMap, std::wstring& _path , SOUND_PLAY _Set);
	//map<FMOD::Sound*, FMOD::Channel*> 타입을 검사하는 함수
	bool FCheckAudio(std::map<FMOD::Sound*, FMOD::Channel*>& _CheckMap, FMOD::Sound* const& _Sndptr);
	//FMOD::Channel*타입을 검사하는 함수
	bool FCheckChannel(FMOD::Channel** _Chennel);
	//FMOD::Sound*타입을 검사하는 함수
	bool FCheckSound(FMOD::Sound** _Sound);
	//파일 찾고 음량을 조절하는 함수
	bool FSetVolume(std::wstring _path);
	//채널의 주파수 또는 재생 속도를 HZ 단위로 설정하는 함수이다.
	//기본Set함수는 아무숫자나 넣어도됨.
	bool FSetFrequency(std::wstring _path);
	bool FSetFrequencyUP(std::wstring _path);
	bool FSetFrequencyDown(std::wstring _path);
	//--------------------------------------
	//기타등등 이펙트 추가시 작업할 공간



	//wchar형 문자열을 multibyte형태 문자열로 바꿔주는 함수이다.
	LPSTR WidetoMulti_FormatTxt(const wchar_t* _msg);
};

#endif

//FMOD 함수 위주, define위주가 있다
//
*/
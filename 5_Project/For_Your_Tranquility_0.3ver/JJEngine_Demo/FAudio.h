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
/// FMOD�� ���� �Ŵ����̴�.
/// ä�� ���� ����Ǵ� ���带 �ϳ��� �ִ´ٰ� ����ȴ�
/// �׷��ٰ� �ϳ��� �Ҹ��� �鸮���¾ʴ´� �ִ� ������� �𸣰����� 8~12������ ����.
/// ä�� 1 ���� 1 �ִ���ø 8~12���� ����ȴ�.
/// 
/// �پ��� ȿ���� �� �����Ÿ� �߰��� ������ �ֵ�������.
/// </summary>
class FAudio 
{
	//FMOD::MAPPING
public:
	static FMOD_SYSTEM* m_sound_system;

	FMOD_BOOL m_FBool;

public:
	FAudio();
	//���Ϸ� ������ �⺻ �������Դϴ�. (�⺻ ����)
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
	//�̱ۻ���� ä��
	FMOD::Channel* m_pSingleSoundCh;

	enum class SOUND_PLAY
	{
		PLAY,
		STOP,
		PAUSE,			//�Ͻ�����
		RESUME,			//�Ͻ������� ���¿��� �����
		VOLUME_SET,     //�������� �⺻���� �ʱ�ȭ��
		VOLUME_MIN,
		VOLUME_MAX,
		FREQUENCY_SET,    //�⺻ Frequency�� ����
		FREQUENCY_UP,	 //Frequency�� �������� ����																																				
		FREQUENCY_DOWN,	 //				�������� ���� 0 ���ķ�(����� ����)																																			
	};
	
	* FMOD_RESULT m_Result;
	�Լ��� �����ϸ� ��ȯ ���� FMOD_OK �Դϴ�.
	�Լ��� �����ϸ� ��ȯ ���� FMOD_RESULT ���ſ� ���� �� �� �� �ϳ��� �˴ϴ�.



	unsigned int m_Version;
	//FMOD �ý����� ������ִ� �Լ� 
	bool FCreate();
	//������� �ý����� �ʱ�ȭ ���ִ��Լ�
	bool FInit();
	//���带 ������ִ��Լ��̴�.
	//���� : ���� �̸��� ���� ����Ѵ�
	//�⺻ ��δ� ../../Resource/Sound/�̴�
	bool FCreateSound(std::wstring _name,bool _loop, FMOD::Sound** _sonund);
	//���带 �߰����ִ� �Լ��̴�. //�Լ��̸��� �Է��ϸ�ȴ�.
	bool FAddSound(std::wstring, bool _loop);
	//���� �̸��� ���带 ���
	bool FPlaySound(std::wstring _path);
	//����� ���� �۾� �Լ�
	bool FRelease();
	//��ϵ� ���� �������
	bool FSoundAllPlay(bool _start);
	//FMOD_RESULT ������� �޼����� ������ִ� �Լ�.
	bool SucceededOrWarn(const std::string& message, FMOD_RESULT result);
	//���� �̸��� ���带 ����
	bool FStop(std::wstring _path);
	//���� �̸��� ���带 �����
	bool FPause(std::wstring _path);
	//���� �̸��� ���带 �����
	bool FResume(std::wstring _path);
	//FMod�ݺ� ������� ���� ������Ʈ �Լ��̴�
	bool FUpdate();
	//���� ã�� �� ����� ������ �Լ�
	bool FFindChannel(std::map<std::wstring, FMOD::Sound*>& _inAudio, std::map<FMOD::Sound*, FMOD::Channel*>& _inMap, std::wstring& _path , SOUND_PLAY _Set);
	//map<FMOD::Sound*, FMOD::Channel*> Ÿ���� �˻��ϴ� �Լ�
	bool FCheckAudio(std::map<FMOD::Sound*, FMOD::Channel*>& _CheckMap, FMOD::Sound* const& _Sndptr);
	//FMOD::Channel*Ÿ���� �˻��ϴ� �Լ�
	bool FCheckChannel(FMOD::Channel** _Chennel);
	//FMOD::Sound*Ÿ���� �˻��ϴ� �Լ�
	bool FCheckSound(FMOD::Sound** _Sound);
	//���� ã�� ������ �����ϴ� �Լ�
	bool FSetVolume(std::wstring _path);
	//ä���� ���ļ� �Ǵ� ��� �ӵ��� HZ ������ �����ϴ� �Լ��̴�.
	//�⺻Set�Լ��� �ƹ����ڳ� �־��.
	bool FSetFrequency(std::wstring _path);
	bool FSetFrequencyUP(std::wstring _path);
	bool FSetFrequencyDown(std::wstring _path);
	//--------------------------------------
	//��Ÿ��� ����Ʈ �߰��� �۾��� ����



	//wchar�� ���ڿ��� multibyte���� ���ڿ��� �ٲ��ִ� �Լ��̴�.
	LPSTR WidetoMulti_FormatTxt(const wchar_t* _msg);
};

#endif

//FMOD �Լ� ����, define���ְ� �ִ�
//
*/
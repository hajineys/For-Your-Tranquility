#pragma once

#include "JMotion.h"

enum ObjectName
{
	Player
};

class JJEngine;

class tResourceManager
{
private:
	tResourceManager();
	~tResourceManager();

private:
	JJEngine* m_pJJEngine;
	static tResourceManager* m_pInstance;

public:
	vector<FMOD_SOUND*>	SoundFiles;

	vector<ID2D1Bitmap*> ImageFiles;
	map<CString, ID2D1Bitmap*> ImageFilesMap;

public:
	static tResourceManager* GetInstance();

	static wstring CStrToWStr(CString Cstr);
	static string CStrToStr(CString Cstr);

public:
	void Initialize(JJEngine* pJJEngine);
	void Release();

	void LoadSoundFile(CString folderPath);
	void LoadImageFile(CString folderPath);
	bool LoadMotionDataFile(CString objectName, vector<JMotion*>& motionVec);
	bool LoadScriptDataFile(CString sceneName, vector<wstring>& textVec);
};
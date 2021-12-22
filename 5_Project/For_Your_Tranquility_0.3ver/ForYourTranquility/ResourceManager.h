#pragma once

/// <summary>
/// ���ҽ� �̹����� �ҷ����� �����ϴ� ���ҽ� �Ŵ���
/// 2021.02.16
/// ������
/// </summary>
class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* m_Instance;

private:
	map<CString, ID2D1Bitmap*> m_ImageFileMap;

public:
	static ResourceManager* GetInstance();

	static wstring CStrToWStr(CString Cstr);
	static string CStrToStr(CString Cstr);

public:
	void Initialize();
	void Release();
	void DeleteInstance();

	void LoadImageFile(CString folderPath);

	ID2D1Bitmap* GetMyImage(CString objectName) { return m_ImageFileMap[objectName]; }

	bool LoadMotionDataFile(CString objectName, vector<JMotion*>& motionVec);
	bool LoadScriptDataFile(CString sceneName, vector<JText>& textVec);
};
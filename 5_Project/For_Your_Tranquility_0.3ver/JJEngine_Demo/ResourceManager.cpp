#include "pch.h"

#include <io.h>
#include "../Json/json.h"

#include <locale>
#include <codecvt>

#include <filesystem>
#include <fstream>

#include "ResourceManager.h"

// static 멤버 변수 초기화
tResourceManager* tResourceManager::m_pInstance = nullptr;

tResourceManager::tResourceManager()
{

}

tResourceManager::~tResourceManager()
{

}

tResourceManager* tResourceManager::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new tResourceManager;
	}

	return m_pInstance;
}

wstring tResourceManager::CStrToWStr(CString Cstr)
{
	wstring _returnStr;

	for (int i = 0; i < Cstr.GetLength(); i++)
	{
		wchar_t _char = Cstr[i];
		_returnStr += _char;
	}

	return _returnStr;
}

string tResourceManager::CStrToStr(CString Cstr)
{
	string _returnStr;

	for (int i = 0; i < Cstr.GetLength(); i++)
	{
		wchar_t _char = Cstr[i];
		_returnStr += _char;
	}

	return _returnStr;
}

void tResourceManager::Initialize(JJEngine* pJJEngine)
{
	m_pJJEngine = pJJEngine;
}

void tResourceManager::Release()
{

}

void tResourceManager::LoadSoundFile(CString folderPath)
{
	CFileFind _file;

	BOOL _isOpen = _file.FindFile(folderPath + _T("\\*.*"));
	CString _fileFilter = ".PNG";

	CString _FilePath, _fileExt, _fileName;

	while (_isOpen)
	{
		_isOpen = _file.FindNextFile();

		if (_file.IsDirectory() && !_file.IsDots())			// 디렉토리 발견시 
		{
			_FilePath = _file.GetFilePath();

			LoadImageFile(_FilePath);						// 하위폴더를 검색하기 위해 재귀호출 발생  
		}

		_FilePath = _file.GetFilePath();
		_fileExt = _FilePath.Mid(_FilePath.ReverseFind('.'));		// 확장자만 추출한다. 
		_fileExt.MakeUpper();										// 대문자화한다.

		if (!_file.IsDots() && _fileExt == _fileFilter)				// 파일 탐색 필터 정의에따라 해당 StringList에 추가
		{
			wstring filePathStr = CStrToWStr(_FilePath);
			_fileName = _file.GetFileName();
			_fileName.Delete(_fileName.GetLength() - 4, 4);

			// 비트맵을 로드
			ID2D1Bitmap* _bitmap;
			JJEngine::GetInstance()->LoadBitmapFromFile(filePathStr.c_str(), 0, 0, &_bitmap);

			if (_file.IsDirectory()) continue;						// 폴더만 남는 경우는 넣으면 안됨

			// 파일이름과 그에 맞는 비트맵을 넣는다.
			ImageFilesMap[_fileName] = _bitmap;
		}
	}
}

void tResourceManager::LoadImageFile(CString folderPath)
{
	CFileFind _file;

	BOOL _isOpen = _file.FindFile(folderPath + _T("\\*.*"));
	CString _fileFilter = ".PNG";

	CString _FilePath, _fileExt, _fileName;

	while (_isOpen)
	{
		_isOpen = _file.FindNextFile();

		if (_file.IsDirectory() && !_file.IsDots())			// 디렉토리 발견시 
		{
			_FilePath = _file.GetFilePath();

			LoadImageFile(_FilePath);						// 하위폴더를 검색하기 위해 재귀호출 발생  
		}

		_FilePath = _file.GetFilePath();
		_fileExt = _FilePath.Mid(_FilePath.ReverseFind('.'));		// 확장자만 추출한다. 
		_fileExt.MakeUpper();										// 대문자화한다.
		
		if (!_file.IsDots() && _fileExt == _fileFilter)				// 파일 탐색 필터 정의에따라 해당 StringList에 추가
		{
			wstring filePathStr = CStrToWStr(_FilePath);
			_fileName = _file.GetFileName();
			_fileName.Delete(_fileName.GetLength() - 4, 4);

			// 비트맵을 로드
			ID2D1Bitmap* _bitmap;
			JJEngine::GetInstance()->LoadBitmapFromFile(filePathStr.c_str(), 0, 0, &_bitmap);

			if (_file.IsDirectory()) continue;						// 폴더만 남는 경우는 넣으면 안됨

			// 파일이름과 그에 맞는 비트맵을 넣는다.
			ImageFilesMap[_fileName] = _bitmap;
		}
	}
}

bool tResourceManager::LoadMotionDataFile(CString objectName, vector<JMotion*>& motionVec)
{
	// 파일 읽기 모드로 OPEN
	CString filePath = _T("../../Data/Sprite/");
	filePath += objectName;
	filePath += _T(".txt");

	CFile file;
	if (!file.Open(filePath, CFile::modeRead))
	{
		wstring _objectName = CStrToWStr(objectName);

		LPSTR _objectNameChar = Debug::WidetoMulti_FormatTxt(_objectName.c_str());
 		Debug::LogFormat("%s : Motion Data 파일 로드 실패!", _objectNameChar);
		
		return false;
	}

	CString fileName = file.GetFileName();

	// 파일을 역직렬화 지정
	CArchive ar(&file, CArchive::load);
	int _motionListSize;
	ar >> _motionListSize;

	for (int i = 0; i < _motionListSize; i++)
	{
		JMotion* _motion = new JMotion();

		ar >> _motion->ObjectName;
		ar >> _motion->Name;
		ar >> _motion->Frame;

		CArray<JSprite> _spriteArr;
		_spriteArr.Serialize(ar);

		for (int i = 0; i < _spriteArr.GetSize(); i++)
		{
			_motion->SpriteVec.push_back(_spriteArr[i]);
		}

		motionVec.push_back(_motion);
	}

	ar.Close();
	file.Close();

	return true;
}

bool tResourceManager::LoadScriptDataFile(CString sceneName, vector<wstring>& textVec)
{
	vector<string> _textVec;

	Json::Value _loadJsonData;

	string _loadPath = "../../Data/Script/";
	_loadPath += CStrToStr(sceneName);
	_loadPath += ".json";

	ifstream _loadFile;

	_loadFile.open(_loadPath, ifstream::in | ifstream::binary);

	if (!_loadFile.good())
	{
		wstring _sceneName = CStrToWStr(sceneName);

		LPSTR _sceneNameChar = Debug::WidetoMulti_FormatTxt(_sceneName.c_str());
		Debug::LogFormat("%s : Script File 로드 실패!", _sceneNameChar);

		return false;
	}
	_loadFile >> _loadJsonData;
	_loadFile.close();

	Json::ValueIterator _loadDataIter = _loadJsonData.begin();
	for (; _loadDataIter != _loadJsonData.end(); _loadDataIter++)
	{
		string _data = (*_loadDataIter).asString();
		_textVec.push_back(_data);
	}

	// string To wstring
	for (int i = 0; i < _textVec.size(); i++)
	{
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convertString;
		wstring wStr = convertString.from_bytes(_textVec[i]);

		textVec.push_back(wStr);
	}

	return true;
}

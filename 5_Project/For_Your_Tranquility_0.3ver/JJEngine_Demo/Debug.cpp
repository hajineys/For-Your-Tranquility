#include "pch.h"
#include "Debug.h"
using namespace std;

/// <summary>
/// 디버깅 클래스입니다
/// 이 클래스는 해당객체에 대한 어떠한 정보를 표시하기 위해
/// 만들었으며 주로 컴파일 디버깅으로 확인하는데 애매할때
/// 사용하면 좋겠다 싶어 만들었습니다
/// </summary>

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(const char* _msg)
{
	//문자열의 길이를 정수로 받습니다
	size_t newSize = strlen(_msg) + 1;
	//wchar*형으로 동적으로 생성해줍니다.
	wchar_t* wmsg = new wchar_t[newSize];

	size_t convertChars;

	//멀티바이트의 문자열을 wchar문자열로 바꿔주는함수.
	//convertChars = 변환한 문자열 개수를 담을버퍼
	//wmsg = 변환한 유니코드 문자열 저장할 버퍼
	//newSize = 버퍼의 크기
	//마지막 인자 = 변환할 버퍼의 최대개수
	mbstowcs_s(&convertChars, wmsg, newSize, _msg, _TRUNCATE);

	wcout << wmsg << endl;
}

void Debug::LogFormat(const char* _msg, ...)
{
	//불특정 가변인자를 사용할때 메세지를 받는 구조입니다
	
	va_list ap;
	va_start(ap, _msg);

	char* buffer = new char[256];
	//vsprint에 들어온 문자열의 수를 반환합니다
	vsprintf_s(buffer, 256, _msg, ap);
	va_end(ap);

	//변환한 문자열의 사이즈
	size_t convertChars;
	wchar_t* wmsg = new wchar_t[256];
	//멀티바이트의 문자열을 wchar문자열로 바꿔주는함수.
	//len의 길이만큼 문자열wmsg를 읽어들여서 buffer에 저장합니다.
	mbstowcs_s(&convertChars, wmsg, 256, buffer, _TRUNCATE);

	//수만큼 버퍼를 동적 생성해줍니다
	size_t size = 256;

	//버퍼의 내용을 출력합니다.
	wcout << wmsg << endl;

	delete[] buffer;
	buffer = nullptr;
}

void Debug::LogError(const char* _msg)
{

}

LPSTR Debug::WidetoMulti_FormatTxt(const wchar_t* _msg)
{
	int strSize = WideCharToMultiByte(CP_ACP, 0, _msg, -1, NULL, 0, NULL, NULL) + 1;
	LPSTR _tempChar = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, _msg, -1, _tempChar, strSize, 0, 0);

	return _tempChar;
}
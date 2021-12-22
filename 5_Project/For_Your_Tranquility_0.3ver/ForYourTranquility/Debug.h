#pragma once

using namespace std;
/// <summary>
/// 콘솔창에서 
/// 로그를 출력해주는 클래스입니다.
/// </summary>
class Debug
{
public:
	Debug();
	~Debug();

public:
	//스태틱으로 전역함수로 설정
	//일반적인 문자열 출력합니다
	static void Log(const char* _msg);
	//해당 로그에 대한 표시 정보를 표시를 가변인자로 받을때 사용합니다.
	static void LogFormat(const char* _msg, ...);

	static LPSTR WidetoMulti_FormatTxt(const wchar_t* _msg);
};
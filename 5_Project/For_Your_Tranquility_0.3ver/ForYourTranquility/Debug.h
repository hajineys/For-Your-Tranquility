#pragma once

using namespace std;
/// <summary>
/// �ܼ�â���� 
/// �α׸� ������ִ� Ŭ�����Դϴ�.
/// </summary>
class Debug
{
public:
	Debug();
	~Debug();

public:
	//����ƽ���� �����Լ��� ����
	//�Ϲ����� ���ڿ� ����մϴ�
	static void Log(const char* _msg);
	//�ش� �α׿� ���� ǥ�� ������ ǥ�ø� �������ڷ� ������ ����մϴ�.
	static void LogFormat(const char* _msg, ...);

	static LPSTR WidetoMulti_FormatTxt(const wchar_t* _msg);
};
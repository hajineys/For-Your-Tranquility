#include "pch.h"
#include "Debug.h"
using namespace std;

/// <summary>
/// ����� Ŭ�����Դϴ�
/// �� Ŭ������ �ش簴ü�� ���� ��� ������ ǥ���ϱ� ����
/// ��������� �ַ� ������ ��������� Ȯ���ϴµ� �ָ��Ҷ�
/// ����ϸ� ���ڴ� �;� ��������ϴ�
/// </summary>

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Log(const char* _msg)
{
	//���ڿ��� ���̸� ������ �޽��ϴ�
	size_t newSize = strlen(_msg) + 1;
	//wchar*������ �������� �������ݴϴ�.
	wchar_t* wmsg = new wchar_t[newSize];

	size_t convertChars;

	//��Ƽ����Ʈ�� ���ڿ��� wchar���ڿ��� �ٲ��ִ��Լ�.
	//convertChars = ��ȯ�� ���ڿ� ������ ��������
	//wmsg = ��ȯ�� �����ڵ� ���ڿ� ������ ����
	//newSize = ������ ũ��
	//������ ���� = ��ȯ�� ������ �ִ밳��
	mbstowcs_s(&convertChars, wmsg, newSize, _msg, _TRUNCATE);

	wcout << wmsg << endl;
}

void Debug::LogFormat(const char* _msg, ...)
{
	//��Ư�� �������ڸ� ����Ҷ� �޼����� �޴� �����Դϴ�
	
	va_list ap;
	va_start(ap, _msg);

	char* buffer = new char[256];
	//vsprint�� ���� ���ڿ��� ���� ��ȯ�մϴ�
	vsprintf_s(buffer, 256, _msg, ap);
	va_end(ap);

	//��ȯ�� ���ڿ��� ������
	size_t convertChars;
	wchar_t* wmsg = new wchar_t[256];
	//��Ƽ����Ʈ�� ���ڿ��� wchar���ڿ��� �ٲ��ִ��Լ�.
	//len�� ���̸�ŭ ���ڿ�wmsg�� �о�鿩�� buffer�� �����մϴ�.
	mbstowcs_s(&convertChars, wmsg, 256, buffer, _TRUNCATE);

	//����ŭ ���۸� ���� �������ݴϴ�
	size_t size = 256;

	//������ ������ ����մϴ�.
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
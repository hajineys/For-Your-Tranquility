#pragma once

using namespace std;
/// <summary>
/// �ܼ�â���� 
/// �α׸� ������ִ� Ŭ�����Դϴ�.
/// �׸��� �Լ��� �����Դϴ�.
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
	static void LogFormat(const char* _msg,...);
	//������ ǥ�õǴ� ���ڿ��� ����մϴ� . 
	static void LogError(const char* _msg);


	static LPSTR WidetoMulti_FormatTxt(const wchar_t* _msg);
	//�α׿� ���� ������ �׸��� ����մϴ�.
	//static void DrawLine(Vector2 _start,Vector2 _end, D2D1_COLOR_F _color,float _duration);

};


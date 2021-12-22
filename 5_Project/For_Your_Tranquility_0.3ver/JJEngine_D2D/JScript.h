#pragma once

/// <summary>
/// �� �ϴ� �ι� ������ ��縦 ���� �ִ� Ŭ����
/// 2021.02.22
/// ������
/// </summary>
class JText
{
public:
	wstring Speaker;
	wstring Text;
};

/// <summary>
/// ��ũ��Ʈ�� ����ϱ� ���� Ŭ����
/// 2021.02.15
/// ������
/// </summary>
class JScript
{
public:
	vector<JText> TextVec;

	wstring NowSpeacker;
	wstring NowText;

	int NowTextIndex;
	bool IsNowTextEnd;

	bool IsAllTextEnd;

	int DrawIndex;
	float DrawTime;

	int DrawCount;		// �� �� ��ο� �� ������

	bool IsSpace;		// �������� �ƴ���

public:
	JScript();
	~JScript() {};

public:
	void NextIndex();
	void DrawAllNowText();
	void ChangeText(int index);
	wstring GetText(int index);
	wstring GetSpeaker(int index);
	void Reset();
	void Update(float dTime, float speed = 1.0f);
};


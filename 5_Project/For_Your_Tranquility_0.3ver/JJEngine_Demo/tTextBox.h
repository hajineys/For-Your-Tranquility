#pragma once

#include "tObject.h"
#include "JScript.h"

/// <summary>
/// ���� ���ǰ� �ؽ�Ʈ�� ����� ��ȭ����
/// 2021.02.16
/// ������
/// </summary>
class tTextBox : public tObject
{
protected:
	JScript m_Script;

public:
	tTextBox();
	~tTextBox();

	bool IsNowTextEnd() { return m_Script.IsNowTextEnd; }

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime);
	virtual void Draw();
	virtual void ShowDebug();

	void DrawNextText();
	void DrawAllNowText();
};
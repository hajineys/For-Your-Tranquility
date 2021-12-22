#pragma once

#include "tObject.h"
#include "JScript.h"

/// <summary>
/// 씬에 사용되고 텍스트를 출력할 대화상자
/// 2021.02.16
/// 정종영
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
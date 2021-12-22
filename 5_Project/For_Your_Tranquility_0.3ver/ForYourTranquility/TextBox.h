#pragma once

#include "Object.h"
#include "JScript.h"
#include "IntroAnimationScene.h"

enum IsHighlight
{
	None,
	Highlight
};

/// <summary>
/// ���� ���ǰ� �ؽ�Ʈ�� ����� ��ȭ����
/// 2021.02.16
/// ������
/// </summary>
class TextBox : public Object
{
protected:
	JScript m_Script;
	vector<JImage*> m_CharacterSpriteVec;	// ĳ���� �̹��� ����
	vector<wstring> m_SpeakerImageNameVec;	// ĳ���� �̸� ����
	bool m_NowState;

	int m_EventStartIndex;
	int m_EventEndIndex;

	bool m_IsTextDrawingNow;

	int m_PrevScriptNowTextIndex;

	JVector m_MonkeyPos;
	bool IsCopOut;
	bool IsTranslate;

public:
	TextBox(UISortLayer layer);
	virtual ~TextBox();

	bool IsNowTextEnd() { return m_Script.IsNowTextEnd; }
	bool IsAllTextEnd() { return m_Script.IsAllTextEnd; }
	int GetKeyIndex() { return m_Script.DrawIndex; }
	void SetKeyIndex(int value) { m_Script.DrawIndex = value; }
	bool GetState() { return m_NowState; }
	int GetScriptTextCount() { return m_Script.TextVec.size() - 1; }

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Release();

	virtual void Update(float dTime, float speed = 1.0f);
	virtual void Draw(float opacity = 0.95f);
	virtual void ShowDebug();

	void DrawNextText();
	void DrawAllNowText();

	void AddCharacterSprite(CString additionalName, int frame);
	void SetStartEndIndex(int start, int end);
	void DrawCharacter(bool isElderFlipX, float opacity = 1.0f);

	wstring GetText(int index);
	wstring GetSpeaker(int index);

	bool IsStartEndIndex();

	void On();
	void Off();

	void Reset();
};
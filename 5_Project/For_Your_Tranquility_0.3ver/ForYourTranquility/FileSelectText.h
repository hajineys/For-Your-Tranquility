#pragma once

#include "Button.h"
#include "TextBox.h"
#include "JScript.h"

/// <summary>
/// ���Ͼȿ��� ��µǰ�, ������ �� �ִ� Text�� Ŭ���� (�繫��, �غνǿ��� ����ϴ� ����)
/// 2021.02.18. JJun
/// </summary>

class FileSelectText : public Button, public TextBox
{
	// ������ �����Կ� ���� �б⸦ ������ ����
	enum StateOfSelectedText
	{
		NONE,MURDER,SUICIDE,ILLNESS,
	};

public:
	FileSelectText(UISortLayer layer);
	~FileSelectText();

private:

	// 3 x 3 �� �ִٰ� Ĩ�ô�.

	int m_CheakState;

	int m_SelectableTextState;

	ObjectManager* m_pObjectManager;

	vector<Button*> m_pSelectableTextVec;

	TextBox* m_pTextBox;

public:
	virtual void Initialize(JVector pos, PCWSTR objectName);
	virtual void Update();
	virtual void Draw();
};
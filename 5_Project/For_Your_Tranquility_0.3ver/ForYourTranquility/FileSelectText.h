#pragma once

#include "Button.h"
#include "TextBox.h"
#include "JScript.h"

/// <summary>
/// 파일안에서 출력되고, 선택할 수 있는 Text의 클래스 (사무실, 해부실에서 사용하는 파일)
/// 2021.02.18. JJun
/// </summary>

class FileSelectText : public Button, public TextBox
{
	// 사인을 선택함에 따라 분기를 나누기 위함
	enum StateOfSelectedText
	{
		NONE,MURDER,SUICIDE,ILLNESS,
	};

public:
	FileSelectText(UISortLayer layer);
	~FileSelectText();

private:

	// 3 x 3 개 있다고 칩시다.

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
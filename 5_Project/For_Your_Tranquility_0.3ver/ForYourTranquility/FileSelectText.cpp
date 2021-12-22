#include "pch.h"
#include "FileSelectText.h"

FileSelectText::FileSelectText(UISortLayer layer)
	:Button(layer), TextBox(layer)
{

}

FileSelectText::~FileSelectText()
{

}

void FileSelectText::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);

	Button* _newButton = new Button(UISortLayer::BUTTON);
	_newButton

	m_pSelectableTextVec.push_back();

	m_pSelectableTextVec.push_back(m_pObjectManager->CreateObject_Button(JVector(300, 300), "디폴트버튼"));

}

void FileSelectText::Update()
{
	switch (m_SelectableTextState)
	{
		case StateOfSelectedText::NONE:

			// 첫번째 공백이 포함된 텍스트 하나만 출력하게 만든다.
			// 이때 공백 사이에 버튼도 하나 드로우시켜주어야한다.

			// 이 버튼을 누를시 위로 3가지 버튼을 추가로 만들어주어야한다.

			// 추가로 만들어진 버튼을 누를 시
			// 누른 버튼만 공백사이에 드로우 시켜준다.(이친구를 누르면 또 3개 버튼 드로우)
			//StateOfSelected가 바뀐다. 
			// 바뀐 StateOfSelected에 따라 다음 텍스트가 출력되어야한다.
			// 위의 내용 반복
			
			break;

		case StateOfSelectedText::MURDER:
			// 살인 관련 텍스트를 띄우게 만든다.

			break;
		case StateOfSelectedText::SUICIDE:
			// 자살 관련 텍스트를 띄우게 만든다.

			break;
		case StateOfSelectedText::ILLNESS:
			// 병사 관련 텍스트를 띄우게 만든다.
			break;


		default:
			break;
	}

}

void FileSelectText::Draw()
{

}

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

	m_pSelectableTextVec.push_back(m_pObjectManager->CreateObject_Button(JVector(300, 300), "����Ʈ��ư"));

}

void FileSelectText::Update()
{
	switch (m_SelectableTextState)
	{
		case StateOfSelectedText::NONE:

			// ù��° ������ ���Ե� �ؽ�Ʈ �ϳ��� ����ϰ� �����.
			// �̶� ���� ���̿� ��ư�� �ϳ� ��ο�����־���Ѵ�.

			// �� ��ư�� ������ ���� 3���� ��ư�� �߰��� ������־���Ѵ�.

			// �߰��� ������� ��ư�� ���� ��
			// ���� ��ư�� ������̿� ��ο� �����ش�.(��ģ���� ������ �� 3�� ��ư ��ο�)
			//StateOfSelected�� �ٲ��. 
			// �ٲ� StateOfSelected�� ���� ���� �ؽ�Ʈ�� ��µǾ���Ѵ�.
			// ���� ���� �ݺ�
			
			break;

		case StateOfSelectedText::MURDER:
			// ���� ���� �ؽ�Ʈ�� ���� �����.

			break;
		case StateOfSelectedText::SUICIDE:
			// �ڻ� ���� �ؽ�Ʈ�� ���� �����.

			break;
		case StateOfSelectedText::ILLNESS:
			// ���� ���� �ؽ�Ʈ�� ���� �����.
			break;


		default:
			break;
	}

}

void FileSelectText::Draw()
{

}

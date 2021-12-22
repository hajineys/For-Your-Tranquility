#include "pch.h"

#include "TextBox.h"

TextBox::TextBox(UISortLayer layer)
	:Object(layer), m_IsTextDrawingNow(true), m_PrevScriptNowTextIndex(0),
	m_EventStartIndex(0), m_EventEndIndex(0), m_NowState(false), IsCopOut(false), IsTranslate(false)
{

}

TextBox::~TextBox()
{

}

void TextBox::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(JVector(200, 1600), objectName);

	ResourceManager::GetInstance()->LoadScriptDataFile(m_ObjectName, m_Script.TextVec);

	// �ؽ�Ʈ �ڽ� �̹����� �߰��Ѵ�.
	AddSprite(L"Intro_ChatWindow", 1);

	// ĳ���� �̹����� �߰��Ѵ�.
	AddCharacterSprite(L"WolfLizard_anim", 3);
	AddCharacterSprite(L"Monkey_anim", 4);
	AddCharacterSprite(L"Gorilla_anim", 2);

	m_MonkeyPos = { m_Transform->Pos.x + m_Transform->Size.x - 750, m_Transform->Pos.y - m_CharacterSpriteVec[1]->Bitmap->GetSize().height + 60 };
}

void TextBox::Release()
{
	Object::Release();
}

void TextBox::Update(float dTime, float speed /*= 1.0f */)
{
	// ��ȭ���ڰ� On�� �� ���콺 Ŭ���ϸ� ��ȭ�� �ѱ��....
	if (InputManager::GetInstance()->CheckLeftButtonUp())
	{
		if (m_NowState && IsStartEndIndex())
		{
			if (m_IsTextDrawingNow == true)
			{
				if (m_Script.IsNowTextEnd)
				{
					DrawNextText();
					m_IsTextDrawingNow = true;
				}
				else
				{
					if (m_EventStartIndex != m_EventEndIndex)
					{
						DrawAllNowText();
						m_IsTextDrawingNow = false;
					}
				}
			}
			else
			{
				DrawNextText();
				m_IsTextDrawingNow = true;
			}
		}
	}

	if (m_NowState && IsStartEndIndex())
	{
		Object::Update(dTime);

		m_PrevScriptNowTextIndex = m_Script.NowTextIndex;

		// ���� �� ���ھ� ���, ���� ���ϴ� ����� ������ ������Ʈ
		m_Script.Update(dTime, speed * 2.5f);

		if (m_PrevScriptNowTextIndex + 1 == m_Script.NowTextIndex && !IsNowTextEnd() && !m_Script.IsSpace)
		{
			if (m_Script.NowSpeacker == L"����")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Gyoung");
			}
			else if (m_Script.NowSpeacker == L"����")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Senpai");
			}
			else if (m_Script.NowSpeacker == L"����")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Soon");
			}
			else if (m_Script.NowSpeacker == L"�Ĺ�")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Me");
			}
			else if (m_Script.NowSpeacker == L"����������")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Byoung");
			}
			else if (m_Script.NowSpeacker == L"�����")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Hyoung.");
			}
			else if (m_Script.NowSpeacker == L"��ȣ������")
			{
				SoundManager::GetInstance()->Play(1, L"Character_Boho");
			}
			else
			{
				/// �ӽ� �ؽ�Ʈ ��� ����
				SoundManager::GetInstance()->Play(1, L"Button_Up_Normal");
			}
		}
	}
	else
	{
		Off();
		m_IsTextDrawingNow = true;
		m_EventStartIndex = 0;
		m_EventEndIndex = 0;

		Reset();
	}

	if (m_NowState)
		m_Transform->TranslateSmoothAnimation(dTime, m_Transform->Pos.x, 750, 80.0f);
	else
	{
		if (!IsTranslate)
		{
			m_Transform->IsTranslateEnd = true;
			IsTranslate = true;
		}

		m_Transform->TranslateSmoothAnimation(dTime, m_Transform->Pos.x, 1600, 120.0f);
	}

	if (IsCopOut && m_NowState)
		JTransform::TranslateSmoothAnimationStatic(dTime, m_MonkeyPos.x, m_MonkeyPos.y, 200, m_Transform->Pos.y - m_CharacterSpriteVec[1]->Bitmap->GetSize().height + 60, 7.0f);
}

void TextBox::Draw(float opacity/*=1.0f*/)
{
	// �ؽ�Ʈ �ڽ� �̹����� �׸���.
	Object::Draw(opacity);

	float offsetX = 0;
	// ����Ŀ�� ���
	switch (m_Script.NowSpeacker.size())
	{
	case 1:
		offsetX = m_Transform->Pos.x + 160;
		break;
	case 2:
		offsetX = m_Transform->Pos.x + 160;
		break;
	case 3:
		offsetX = m_Transform->Pos.x + 145;
		break;
	case 4:
		offsetX = m_Transform->Pos.x + 130;
		break;
	case 5:
		offsetX = m_Transform->Pos.x + 115;
		break;
	case 6:
		offsetX = m_Transform->Pos.x + 100;
		break;
	case 7:
		offsetX = m_Transform->Pos.x + 85;
		break;
	case 8:
		offsetX = m_Transform->Pos.x + 70;
	default:
		break;
	}
	
	JJEngine::GetInstance()->DrawText(offsetX, m_Transform->Pos.y + 30, m_Transform->Size.x, m_Transform->Size.y, 30, ColorF(ColorF::LightGray), m_Script.NowSpeacker.c_str());

	// ��ũ��Ʈ�� ���
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x + 70, m_Transform->Pos.y + 120, m_Transform->Size.x - 130, m_Transform->Size.y, 25, ColorF(ColorF::LightGray), m_Script.NowText.c_str());

	ShowDebug();
}

void TextBox::DrawCharacter(bool IsElderFlipX, float opacity /*= 1.0f*/)
{
	if (m_CharacterSpriteVec.size() > 2)
	{
		if (m_Script.NowSpeacker == L"����" || m_Script.NowSpeacker == L"����")
		{
			if (m_Script.NowSpeacker == L"����")
				m_CharacterSpriteVec[0]->ChangeFrame(2);
			else
				m_CharacterSpriteVec[0]->ChangeFrame(1);
		}
		else
			m_CharacterSpriteVec[0]->ChangeFrame(None);

		if (m_Script.NowSpeacker == L"����")
		{
			if (IsElderFlipX)
			{
				m_CharacterSpriteVec[1]->ChangeFrame(3);
			}
			else
			{
				m_CharacterSpriteVec[1]->ChangeFrame(1);
			}
		}
		else
		{
			if (IsElderFlipX)
			{
				m_CharacterSpriteVec[1]->ChangeFrame(2);
			}
			else
			{
				m_CharacterSpriteVec[1]->ChangeFrame(None);
			}
		}

		if (m_Script.NowSpeacker == L"�Ĺ�")
		{
			m_CharacterSpriteVec[2]->ChangeFrame(1);
		}
		else
			m_CharacterSpriteVec[2]->ChangeFrame(None);

		if (!IsElderFlipX)
		{
			// ���� ĳ���� ���
			JJEngine::GetInstance()->DrawSprite(m_CharacterSpriteVec[0], m_Transform->Pos.x + 20, m_Transform->Pos.y - m_CharacterSpriteVec[0]->Bitmap->GetSize().height + 110, opacity);

			// ������ ĳ���� ���
			JJEngine::GetInstance()->DrawSprite(m_CharacterSpriteVec[2], m_Transform->Pos.x + m_Transform->Size.x - 550, m_Transform->Pos.y - m_CharacterSpriteVec[2]->Bitmap->GetSize().height + 110, opacity);
			JJEngine::GetInstance()->DrawSprite(m_CharacterSpriteVec[1], m_MonkeyPos.x, m_Transform->Pos.y - m_CharacterSpriteVec[1]->Bitmap->GetSize().height + 110, opacity);
		}
		else
		{
			IsCopOut = true;

			// ���� ĳ���� ���
			JJEngine::GetInstance()->DrawSprite(m_CharacterSpriteVec[1], m_MonkeyPos.x, m_Transform->Pos.y - m_CharacterSpriteVec[1]->Bitmap->GetSize().height + 110, opacity);

			// ������ ĳ���� ���
			JJEngine::GetInstance()->DrawSprite(m_CharacterSpriteVec[2], m_Transform->Pos.x + m_Transform->Size.x - 550, m_Transform->Pos.y - m_CharacterSpriteVec[2]->Bitmap->GetSize().height + 110, opacity);
		}
	}
}

std::wstring TextBox::GetText(int index)
{
	return m_Script.GetText(index);
}

std::wstring TextBox::GetSpeaker(int index)
{
	return m_Script.GetSpeaker(index);
}

bool TextBox::IsStartEndIndex()
{
	return m_Script.DrawIndex >= m_EventStartIndex && m_Script.DrawIndex <= m_EventEndIndex;
}

void TextBox::On()
{
	m_NowState = true;
}

void TextBox::Off()
{
	if (m_NowState)
	{
		//m_Transform->Pos = JVector(200, 750);
	}

	m_NowState = false;
}

void TextBox::Reset()
{
	IsTranslate = false;
}

void TextBox::ShowDebug()
{
	Object::ShowDebug();
}

void TextBox::DrawNextText()
{
	m_Script.NextIndex();
}

void TextBox::DrawAllNowText()
{
	m_Script.DrawAllNowText();
}

void TextBox::AddCharacterSprite(CString additionalName, int frame)
{
	JImage* _newSprite = new JImage(frame);

	_newSprite->Bitmap = ResourceManager::GetInstance()->GetMyImage(additionalName);

	// �̸��� �־��ش�.
	wstring _speakerName = ResourceManager::CStrToWStr(additionalName);
	m_SpeakerImageNameVec.push_back(_speakerName);

	if (_newSprite->Bitmap != nullptr)
	{
		// �̹����� �־��ش�.
		m_CharacterSpriteVec.push_back(_newSprite);
	}
}

void TextBox::SetStartEndIndex(int start, int end)
{
	// 0. �ؽ�Ʈ �ڽ��� ���۰� �� �ε����� �������ش�.
	m_EventStartIndex = start;
	m_EventEndIndex = end;

	// 1. ��ũ��Ʈ�� ���� �ε����� �������ش�.
	m_Script.DrawIndex = m_EventStartIndex;

	if (start == end)
		m_Script.Reset();

	// 2. �����ε������� ������ ����� ������ �������ְ� ��ȭ���ڸ� Ų��.
	if (IsStartEndIndex())
	{
		Reset();
		On();
		//m_Script.NowTextIndex = 0;
		//m_Transform->Pos = JVector(200, 1600);
	}
}
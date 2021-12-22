#include "pch.h"
#include "JScript.h"

JScript::JScript()
	:DrawIndex(0), DrawTime(0), NowText(L""), NowTextIndex(0), IsNowTextEnd(false), IsAllTextEnd(false), DrawCount(0)
	,IsSpace(false)
{

}

void JScript::NextIndex()
{
	DrawIndex++;

	if (DrawIndex < TextVec.size())
	{
		Reset();
	}	
	else
	{
		IsAllTextEnd = true;
	}
}

void JScript::DrawAllNowText()
{
	NowTextIndex = TextVec[DrawIndex].Text.size();
	IsNowTextEnd = true;
}

void JScript::ChangeText(int index)
{
	if (index < TextVec.size())
		DrawIndex = index;
}

wstring JScript::GetText(int index)
{
	if (index < TextVec.size())
	{
		return TextVec[index].Text;
	}
}

wstring JScript::GetSpeaker(int index)
{
	if (index < TextVec.size())
	{
		return TextVec[index].Speaker;
	}
}

void JScript::Reset()
{
	NowTextIndex = 0;
	IsNowTextEnd = false;
}

void JScript::Update(float dTime, float speed /* = 1.0f*/)
{
	NowText = L"";
	DrawTime += dTime * 10 * speed;

	if (DrawTime >= 1)
	{
		DrawTime = 0;

		if (NowTextIndex == TextVec[DrawIndex].Text.size())
			IsNowTextEnd = true;

		if (NowTextIndex < TextVec[DrawIndex].Text.size())
		{
			NowTextIndex++;

			if (NowTextIndex < TextVec[DrawIndex].Text.size())
			{
				const wchar_t _space[2] = L" ";
				const wchar_t _checkText[2] = { TextVec[DrawIndex].Text.at(NowTextIndex) };

				wstring _spaceStr = _space;
				wstring _checkTextStr = _checkText;

				// 공백인지 아닌지 체크
				if (_spaceStr == _checkTextStr)
				{
					IsSpace = true;
				}
				else
					IsSpace = false;
			}
		}
	}

	for (int i = 0; i < NowTextIndex && i < TextVec[DrawIndex].Text.size(); i++)
	{
		NowText += TextVec[DrawIndex].Text[i];
	}

	NowSpeacker = TextVec[DrawIndex].Speaker;
}

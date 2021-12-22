#include "pch.h"

#include "JMotion.h"

JMotion::JMotion()
	:ObjectName(""), Name(""), Frame(0), DrawIndex(0), DrawTime(0), PlayCount(0)
{
	Reset();
}

void JMotion::Reset()
{
	DrawTime = 0;
	DrawIndex = 0;

	PlayCount = 1;
}

void JMotion::Update(float dTime, float speed /*= 1.0f*/)
{
	DrawTime += dTime * (10 * speed);

	if (DrawTime >= 1)
	{
		DrawTime = 0;
		DrawIndex++;
		if (DrawIndex >= Frame)
			DrawIndex = 0;
	}
}

void JMotion::ChangeMotionFrame(int frame)
{
	// 이 애니메이션의 프레임을 넘어서지 않을 경우만 프레임 교체
	if (frame <= Frame)
		DrawIndex = frame;
}

void JMotion::NextMotionFrame()
{
	DrawIndex++;

	if (DrawIndex >= Frame)
		DrawIndex = 0;
}

void JMotion::Play(float dTime, float speed /*= 1.0f*/)
{
	if (PlayCount > 0)
	{
		DrawTime += dTime * (10 * speed);

		if (DrawTime >= 1 && DrawIndex < Frame - 1)
		{
			DrawTime = 0;
			DrawIndex++;

			if (DrawIndex >= Frame - 1)
			{
				PlayCount--;

				if (PlayCount > 0)
					DrawIndex = 0;
			}
		}
	}
}

JImage::JImage(int frame)
	:ObjectName(""), Frame(frame), DrawIndex(0), DrawTime(0), Bitmap(nullptr), PlayOnlyOnce(true)
{

}

void JImage::Reset()
{
	DrawTime = 0;
	DrawIndex = 0;
	PlayOnlyOnce = true;
}

void JImage::Update(float dTime, float speed /* = 1.0f*/)
{
	DrawTime += dTime * (10 * speed);

	if (DrawTime >= 1)
	{
		DrawTime = 0;
		DrawIndex++;
		if (DrawIndex >= Frame)
			DrawIndex = 0;
	}
}

void JImage::ChangeFrame(int frame)
{
	// 이 애니메이션의 프레임을 넘어서지 않을 경우만 프레임 교체
	if (frame <= Frame)
		DrawIndex = frame;
}

void JImage::NextFrame()
{
	DrawIndex++;

	if (DrawIndex >= Frame)
		DrawIndex = 0;
}

bool JImage::Play(float dTime, float speed /*= 1.0f*/)
{
	DrawTime += dTime * (10 * speed);

	if (DrawTime >= 1 && DrawIndex < Frame)
	{
		DrawTime = 0;

		if (DrawIndex < Frame - 1)
		{
			DrawIndex++;
			//DrawIndex = 0;
		}
		else
			return true;
	}

	return false;
}

bool JImage::PlayAndReset(float dTime, float speed /*= 1.0f*/)
{
	DrawTime += dTime * (10 * speed);

	if (DrawTime >= 1 && DrawIndex < Frame && PlayOnlyOnce == true)
	{
		DrawTime = 0;
		DrawIndex++;

		if (DrawIndex >= Frame)
		{
			DrawIndex = 0;
			PlayOnlyOnce = false;
			return true;
		}
	}

	return false;
}
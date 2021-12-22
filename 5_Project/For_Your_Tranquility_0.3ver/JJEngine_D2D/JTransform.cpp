#include "pch.h"

#include "JTransform.h"

JMatrix_3X3::JMatrix_3X3(float _m[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = _m[i][j];
		}
	}
}

JMatrix_3X3::JMatrix_3X3()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = 0;
		}
	}
}

JMatrix_3X3 JMatrix_3X3::operator=(JMatrix_3X3 v)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = v.m[i][j];
		}
	}

	return JMatrix_3X3(m);
}

JMatrix_3X3 JMatrix_3X3::operator+(JMatrix_3X3& v)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] += v.m[i][j];
		}
	}

	return JMatrix_3X3(m);
}

JMatrix_3X3 JMatrix_3X3::operator-(JMatrix_3X3& v)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] -= v.m[i][j];
		}
	}

	return JMatrix_3X3(m);
}

JMatrix_3X3 JMatrix_3X3::operator*(JMatrix_3X3& v)
{
	// 곱셈 결과값 저장
	float temp[3][3] = { 0, };
	// 곱셈 합
	int sum = 0;

	// 행렬의 곱셈	
	int c = 0;		//column 열
	for (int r = 0; r < 3; r++) //row 행
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sum += m[r][j] * v.m[j][i];
			}
			temp[r][c] = sum;
			sum = 0;
			c++;
		}
		c = 0;
	}

	// 곱셈결과를 행렬 요소에 넣는다.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = temp[i][j];
		}
	}

	return JMatrix_3X3(m);
}

JVector JVector::operator*(JMatrix_3X3& m)
{
	JVector _result;

	_result.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * 1;
	_result.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * 1;

	return _result;
}

JVector JVector::operator*(float f)
{
	x = x * f;
	y = y * f;

	return JVector(x, y);
}

JTransform::JTransform()
	:Pos({ 0,0 }), Size({ 0,0 }), CenterPos({ 0,0 }), AnimationTime(0)
{

}

JTransform::~JTransform()
{

}

void JTransform::Translate(float dx, float dy)
{
	JMatrix_3X3 translationMatrix = GetTranslationMatrix(dx, dy);

	Pos = Pos * translationMatrix;

	// 각 점의 좌표를 이동시킴
	for (int i = 0; i < TOTAL_POINT; i++)
	{
		RectPos[i] = RectPos[i] * translationMatrix;
	}
}

void JTransform::Rotate(float angle)
{
	JVector howMove = { CenterPos.x,  CenterPos.y };
	// 원점으로 이동
	Translate(-howMove.x, -howMove.y);

	JMatrix_3X3 rotationMatrix = GetRotationMatrix(angle);

	// 각 점의 좌표를 이동시킴
	for (int i = 0; i < TOTAL_POINT; i++)
	{
		RectPos[i] = RectPos[i] * rotationMatrix;
	}

	//원래 위치로 이동
	Translate(howMove.x, howMove.y);
}

void JTransform::Scale(float sx, float sy)
{
	JMatrix_3X3 scaleMatrix = GetScaleMatrix(sx, sy);

	Size = Size * scaleMatrix;

	// 의도치 않은 이동 방지
	JVector move = RectPos[LEFT_TOP];

	// 각 점의 좌표를 이동시킴
	for (int i = 0; i < TOTAL_POINT; i++)
	{
		RectPos[i] = RectPos[i] * scaleMatrix;
	}

	move = move - RectPos[LEFT_TOP];

	// 각 점의 좌표를 이동시킴
	for (int i = 0; i < TOTAL_POINT; i++)
	{
		RectPos[i] = RectPos[i] + move;
	}
}

void JTransform::Scale(float size)
{
	JMatrix_3X3 scaleMatrix = GetScaleMatrix(size);

	Size = Size * scaleMatrix;
}

void JTransform::TranslateAnimation(float dTime, float targetX, float targetY, float speed /*= 1.0f*/)
{
	AnimationTime += dTime * 1000;

	JVector _targetVector = { targetX, targetY };
	JVector _dirVector = _targetVector - Pos;

	if (AnimationTime >= 1 && _dirVector.x >= 0 && _dirVector.y >= 0)
	{
		AnimationTime = 0;

		// 단위 벡터를 구한다.
		float _unitVec = sqrt(_dirVector.x * _dirVector.x + _dirVector.y * _dirVector.y);
		
		Pos.x = Pos.x + _dirVector.x / _unitVec * speed;
		Pos.y = Pos.y + _dirVector.y / _unitVec * speed;
	}
}

void JTransform::TranslateSmoothAnimation(float dTime, float targetX, float targetY, float speed /*= 1.0f*/)
{
	static float percent = 0;
	
	if (IsTranslateEnd)
	{
		percent = 0;
		IsTranslateEnd = false;
	}

	percent += dTime * 0.01f * speed;

	if (percent >= 1.0f)
		percent = 1.0f;

	JVector _targetVector = { targetX * 2, targetY * 2 };
	JVector _dirVector = _targetVector - Pos;

	JVector _Lerp = Lerp(Pos, _targetVector, percent);

	Pos = _Lerp;
}

void JTransform::TranslateSmoothAnimationStatic(float dTime, float& sourceX, float& sourceY, float targetX, float targetY, float speed /*= 1.0f*/)
{
	static float percent = 0;
	static bool _IsFirst = false;

	percent += dTime * 0.01f * speed;

	if (percent >= 1.0f)
		percent = 1.0f;

	JVector _targetVector = { targetX * 2, targetY * 2 };
	JVector _myPos = { sourceX, sourceY };
	JVector _dirVector = _targetVector - _myPos;

	if (_dirVector.x <= 0 && _dirVector.y <= 0 && _IsFirst == false)
	{
		percent = 0;
		_IsFirst = true;
	}

	JVector _Lerp = Lerp(_myPos, _targetVector, percent);

	sourceX = _Lerp.x;
	sourceY = _Lerp.y;
}

JMatrix_3X3 JTransform::GetTranslationMatrix(float dx, float dy)
{
	float trans[3][3] = {
		{1, 0, dx},
		{0, 1, dy},
		{0, 0,  1}
	};
	JMatrix_3X3 translationMatrix(trans);

	return translationMatrix;
}

JMatrix_3X3 JTransform::GetRotationMatrix(float angle)
{
	const double pi = 3.14159265358979f;
	float rad = angle * pi / 180;
	//float rad = pi / (180 / m_Angle);

	float rotation[3][3] = {
			{ cos(rad),  sin(rad),	0 },
			{ -sin(rad), cos(rad),	0 },
			{ 0,		  0,		1 }
	};
	JMatrix_3X3 rotationMatrix(rotation);

	return rotationMatrix;
}

JMatrix_3X3 JTransform::GetScaleMatrix(float sx, float sy)
{
	float scale[3][3] = {
			{ sx, 0,  0 },
			{ 0,  sy, 0 },
			{ 0,  0,  1 }
	};

	JMatrix_3X3 scaleMatrix(scale);

	return scaleMatrix;
}

JMatrix_3X3 JTransform::GetScaleMatrix(float size)
{
	float scale[3][3] = {
			{ size, 0,  0 },
			{ 0,  size, 0 },
			{ 0,  0,  1 }
	};

	JMatrix_3X3 scaleMatrix(scale);

	return scaleMatrix;
}

JVector JTransform::Lerp(JVector pos, JVector targetPos, float percent)
{
	JVector returnVec;

	returnVec.x = (pos.x * (1.0f - percent) + targetPos.x * percent);
	returnVec.y = (pos.y * (1.0f - percent) + targetPos.y * percent);

	return returnVec;
}

#pragma once
#include <atltypes.h>

#include <vector>
using namespace std;

// 시트에서 위치만 저장 (스프라이트 툴과 호환)
class JSprite
{
public:
	CPoint DrawPoint;
	float Width;
	float Height;

	CPoint Pivot;

	/// 툴용 변수
	CRect RectPos;
	CRect CancelRect;
	CPoint Pivot2;

public:
	JSprite();
	~JSprite();
};
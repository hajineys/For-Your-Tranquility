#pragma once
#include <atltypes.h>

#include <vector>
using namespace std;

// ��Ʈ���� ��ġ�� ���� (��������Ʈ ���� ȣȯ)
class JSprite
{
public:
	CPoint DrawPoint;
	float Width;
	float Height;

	CPoint Pivot;

	/// ���� ����
	CRect RectPos;
	CRect CancelRect;
	CPoint Pivot2;

public:
	JSprite();
	~JSprite();
};
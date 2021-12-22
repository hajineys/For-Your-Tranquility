#pragma once

class JMatrix_3X3
{
public:
	float m[3][3];

public:
	JMatrix_3X3();
	JMatrix_3X3(float _m[3][3]);
	~JMatrix_3X3() {};

public:
	JMatrix_3X3 operator= (JMatrix_3X3 v);
	JMatrix_3X3 operator+ (JMatrix_3X3& v);
	JMatrix_3X3 operator- (JMatrix_3X3& v);
	JMatrix_3X3 operator* (JMatrix_3X3& v);
};

class JVector
{
public:
	float x;
	float y;

public:
	JVector(float _x, float _y) : x(_x), y(_y) {}
	JVector() : x(0), y(0) {}
	~JVector() {};

public:
	JVector operator+ (JVector& v) { x += v.x; y += v.y; return JVector(x, y); }
	JVector operator- (JVector& v) { x -= v.x; y -= v.y; return JVector(x, y); }
	JVector operator* (JVector& v) { x *= v.x; y *= v.y; return JVector(x, y); }
	JVector operator/ (JVector& v) { x /= v.x; y /= v.y; return JVector(x, y); }

	JVector operator* (JMatrix_3X3& m);
	JVector operator* (float f);
};

class JTransform
{
public:
	JVector Pos;
	JVector Size;
	JVector CenterPos;

	enum RECT_POINT
	{
		LEFT_TOP,
		RIGHT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
		TOTAL_POINT
	};

	// 사각형의 네 꼭짓점 (회전을 위한 보조 Pos)
	JVector RectPos[TOTAL_POINT];

public:
	// 트랜스폼 애니메이션 변수
	float AnimationTime;
	float LerpPercent;
	bool IsTranslateEnd;

public:
	JTransform();
	JTransform(JVector _pos, JVector _size) :Pos(_pos), Size(_size), AnimationTime(0), IsTranslateEnd(false), LerpPercent(0) { };
	~JTransform();

	void SetPos(float x, float y) { Pos.x = x; Pos.y = y; }

public:
	/// Transform
	void Translate(float dx, float dy);
	void Rotate(float angle);
	void Scale(float sx, float sy);
	void Scale(float size);

	void TranslateAnimation(float dTime, float targetX, float targetY, float speed = 1.0f);
	void TranslateSmoothAnimation(float dTime, float targetX, float targetY, float speed = 1.0f);
	static void TranslateSmoothAnimationStatic(float dTime, float& sourceX, float& sourceY, float targetX, float targetY, float speed = 1.0f);

	static JMatrix_3X3 GetTranslationMatrix(float dx, float dy);
	static JMatrix_3X3 GetRotationMatrix(float angle);
	static JMatrix_3X3 GetScaleMatrix(float sx, float sy);
	static JMatrix_3X3 GetScaleMatrix(float size);

	static JVector Lerp(JVector pos, JVector targetPos, float percent);
};


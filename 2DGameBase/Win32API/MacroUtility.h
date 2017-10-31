#pragma once

// ���� �� ����
inline int GetRandom(int max)
{
	return rand() % max;
}

// �ּҰ��� �ִ밪 ������ ���� �� ����(�ּ�, �ִ밪 ����)
inline int GetRandom(int min, int max)
{
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
}

//�� �׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void BoudingLineMake(HDC hdc, int x1, int y1, int sizeX, int sizeY)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1 + sizeX, y1);
	LineTo(hdc, x1 + sizeX, y1 + sizeY);
	LineTo(hdc, x1, y1 + sizeY);
	LineTo(hdc, x1, y1);
}

//��Ʈ �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//��Ʈ �������� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline RECT RectMakeCenter(RECT rt, int width, int height)
{
	RECT rc;
	rc.left = (rt.right + rt.left) / 2 - width / 2;
	rc.top = (rt.top + rt.bottom) / 2 - height / 2;
	rc.right = rc.left + width;
	rc.bottom = rc.top + height;

	return rc;
}

//��Ʈ ����ü�� �簢�� �׸���
inline void RectangleMake(HDC hdc, RECT rt)
{
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

//�簢�� �׸��� (Rectangle�Լ��̿�)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//�� �׸��� (Ellipse�Լ��̿�)
inline void EllipseMake(HDC hdc, RECT rt)
{
	Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//�� ������ �׸��� (Ellipse�Լ��̿�)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// �Ÿ�(�밢�� ����) ���ϴ� �Լ�
inline float GetLength(float x1, float y1, float x2, float y2)
{
	float fLengthX = x2 - x1;
	float fLengthY = y2 - y1;

	return sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);
}

// �� �� ������ ���� ���ϴ� �Լ� (1: ������, 2: ������)
inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float fLengthDiagonal = GetLength(x1, y1, x2, y2);

	if (fLengthDiagonal < FLT_EPSILON) return 0;

	float fAngle = acosf((x2 - x1) / fLengthDiagonal) / PI * 180.0f;

	// ���� ���� ó��
	if (y1 < y2)
	{
		fAngle = 360.0f - fAngle;

		if (fAngle >= 360.0f)
			fAngle -= 360.0f;
	}

	return fAngle;
}

// ���� ����
inline void LinearInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float toX, IN float toY, IN float t)
{
	x = fromX * (1.0f - t) + toX * t;
	y = fromY * (1.0f - t) + toY * t;
}

// ������ �
inline void BezierInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float viaX, IN float viaY, IN float toX, IN float toY, IN float t)
{
	float x1, y1, x2, y2;

	//x1 = fromX * (1.0f - t) + viaX * t;
	//y1 = fromY * (1.0f - t) + viaY * t;
	LinearInterpolation(x1, y1, fromX, fromY, viaX, viaY, t);

	//x2 = viaX * (1.0f - t) + toX * t;
	//y2 = viaY * (1.0f - t) + toY * t;
	LinearInterpolation(x2, y2, viaX, viaY, toX, toY, t);

	//x = x1 * (1.0f - t) + x2 * t;
	//y = y1 * (1.0f - t) + y2 * t;
	LinearInterpolation(x, y, x1, y1, x2, y2, t);
}

// ������ �
inline void BezierInterpolation2(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float viaX, IN float viaY, IN float toX, IN float toY, IN float t)
{
	float x1, y1, x2, y2, x3, y3;

	float viaX2 = viaX;
	float viaY2 = fromY + fromY - viaY;

	LinearInterpolation(x1, y1, fromX, fromY, viaX, viaY, t);
	LinearInterpolation(x2, y2, viaX, viaY, viaX2, viaY2, t);
	LinearInterpolation(x3, y3, viaX2, viaY2, toX, toY, t);

	BezierInterpolation(x, y, x1, y1, x2, y2, x3, y3, t);
}
#include "stdafx.h"
#include "cImage.h"


cImage::cImage()
	: m_pImageInfo(NULL)
	, m_szFileName(NULL)
	, m_isTrans(false)
	, m_transColor(RGB(0, 0, 0))
	, m_pBlendImage(NULL)
{
}


cImage::~cImage()
{
	// �̹��� ������ �ִ� ��쿡�� ����
	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBit);
		DeleteObject(m_pImageInfo->hBit);
		DeleteDC(m_pImageInfo->hMemDC);

		if (m_szFileName) delete m_szFileName;
		delete m_pImageInfo;
	}

	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBit);
		DeleteObject(m_pBlendImage->hBit);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}
}

// �� ��Ʈ�� �¾�
void cImage::Setup(int width, int height)
{
	// DC ��������
	HDC hdc = GetDC(g_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_EMPTY;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width;
	m_pImageInfo->nFrameHeight = height;

	// DC ����
	ReleaseDC(g_hWnd, hdc);
}

// �̹��� ���� �¾�
void cImage::Setup(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// DC ��������
	HDC hdc = GetDC(g_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width;
	m_pImageInfo->nFrameHeight = height;

	assert(m_pImageInfo->hBit && "�̹��� ������ �о���� �� �ߴ�.");

	// ���� �̸�
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// ����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC ����
	ReleaseDC(g_hWnd, hdc);
}

// ������ �̹��� �¾�
void cImage::Setup(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// DC ��������
	HDC hdc = GetDC(g_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;

	assert(m_pImageInfo->hBit && "������ �̹��� ������ �о���� �� �ߴ�.");

	// ���� �̸�
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// ����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC ����
	ReleaseDC(g_hWnd, hdc);
}

void cImage::Setup(const char * fileName, int width, int height, int frameX, int frameY,
	int x, int y, bool isTrans, COLORREF transColor)
{
	// DC ��������
	HDC hdc = GetDC(g_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	m_pImageInfo = new IMAGE_INFO;
	m_pImageInfo->btLoadType = LOAD_FILE;
	m_pImageInfo->dwResID = 0;
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pImageInfo->hBit = (HBITMAP)LoadImage(g_hInst, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_pImageInfo->hOldBit = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBit);
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->fPosX = x - width / frameX / 2.0f;
	m_pImageInfo->fPosY = y - height / frameY / 2.0f;

	assert(m_pImageInfo->hBit && "������ �̹��� ������ �о���� �� �ߴ�.");

	// ���� �̸�
	int len = strlen(fileName);
	m_szFileName = new char[len + 1];
	strcpy_s(m_szFileName, len + 1, fileName);

	// ����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	// DC ����
	ReleaseDC(g_hWnd, hdc);
}

// ���ĺ��忡 ��� �� �� ��Ʈ���� �ϳ� ����
void cImage::SetupForAlphaBlend()
{
	// ���ĺ��� ����ü �ʱ�ȭ (�⺻ ���� �ٲ� ���� ����)
	m_stBlendFunc.BlendOp = AC_SRC_OVER;
	m_stBlendFunc.BlendFlags = 0;
	m_stBlendFunc.AlphaFormat = 0;

	// DC ��������
	HDC hdc = GetDC(g_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->btLoadType = LOAD_EMPTY;
	m_pBlendImage->dwResID = 0;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_pImageInfo->nWidth, m_pImageInfo->nHeight);
	m_pBlendImage->hOldBit = (HBITMAP)SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hBit);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// DC ����
	ReleaseDC(g_hWnd, hdc);
}

// ȭ���� ���� ��� ���� �׸���.
void cImage::Render(HDC hdc)
{
	if (m_isTrans)	// ������ ���� ���
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
		GdiTransparentBlt(
			hdc,					// ���� �� ����� DC
			0,						// ���� �� ��ǥ ���� ���� X
			0,						// ���� �� ��ǥ ���� ���� Y
			m_pImageInfo->nWidth,	// ���� �� �̹����� ���� ũ��
			m_pImageInfo->nHeight, // ���� �� �̹����� ���� ũ��
			m_pImageInfo->hMemDC,	// ���� �� ��� DC
			0,						// ���� ���� ���� X
			0,						// ���� ���� ���� Y
			m_pImageInfo->nWidth,	// ���� ���� ���� ũ��
			m_pImageInfo->nHeight,	// ���� ���� ���� ũ��
			m_transColor			// ���� �� �� ���� �� ����(����ó��)
		);
	}
	else // ���� �̹��� �״�� ���
	{
		// BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		// �޸�DC�� �׷������� ȭ��DC�� ��Ӻ��縦 �Ѵ�
		BitBlt(hdc, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// ���� �� ��ġ�� �׸���.
void cImage::Render(HDC hdc, int destX, int destY)
{
	if (m_isTrans)	// ������ ���� ���
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
		GdiTransparentBlt(
			hdc,					// ���� �� ����� DC
			destX,					// ���� �� ��ǥ ���� ���� X
			destY,					// ���� �� ��ǥ ���� ���� Y
			m_pImageInfo->nWidth,	// ���� �� �̹����� ���� ũ��
			m_pImageInfo->nHeight, // ���� �� �̹����� ���� ũ��
			m_pImageInfo->hMemDC,	// ���� �� ��� DC
			0,						// ���� ���� ���� X
			0,						// ���� ���� ���� Y
			m_pImageInfo->nWidth,	// ���� ���� ���� ũ��
			m_pImageInfo->nHeight,	// ���� ���� ���� ũ��
			m_transColor			// ���� �� �� ���� �� ����(����ó��)
		);
	}
	else // ���� �̹��� �״�� ���
	{
		// BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		// �޸�DC�� �׷������� ȭ��DC�� ��Ӻ��縦 �Ѵ�
		BitBlt(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void cImage::Render(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{
	// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
	GdiTransparentBlt(
		hdc,					// ���� �� ����� DC
		destX,					// ���� �� ��ǥ ���� ���� X
		destY,					// ���� �� ��ǥ ���� ���� Y
		sizeX,					// ���� �� �̹����� ���� ũ��
		sizeY,					// ���� �� �̹����� ���� ũ��
		m_pImageInfo->hMemDC,	// ���� �� ��� DC
		0,						// ���� ���� ���� X
		0,						// ���� ���� ���� Y
		m_pImageInfo->nWidth,	// ���� ���� ���� ũ��
		m_pImageInfo->nHeight,	// ���� ���� ���� ũ��
		m_transColor			// ���� �� �� ���� �� ����(����ó��)
	);
}

// ���� �� ��ġ�� ���ϴ� �κ��� �׸���.
void cImage::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (m_isTrans)	// ������ ���� ���
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
		GdiTransparentBlt(
			hdc,					// ���� �� ����� DC
			destX,					// ���� �� ��ǥ ���� ���� X
			destY,					// ���� �� ��ǥ ���� ���� Y
			sourWidth,				// ���� �� �̹����� ���� ũ��
			sourHeight,				// ���� �� �̹����� ���� ũ��
			m_pImageInfo->hMemDC,	// ���� �� ��� DC
			sourX,					// ���� ���� ���� X
			sourY,					// ���� ���� ���� Y
			sourWidth,				// ���� ���� ���� ũ��
			sourHeight,				// ���� ���� ���� ũ��
			m_transColor			// ���� �� �� ���� �� ����(����ó��)
		);
	}
	else // ���� �̹��� �״�� ���
	{
		// BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		// �޸�DC�� �׷������� ȭ��DC�� ��Ӻ��縦 �Ѵ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			m_pImageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void cImage::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// ���ĺ��� ó�� ���� �ʱ�ȭ
	if (!m_pBlendImage) SetupForAlphaBlend();

	// ���İ� �ʱ�ȭ
	m_stBlendFunc.SourceConstantAlpha = alpha;

	if (m_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׷��ش�
		BitBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc, destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ ���� �����ش�)
		GdiTransparentBlt(m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���
		GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
	}
	else
	{
		// ���ĺ��� �ɼ� ���� ����ؼ� �׸���.
		GdiAlphaBlend(hdc, destX, destY, m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC, 0, 0, m_pImageInfo->nWidth, m_pImageInfo->nHeight, m_stBlendFunc);
	}
}

void cImage::FrameRender(HDC hdc, int destX, int destY)
{
	if (m_isTrans)	// ������ ���� ���
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
		GdiTransparentBlt(
			hdc,					// ���� �� ����� DC
			destX,					// ���� �� ��ǥ ���� ���� X
			destY,					// ���� �� ��ǥ ���� ���� Y
			m_pImageInfo->nFrameWidth,	// ���� �� �̹����� ���� ũ��
			m_pImageInfo->nFrameHeight, // ���� �� �̹����� ���� ũ��
			m_pImageInfo->hMemDC,	// ���� �� ��� DC
			m_pImageInfo->nCurrFrameX * m_pImageInfo->nFrameWidth, // ���� �������� �������� X
			m_pImageInfo->nCurrFrameY * m_pImageInfo->nFrameHeight,// ���� �������� �������� Y
			m_pImageInfo->nFrameWidth,	// ���� ���� ���� ũ��
			m_pImageInfo->nFrameHeight,	// ���� ���� ���� ũ��
			m_transColor			// ���� �� �� ���� �� ����(����ó��)
		);
	}
	else // ���� �̹��� �״�� ���
	{
		// BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		// �޸�DC�� �׷������� ȭ��DC�� ��Ӻ��縦 �Ѵ�
		BitBlt(hdc, destX, destY,
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,
			m_pImageInfo->hMemDC,
			m_pImageInfo->nCurrFrameX * m_pImageInfo->nFrameWidth,
			m_pImageInfo->nCurrFrameY * m_pImageInfo->nFrameHeight,
			SRCCOPY);
	}
}

void cImage::FrameRender(HDC hdc, int destX, int destY, int sourX, int sourY)
{
	if (m_isTrans)	// ������ ���� ���
	{
		// GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� ���縦 �ϴ� �Լ�
		GdiTransparentBlt(
			hdc,					// ���� �� ����� DC
			destX,					// ���� �� ��ǥ ���� ���� X
			destY,					// ���� �� ��ǥ ���� ���� Y
			m_pImageInfo->nFrameWidth,	// ���� �� �̹����� ���� ũ��
			m_pImageInfo->nFrameHeight, // ���� �� �̹����� ���� ũ��
			m_pImageInfo->hMemDC,	// ���� �� ��� DC
			sourX * m_pImageInfo->nFrameWidth, // ���� �������� �������� X
			sourY * m_pImageInfo->nFrameHeight,// ���� �������� �������� Y
			m_pImageInfo->nFrameWidth,	// ���� ���� ���� ũ��
			m_pImageInfo->nFrameHeight,	// ���� ���� ���� ũ��
			m_transColor			// ���� �� �� ���� �� ����(����ó��)
		);
	}
	else // ���� �̹��� �״�� ���
	{
		// BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		// �޸�DC�� �׷������� ȭ��DC�� ��Ӻ��縦 �Ѵ�
		BitBlt(hdc, destX, destY,
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,
			m_pImageInfo->hMemDC,
			sourX * m_pImageInfo->nFrameWidth,
			sourY * m_pImageInfo->nFrameHeight,
			SRCCOPY);
	}
}

// �ִϸ��̼� ���� �� ������ ���� ������ ����
void cImage::FrameRender(HDC hdc, int destX, int destY,
	int sourX, int sourY, int maxX, int maxY, int delay)
{
	if (m_pImageInfo->nDelay >= delay)
	{
		m_pImageInfo->nDelay = 0;

		if (m_pImageInfo->nCurrFrameX >= maxX)
			m_pImageInfo->nCurrFrameX = sourX;
		else
			++m_pImageInfo->nCurrFrameX;

		if (m_pImageInfo->nCurrFrameY >= maxY)
			m_pImageInfo->nCurrFrameY = sourY;
		else
			++m_pImageInfo->nCurrFrameY;
	}
	else
		++m_pImageInfo->nDelay;

	FrameRender(hdc, destX, destY);
}

void cImage::SetTransColor(bool isTrans, COLORREF transColor)
{
	m_isTrans = isTrans;
	m_transColor = transColor;
}
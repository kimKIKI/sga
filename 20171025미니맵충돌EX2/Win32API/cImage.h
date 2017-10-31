#pragma once
class cImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_EMPTY,			// �� ��Ʈ�� �ε�
		LOAD_FILE,			// ���Ϸ� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		dwResID;		// ���ҽ� ID
		HDC			hMemDC;			// �޸� DC
		HBITMAP		hBit;			// ��Ʈ��
		HBITMAP		hOldBit;		// �õ� ��Ʈ��
		int			nWidth;			// �̹��� ���� ũ��
		int			nHeight;		// �̹��� ���� ũ��
		BYTE		btLoadType;		// �̹��� �ε� Ÿ��

		int			nCurrFrameX;	// ���� ������ x
		int			nCurrFrameY;	// ���� ������ y
		int			nMaxFrameX;		// �ִ� x�� ������ ����
		int			nMaxFrameY;		// �ִ� y�� ������ ����
		int			nFrameWidth;	// �� ������ ���� ����
		int			nFrameHeight;	// �� ������ ���� ����

		float		fPosX;			// �̹����� ȭ�鿡�� x��(����) ��ġ
		float		fPosY;			// �̹����� ȭ�鿡�� y��(����) ��ġ
		int			nDelay;			// �̹��� �ִϸ��̼� ������

		tagImage()
		{
			dwResID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			nWidth = 0;
			nHeight = 0;
			btLoadType = LOAD_EMPTY;

			nCurrFrameX = 0;
			nCurrFrameY = 0;
			nMaxFrameX = 1;
			nMaxFrameY = 1;
			nFrameWidth = 0;
			nFrameHeight = 0;
			fPosX = WINSIZEX / 2.0f;
			fPosY = WINSIZEY / 2.0f;
			nDelay = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	m_pImageInfo;	// �̹��� ���� ����ü
	char*			m_szFileName;	// �̹��� ���� �̸�
	bool			m_isTrans;		// ���� ȿ�� ��� ���� 
	COLORREF		m_transColor;	// �������� ��� �� ���� (����Ÿ = RGB(255, 0, 255));

	BLENDFUNCTION	m_stBlendFunc;	// ���ĺ��� ���� ����ü
	LPIMAGE_INFO	m_pBlendImage;	// ���ĺ��� �̹��� ���� ����ü

public:
	cImage();
	~cImage();

	//==================================================================
	//		## �¾� ##
	//==================================================================
	// �� ��Ʈ�� �¾�
	void Setup(int width, int height);
	// �̹��� ���� �¾�
	void Setup(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� �¾�
	void Setup(const char* fileName, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void Setup(const char* fileName, int width, int height, int frameX, int frameY,
		int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//���ĺ��� �ʱ�ȭ
	void SetupForAlphaBlend();

	//==================================================================
	//		## �Ϲ� ���� ##
	//==================================================================
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## ���� ���� ##
	//==================================================================
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	//==================================================================
	//		## ������ ���� ##
	//==================================================================
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int sourX, int sourY);
	void FrameRender(HDC hdc, int destX, int destY,
		int sourX, int sourY, int maxX, int maxY, int delay);

	//==================================================================
	//		## inline ## (�ζ��� �Լ��� - ����, ����)
	//==================================================================
	// ���� ��� ���� ����
	void SetTransColor(bool isTrans, COLORREF transColor);
	// ����� DC ���
	HDC GetMemDC() { return m_pImageInfo->hMemDC; }
	int GetWidth() { return m_pImageInfo->nWidth; }
	int GetHeight() { return m_pImageInfo->nHeight; }
	int GetFrameWidth() { return m_pImageInfo->nFrameWidth; }
	int GetFrameHeight() { return m_pImageInfo->nFrameHeight; }

	// ������ �ε��� ����, ����
	int GetFrameX() { return m_pImageInfo->nCurrFrameX; }
	void SetFrameX(int x) { m_pImageInfo->nCurrFrameX = x; }
	int GetFrameY() { return m_pImageInfo->nCurrFrameY; }
	void SetFrameY(int y) { m_pImageInfo->nCurrFrameY = y; }

	// �ƽ� ������ ����
	int GetMaxFrameX() { return m_pImageInfo->nMaxFrameX; }
	int GetMaxFrameY() { return m_pImageInfo->nMaxFrameY; }

	// ������ ��ġ ���� ���� (���� ����)
	float GetPosX() { return m_pImageInfo->fPosX; }
	void SetPosX(float x) { m_pImageInfo->fPosX = x; }
	float GetPosY() { return m_pImageInfo->fPosY; }
	void SetPosY(float y) { m_pImageInfo->fPosY = y; }
	// ������ ���� ��ġ ����
	void SetCenterX(float x) { m_pImageInfo->fPosX = x - m_pImageInfo->nFrameWidth / 2;	}
	void SetCenterY(float y) { m_pImageInfo->fPosY = y - m_pImageInfo->nFrameHeight / 2; }

	RECT GetBoundingBox()
	{
		return RectMakeCenter(m_pImageInfo->fPosX, m_pImageInfo->fPosY,
			m_pImageInfo->nFrameWidth, m_pImageInfo->nFrameHeight);
	}

	RECT GetBoundingBox(int adjX, int adjY)
	{
		return RectMakeCenter(m_pImageInfo->fPosX, m_pImageInfo->fPosY,
			m_pImageInfo->nFrameWidth - adjX, m_pImageInfo->nFrameHeight - adjY);
	}
};


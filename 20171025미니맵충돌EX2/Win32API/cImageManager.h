#pragma once
#include "cSingletonBase.h"
#include "cImage.h"

#define g_pImageManager cImageManager::GetInstance()

/*
�ڷᱸ�� : map - Ű ���� �����͸� ������ �ڷᱸ��
*/

class cImageManager : public cSingletonBase<cImageManager>
{
private:
	map<string, cImage*>			m_mapImage;
	map<string, cImage*>::iterator	m_mapIter;

public:
	//==================================================================
	//		## �¾� ##
	//==================================================================
	// �� ��Ʈ�� �¾�
	cImage* AddImage(string key, int width, int height);
	// �̹��� ���� �¾�
	cImage* AddImage(string key, const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� �¾�
	cImage* AddImage(string key, const char* fileName, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	cImage* AddImage(string key, const char* fileName, int width, int height, int frameX, int frameY,
		int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//==================================================================
	//		## �̹��� �˻� �� ���� ##
	//==================================================================
	cImage* FindImage(string key);		// �̹��� ã��
	void DeleteImage(string key);		// �̹��� ����
	void DeleteAll();					// ��� �̹��� ����

	//==================================================================
	//		## �Ϲ� ���� ##
	//==================================================================
	void Render(string key, HDC hdc);
	void Render(string key, HDC hdc, int destX, int destY);
	void Render(string key, HDC hdc, int destX, int destY, int sizeX, int sizeY);
	void Render(string key, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## ���� ���� ##
	//==================================================================
	void AlphaRender(string key, HDC hdc, int destX, int destY, BYTE alpha);

	//==================================================================
	//		## ������ ���� ##
	//==================================================================
	void FrameRender(string key, HDC hdc, int destX, int destY);
	void FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY);
	void FrameRender(string key, HDC hdc, int destX, int destY,
		int sourX, int sourY, int maxX, int maxY, int delay);
};


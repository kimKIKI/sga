#include "stdafx.h"
#include "cImageManager.h"

cImage* cImageManager::AddImage(string key, int width, int height)
{
	// �߰� �Ϸ��� Ű ���� �ش��ϴ� �̹����� �����ϴ��� Ȯ��
	cImage* img = FindImage(key);

	// �߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� ��ȯ
	// �׷��� ���� ��� ���� �߰��ϰ� �߰� �� �༮�� ��ȯ
	if (img == NULL)
	{
		img = new cImage;
		img->Setup(width, height);
		//m_mapImage.insert(pair<string, cImage*>(key, img));
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, frameX, frameY, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::AddImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, int x, int y, bool isTrans, COLORREF transColor)
{
	cImage* img = FindImage(key);

	if (img == NULL)
	{
		img = new cImage;
		img->Setup(fileName, width, height, frameX, frameY, x, y, isTrans, transColor);
		m_mapImage.insert(make_pair(key, img));
	}

	return img;
}

cImage* cImageManager::FindImage(string key)
{
	// �ʿ��� Ű ���� �ش��ϴ� �ڷḦ ã�Ƽ� ���ͷ����Ϳ� �ִ´�.
	m_mapIter = m_mapImage.find(key);

	// Ű ���� �ش��ϴ� �����Ͱ� �ִ� ��� ������ ���� ��ȯ
	// first == Ű ��, second == ������ ��
	if (m_mapIter != m_mapImage.end())
		return m_mapIter->second;

	// Ű ���� �ش��ϴ� �����Ͱ� ���� ��� �� ��ȯ
	return NULL;
}

void cImageManager::DeleteImage(string key)
{
	m_mapIter = m_mapImage.find(key);

	if (m_mapIter != m_mapImage.end())
	{
		// �̹��� ����
		//if (m_mapIter->second != NULL)
		//	delete m_mapIter->second;

		// ��ũ�� ��� ���� ������ �ǹ�
		SAFE_DELETE(m_mapIter->second);

		// �ʿ��� �ش� Ű �ڷ� ����(�ʿ����� ����)
		m_mapImage.erase(m_mapIter);
	}
}

void cImageManager::DeleteAll()
{
	m_mapIter = m_mapImage.begin();

	// ��ü ����
	while (m_mapIter != m_mapImage.end())
	{
		SAFE_DELETE(m_mapIter->second);
		m_mapIter = m_mapImage.erase(m_mapIter);
	}
}

void cImageManager::Render(string key, HDC hdc)
{
	// �̹����� Ű ������ �˻��ؼ� �׸���.
	cImage* img = FindImage(key);
	if (img) img->Render(hdc);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY, int sizeX, int sizeY)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY, sizeX, sizeY);
}

void cImageManager::Render(string key, HDC hdc, int destX, int destY, int sourX, int sourY,
	int sourWidth, int sourHeight)
{
	cImage* img = FindImage(key);
	if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void cImageManager::AlphaRender(string key, HDC hdc, int destX, int destY, BYTE alpha)
{
	cImage* img = FindImage(key);
	if (img) img->AlphaRender(hdc, destX, destY, alpha);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY, sourX, sourY);
}

void cImageManager::FrameRender(string key, HDC hdc, int destX, int destY, int sourX, int sourY,
	int maxX, int maxY, int delay)
{
	cImage* img = FindImage(key);
	if (img) img->FrameRender(hdc, destX, destY, sourX, sourY, maxX, maxY, delay);
}

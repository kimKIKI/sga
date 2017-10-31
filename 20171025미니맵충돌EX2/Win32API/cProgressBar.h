#pragma once
class cProgressBar
{
private:
	cImage*		m_imgBack;
	cImage*		m_imgFront;

	RECT		m_rt;			// �׷��� ��ġ ��Ʈ
	int			m_nPosX;		// ���� x ��ġ
	int			m_nPosY;		// ���� y ��ġ
	int			m_nWidth;		// ���� ����
	int			m_nHeight;		// ���� ����
	int			m_nCurrWidth;	// ���� ü�¹� ����

public:
	cProgressBar(string strBack, string strFront, int width, int heigth);
	~cProgressBar();

	void Update();
	void Render();

	void SetGauge(float maxGauge, float currGauge);
	void SetPosX(int x) { m_nPosX = x; }
	void SetPosY(int y) { m_nPosY = y; }

	RECT GetRect() { return m_rt; }
};


#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// �÷��̾� �̹��� ����
	cImage*			m_pImgMapBuffer;	// ��� ���� �̹���

	float			m_fPosX;
	float			m_fPosY;

	float			m_fGravity;			// �߷� (������ ���)
	bool			m_isJumpping;		// ���� ���̳�?
	float			m_fJumpPower;		// ���� �Ŀ�

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)


	float			m_fMaxHp;
	float			m_fCurrHp;
	bool            m_IsLimit;        //����̹����� ������ �Ǵ��Ѵ�
	bool            m_bRide;          //�����̴� ��ü�� ſ���� �Ǵ��Ѵ�.
	

   //------------�ܺο���---------------------------------
	cProgressBar*	m_pHpBar;          //�ܺο���
	cMap*           m_pMap;            //�ܺο���
	RECT rt;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render();

	void SetLanding();
	RECT GetBoundingBox() {  
		rt = m_pPlayerImage->GetBoundingBox();
		 return m_pPlayerImage->GetBoundingBox(); }
	float GetPosX() { return m_pPlayerImage->GetPosX(); }
	float GetPosY() { return m_pPlayerImage->GetPosY(); }

	int GetDamageDelay() { return m_nDamageDelay; }
	void SetDamageDelay(int delay) { m_nDamageDelay = delay; }

	void SetMap(cMap * map) { m_pMap = map; };
	void SetRide(bool isride) { m_bRide = isride; };
	
};


#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// 플레이어 이미지 파일
	cImage*			m_pImgMapBuffer;	// 배경 정보 이미지

	float			m_fPosX;
	float			m_fPosY;

	float			m_fGravity;			// 중력 (점프시 사용)
	bool			m_isJumpping;		// 점프 중이냐?
	float			m_fJumpPower;		// 점프 파워

	int				m_nMapYPos;			// 플레이어의 바닥위 설정 (맵에 따라 다르게 설정이 필요)
	int				m_nDamageDelay;		// 연속 데미지 방지용 딜레이(무적 모드)


	float			m_fMaxHp;
	float			m_fCurrHp;
	bool            m_IsLimit;        //배경이미지의 끝인지 판단한다
	bool            m_bRide;          //움직이는 물체에 탓는지 판단한다.
	

   //------------외부연결---------------------------------
	cProgressBar*	m_pHpBar;          //외부연결
	cMap*           m_pMap;            //외부연결
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


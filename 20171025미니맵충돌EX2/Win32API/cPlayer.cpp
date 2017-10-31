#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	//m_pPlayerImage = new cImage;
	//m_pPlayerImage->Setup("images/ch.bmp", 960, 960, 12, 12,
	//	200, MAP1_Y, true, RGB(255, 0, 255));

	m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
	m_pPlayerImage->GetFrameWidth(), 10);
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_bRide = true;

	
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));
	saveData.push_back(itoa(m_fCurrHp, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);

	SetLanding();

	//vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");
	//if (!vecLoad.empty())
	//{
	//	m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
	//	m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
	//	m_fCurrHp = atoi(vecLoad[2].c_str());
	//}
}

void cPlayer::Update()
{
	float probeX = m_pPlayerImage->GetPosX();
	float probeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2;

	if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + 5);
	else if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - 5);

	//-----------KEY  CONTROLLER----------------------------
	if (g_pKeyManager->isStayKeyDown('A')  )
	{
		m_bRide = true;

		m_pPlayerImage->SetPosX(m_fPosX - 3.0f);
		float limit = (m_pPlayerImage->GetPosX());
		if ((int)limit <= 200 )
		{
			m_pPlayerImage->SetPosX(200);
			m_pMap->SetX(m_pMap->GetX() + 3);
			if (m_pMap->GetX() >= 0) //맵이동을 멈추는 과정
				m_pMap->SetX(0);
	     	}
	   }
	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_bRide = true;
		m_pPlayerImage->SetPosX(m_fPosX + 3.0f);
		float limit = (m_pPlayerImage->GetPosX());
		
		if ((int)limit >= 700  && m_pMap->GetX() >-1800)
		{
			m_pPlayerImage->SetPosX(700);  //플레이어 좌표는 움직이지 않고 
			m_pMap->SetX(m_pMap->GetX() - 3);
		}
	}


	if (g_pKeyManager->isStayKeyDown('W'))
	{
		m_bRide = true;
		m_pPlayerImage->SetPosY(m_fPosY - 3.0f);
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		m_bRide = true;
		m_pPlayerImage->SetPosY(m_fPosY + 3.0f);
	}

	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		m_bRide = true;
		m_fCurrHp -= 1.0f;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		m_bRide = true;
		m_fCurrHp += 1.0f;
	}

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_bRide = true;
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			probeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - 5) == false)
				SetLanding();
		}
	}
	//------------------------------------------------------------

	//움직이는 물체에 탑승시 물체에 따라 이동하게 한다.
	if (!m_bRide)
	{
		int RePos = m_pPlayerImage->GetPosX();
		
		if (m_pMap->GetMoveRight())
		{
			RePos += 1;
			m_pPlayerImage->SetPosX(RePos);
		}
		else 
		{
			RePos -= 1;
			m_pPlayerImage->SetPosX(RePos);
		}
		
	}

	if (m_nDamageDelay > 0)
		--m_nDamageDelay;

	m_fPosX = m_pPlayerImage->GetPosX();
	m_fPosY = m_pPlayerImage->GetPosY();

	m_pHpBar->SetPosX(m_fPosX);
	m_pHpBar->SetPosY(m_fPosY - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();



}

void cPlayer::MiniRender()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	EllipseMakeCenter(g_hDC, m_pPlayerImage->GetPosX(), m_pPlayerImage->GetPosY(), 10, 10);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	BoudingLineMake(g_hDC, m_pPlayerImage->GetBoundingBox().left,
		m_pPlayerImage->GetBoundingBox().top,
		m_pPlayerImage->GetFrameWidth(),
		m_pPlayerImage->GetFrameHeight());

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	// 무적 모드 중에는 반짝이게 표현
	if (m_nDamageDelay % 2 == 0)
	{
		m_pPlayerImage->FrameRender(g_hDC,
			m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
			m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
			1, 0, 8, 0, 3);
	}
	
	char strD[128];
	sprintf_s(strD, "GETX 좌표 : %d",(int) m_pPlayerImage->GetPosX());//앞에 보여질 부분
	TextOut(g_hDC, 10, 300, strD, strlen(strD));
	

	m_pHpBar->Render();
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
}
#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame():
           m_Imagect(0)
          , m_Imagect2(0)
	      , m_isPlaying(false)
	      , m_isMain(false)
	      , m_LoadingDelay(LOADINGDELAY)
	      , m_ImagectDelay(IMAGEDELAY)
	
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
 
	

}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMainGame::Setup()
{
	m_pMap->Setup();
	m_pMap->SetMap(m_pPlayer);

	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->Setup();
	
	

}

void cMainGame::Update()
{
	cGameNode::Update();

	   // 시작과 동시 카운트 
	if (!m_isPlaying && !m_isMain)
		--m_LoadingDelay;


	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
	}
	else if (m_isMain)
	{
		if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		{
			m_isMain = false;
			m_isPlaying = true;
			Setup();
		}
	}

	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN) || m_LoadingDelay <= 0)
	{
		Setup();
		m_isMain = true;
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pImgBackground->Render(g_hDC, 0, 0);
		m_pMap->Render();
		MiniMapRender();
		m_pPlayer->Render();
	   // MiniMapRender2();


	}
	else if (m_isMain) 
	{
		//메인화면에는 게임 메인이미지을 출력한다
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "메인입니다.", strlen("메인입니다."));
		g_pImageManager->FindImage("Main")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		g_pImageManager->FindImage("StartText")->FrameRender(g_hDC, WINSIZEX / 4 + 175, WINSIZEY / 2 + 100, 0, 0, 1, 0, 20);
	
	}
	else
	{

		//char strD[128];
		//sprintf_s(strD, "두번째선택 : %d", );//앞에 보여질 부분
		//TextOut(g_hDC, 300, 300, strD, strlen(strD));
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));

		      //첨시작 검은 화면       
		g_pImageManager->FindImage("Loading")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);

		   //로딩화면 마크또는 로그보여줌
		if (m_Imagect < 255 && m_ImagectDelay > 0)    //m_Iagect 0 ~255까지 increase
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, ++m_Imagect);
		  
		   //로딩화면이 보인상태로  감소카운팅시작  --로딩화면 유지 시간 = m_ImagetDelay
		if (m_Imagect >= 255 && m_ImagectDelay > 0)  
		{
			--m_ImagectDelay;
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 255);
		}
		     
		      //로딩로고  다시 어둡게 시작 
		if (m_Imagect > 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, --m_Imagect);
		     //로딩이 사라짐 
		if (m_Imagect <= 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 0);

	}
}
  
void cMainGame::LoadImageFromFile()
{
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/backGround.bmp",3000, 564); //뒷배경
	

	//Starting logo
	g_pImageManager->AddImage("Loading", "images/BlockColor.bmp", 1200, 600);
	g_pImageManager->AddImage("LoadingLogo", "images/로딩화면.bmp", 1200, 600);
	g_pImageManager->AddImage("Main", "images/메인화면.bmp", 1200, 600);
	g_pImageManager->AddImage("StartText", "images/스타트로고.bmp", 700, 80, 2, 1,
		WINSIZEX / 4, WINSIZEY / 4 + 100, true, RGB(255, 0, 255));



	/* 맵 */  
	g_pImageManager->AddImage("Map", "images/FrontGround.bmp", 3000, 600); 
	g_pImageManager->AddImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵 */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX / 5, WINSIZEY / 5);

	
	/* 프로그레스바 */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* 지형물 오브젝트*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 894, 894, true, RGB(255, 255, 255));
	

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 200, MAP1_Y, true, RGB(255, 0, 255));

	/* 몬스터 */


	/*사이즈 작게 축소*/

	  // m_pNewBufferMap  =  g_pImageManager->AddImage("MiniMap2", WINSIZEX , WINSIZEY / 5);  
	   //m_pImgSmallSizeBack = g_pImageManager->AddImage("BackGround", "images/ChloeBennet.bmp", 1200, 200); //뒷배경
	   //충돌체
	  // m_pImgSmallSizeFront = g_pImageManager->AddImage("BackFront", "images/worms_map_magenta.bmp", 1200, 200,true,RGB(255,0,255));
	
	 /*아이템*/
	g_pImageManager->AddImage("Coin", "images/ItemCoin.bmp",384, 64, 6, 1, 1, 1, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("Item", "images/Item.bmp", 128, 128, true, RGB(255, 0, 255));

}

void cMainGame::MiniMapRender()
{

	m_pPlayer->MiniRender();

	//담겨있는 화면의 설정크기
	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY /5 );
	//MiniMap->Render
	
	//미니맵의 생성위치 
	m_pImgMiniMap->Render(m_pImgBackBuffer->GetMemDC(), 500, 120);
	//m_pImgBackMini


}

        // 전체 길이로 보여질 미니맵
void cMainGame::MiniMapRender2()
{

	m_pPlayer->MiniRender();
	
	m_pImageSmallOBJ = g_pImageManager->FindImage("Object");

	//m_pImgSmallSizeBack->Render(m_pNewBufferMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	//m_pImgSmallSizeFront->Render(m_pNewBufferMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	//m_pImageSmallOBJ->Render(m_pNewBufferMap->GetMemDC(), 0, 0, WINSIZEX/13, WINSIZEY /15);

	// ->Render(m_pNewBufferMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5);
	m_pNewBufferMap->Render(m_pImgBackBuffer->GetMemDC(), 0, 0);
	
};



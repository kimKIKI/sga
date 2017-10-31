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

	   // ���۰� ���� ī��Ʈ 
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
	// ������� �̹����� ĥ�Ѵ�.
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
		//����ȭ�鿡�� ���� �����̹����� ����Ѵ�
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "�����Դϴ�.", strlen("�����Դϴ�."));
		g_pImageManager->FindImage("Main")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
		g_pImageManager->FindImage("StartText")->FrameRender(g_hDC, WINSIZEX / 4 + 175, WINSIZEY / 2 + 100, 0, 0, 1, 0, 20);
	
	}
	else
	{

		//char strD[128];
		//sprintf_s(strD, "�ι�°���� : %d", );//�տ� ������ �κ�
		//TextOut(g_hDC, 300, 300, strD, strlen(strD));
		//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));

		      //÷���� ���� ȭ��       
		g_pImageManager->FindImage("Loading")->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);

		   //�ε�ȭ�� ��ũ�Ǵ� �α׺�����
		if (m_Imagect < 255 && m_ImagectDelay > 0)    //m_Iagect 0 ~255���� increase
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, ++m_Imagect);
		  
		   //�ε�ȭ���� ���λ��·�  ����ī���ý���  --�ε�ȭ�� ���� �ð� = m_ImagetDelay
		if (m_Imagect >= 255 && m_ImagectDelay > 0)  
		{
			--m_ImagectDelay;
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 255);
		}
		     
		      //�ε��ΰ�  �ٽ� ��Ӱ� ���� 
		if (m_Imagect > 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, --m_Imagect);
		     //�ε��� ����� 
		if (m_Imagect <= 0 && m_ImagectDelay <= 0)
			g_pImageManager->FindImage("LoadingLogo")->AlphaRender(g_hDC, 0, 0, 0);

	}
}
  
void cMainGame::LoadImageFromFile()
{
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/backGround.bmp",3000, 564); //�޹��
	

	//Starting logo
	g_pImageManager->AddImage("Loading", "images/BlockColor.bmp", 1200, 600);
	g_pImageManager->AddImage("LoadingLogo", "images/�ε�ȭ��.bmp", 1200, 600);
	g_pImageManager->AddImage("Main", "images/����ȭ��.bmp", 1200, 600);
	g_pImageManager->AddImage("StartText", "images/��ŸƮ�ΰ�.bmp", 700, 80, 2, 1,
		WINSIZEX / 4, WINSIZEY / 4 + 100, true, RGB(255, 0, 255));



	/* �� */  
	g_pImageManager->AddImage("Map", "images/FrontGround.bmp", 3000, 600); 
	g_pImageManager->AddImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* �̴ϸ� */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX / 5, WINSIZEY / 5);

	
	/* ���α׷����� */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* ������ ������Ʈ*/
	g_pImageManager->AddImage("Object", "images/angrybirds-name-03.bmp", 894, 894, true, RGB(255, 255, 255));
	

	/* �÷��̾� */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 200, MAP1_Y, true, RGB(255, 0, 255));

	/* ���� */


	/*������ �۰� ���*/

	  // m_pNewBufferMap  =  g_pImageManager->AddImage("MiniMap2", WINSIZEX , WINSIZEY / 5);  
	   //m_pImgSmallSizeBack = g_pImageManager->AddImage("BackGround", "images/ChloeBennet.bmp", 1200, 200); //�޹��
	   //�浹ü
	  // m_pImgSmallSizeFront = g_pImageManager->AddImage("BackFront", "images/worms_map_magenta.bmp", 1200, 200,true,RGB(255,0,255));
	
	 /*������*/
	g_pImageManager->AddImage("Coin", "images/ItemCoin.bmp",384, 64, 6, 1, 1, 1, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("Item", "images/Item.bmp", 128, 128, true, RGB(255, 0, 255));

}

void cMainGame::MiniMapRender()
{

	m_pPlayer->MiniRender();

	//����ִ� ȭ���� ����ũ��
	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY /5 );
	//MiniMap->Render
	
	//�̴ϸ��� ������ġ 
	m_pImgMiniMap->Render(m_pImgBackBuffer->GetMemDC(), 500, 120);
	//m_pImgBackMini


}

        // ��ü ���̷� ������ �̴ϸ�
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



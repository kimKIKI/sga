#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"


class cObject;

cMap::cMap()
{
	m_pImgGround = g_pImageManager->FindImage("Map");
	m_pObject = g_pImageManager->FindImage("Object");
	m_pCoin = g_pImageManager->FindImage("Coin");
	m_pItem = g_pImageManager->FindImage("Item");


	//--------------------------------------------------------------------------------
	m_pNewBufferMap = g_pImageManager->AddImage("MiniMap2", WINSIZEX, WINSIZEY / 5);
	m_pImgSmallSizeBack = g_pImageManager->AddImage("BackGround", "images/backGround.bmp", 1200, 100); //뒷배경																							//충돌체
	m_pImgSmallSizeFront = g_pImageManager->AddImage("BackFront", "images/FrontGround.bmp", 1200, 100, true, RGB(255, 0, 255));
	//--------------------------------------------------------------------------------

	
	

	//오브젝트의 첫 spawn Position -----------
	m_pObject->SetPosX(300);
	m_pObject->SetPosY(500);
	m_pItem->SetPosX(645);
	m_pItem->SetPosY(365);
	m_pCoin->SetPosX(200);
	m_pCoin->SetPosY(300);


	int spawnPosX = m_pObject->GetPosX();
	int spawnPosY = m_pObject->GetPosY();

	//일단 하나만 만들어보고 ----vector---------------
	MakeObject(spawnPosX,spawnPosY,300,300);
	CreateItem(m_pCoin->GetPosX(), m_pCoin->GetPosY(), 128, 128);




	m_bMoveRight = true;

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_MapSpeed = 0;
	m_GetX = 0; //맵의 위치
	m_MapsizeX = 3000; //Mapsize사이즈에 접근하기 위해서 

	m_EnemyCount = 3; //Level Count 3개

	//init
	m_iCoin = 100;

	//DEBUG________________________
     	RECT_POSX = 0;
		Pixel_POSX = 0;
   //DEGUG END---------------------

}


cMap::~cMap()
{
}

void cMap::Setup()
{

	//자동으로 움직이는 enemy를 위해서 class 화 준비-----
	//cObject   cEnemy;
	for (int i = 0; i < m_EnemyCount; ++i)
	{
		//m_vecCObjects.push_back(cEnemy);
	}
	//----------------------------------------------------


}

void cMap::Update()
{
	MoveObject();

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);

	
	for (auto iter = m_vecObjects.begin(); iter != m_vecObjects.end(); ++iter)
	{
		RECT rt;
		//cout << iter->rt.left << " " << endl;

 		if (IntersectRect(&rt, &m_cPlayer->GetBoundingBox(), &iter->rt))
		{
			if (iter->name == "아이템")
			{

				m_iCoin += 10000;

				iter->bVisible = false;
			    iter = m_vecObjects.erase(iter);
			
					break;

			}
			//cout << "충돌" << endl;
			 RECT1 = m_cPlayer->GetBoundingBox().left;
			 RECT2 = iter->rt.left;
			//탑승유무판단
			 m_cPlayer->SetRide(false);
			break;
		}
	}

}

void cMap::Render()
{
	
	//충돌 처리용 이미지 버퍼에 그림을 그린다.
	m_pImgGround->Render(m_pImgMapBuffer->GetMemDC(), m_GetX, 0, 3000, 600);
	m_pObject->Render(m_pImgMapBuffer->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 180, 70);
	m_pItem->Render(m_pImgMapBuffer->GetMemDC(), m_pItem->GetPosX(), m_pItem->GetPosY(), 100, 100);

	for (auto iter = m_vecObjects.begin(); iter != m_vecObjects.end(); ++iter)
	{
		if (iter->bVisible)
		{
			m_pCoin->FrameRender(g_hDC, m_pCoin->GetPosX(), m_pCoin->GetPosY(), 0, 0, 5, 0, 3);
		} 
		
		
	}

	
	//2차 미니맵 이미지 
	m_pImgSmallSizeBack->Render(m_pNewBufferMap->GetMemDC(), 0, 0, 1200, 200);
	m_pImgSmallSizeFront->Render(m_pNewBufferMap->GetMemDC(), 0, 0, 1200, 200);
	m_pObject->Render(m_pNewBufferMap->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 180, 70);

	// 백버퍼에 그린다.
	m_pNewBufferMap->Render(g_hDC, 0, 0);
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	
	//DEBUG  -TEXTING -- STRING___________________________________________
	char strD[128];
	sprintf_s(strD, "오브젝트좌표 : %d", Pixel_POSX );//앞에 보여질 부분
	TextOut(g_hDC, 10, 400, strD, strlen(strD));

	char strA[128];
	sprintf_s(strA, "오브젝트RECT : %d", RECT_POSX);//앞에 보여질 부분
	TextOut(g_hDC, 10, 420, strA, strlen(strA));

	char strB[128];
	sprintf_s(strB, "plsyer충돌좌표 : %d", RECT1);//앞에 보여질 부분
	TextOut(g_hDC, 10, 220, strB, strlen(strB));

	char strF[128];
	sprintf_s(strF, "iter좌표 : %d", RECT2);//앞에 보여질 부분
	TextOut(g_hDC, 10, 200, strF, strlen(strF));

	char strG[128];
	sprintf_s(strG, "Coin : %d", m_iCoin);//앞에 보여질 부분
	TextOut(g_hDC, 10, 180, strG, strlen(strG));

  //------END-----------------------------------------------------
	
	
}

//움직이는 오브젝트 생성
void cMap::MakeObject(int posX, int posY,int width,int Height)
{
	stObject  newObj;
	newObj.bVisible = false;
	newObj.rt = { posX-width/2 ,posY-Height/2,posX+width/2,posY+Height/2};
	m_vecObjects.push_back(newObj);
}

void cMap::MoveObject()
{

   for (auto iter = m_vecObjects.begin(); iter != m_vecObjects.end(); ++iter)
        {
	         if (m_bMoveRight && m_pObject->GetPosX() < 500)
	               {
	              	//ImagePixel의 MOVE
		            m_pObject->SetPosX(m_pObject->GetPosX() + 1);
		            //RECT 의 MOVE
		           iter->rt.left = m_pObject->GetPosX() + 1;
				                                  //Box  size 30 
		           iter->rt.right = m_pObject->GetPosX() +30 + 1;

				   //DEGUB_________________________________
				   RECT_POSX = iter->rt.left;
				   Pixel_POSX = m_pObject->GetPosX();
				   //DEGUB END-----------------------------


		      if (m_pObject->GetPosX() >= 500)
			        m_bMoveRight = false;

	                }
	         else if (m_pObject->GetPosX() > 300)
	          {
		          //ImagePixel의 MOVE              -1 스피드값
	           	m_pObject->SetPosX(m_pObject->GetPosX() - 1);
		          //RECT의 MOVE
		       iter->rt.left = m_pObject->GetPosX() - 1;
		       iter->rt.right = m_pObject->GetPosX()+30 -1;


		          if (m_pObject->GetPosX() <= 300)
			         m_bMoveRight = true;
	             }

			 
               } //VECTER END
	
             }

void cMap::CreateItem(int posX, int posY, int width, int Height)
{

	stObject newItem;
	newItem.name = "아이템";
	newItem.bVisible = true;
	newItem.rt = { posX - width / 2 ,posY - Height / 2,posX + width / 2,posY + Height / 2 };
	m_vecObjects.push_back(newItem);

}
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
	m_pImgSmallSizeBack = g_pImageManager->AddImage("BackGround", "images/backGround.bmp", 1200, 100); //�޹��																							//�浹ü
	m_pImgSmallSizeFront = g_pImageManager->AddImage("BackFront", "images/FrontGround.bmp", 1200, 100, true, RGB(255, 0, 255));
	//--------------------------------------------------------------------------------

	
	

	//������Ʈ�� ù spawn Position -----------
	m_pObject->SetPosX(300);
	m_pObject->SetPosY(500);
	m_pItem->SetPosX(645);
	m_pItem->SetPosY(365);
	m_pCoin->SetPosX(200);
	m_pCoin->SetPosY(300);


	int spawnPosX = m_pObject->GetPosX();
	int spawnPosY = m_pObject->GetPosY();

	//�ϴ� �ϳ��� ������ ----vector---------------
	MakeObject(spawnPosX,spawnPosY,300,300);
	CreateItem(m_pCoin->GetPosX(), m_pCoin->GetPosY(), 128, 128);




	m_bMoveRight = true;

	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_MapSpeed = 0;
	m_GetX = 0; //���� ��ġ
	m_MapsizeX = 3000; //Mapsize����� �����ϱ� ���ؼ� 

	m_EnemyCount = 3; //Level Count 3��

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

	//�ڵ����� �����̴� enemy�� ���ؼ� class ȭ �غ�-----
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
			if (iter->name == "������")
			{

				m_iCoin += 10000;

				iter->bVisible = false;
			    iter = m_vecObjects.erase(iter);
			
					break;

			}
			//cout << "�浹" << endl;
			 RECT1 = m_cPlayer->GetBoundingBox().left;
			 RECT2 = iter->rt.left;
			//ž�������Ǵ�
			 m_cPlayer->SetRide(false);
			break;
		}
	}

}

void cMap::Render()
{
	
	//�浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
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

	
	//2�� �̴ϸ� �̹��� 
	m_pImgSmallSizeBack->Render(m_pNewBufferMap->GetMemDC(), 0, 0, 1200, 200);
	m_pImgSmallSizeFront->Render(m_pNewBufferMap->GetMemDC(), 0, 0, 1200, 200);
	m_pObject->Render(m_pNewBufferMap->GetMemDC(), m_pObject->GetPosX(), m_pObject->GetPosY(), 180, 70);

	// ����ۿ� �׸���.
	m_pNewBufferMap->Render(g_hDC, 0, 0);
	m_pImgMapBuffer->Render(g_hDC, 0, 0);

	
	//DEBUG  -TEXTING -- STRING___________________________________________
	char strD[128];
	sprintf_s(strD, "������Ʈ��ǥ : %d", Pixel_POSX );//�տ� ������ �κ�
	TextOut(g_hDC, 10, 400, strD, strlen(strD));

	char strA[128];
	sprintf_s(strA, "������ƮRECT : %d", RECT_POSX);//�տ� ������ �κ�
	TextOut(g_hDC, 10, 420, strA, strlen(strA));

	char strB[128];
	sprintf_s(strB, "plsyer�浹��ǥ : %d", RECT1);//�տ� ������ �κ�
	TextOut(g_hDC, 10, 220, strB, strlen(strB));

	char strF[128];
	sprintf_s(strF, "iter��ǥ : %d", RECT2);//�տ� ������ �κ�
	TextOut(g_hDC, 10, 200, strF, strlen(strF));

	char strG[128];
	sprintf_s(strG, "Coin : %d", m_iCoin);//�տ� ������ �κ�
	TextOut(g_hDC, 10, 180, strG, strlen(strG));

  //------END-----------------------------------------------------
	
	
}

//�����̴� ������Ʈ ����
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
	              	//ImagePixel�� MOVE
		            m_pObject->SetPosX(m_pObject->GetPosX() + 1);
		            //RECT �� MOVE
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
		          //ImagePixel�� MOVE              -1 ���ǵ尪
	           	m_pObject->SetPosX(m_pObject->GetPosX() - 1);
		          //RECT�� MOVE
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
	newItem.name = "������";
	newItem.bVisible = true;
	newItem.rt = { posX - width / 2 ,posY - Height / 2,posX + width / 2,posY + Height / 2 };
	m_vecObjects.push_back(newItem);

}
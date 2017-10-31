#pragma once

#include "cObject.h"

class cPlayer;

struct stObject {

	RECT rt;
	char*name;
	int posX;
	int posY;
	int Coin;
	int Score;
	bool bVisible;

};


class cMap
{
private:
	cImage*		m_pImgGround;		 // �⺻ ���� �̹���
	cImage*		m_pObject;			 // �����̴� ������Ʈ
	cImage*     m_pItem;              //Item
	cImage*     m_pCoin;              //Coin
	bool		m_bMoveRight;

	int         m_EnemyCount;        //��ü ��������

	vector<cObject>  m_vecCObjects;  //Ŭ��������
	vector<stObject> m_vecObjects;   //����ü ���� 



	//-----------------------------------------------------------------------------
	cImage* m_pNewBufferMap;        //MinimapBuffer
	cImage* m_pImgSmallSizeBack;    //�޹��  
	cImage* m_pImgSmallSizeFront;   //�浹ü �к�
	//-----------------------------------------------------------------------------
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����


	float       m_MapSpeed;         //���̵�
	void        MoveObject();
	int         m_GetX;
	int         m_MapsizeX;         //������ �Ǵ��ϱ� ���ؼ� Xsize
	int         m_iCoin;             //���� �������� 
	//-----------�ܺο���-----------------------------------------------------------
	cPlayer*   m_cPlayer;

	//--------DEBUG----------------------------------------------------------------
	int        RECT_POSX;
	int        Pixel_POSX;
	int        RECT1;
	int        RECT2;
	//---DEBUG--END-----------------------------------------------------------------

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetMoveSpeed(float Speed) { m_MapSpeed = Speed; }
	float GetMoveSpeed() { return  m_MapSpeed; };

	int  GetMapSize() { return m_MapsizeX; };
	int  GetX() { return m_GetX; };
	void SetX(int move) { m_GetX = move; };

	void MakeObject(int posX,int posY,int width,int Height);

	vector<cObject> GetVecObjects(){  return  m_vecCObjects;};
	vector<stObject> GetObjects() { return m_vecObjects; }
	void SetMap(cPlayer* player) { m_cPlayer = player; };
	bool GetMoveRight() { return m_bMoveRight; };
	void CreateItem(int x,int y,int width,int height);
};


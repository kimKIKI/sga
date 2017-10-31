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
	cImage*		m_pImgGround;		 // 기본 지형 이미지
	cImage*		m_pObject;			 // 움직이는 오브젝트
	cImage*     m_pItem;              //Item
	cImage*     m_pCoin;              //Coin
	bool		m_bMoveRight;

	int         m_EnemyCount;        //전체 적군숫자

	vector<cObject>  m_vecCObjects;  //클래스벡터
	vector<stObject> m_vecObjects;   //구조체 벡터 



	//-----------------------------------------------------------------------------
	cImage* m_pNewBufferMap;        //MinimapBuffer
	cImage* m_pImgSmallSizeBack;    //뒷배경  
	cImage* m_pImgSmallSizeFront;   //충돌체 분분
	//-----------------------------------------------------------------------------
	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼


	float       m_MapSpeed;         //맵이동
	void        MoveObject();
	int         m_GetX;
	int         m_MapsizeX;         //조건을 판단하기 위해서 Xsize
	int         m_iCoin;             //현재 코인증가 
	//-----------외부연결-----------------------------------------------------------
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


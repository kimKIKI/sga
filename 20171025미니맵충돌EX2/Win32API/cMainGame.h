#pragma once
#include "cGameNode.h"

#define LOADINGDELAY 300
#define IMAGEDELAY 100


class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;
	int				m_LoadingDelay; //처음시작하자 마다 딜레이
	int				m_Imagect;    //?
	int				m_Imagect2;   //?
	int				m_ImagectDelay;






	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgBackMini;
	cImage*         m_pImgBord;            // 버퍼에서 저장된 이미지 
	cImage*			m_pImgMiniMap;		   // 미니맵용 이미지 버퍼
	//------------------------------------------------------------
	cImage*         m_pNewBufferMap;       //새로운 미니 버퍼맵
	cImage*         m_pImgSmallSizeBack;   //뒷배경
	cImage*         m_pImgSmallSizeFront;  //앞배경
	cImage*         m_pImageSmallOBJ;      //오브젝트 
	bool            m_isMain;              //엔터치기전에 타이틀화면이 보이게함



	
	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void MiniMapRender2();
	
	virtual void Update() override;
	virtual void Render() override;
};
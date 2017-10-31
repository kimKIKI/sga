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
	int				m_LoadingDelay; //ó���������� ���� ������
	int				m_Imagect;    //?
	int				m_Imagect2;   //?
	int				m_ImagectDelay;






	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgBackMini;
	cImage*         m_pImgBord;            // ���ۿ��� ����� �̹��� 
	cImage*			m_pImgMiniMap;		   // �̴ϸʿ� �̹��� ����
	//------------------------------------------------------------
	cImage*         m_pNewBufferMap;       //���ο� �̴� ���۸�
	cImage*         m_pImgSmallSizeBack;   //�޹��
	cImage*         m_pImgSmallSizeFront;  //�չ��
	cImage*         m_pImageSmallOBJ;      //������Ʈ 
	bool            m_isMain;              //����ġ������ Ÿ��Ʋȭ���� ���̰���



	
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
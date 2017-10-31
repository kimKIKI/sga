#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:

	bool			m_isPlaying;

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	void LoadImageFromFile();
	

public:
	cMainGame();
	~cMainGame();

	void Setup();
	virtual void Update() override;
	virtual void Render() override;
};
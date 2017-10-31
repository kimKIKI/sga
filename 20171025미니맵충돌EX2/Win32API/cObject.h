#pragma once

class cMap;
class cPlayer;



class cObject
{

private:
	float posX;
	float posY;
	RECT  m_rtBody;
	char* name;
	cImage* m_imgOBJ;


public:
	cObject(string SpriteName);
	~cObject();

	RECT GetRect() {return m_rtBody;};
};


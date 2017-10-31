#include "stdafx.h"
#include "cObject.h"
#include "cMap.h"
#include "cPlayer.h"



cObject::cObject(string spriteKey)
{
	m_imgOBJ = g_pImageManager->FindImage(spriteKey);
}


cObject::~cObject()
{

}

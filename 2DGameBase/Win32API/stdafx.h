	// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <time.h>
#include <string.h>
#include <map>
#include <assert.h>

using namespace std;

//==================================================================
//		## �����ι� - ��ũ�� ## (������â �ʱ�ȭ)
//==================================================================
#define WINNAME (LPCWSTR)(TEXT("�ڵ� ������ ���Ű� ȯ�� �մϴ�."))
#define WINSTARTX		0
#define WINSTARTY		0
#define WINSIZEX		800
#define WINSIZEY		600
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#define PURE			= 0
#define PI				3.141592654f
#define GRAVITY			0.3f

#include "MacroUtility.h"

//==================================================================
//		## ��ũ���Լ� ## (Ŭ���� �����Ҵ�� �κ� ����)
//==================================================================
#define SAFE_DELETE(p)		{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY	{ if(p) { delete[] (p); (p) = NULL; } }

//==================================================================
//		## �Ŵ��� �߰� ##
//==================================================================
#include "cKeyManager.h"
#include "cImage.h"
#include "cImageManager.h"
#include "cFileDataManager.h"
#include "cPixelCollision.h"

//==================================================================
//		## �������� ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern HDC			g_hDC;
#pragma once
#include "cSingletonBase.h"
#include <bitset>

#define g_pKeyManager cKeyManager::GetInstance()

using namespace std;

#define KEYMAX 256

class cKeyManager :	public cSingletonBase<cKeyManager>
{
private:
	bitset<KEYMAX> m_bitKeyUp;
	bitset<KEYMAX> m_bitKeyDown;

public:
	// Ű �Ŵ��� �ʱ�ȭ
	void Setup();

	// Ű�� �ѹ� ����
	bool isOnceKeyDown(int key);
	// Ű�� ���ȴ� ��
	bool isOnceKeyUp(int key);
	// Ű�� ������ ����
	bool isStayKeyDown(int key);
	// ���Ű(Ű�� ���� Ű)
	bool isToggleKey(int key);
};
#include "stdafx.h"
#include "cKeyManager.h"

void cKeyManager::Setup()
{
	for (int i = 0; i < KEYMAX; ++i)
	{
		m_bitKeyUp.set(i, false);
		m_bitKeyDown.set(i, false);
	}
}

bool cKeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// Ű�� ������ ������ ���� ����
		if (!m_bitKeyDown[key])
		{
			// ���� ���·� ���� �ϰ� Ŭ�� �ƴٰ� Ʈ�� ��ȯ
			m_bitKeyDown.set(key, true);
			return true;
		}
	}
	else
	{
		m_bitKeyDown.set(key, false);
	}

	return false;
}

bool cKeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_bitKeyUp.set(key, true);
	}
	else
	{
		// ������ �ִٰ� ���� ��
		if (m_bitKeyUp[key])
		{
			m_bitKeyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
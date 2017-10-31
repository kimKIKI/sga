#pragma once

/*
�̱��� ���� : ���� ��ü ���� ���
�ν��Ͻ��� ȣ�� �� ó�� ȣ��(�ν��Ͻ��� ���� �Ǳ� ��)�� �Ǹ�
�ν��Ͻ��� ���� �ؼ� ��ȯ �Ѵ�.
�ν��Ͻ��� ���� �� ���� ȣ�� �ϰ� �Ǹ� ������ ���� �� �ν��Ͻ��� ��ȯ�Ѵ�.
*/

template <class T> // template<typename T>
class cSingletonBase
{
protected:
	// �̱��� �ν��Ͻ� ����
	static T* instance;

	cSingletonBase() {};
	~cSingletonBase() {};

public:
	// �̱��� �ν��Ͻ� ��������
	static T* GetInstance();
	// �̱��� �ν��Ͻ� �����ϱ�
	void ReleaseInstance();
};

// �̱��� �ʱ�ȭ
template<typename T>
T* cSingletonBase<T>::instance = NULL;

// �̱��� �ν��Ͻ� ��������
template<typename T>
T* cSingletonBase<T>::GetInstance()
{
	// �̱��� �ν��Ͻ��� ���� �Ǿ� ���� �ʴٸ� ���� ����
	if (!instance)
		instance  = new T;

	return instance;
}

// �̱��� �ν��Ͻ� �����ϱ�
template<typename T>
void cSingletonBase<T>::ReleaseInstance()
{
	// �̱��� �ν��Ͻ��� �����Ǿ� �ִٸ� ���� �Ѵ�.
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}
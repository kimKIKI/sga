#include <iostream>

using namespace std;

int main()
{
	// �迭[]
	//���� ������ �޸� ������ ���������� �����Ǿ� �ִ� ��.

	//�迭 3�� ����
	//int number[3];
	//
	//number[0] = 2;
	//number[1] = 3;
	//number[2] = 7;
	//
	////                [0]   [1]  [2]  [3]
	//int number2[4] = { 100, 200, 300, 400 };
	//
	//cout << number2[2] << endl;
	//
	//int num[] = { 1, 2, 3, 4 };

	int number[10];

	for (int i = 0; i < 10; i++)
	{
		number[i] = i + 1;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << number[i] << endl;
	}



	return 0;
}
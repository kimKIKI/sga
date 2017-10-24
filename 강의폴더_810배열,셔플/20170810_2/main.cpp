#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));
	/*
	int number[10];
	//셔플 알고리즘
	int dest, sour, temp;

	for (int i = 0; i < 10; i++)
	{
		number[i] = i + 1;
	}

	for (int i = 0; i < 1000; i++)
	{
		//0 ~ 9
		dest = rand() % 10; //1
		sour = rand() % 10; //9

		//temp = number[2]
		temp = number[dest];
		//number[2] = number[8]
		number[dest] = number[sour];
		//number[8] = temp
		number[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << number[i] << endl;
	}
	*/

	int lottoNum[45];

	for (int i = 0; i < 45; i++)
	{
		lottoNum[i] = i + 1;
	}

	int dest, sour, temp;

	for (int i = 0; i < 777; i++)
	{
		dest = rand() % 45;
		sour = rand() % 45;

		temp = lottoNum[dest];
		lottoNum[dest] = lottoNum[sour];
		lottoNum[sour] = temp;
	}

	for (int i = 0; i < 6; i++)
	{
		cout << lottoNum[i] << endl;
	}



	return 0;
}
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));

	int comNum1, comNum2, comNum3;
	int playerNum1, playerNum2, playerNum3;
	int strikeCount = 0;
	int ballCount = 0;
	int roundCount = 9;

	while (true)
	{
		comNum1 = rand() % 10;
		if (comNum1 == 0) continue;

		comNum2 = rand() % 10;
		if (comNum2 == comNum1) continue;

		comNum3 = rand() % 10;
		if (comNum3 == comNum1 || comNum3 == comNum2) continue;

		break;
	}

	cout << "============= 숫 자 야 구 ==============" << endl;
	cout << "10번의 기회가 있으니 맞춰보시요!" << endl;

	while (true)
	{
		cout << "첫번째 수 입력 : ";
		cin >> playerNum1;

		if (playerNum1 <= 0 || playerNum1 > 9)
		{
			cout << "1 ~ 9까지만 입력하시요" << endl;
			continue;
		}
		cout << "두번째 수 입력 : ";
		cin >> playerNum2;

		if (playerNum2 < 0 || playerNum2 > 9)
		{
			cout << "0 ~ 9까지만 입력하시요" << endl;
			continue;
		}

		cout << "세번째 수 입력 : ";
		cin >> playerNum3;
		if (playerNum3 < 0 || playerNum3 > 9)
		{
			cout << "0 ~ 9까지만 입력하시요" << endl;
			continue;
		}

		if (comNum1 == playerNum1) strikeCount++;
		if (comNum1 == playerNum2) ballCount++;
		if (comNum1 == playerNum3) ballCount++;
		if (comNum2 == playerNum1) ballCount++;
		if (comNum2 == playerNum2) strikeCount++;
		if (comNum2 == playerNum3) ballCount++;
		if (comNum3 == playerNum1) ballCount++;
		if (comNum3 == playerNum2) ballCount++;
		if (comNum3 == playerNum3) strikeCount++;

		if (strikeCount < 1 && ballCount < 1)
		{
			cout << "아웃!" << endl;
		}
		else if (strikeCount > 0 && ballCount < 1)
		{
			cout << strikeCount << " 스트라이크" << endl;
		}
		else if (strikeCount < 1 && ballCount > 0)
		{
			cout << ballCount << " 볼" << endl;
		}
		else
		{
			cout << strikeCount << " 스트라이크, " << ballCount << " 볼" << endl;
		}
		

		if (strikeCount == 3)
		{
			cout << "You Win!" << endl;
			break;
		}


		cout << roundCount << " 라운드 남았다" << endl;
		roundCount--;

		if (roundCount < 0) break;

		strikeCount = ballCount = 0;
	}

}
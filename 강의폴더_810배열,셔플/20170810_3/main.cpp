#include <iostream>

using namespace std;

int main()
{
	float speed = 3.3f;

	int moveDistance = speed * 3;

	//casting == 형변환

	cout << "스피드 : " << (int)speed << endl;
	cout << "이동거리 : " << moveDistance << endl;

	//C스타일 형변환
	//(자료형)변수
	//장점 : 무조건 형을 바꿔버린다
	//단점 : 무조건 형을 바꿔버린다

	int num = 66;

	cout << (char)num << endl;

	//C++ 형변환
	//static_cast<형>(변수) : 일반적인 형변환
	//reinterpret_cast : 비트단위로 형변환
	
	//알아만 두세요
	//const_cast : const(상수) 속성을 없애버린다 == 고로 쓰지않는다
	//dynamic_cast : 정말 안정적으로 형변환을 하는데 너무 느리다.


	return 0;
}
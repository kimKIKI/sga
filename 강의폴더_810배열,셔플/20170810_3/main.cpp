#include <iostream>

using namespace std;

int main()
{
	float speed = 3.3f;

	int moveDistance = speed * 3;

	//casting == ����ȯ

	cout << "���ǵ� : " << (int)speed << endl;
	cout << "�̵��Ÿ� : " << moveDistance << endl;

	//C��Ÿ�� ����ȯ
	//(�ڷ���)����
	//���� : ������ ���� �ٲ������
	//���� : ������ ���� �ٲ������

	int num = 66;

	cout << (char)num << endl;

	//C++ ����ȯ
	//static_cast<��>(����) : �Ϲ����� ����ȯ
	//reinterpret_cast : ��Ʈ������ ����ȯ
	
	//�˾Ƹ� �μ���
	//const_cast : const(���) �Ӽ��� ���ֹ����� == ��� �����ʴ´�
	//dynamic_cast : ���� ���������� ����ȯ�� �ϴµ� �ʹ� ������.


	return 0;
}
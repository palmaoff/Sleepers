/*

	���� �� ���������� ����
	�� ���������� ������� (P)
	����� (S) ������������ ��������� ������� � ���������� ������ (C)
	��� ���������� ���������� ������
	����� ����� ������������
	����� ����� ������� ��� �����
	Controls: A = Turn Left, D = Turn Right, W = Walk Forwards, S = Walk Backwards
	Last Updated: 19/11/2020
*/

#include "Header.h"

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)

int main()
{
	Map world;

	world.run();
	return 0;
}

#include<iostream>
#include"Dominoes.h"

int check();

int main()
{
	setlocale(LC_ALL, "rus");

	std::cout << "������� ���������� ���������, ������� ����� � �������" << std::endl;
	int size = check();

	int** player1 = new int* [7];
	int** player2 = new int* [7];

	for (int i = 0; i < 7; i++)
	{
		player1[i] = new int[7];
		player2[i] = new int[7];
	}

	std::cout << "��������� ����� ��������� ��� ������� ������\n\n";
	distribution(size, player1);

	std::cout << "��������� ����� ��������� ��� ������� ������\n\n";
	distribution(size, player2);

	bool flag;
	searchSkippingMove(player1, player2, size, flag);

	if (flag)
		std::cout << "����������\n";
	else
		std::cout << "�� ����������\n";

	return 0;
}

int check()
{
	int x;
	std::cin >> x;

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "����� ������ �����\n";
		std::cin >> x;
	}
	return x;
}
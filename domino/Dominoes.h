#pragma once

#include<iostream>
#include <vector>

void distribution(int size,int** player)
{
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			player[i][j] = -1;


	for (int i = 0; i < size; i++) {

		int x1, x2;
		std::cout << i + 1 << " доминошка\n";
		std::cin >> x1 >> x2;
		player[x1][x2] = 1;

		std::cout << std::endl;
	}
}

std::vector<std::pair<int, int>> searchAvailableMove(int** player, int* field)
{
	std::vector<std::pair<int, int>>availableMove;
	std::pair<int, int> x;

	for (int i = 0; i < 7; i++)
		if (field[i] > 0)
			for (int j = 0; j < 7; j++)
				if (player[i][j] == 1 || player[j][i] == 1)
				{
					x.first = i;
					x.second = j;
					availableMove.push_back(x);
				}

	return availableMove;
}

void searchSkippingMove(int** player1, int** player2, int size, bool& flag, int motion = 0, int iteration = 0)
{
	if (iteration >= 2*size) return;

	static int field[7] = { 0,0,0,0,0,0 };

	std::vector<std::pair<int, int>>availableMove;


	if (!iteration)
	{
		flag = false;

		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				if (player1[i][j] == 1)
				{
					player1[i][j] = -1;
					field[i]++;
					field[j]++;
					searchSkippingMove(player1, player2, size, flag, 1, 1);

					player1[i][j] = 1;
					field[i]--;
					field[j]--;
				}
	}
	else
	{
		int side1, side2;

		if (motion == 0)
		{
			availableMove = searchAvailableMove(player1, field);

			if (availableMove.empty())
			{
				motion = 1;
				iteration++;
			}
			else
			{

				for (int i = 0; i < availableMove.size(); i++)
				{
					side1 = availableMove[i].first;
					side2 = availableMove[i].second;

					player1[side1][side2] = -1;
					player1[side2][side1] = -1;

					if (field[side1] > 0)
					{
						field[side1]--;
						field[side2]++;
						searchSkippingMove(player1, player2, size, flag, 1, iteration + 1);

						field[side1]++;
						field[side2]--;
						player1[side1][side2] = 1;
					}

					if(field[side2] > 0)
					{
						field[side2]--;
						field[side1]++;
						searchSkippingMove(player1, player2, size, flag, 1, iteration + 1);

						field[side2]++;
						field[side1]--;
						player1[side1][side2] = 1;
					}

				}
			}


		}//motion=0

		if (motion == 1)
		{
			availableMove = searchAvailableMove(player2, field);

			if (availableMove.empty())
			{
				flag = true;
				return;
			}
			else
			{

				for (int i = 0; i < availableMove.size(); i++)
				{
					side1 = availableMove[i].first;
					side2 = availableMove[i].second;

					player2[side1][side2] = -1;
					player2[side2][side1] = -1;

					if (field[side1] > 0)
					{
						field[side1]--;
						field[side2]++;
						searchSkippingMove(player1, player2, size, flag, 0, iteration + 1);

						field[side1]++;
						field[side2]--;
						player2[side1][side2] = 1;
					}

					if (field[side2] > 0)
					{
						field[side2]--;
						field[side1]++;
						searchSkippingMove(player1, player2, size, flag, 0, iteration + 1);

						field[side2]++;
						field[side1]--;
						player2[side1][side2] = 1;
					}

				}
			}


		}
	}


}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

bool repeated_search(int[101], int);
int cost(int[101], int[100][100]);

int main()
{
	//read the city paths
	ifstream q;
	q.open("C:\\Users\\Pasargad\\Desktop\\test2.txt");
	if (!q)
	{
		cout << "Cant open the file !" << endl;
	}
	int paths[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			q >> paths[i][j];
	q.close();

	//make random cities in an array
	int turn[101];
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		int temp = (((double)rand() / RAND_MAX) * 99);
		while (repeated_search(turn, temp))
			temp = (((double)rand() / RAND_MAX) * 99);
		turn[i] = temp;
	}
	turn[100] = turn[0];

	int turn_cost = cost(turn, paths);
	int min_turn[101];
	for (int i = 0; i < 101; i++)
		min_turn[i] = turn[i];
	int min_cost = LONG_MAX;
	//algorithms
	while (true)
	{
		for (int i = 0; i < 100; i++)
			for (int j = i + 1; j < 101; j++)
			{
				if (!(i == 0 && j == 100))
				{
					//save the array for swaping cities
					int myturn[101];
					for (int i = 0; i < 101; i++)
						myturn[i] = turn[i];
					swap(myturn[i], myturn[j]);
					if (i == 0)
						myturn[100] = myturn[0];
					else if (j == 100)
						myturn[0] = myturn[100];
					int my_cost = cost(myturn, paths);
					if (my_cost < min_cost)
					{
						min_cost = my_cost;
						for (int i = 0; i < 101; i++)
							min_turn[i] = myturn[i];
					}
				}
			}
		if (min_cost < turn_cost)
		{
			for (int i = 0; i < 101; i++)
				turn[i] = min_turn[i];
			turn_cost = cost(turn, paths);
		}
		else
		{
			cout << "the minimum turn is : " << endl;
			for (int i = 0; i < 101; i++)
				cout << turn[i] << "\t";
			cout << endl << endl;
			cout << "the minimum cost is : " << turn_cost << endl;
			break;
		}
	}
	system("pause");
	return 0;

}

bool repeated_search(int turn[101], int check)
{
	for (int i = 0; i < 101; i++)
		if (turn[i] == check)
			return true;
	return false;
}

int cost(int turn[101], int paths[100][100])
{
	int turn_cost = 0;
	for (int i = 0; i < 100; i++)
	{
		int x = turn[i];
		int y = turn[i + 1];
		turn_cost += paths[x][y];
	}
	return turn_cost;
}
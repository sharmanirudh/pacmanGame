#include<conio.h>
#include<iostream.h>
#include<stdio.h>
#include<process.h>
#include<dos.h>

#define MAT_MAX 10
#define MAT_MIN 10

struct pos
{
	int x,y;
};
struct arrayPassByValue
{
	pos path[MAT_MAX * MAT_MAX];
};
int a;

int findPath(int matrix[][MAT_MAX], int visited[][MAT_MAX], pos currentPos, pos pacmanPos, arrayPassByValue pathToPacman, int size)
{
	visited[currentPos.x][currentPos.y] = 1;
	if(!matrix[currentPos.x][currentPos.y] || currentPos.x < 0 || currentPos.x >= MAT_MAX || currentPos.y < 0 || currentPos.y >= MAT_MAX)
	{
		size--;
		return 0;
	}

	for(int i = 0; i < MAT_MAX; i++)
	{
		for(int j = 0; j < MAT_MAX; j++)
			cout<<visited[i][j]<<" ";
		cout<<"\n";
	}
	delay(1000);
	pathToPacman.path[size] = currentPos;
	size++;
	if(currentPos.x == pacmanPos.x && currentPos.y ==  pacmanPos.y)
	{
		a = 1;
		cout<<"DHAPPA\n";
		for(i = 0; i < size; i++)
			cout<<"("<<pathToPacman.path[i].x<<", "<<pathToPacman.path[i].y<<"), ";
		getch();
		exit(0);
	}
	clrscr();
	arrayPassByValue pathUptilNow;
	for(i = 0; i < size; i++)
		pathUptilNow.path[i] = pathToPacman.path[i];
	if(matrix[currentPos.x][currentPos.y - 1] && !visited[currentPos.x][currentPos.y - 1])
	{
		pos newPos = {currentPos.x, currentPos.y - 1};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(matrix[currentPos.x - 1][currentPos.y] && !visited[currentPos.x - 1][currentPos.y])
	{
		pos newPos = {currentPos.x - 1, currentPos.y};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(matrix[currentPos.x + 1][currentPos.y] && !visited[currentPos.x + 1][currentPos.y])
	{
		pos newPos = {currentPos.x + 1, currentPos.y};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(matrix[currentPos.x][currentPos.y + 1] && !visited[currentPos.x][currentPos.y + 1])
	{
		pos newPos = {currentPos.x, currentPos.y + 1};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	return 0;
}

void movePacman(int matrixOriginal[][MAT_MAX], pos pacmanPos)
{
	int matrix[10][10] = {{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0}};
	while(1)
	{
		if(kbhit())
		{
			char ch = getch();
			if(ch == 'w' || ch == 'a' || ch == 's' ||  ch == 'd')
			{
				if(ch == 'w')
				{
					if(pacmanPos.x - 1 >= 0 && pacmanPos.x - 1 < MAT_MAX && pacmanPos.y >= 0 && pacmanPos.y < MAT_MAX)
					{
						matrix[pacmanPos.x][pacmanPos.y] = 0;
						matrix[--pacmanPos.x][pacmanPos.y] = 1;
					}
				}
				else if(ch == 'a')
				{
					if(pacmanPos.x >= 0 && pacmanPos.x < MAT_MAX && pacmanPos.y - 1 >= 0 && pacmanPos.y - 1 < MAT_MAX)
					{
						matrix[pacmanPos.x][pacmanPos.y] = 0;
						matrix[pacmanPos.x][--pacmanPos.y] = 1;
					}
				}
				else if(ch == 's')
				{
					if(pacmanPos.x + 1 >= 0 && pacmanPos.x + 1 < MAT_MAX && pacmanPos.y >= 0 && pacmanPos.y < MAT_MAX)
					{
						matrix[pacmanPos.x][pacmanPos.y] = 0;
						matrix[++pacmanPos.x][pacmanPos.y] = 1;
					}
				}
				else if(ch == 'd')
				{
					if(pacmanPos.x >= 0 && pacmanPos.x < MAT_MAX && pacmanPos.y + 1 >= 0 && pacmanPos.y + 1 < MAT_MAX)
					{
						matrix[pacmanPos.x][pacmanPos.y] = 0;
						matrix[pacmanPos.x][++pacmanPos.y] = 1;
					}
				}
				clrscr();
				for(int i = 0; i < MAT_MAX; i++)
				{
					for(int j = 0; j < MAT_MAX; j++)
						cout<<matrix[i][j]<<" ";
					cout<<"\n";
				}
			}
			else if(ch == 'q')
				break;
		}
	}
}

int main()
{
	clrscr();
	int matrix[10][10] = {{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,1,1,1,0,0,0},
												{0,0,0,0,1,1,1,0,0,0},
												{0,0,0,0,1,0,0,0,0,0},
												{0,0,0,0,1,1,1,1,0,0},
												{0,0,0,0,0,0,1,1,0,0},
												{0,0,0,0,0,0,1,1,1,1}}, i, j;

	int visited[10][10] ={{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0},
												{0,0,0,0,0,0,0,0,0,0}};
	arrayPassByValue pathToPacman;
	/*for(i = 0; i < MAT_MAX; i++)
	{
		for(j = 0; j < MAT_MAX; j++)
			cout<<matrix[i][j]<<" ";
		cout<<"\n";
	}*/
	pos currentPos = {4, 4}, pacmanPos = {9, 9};
	//findPath(matrix, visited, currentPos, pacmanPos, pathToPacman, 0);
	movePacman(matrix, pacmanPos);
	getch();
	return 0;
}
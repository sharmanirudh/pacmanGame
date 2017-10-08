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
pos pathToCatchPacman[MAT_MAX * MAT_MAX];

int findPath(int matrix[][MAT_MAX], int visited[][MAT_MAX], pos currentPos, pos pacmanPos, arrayPassByValue pathToPacman, int size)
{
	static int flag = 0;
	int i, j;
	visited[currentPos.x][currentPos.y] = 1;
	if(!matrix[currentPos.x][currentPos.y] || currentPos.x < 0 || currentPos.x >= MAT_MAX || currentPos.y < 0 || currentPos.y >= MAT_MAX)
	{
		size--;
		return 0;
	}

	/*for(i = 0; i < MAT_MAX; i++)
	{
		for(j = 0; j < MAT_MAX; j++)
			cout<<visited[i][j]<<" ";
		cout<<"\n";
	}
	delay(1000);
	*/
	pathToPacman.path[size] = currentPos;
	size++;
	if(currentPos.x == pacmanPos.x && currentPos.y ==  pacmanPos.y)
	{
		//cout<<"DHAPPA\n";
		for(i = 0; i < size; i++)
		{
			//cout<<"("<<pathToPacman.path[i].x<<", "<<pathToPacman.path[i].y<<"), ";
			pathToCatchPacman[i].x = pathToPacman.path[i].x;
			pathToCatchPacman[i].y = pathToPacman.path[i].y;
		}
		return 1;
	}
	//clrscr();
	arrayPassByValue pathUptilNow;
	for(i = 0; i < size; i++)
		pathUptilNow.path[i] = pathToPacman.path[i];
	if(!flag && matrix[currentPos.x][currentPos.y + 1] && !visited[currentPos.x][currentPos.y + 1])
	{
		pos newPos = {currentPos.x, currentPos.y + 1};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(!flag && matrix[currentPos.x + 1][currentPos.y] && !visited[currentPos.x + 1][currentPos.y])
	{
		pos newPos = {currentPos.x + 1, currentPos.y};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(!flag && matrix[currentPos.x - 1][currentPos.y] && !visited[currentPos.x - 1][currentPos.y])
	{
		pos newPos = {currentPos.x - 1, currentPos.y};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	if(matrix[currentPos.x][currentPos.y - 1] && !visited[currentPos.x][currentPos.y - 1])
	{
		pos newPos = {currentPos.x, currentPos.y - 1};
		findPath(matrix, visited, newPos, pacmanPos, pathUptilNow, size);
	}
	return 0;
}

pos moveGhost(int matrix[][MAT_MAX], int matrixOriginal[][MAT_MAX], pos currentPos, pos pacmanPos)
{
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
	findPath(matrixOriginal, visited, currentPos, pacmanPos, pathToPacman, 0);
	matrix[pathToCatchPacman[0].x][pathToCatchPacman[0].y] = 0;
	matrix[pathToCatchPacman[1].x][pathToCatchPacman[1].y] = 5;
	currentPos.x = pathToCatchPacman[1].x;
	currentPos.y = pathToCatchPacman[1].y;
	return currentPos;
}

void movePacman(int matrixOriginal[][MAT_MAX], pos pacmanPos, pos ghostCurrentPos)
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
												{0,0,0,0,0,0,0,0,0,0}}, i, j;
	while(1)
	{
		ghostCurrentPos = moveGhost(matrix, matrixOriginal, ghostCurrentPos, pacmanPos);
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
			}
			else if(ch == 'q')
				break;
		}
		clrscr();
		for(int i = 0; i < MAT_MAX; i++)
		{
			for(int j = 0; j < MAT_MAX; j++)
				cout<<matrix[i][j]<<" ";
			cout<<"\n";
		}
		delay(1000);
	}
}

int main()
{
	clrscr();
	int matrix[10][10] = {{1,1,1,1,1,0,0,1,0,0},
												{0,1,0,0,1,1,1,1,0,0},
												{0,1,0,0,0,0,0,0,0,0},
												{0,1,0,0,0,0,0,0,0,0},
												{0,1,0,0,1,1,1,0,0,0},
												{0,1,1,1,1,1,1,0,0,0},
												{0,0,1,1,1,0,0,0,0,0},
												{0,0,0,0,1,1,1,1,0,0},
												{0,0,0,0,0,0,1,1,0,0},
												{0,0,0,0,0,0,1,1,1,1}}, i, j;

	/*int visited[10][10] ={{0,0,0,0,0,0,0,0,0,0},
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
	*/
	/*for(i = 0; i < MAT_MAX; i++)
	{
		for(j = 0; j < MAT_MAX; j++)
			cout<<matrix[i][j]<<" ";
		cout<<"\n";
	}*/
	pos ghostCurrentPos = {0, 0};
	pos pacmanPos = {9, 9};
	//findPath(matrix, visited, ghostCurrentPos, pacmanPos, pathToPacman, 0);
	movePacman(matrix, pacmanPos, ghostCurrentPos);
	getch();
	return 0;
}
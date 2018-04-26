#include "stdafx.h"
#include "FoundMethods.h"
#include "maze.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int FoundRoute(Position &Start, int Num)
{
	maze[Start.y][Start.x] = Num;
	if (Start.y-1 >= 0 && maze[Start.y-1][Start.x] == 0) {
		Position NewStart;
		NewStart.x = Start.x;
		NewStart.y = Start.y - 1;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.x+1 < MAZESIZE && maze[Start.y][Start.x + 1] == 0) {
		Position NewStart;
		NewStart.x = Start.x+1;
		NewStart.y = Start.y;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.y+1 < MAZESIZE && maze[Start.y + 1][Start.x] == 0) {
		Position NewStart;
		NewStart.x = Start.x;
		NewStart.y = Start.y + 1;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.x-1 >= 0 && maze[Start.y][Start.x - 1] == 0) {
		Position NewStart;
		NewStart.x = Start.x-1;
		NewStart.y = Start.y;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.x == 19 && Start.y == 19) {
		return Num;
	}
}

void PrintMaze()
{
	system("cls");
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			if (maze[i][j] == 1) {
				printf("---");
			}
			else if (maze[i][j] == 0) {
				printf("000");
			}
			else {
				printf("%d", maze[i][j]);
			}
		}
		printf("\n");
	}
}

void FoundFinalRoute(std::stack<Position*> Final)
{
	int num = maze[19][19];
	Position* FRoute = new Position;
	FRoute->y= 19;
	FRoute->x = 19;
	Final.push(FRoute);
	FoundFinalRoute_Going(Final,FRoute,num);
}

void FoundFinalRoute_Going(std::stack<Position*> Final, Position* FRoute,int num)
{
	if (FRoute->y - 1 >= 0 && maze[FRoute->y - 1][FRoute->x] == num -1) {
		Position* NewPos = new Position;
		NewPos->x = FRoute->x;
		NewPos->y = FRoute->y;
		NewPos->y--;
		Final.push(NewPos);
		num--;
		FoundFinalRoute_Going(Final, FRoute, num);
	}
	if (FRoute->x + 1 < MAZESIZE && maze[FRoute->y][FRoute->x + 1] == num - 1) {
		Position* NewPos = new Position;
		NewPos->x = FRoute->x;
		NewPos->y = FRoute->y;
		NewPos->x++;
		Final.push(NewPos);
		num--;
		FoundFinalRoute_Going(Final, FRoute, num);
	}
	if (FRoute->y + 1 < MAZESIZE && maze[FRoute->y + 1][FRoute->x] == num - 1) {
		Position* NewPos = new Position;
		NewPos->x = FRoute->x;
		NewPos->y = FRoute->y;
		NewPos->y++;
		Final.push(NewPos);
		num--;
		FoundFinalRoute_Going(Final, FRoute, num);
	}
	if (FRoute->x - 1 >= 0 && maze[FRoute->y][FRoute->x - 1] == num - 1) {
		Position* NewPos = new Position;
		NewPos->x = FRoute->x;
		NewPos->y = FRoute->y;
		NewPos->x--;
		Final.push(NewPos);
		num--;
		FoundFinalRoute_Going(Final, FRoute, num);
	}
}

void ClearMase()
{
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			maze[i][j] = mazeOrigin[i][j];
		}
	}
}

void WriteFinalRoute(std::stack<Position*> Final, int num)
{
	for (; num > 100; --num) {
		Position* Good = Final.top();
		maze[Good->y][Good->x] = num;
		Final.pop();
	}
}

void PrintFinalRoute()
{
	system("cls");
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			if (maze[i][j] == 1) {
				printf("---");
			}
			else if (maze[i][j] == 0) {
				printf("000");
			}
			else {
				printf("%d", maze[i][j]);
			}
		}
		printf("\n");
	}
}

int FoundRange(Position & Start, int count)
{
	if (mazeRange[Start.y][Start.x] == 1) {
		mazeRange[Start.y][Start.x] = 3;
		count++;
		PrintMazeRange();
		if (Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x] == 1) {
			Position NewStart;
			NewStart.x = Start.x;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < MAZESIZE && mazeRange[Start.y][Start.x + 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y;
			count = FoundRange(NewStart, count);
		}
		if (Start.y + 1 < MAZESIZE && mazeRange[Start.y + 1][Start.x] == 1) {
			Position NewStart;
			NewStart.x = Start.x;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && mazeRange[Start.y][Start.x - 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x - 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && Start.y + 1 < MAZESIZE && mazeRange[Start.y + 1][Start.x - 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < MAZESIZE && Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x - 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < MAZESIZE && Start.y + 1 < MAZESIZE && mazeRange[Start.y + 1][Start.x + 1] == 1) {
			Position NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
	}
	return count;
}

void PrintMazeRange()
{
	system("cls");
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			if (mazeRange[i][j] == 1) {
				printf("---");
			}
			else if (mazeRange[i][j] == 0) {
				printf("000");
			}
			else if (mazeRange[i][j] == 3){
				printf("111");
			}
		}
		printf("\n");
	}
}
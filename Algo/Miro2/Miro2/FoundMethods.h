#pragma once

#include "Position.h"
#include <stack>

int FoundRoute(Position &Start, int Num);

void PrintMaze();

void FoundFinalRoute(std::stack<Position*> Final);

void FoundFinalRoute_Going(std::stack<Position*> Final, Position* FRoute, int num);

void ClearMase();

void WriteFinalRoute(std::stack<Position*> Final, int num);

void PrintFinalRoute();

int FoundRange(Position& Start, int Num);

void PrintMazeRange();
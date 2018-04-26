#include "stdafx.h"
#include "Problem_1.h"
#include <iostream>
#include <conio.h>
#include <stack>
#include <queue>

void Prom_1_2()
{
	std::cout << "첫번째 문제" << std::endl;
	int First[101];                    //  배열 선언
	for (int i = 1; i <= 100; ++i) {    //  1 ~ 100까지 할당
		First[i] = i;
	}
	std::cout << "배열 선언 밑 숫자넣기 완료" << std::endl;
	std::cout << "두번재 문제" << std::endl;
	for (int i = 1; i <= 100; ++i) {
		std::cout << First[i] << " ";  // 배열 하나씩 출력
	}
	std::cout << std::endl;
}

void Prom_3()
{
	std::cout << "세번째 문제" << std::endl;
	char* First_3 = new char;
	std::cout << "문자열을 입력하세요" << std::endl;
	std::cin >> First_3;  // 문자열을 입력받아 포인터에 저장
	int length = 0;
	while (First_3[length] != NULL) {
		length++;
	}
	std::cout << "입력받은 문자열의 길이 : " << length << std::endl;
}

void Prom_4()
{
	Single_List Good;
	for (int i = 1; i <= 10; ++i) {
		Good.AddNode(i);
	}
	Good.PrintNodes();
}

void Prom_5()
{
	Double_List Good;
	for (int i = 1; i <= 10; ++i) {
		Good.AddTail(i);
	}
	Good.PrintFTail();
	return;
}

void Prom_6()
{
	View_List Good;
	char buffer[1024] = { 0 };
	FILE* fp = fopen("data.txt", "r");
	Line Temp;

	while (!feof(fp)) {
		fgets(buffer, 100, fp);
		memcpy(Temp.Text, buffer, 100);
		Good.AddTail(Temp);
	}
	
	char InputKey;
	int StartLine = 1;
	int MaxLine = 100;
	int i = 0;

	do {         //  출력하는 방법
		for (View_Node* Current = Good.IndexOf(StartLine); Current != Good.Tail; Current = Current->Next) {
			i++;
			printf("%s", Current->Text.Text);
			if (i > 5) {
				i = 0;
				break;
			}
		}
		InputKey = _getch();
		if (InputKey == 'w') {
			if (StartLine == 1) {

			}
			else {
				--StartLine;
			}
		}
		else if (InputKey == 's') {
			++StartLine;
		}
		system("cls");
	} while (InputKey != 'q');


	fclose(fp);
}

void Prom_7()
{
	// 스택 선언
	DL_Stack Good;
	// 1~10까지 넣기(Push)
	for (int i = 1; i <= 10; ++i) {
		Good.Push(i);
	}
	// Pop 하며 출력(알아서 거꾸로 출력됨)
	for (int i = 1; i <= 10; ++i) {
		std::cout << Good.Pop() << " ";
	}
	std::cout << std::endl;
	std::cout << "출력 완료" << std::endl;
}

void Prom_8()
{
	// 큐 선언
	DL_Queue Good;
	// 1~10 푸쉬
	for (int i = 1; i <= 10; ++i) {
		Good.Push(i);
	}
	// 출력
	for (int i = 1; i <= 10; ++i) {
		std::cout << Good.Pop() << " ";
	}
	std::cout << std::endl;
	std::cout << "출력 완료" << std::endl;
}

char Infix[] = "81 + 95 - 100 * 3 / 5 ( 85 + 12 - 8 ) + 5";
char Operators[] = "+-/*()";
int OperatorPriority[] = { 1, 1, 2, 2, -1, -1 };

std::stack<char*> PostFixStack;

int IsOperator(char ch) {
	for (int i = 0; i < 6; ++i) {
		if (ch == Operators[i]) {
			return i;
		}
	}

	return -1;
}

int GetPriority(char* Operator)
{
	return OperatorPriority[IsOperator(Operator[0])];
}

char* OperatorProcess(char* Operator, char* Cursor) {
	if ((PostFixStack.size() == 0) || Operator[0] == '(') {
		PostFixStack.push(Operator);
	}
	else {
		char* Top = PostFixStack.top();
		while (!(PostFixStack.size() == 0) && GetPriority(Top) >= GetPriority(Operator)) {
			PostFixStack.pop();
			if (Top[0] == '(') {
				break;
			}
			sprintf(Cursor, "%s ", Top);
			Cursor += (strlen(Top) + 1);

			if (!(PostFixStack.size() == 0)) {
				Top = PostFixStack.top();
			}
		}if (Operator[0] != ')') {
			PostFixStack.push(Operator);
		}
	}
	return Cursor;
}

char* ConvertPostFix(char* InfixNotation) {
	char* PostFixString = new char[strlen(InfixNotation) + 1];
	char* Cursor = PostFixString;

	char* token = strtok(InfixNotation, " ");
	while (token != NULL) {
		if (token[0] >= '0' && token[0] <= '9') {
			sprintf(Cursor, "%s ", token);
			Cursor += (strlen(token) + 1);
		}
		else if (IsOperator(token[0]) != -1) {
			Cursor = OperatorProcess(token, Cursor);
		}
		else {
			printf("error");
			return NULL;
		}

		token = strtok(NULL, " ");
	}

	while (!(PostFixStack.size() == 0)) {
		char* Pop = PostFixStack.top();
		PostFixStack.pop();
		sprintf(Cursor, "%s ", Pop);
		Cursor += (strlen(Pop) + 1);
	}

	sprintf(Cursor, "\0");
	return PostFixString;
}

void Prom_9()
{
	char* PostFixString = ConvertPostFix(Infix);
	printf("%s\n", PostFixString);
}

double PostFixCalculate(char* PostFixString)
{
	std::stack<char*> PostFixCal;

	char* token = strtok(PostFixString, " ");
	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9')
		{
			PostFixCal.push(token);
		}
		else if (IsOperator(token[0]) != -1)
		{
			char* second = PostFixCal.top();
			PostFixCal.pop();
			char* first = PostFixCal.top();
			PostFixCal.pop();

			double result = 0;
			switch (token[0])
			{
			case '+':
				result = atof(first) + atof(second);
				break;
			case '-':
				result = atof(first) - atof(second);
				break;
			case '/':
				result = atof(first) / atof(second);
				break;
			case '*':
				result = atof(first) * atof(second);
				break;
			}
			
			char* temp = new char[10];
			sprintf(temp, "%f", result);
			PostFixCal.push(temp);
		}
		else // 예외 처리
		{
			printf("error");
			return NULL;
		}

		token = strtok(NULL, " ");
	}
	char* Final = PostFixCal.top();
	PostFixCal.pop();

	return atof(Final);
}

void Prom_10()
{
	char* PostFixString = ConvertPostFix(Infix);
	printf("%f\n", PostFixCalculate(PostFixString));
}

void Prom_11()
{
	int maze[10][10] = {
	{ 0,1,1,1,1,1,1,1,1,1 },
	{ 0,1,1,1,0,0,0,0,0,1 },
	{ 0,0,0,1,0,1,1,1,0,1 },
	{ 1,1,0,1,0,1,0,1,0,1 },
	{ 1,1,0,0,0,0,0,1,1,1 },
	{ 1,1,1,1,0,1,0,1,1,1 },
	{ 1,1,1,1,0,1,0,1,1,1 },
	{ 1,1,1,1,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,0,0 },
	{ 1,1,1,1,1,1,1,1,1,0 }
	};
	std::stack<Pos*> Trace;

	Pos Start;
	Start.x = 0;
	Start.y = 0;
	maze[Start.y][Start.x] = 2;
	Pos* Possible = Start.FindPossible(maze);

	while (1) {
		if (Possible==NULL) {
			Possible = Trace.top();
			Trace.pop();
		}
		else if (Possible->x == 9 && Possible->y == 9) {
			break;
		}
		else{
			maze[Possible->y][Possible->x] = 2;
			Possible = Possible->FindPossible(maze);
			Trace.push(Possible);
		}
	}
	maze[Possible->y][Possible->x] = 2;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			std::cout << maze[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Pos Dir[4];

void InitDir() {
	Dir[0].x = 0;
	Dir[0].y = -1;

	Dir[1].x = 1;
	Dir[1].y = 0;

	Dir[2].x = 0;
	Dir[2].y = 1;

	Dir[3].x = -1;
	Dir[3].y = 0;
}

bool CanMove(const Pos& Current, Pos& NewPosition, int dir, int maze[10][10]) {
	Pos Next;

	Next.x = Current.x + Dir[dir].x;
	Next.y = Current.y + Dir[dir].y;

	if (Next.x < 0 || Next.y < 0 || Next.x > 9 || Next.y > 9) {
		return false;
	}

	if (maze[Next.y][Next.x] == 0) {
		NewPosition = Next;
		return true;
	}
	return false;
}

void Prom_12()
{
	int maze[10][10] = {
	{ 0,1,1,1,1,1,1,1,1,1 },
	{ 0,1,1,1,0,0,0,0,0,1 },
	{ 0,0,0,1,0,1,1,1,0,1 },
	{ 1,1,0,1,0,1,0,1,0,1 },
	{ 1,1,0,0,0,0,0,1,1,1 },
	{ 1,1,1,1,0,1,0,1,1,1 },
	{ 1,1,1,1,0,1,0,1,1,1 },
	{ 1,1,1,1,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,0,0 },
	{ 1,1,1,1,1,1,1,1,1,0 }
	};
	std::queue<Pos> Trace;
	InitDir();

	Pos Start;
	Start.x = 0;
	Start.y = 0;

	Trace.push(Start);
	maze[0][0] = 100;
	bool found = false;

	while (!Trace.empty()) {
		Start = Trace.front();
		Trace.pop();
		for (int i = 0; i < 4; ++i) {
			Pos NewPosition;
			if (CanMove(Start, NewPosition, i, maze)) {
				maze[NewPosition.y][NewPosition.x] = maze[Start.y][Start.x] + 1;
				if (NewPosition.x == 9 && NewPosition.y == 9) {
					std::cout << "나왔땅~!" << std::endl;
					found = true;
					break;
				}

				Trace.push(NewPosition);
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (maze[i][j] == 1) {
				std::cout << "---";
			}
			else {
				std::cout << maze[i][j];
			}
		}
		std::cout << std::endl;
	}
}

void Prom_13()
{
	std::stack<char> Good;
	int Target = 132;

	while (Target >= 1) {
		if (Target % 2 == 1) {
			char temp = '1';
			Good.push(temp);
		}
		else {
			char temp = '0';
			Good.push(temp);
		}
		Target = Target / 2;
	}

	while (Good.size() != 0) {
		std::cout << Good.top();
		Good.pop();
	}
}

int Searching(int arr[], int Target) {
	int Length = 0;
	for (int i = 0; arr[i] >= 0; ++i) {
		Length = i;
	}
	if (Target == arr[Length / 2]) {
		return (Length / 2) + 1;
	}
	else if (Target < arr[Length / 2]) {
		for (int i = 0; i < Length / 2; ++i) {
			if (arr[i] == Target) {
				return i + 1;
			}
		}
	}
	else if(Target>arr[Length/2]){
		for (int i = Length / 2; i < Length; ++i) {
			if (arr[i] == Target) {
				return i + 1;
			}
		}
	}
	return -1;
}

void Prom_14()
{
	int arr[10] = { 1,4,6,7,8,14,73,143,556,1000 };
	std::cout << "배열 선언, 배열에는 1,4,6,7,8,14,73,143,556,1000 가 있습니다." << std::endl;
	std::cout << "그 중 6은 " << Searching(arr, 6) << "번째에 있고, 143 은 " << Searching(arr, 143) << "번째에 있습니다." << std::endl;
}

int RecursiveSum(int a) {
	if (a == 1) {
		return 1;
	}
	return a + RecursiveSum(a - 1);
}

void Prom_15()
{
	std::cout << "10부터 1까지의 합은 " << RecursiveSum(10) << "이다" << std::endl;
}

int RecursiveStringLength(std::string str, int Length) {
	if (str[Length] == NULL) {
		return 0;
	}
	return 1 + RecursiveStringLength(str, Length + 1);
}

void Prom_16() {
	std::cout << "문자열 StrongAndGoodMorning! 의 길이는 " << RecursiveStringLength("StrongAndGoodMorning!", 0) << "입니다." << std::endl;
}

#define MAZESIZE 20
int maze[MAZESIZE][MAZESIZE] = {
	{ 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
{ 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0 },
{ 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 }
};

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

int FoundRoute(Pos &Start, int Num)
{
	maze[Start.y][Start.x] = Num;
	if (Start.y - 1 >= 0 && maze[Start.y - 1][Start.x] == 0) {
		Pos NewStart;
		NewStart.x = Start.x;
		NewStart.y = Start.y - 1;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.x + 1 < MAZESIZE && maze[Start.y][Start.x + 1] == 0) {
		Pos NewStart;
		NewStart.x = Start.x + 1;
		NewStart.y = Start.y;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.y + 1 < MAZESIZE && maze[Start.y + 1][Start.x] == 0) {
		Pos NewStart;
		NewStart.x = Start.x;
		NewStart.y = Start.y + 1;
		int NewNum = Num + 1;
		PrintMaze();
		//getchar();
		FoundRoute(NewStart, NewNum);
	}
	if (Start.x - 1 >= 0 && maze[Start.y][Start.x - 1] == 0) {
		Pos NewStart;
		NewStart.x = Start.x - 1;
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

void Prom_17()
{
	std::stack<Pos*> Good;
	Pos Start;
	Start.x = 0;
	Start.y = 0;

	int num = 100;    // 순서를 세기 위함

	num = FoundRoute(Start, num);

}

int partition(int* data, int begin, int end)
{
	int pivot = data[end];
	int min = begin - 1;

	for (int max = begin; max <= end - 1; ++max)
	{
		if (data[max] <= pivot)
		{
			min++;
			int temp = data[max];
			data[max] = data[min];
			data[min] = temp;
		}
	}
	int temp = data[min+1];
	data[min+1] = data[end];
	data[end] = temp;

	return min + 1;
}

void quickSort(int* data, int begin, int end)
{
	if (begin < end)
	{
		int pivot = partition(data, begin, end);
		quickSort(data, begin, pivot - 1);
		quickSort(data, pivot + 1, end);

	}
}

void Prom_18()
{
	std::cout <<"정렬 전"<< std::endl;
	int data[10];
	for (int i = 0; i < 10; ++i) {
		data[i] = rand() % 100;
	}
	for (int i = 0; i < 10; ++i) {
		std::cout << data[i] << " ";
	}

	quickSort(data, 0, 9);

	std::cout << std::endl;
	std::cout << "정렬 후" << std::endl;

	for (int i = 0; i < 10; ++i) {
		std::cout << data[i] << " ";
	}
}

int mazeRange[20][20] = {
	{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
{ 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 },
{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0 },
{ 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 }
};

void PrintMazeRange()
{
	system("cls");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (mazeRange[i][j] == 1) {
				printf("---");
			}
			else if (mazeRange[i][j] == 0) {
				printf("000");
			}
			else if (mazeRange[i][j] == 3) {
				printf("111");
			}
		}
		printf("\n");
	}
}

int FoundRange(Pos & Start, int count)
{
	if (mazeRange[Start.y][Start.x] == 1) {
		mazeRange[Start.y][Start.x] = 3;
		count++;
		PrintMazeRange();
		if (Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x] == 1) {
			Pos NewStart;
			NewStart.x = Start.x;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < 20 && mazeRange[Start.y][Start.x + 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y;
			count = FoundRange(NewStart, count);
		}
		if (Start.y + 1 < 20 && mazeRange[Start.y + 1][Start.x] == 1) {
			Pos NewStart;
			NewStart.x = Start.x;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && mazeRange[Start.y][Start.x - 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x - 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x - 1 >= 0 && Start.y + 1 < 20 && mazeRange[Start.y + 1][Start.x - 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x - 1;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < 20 && Start.y - 1 >= 0 && mazeRange[Start.y - 1][Start.x - 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y - 1;
			count = FoundRange(NewStart, count);
		}
		if (Start.x + 1 < 20 && Start.y + 1 < 20 && mazeRange[Start.y + 1][Start.x + 1] == 1) {
			Pos NewStart;
			NewStart.x = Start.x + 1;
			NewStart.y = Start.y + 1;
			count = FoundRange(NewStart, count);
		}
	}
	return count;
}

void Prom_19()
{
	bool good = true;
	while (good) {
		PrintMazeRange();
		Pos Start;
		std::cout << "X 좌표 : " << std::ends;
		std::cin >> Start.x;

		std::cout << "Y 좌표 : " << std::ends;
		std::cin >> Start.y;

		int count = FoundRange(Start, 0);
		std::cout << "선택된 영역의 갯수는 " << count << "개 입니다" << std::endl;

		int re;
		std::cout << "다시?(1을 입력하면 다시 합니다)" << std::ends;
		std::cin >> re;
		if (re == 1) {
			good = true;
		}
		else {
			good = false;
		}
	}
}

void Prom_20()
{
	BTree TestTree(1);

	TestTree.Root->MakeLeftChild(2);
	TestTree.Root->MakeRightChild(3);
	TestTree.Root->Left->MakeLeftChild(4);
	TestTree.Root->Left->MakeRightChild(5);
	TestTree.Root->Right->MakeRightChild(6);
	TestTree.Root->Left->Left->MakeLeftChild(7);
	TestTree.Root->Left->Right->MakeLeftChild(8);
	TestTree.Root->Right->Right->MakeLeftChild(9);
	TestTree.Root->Right->Right->MakeRightChild(10);
	TestTree.Root->Left->Right->Left->MakeLeftChild(11);
	TestTree.Root->Left->Right->Left->MakeRightChild(12);

	std::cout << "Preorder 탐색" << std::endl;
	TestTree.PreorderSearch(TestTree.Root);
	std::cout << std::endl;
	std::cout << "Inorder 탐색" << std::endl;
	TestTree.InorderSearch(TestTree.Root);
	std::cout << std::endl;
	std::cout <<"Postorder 탐색"<<std::endl;
	TestTree.PostorderSearch(TestTree.Root);
}

Single_List::Single_List()
{
	Head = NULL;
}

void Single_List::AddNode(int NewValue)
{
	if (Head == NULL) {
		Single_Node* NewNode = new Single_Node;
		NewNode->Value = NewValue;
		NewNode->Next = NULL;
		Head = NewNode;
		return;
	}
	Single_Node* Target = SearchEnd();
	Single_Node* NewNode = new Single_Node;
	NewNode->Value = NewValue;
	NewNode->Next = NULL;
	Target->Next = NewNode;
}

void Single_List::PrintNodes()
{
	Single_Node* Target = Head;
	while (Target != NULL) {
		std::cout << Target->Value << " ";
		if (Target->Next != NULL) {
			Target = Target->Next;
		}
		else {
			break;
		}
	}
	std::cout << std::endl;
	std::cout << "출력 완료" << std::endl;
}

Single_Node * Single_List::SearchEnd()
{
	Single_Node* Target = Head;
	while (Target->Next != NULL) {
		Target = Target->Next;
	}
	return Target;
}

Double_List::Double_List()
{
	Head = new Double_Node;
	Tail = new Double_Node;
	Head->Value = 100000;
	Head->Next = Tail;
	Head->Prev = NULL;
	Tail->Value = 100000;
	Tail->Prev = Head;
	Tail->Next = NULL;
}

void Double_List::AddTail(int NewValue)
{
	if (Head->Next == Tail) {
		Double_Node* NewNode = new Double_Node;
		NewNode->Value = NewValue;
		NewNode->Prev = Head;
		NewNode->Next = Tail;
		Head->Next = NewNode;
		Tail->Prev = NewNode;
		return;
	}
	Double_Node* NewNode = new Double_Node;
	NewNode->Value = NewValue;
	NewNode->Next = Tail;
	NewNode->Prev = Tail->Prev;
	Tail->Prev->Next = NewNode;
	Tail->Prev = NewNode;
}

void Double_List::PrintFTail()
{
	if (Head->Next != Tail) {
		Double_Node* Target = Tail->Prev;
		while (Target != Head) {
			std::cout << Target->Value << " ";
			Target = Target->Prev;
		}
		std::cout << std::endl;
		std::cout << "출력 완료" << std::endl;
	}
}

void Double_List::DeleteTail()
{
	Double_Node* Temp = Tail->Prev;
	Temp->Prev->Next = Tail;
	Tail->Prev = Temp->Prev;
	delete(Temp);
}

void Double_List::DeleteHead()
{
	Double_Node* Temp = Head->Next;
	Temp->Next->Prev = Head;
	Head->Next = Temp->Next;
	delete(Temp);
}

View_List::View_List()
{
	Head = new View_Node;
	Tail = new View_Node;
	Head->Next = Tail;
	Head->Prev = NULL;
	Tail->Prev = Head;
	Tail->Next = NULL;
	Count = 0;
}

void View_List::AddTail(Line NewText)
{
	if (Head->Next == Tail) {
		View_Node* NewNode = new View_Node;
		NewNode->Text = NewText;
		NewNode->Prev = Head;
		NewNode->Next = Tail;
		Head->Next = NewNode;
		Tail->Prev = NewNode;
	}
	else {
		View_Node* NewNode = new View_Node;
		NewNode->Text = NewText;
		NewNode->Prev = Tail->Prev;
		Tail->Prev->Next = NewNode;
		Tail->Prev = NewNode;
		NewNode->Next = Tail;
	}
	Count++;
}

View_Node * View_List::IndexOf(int Index)
{
	long ObjectCount = 0;
	for (View_Node* Current = Head; Current != Tail; Current = Current->Next) {
		if ((ObjectCount == Index) && (Index != 0) && (Index < Count)) {
			return Current;
		}
		ObjectCount++;
	}
	return NULL;
}

void DL_Stack::Push(int Value)
{
	Data.AddTail(Value);
}

int DL_Stack::Pop()
{
	int Value = Data.Tail->Prev->Value;
	Data.DeleteTail();
	return Value;
}

int DL_Stack::Top()
{
	return Data.Tail->Prev->Value;
}

void DL_Queue::Push(int Value)
{
	Data.AddTail(Value);
}

int DL_Queue::Pop()
{
	int Value = Data.Head->Next->Value;
	Data.DeleteHead();
	return Value;
}

int DL_Queue::Top()
{
	return Data.Head->Next->Value;
}

Pos* Pos::FindPossible(int maze[10][10])
{
	// 위
	if (y - 1 > 0 && maze[y - 1][x] == 0) {
		Pos* NewPos = new Pos;
		NewPos->y = y - 1;
		NewPos->x = x;
		return NewPos;
	}
	// 오른쪽
	else if (x + 1 < 10 && maze[y][x + 1] == 0) {
		Pos* NewPos = new Pos;
		NewPos->y = y;
		NewPos->x = x+1;
		return NewPos;
	}
	// 아래
	else if (y + 1 < 10 && maze[y + 1][x] == 0) {
		Pos* NewPos = new Pos;
		NewPos->y = y+1;
		NewPos->x = x;
		return NewPos;
	}
	// 왼쪽
	else if (x - 1 > 0 && maze[y][x - 1] == 0) {
		Pos* NewPos = new Pos;
		NewPos->y = y;
		NewPos->x = x-1;
		return NewPos;
	}
	else if (x == 9 && y == 9) {
		return this;
	}
	return NULL;
}

BTree::BTree(int Value)
{
	Root = new BTreeNode();
	Root->Data = Value;
}

void BTree::PreorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}

	std::cout << Node->Data << " ";
	PreorderSearch(Node->Right);
	PreorderSearch(Node->Left);
}

void BTree::InorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}
	InorderSearch(Node->Left);
	std::cout << Node->Data << " ";
	InorderSearch(Node->Right);
}

void BTree::PostorderSearch(BTreeNode* Node)
{
	if (Node == NULL) {
		return;
	}
	PostorderSearch(Node->Left);
	PostorderSearch(Node->Right);
	std::cout << Node->Data << " ";
}

BTreeNode::BTreeNode()
{
	Data = 0;
}

BTreeNode::BTreeNode(int Value)
{
	Data = Value;
}

void BTreeNode::MakeLeftChild()
{
	Left = new BTreeNode();
	Left->Data = 0;
}

void BTreeNode::MakeLeftChild(int Value)
{
	Left = new BTreeNode();
	Left->Data = Value;
}

void BTreeNode::MakeRightChild()
{
	Right = new BTreeNode();
	Right->Data = 0;
}

void BTreeNode::MakeRightChild(int Value)
{
	Right = new BTreeNode();
	Right->Data = Value;
}
#include <raylib.h>
#include <cmath>
#include <array>
#include <iostream>
using namespace std;
const int dataSize = 78;
int dataArray[dataSize];

void drawDataRectangle(int posX, int posY, int width, int height, Color color) //Drawing method for a rectangle with gray bounds
{
	DrawRectangle(posX, posY, width, height, color);
	DrawRectangleLines(posX, posY, width, height, GRAY);
}

void drawData(int data[]) //Drawing method for the arrays
{
	int x = 10; //gap between lines
	int y = 590; 

	for (int i = 0; i < dataSize; i++)
	{
		drawDataRectangle(x * i + 10, y - data[i], 10, data[i], WHITE);
	}
}

void drawData(int data[], int num, Color color) //Drawing method the certain unit of array with a certain color
{
	int x = 10; //gap between lines
	int y = 590;
	drawDataRectangle(x * num + 10, y - data[num], 10, data[num], color);
}

void fillData(int data[])  //Filling the arrays method
{
	int r = rand() % 400 + 1; //the range 1 to 100

	for (int i = 0; i < dataSize; i++)
	{
		r = rand() % 400 + 1;
		data[i] = r;
	}
}

void bubbleSort(int data[], int i)
{
	if (i < dataSize - 1)
	{
		drawData(data, i, RED);
		drawData(data, i + 1, RED);
		if (data[i] > data[i + 1])
		{
			int m = data[i + 1];
			dataArray[i + 1] = data[i];
			dataArray[i] = m;
		}
	}
}


int main() 
{
	int counter = 0;
	InitWindow(800, 600, "Game");
	SetWindowState(FLAG_VSYNC_HINT);
	fillData(dataArray);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		drawData(dataArray);

		if (IsKeyDown(KEY_B))
		{
			bubbleSort(dataArray, counter);
			if (counter < dataSize)
			{
				counter++;
			}
			else counter = 0;
		}












		EndDrawing();
	}
	return 0;
}
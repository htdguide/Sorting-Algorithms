#include <raylib.h>
#include <cmath>
#include <array>
#include <iostream>
#include <string>

using namespace std;
const int dataSize = 78;
int dataArray[dataSize];

void drawDataRectangle(int posX, int posY, int width, int height, Color color) //Drawing method for a rectangle with gray bounds
{
	DrawRectangle(posX, posY, width, height, color);
	DrawRectangleLines(posX, posY, width, height, GRAY);
}

void drawData(int data[], Color color) //Drawing method for the arrays
{
	int x = 10; //gap between lines
	int y = 590; 

	for (int i = 0; i < dataSize; i++)
	{
		drawDataRectangle(x * i + 10, y - data[i], 10, data[i], color);
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
	int attempts = 0;
	int tempDataSize = dataSize;
	int FPS = 60;
	int counter = 0;
	string s = "Attempts: ";
	string msg, sort, bubble;
	InitWindow(800, 600, "Sorting");
	SetTargetFPS(120);
	fillData(dataArray);

	while (!WindowShouldClose())
	{
		SetTargetFPS(FPS);
		BeginDrawing();
		DrawFPS(700, 10);
		ClearBackground(BLACK);
		msg = s + to_string(attempts);
		sort = bubble;
		DrawText(msg.c_str(), 10, 10, 30, WHITE);
		DrawText(sort.c_str(), 10, 40, 20, WHITE);
		drawData(dataArray, WHITE);

		if (IsKeyDown(KEY_B))
		{
			bubbleSort(dataArray, counter);
			bubble = "Bubble ";
			if (counter < tempDataSize)
			{
				counter++;
				attempts++;
			}
			else if (tempDataSize != 0)
			{
				counter = 0;
				tempDataSize--;
				attempts++;
			}
			else drawData(dataArray, GREEN);
		}

		if (IsKeyDown(KEY_UP) && FPS < 300)
		{
			FPS++;
		}
		if (IsKeyDown(KEY_DOWN) && FPS > 24)
		{
			FPS--;
		}
		if (IsKeyDown(KEY_R))
		{
			fillData(dataArray);
			attempts = 0;
			tempDataSize = dataSize;
			counter = 0;
			bubble = " ";
		}











		EndDrawing();
	}
	return 0;
}
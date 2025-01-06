#include <raylib.h>
#include <cmath>
#include <array>
#include <iostream>
#include <string>
#include <emscripten.h>

using namespace std;
const int dataSize = 40;
int dataArray[dataSize];

void drawDataRectangle(int posX, int posY, int width, int height, Color color) 
{
    DrawRectangle(posX, posY, width, height, color);
    DrawRectangleLines(posX, posY, width, height, GRAY);
}

void drawData(int data[], Color color, int screenWidth, int screenHeight) 
{
    int xSpacing = screenWidth / (dataSize + 2);
    int yBase = screenHeight - 200;

    for (int i = 0; i < dataSize; i++)
    {
        drawDataRectangle(xSpacing * i + 10, yBase - data[i], xSpacing - 2, data[i], color);
    }
}

void drawData(int data[], int num, Color color, int screenWidth, int screenHeight) 
{
    int xSpacing = screenWidth / (dataSize + 2);
    int yBase = screenHeight - 200;
    drawDataRectangle(xSpacing * num + 10, yBase - data[num], xSpacing - 2, data[num], color);
}

void fillData(int data[])  
{
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = rand() % 300 + 1;
    }
}

void bubbleSort(int data[], int &i, int &j)
{
    if (i < dataSize - 1)
    {
        drawData(data, i, RED, GetScreenWidth(), GetScreenHeight());
        drawData(data, i + 1, RED, GetScreenWidth(), GetScreenHeight());
        if (data[i] > data[i + 1])
        {
            int m = data[i + 1];
            data[i + 1] = data[i];
            data[i] = m;
        }
        j = i;
        i++;
    }
    else
    {
        i = 0;
    }
}

void selectionSort(int data[], int &i, int &minIndex)
{
    if (i < dataSize)
    {
        drawData(data, i, BLUE, GetScreenWidth(), GetScreenHeight());
        minIndex = i;
        for (int j = i + 1; j < dataSize; j++)
        {
            if (data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            int temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
        }
        i++;
    }
    else
    {
        i = 0;
    }
}

void insertionSort(int data[], int &i, int &j)
{
    if (i < dataSize - 1)
    {
        drawData(data, i, GREEN, GetScreenWidth(), GetScreenHeight());
        int key = data[i + 1];
        int j = i;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
        i++;
    }
    else
    {
        i = 0;
    }
}

void handleTouchInput()
{
    for (int i = 0; i < GetTouchPointCount(); i++)
    {
        Vector2 touchPos = GetTouchPosition(i);
        if (CheckCollisionPointRec(touchPos, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}))
        {
            SetMousePosition((int)touchPos.x, (int)touchPos.y);
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                DrawCircleV(touchPos, 5, RED);
            }
        }
    }
}

int attempts = 0;
int tempDataSize = dataSize;
int FPS = 60;
int counter = 0;
string s = "Attempts: ";
string msg;

Rectangle bubbleButton = { 10, 320, 180, 30 };
Rectangle selectionButton = { 210, 320, 180, 30 };
Rectangle insertionButton = { 10, 360, 180, 30 };
Rectangle randomButton = { 210, 360, 180, 30 };
Rectangle fpsIncreaseButton = { 10, 400, 180, 30 };
Rectangle fpsDecreaseButton = { 210, 400, 180, 30 };

void drawButton(Rectangle button, const char* text, bool isPressed)
{
    DrawRectangleRec(button, isPressed ? LIGHTGRAY : DARKGRAY);
    DrawText(text, button.x + 10, button.y + 5, 16, WHITE);
}

void gameLoop()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    SetTargetFPS(FPS);

    handleTouchInput();

    BeginDrawing();
    ClearBackground(BLACK);

    msg = s + to_string(attempts);
    DrawText(("Attempts: " + to_string(attempts)).c_str(), 10, 450, 20, WHITE);
    DrawText(("FPS: " + to_string(FPS)).c_str(), 10, 480, 20, WHITE);

    drawData(dataArray, WHITE, screenWidth, screenHeight);

    static int bubbleI = 0, bubbleJ = 0;
    static int selectionI = 0, selectionMinIndex = 0;
    static int insertionI = 0, insertionJ = 0;

    bool bubblePressed = CheckCollisionPointRec(GetMousePosition(), bubbleButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool selectionPressed = CheckCollisionPointRec(GetMousePosition(), selectionButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool insertionPressed = CheckCollisionPointRec(GetMousePosition(), insertionButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool randomPressed = CheckCollisionPointRec(GetMousePosition(), randomButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool fpsIncreasePressed = CheckCollisionPointRec(GetMousePosition(), fpsIncreaseButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool fpsDecreasePressed = CheckCollisionPointRec(GetMousePosition(), fpsDecreaseButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    drawButton(bubbleButton, "Bubble Sort", bubblePressed);
    drawButton(selectionButton, "Selection Sort", selectionPressed);
    drawButton(insertionButton, "Insertion Sort", insertionPressed);
    drawButton(randomButton, "Randomize", randomPressed);
    drawButton(fpsIncreaseButton, "FPS+", fpsIncreasePressed);
    drawButton(fpsDecreaseButton, "FPS-", fpsDecreasePressed);

    if (bubblePressed)
    {
        bubbleSort(dataArray, bubbleI, bubbleJ);
        attempts++;
    }

    if (selectionPressed)
    {
        selectionSort(dataArray, selectionI, selectionMinIndex);
        attempts++;
    }

    if (insertionPressed)
    {
        insertionSort(dataArray, insertionI, insertionJ);
        attempts++;
    }

    if (randomPressed)
    {
        fillData(dataArray);
        attempts = 0;
        bubbleI = bubbleJ = 0;
        selectionI = selectionMinIndex = 0;
        insertionI = insertionJ = 0;
    }

    if (fpsIncreasePressed)
    {
        FPS += 1;
        if (FPS > 60) FPS = 60; // Ensure FPS doesn't exceed 60
    }

    if (fpsDecreasePressed)
    {
        FPS -= 1;
        if (FPS < 5) FPS = 5;
    }

    EndDrawing();
}

int main() 
{
    InitWindow(400, 500, "Sorting");
    fillData(dataArray);

    emscripten_set_main_loop(gameLoop, 0, 1);

    return 0;
}

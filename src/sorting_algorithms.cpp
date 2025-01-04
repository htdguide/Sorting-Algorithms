#include <raylib.h>
#include <cmath>
#include <array>
#include <iostream>
#include <string>
#include <emscripten.h>

using namespace std;
const int dataSize = 78;
int dataArray[dataSize];

// Drawing method for a rectangle with gray bounds
void drawDataRectangle(int posX, int posY, int width, int height, Color color) 
{
    DrawRectangle(posX, posY, width, height, color);
    DrawRectangleLines(posX, posY, width, height, GRAY);
}

// Drawing method for the arrays
void drawData(int data[], Color color, int screenWidth, int screenHeight) 
{
    int xSpacing = screenWidth / (dataSize + 2); // gap between lines based on screen width
    int yBase = screenHeight - 160; // Move the array up to reduce the gap

    for (int i = 0; i < dataSize; i++)
    {
        drawDataRectangle(xSpacing * i + 10, yBase - data[i], xSpacing - 2, data[i], color);
    }
}

// Drawing method for a specific unit of the array with a certain color
void drawData(int data[], int num, Color color, int screenWidth, int screenHeight) 
{
    int xSpacing = screenWidth / (dataSize + 2); // gap between lines based on screen width
    int yBase = screenHeight - 160; // Same adjustment for individual element
    drawDataRectangle(xSpacing * num + 10, yBase - data[num], xSpacing - 2, data[num], color);
}

// Filling the arrays method with random values
void fillData(int data[])  
{
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = rand() % 300 + 1;
    }
}

// Bubble sort logic
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

// Selection sort logic
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

// Insertion sort logic
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

// Check if touch is inside the button rectangle
bool isTouchingButton(Rectangle button)
{
    return CheckCollisionPointRec(GetTouchPosition(0), button);
}

int attempts = 0;
int tempDataSize = dataSize;
int FPS = 60;
int counter = 0;
string s = "Attempts: ";
string msg, sortMethod;

Rectangle bubbleButton = { 10, 460, 90, 30 };
Rectangle selectionButton = { 110, 460, 90, 30 };  // 10px gap
Rectangle insertionButton = { 210, 460, 90, 30 };  // 10px gap
Rectangle randomButton = { 310, 460, 90, 30 };  // 10px gap
Rectangle fpsUpButton = { 410, 460, 90, 30 };  // 10px gap
Rectangle fpsDownButton = { 510, 460, 90, 30 };  // 10px gap

void gameLoop()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Dynamically resize buttons
    float buttonWidth = screenWidth / 7.0f; 
    float buttonHeight = screenHeight / 20.0f;

    bubbleButton.width = buttonWidth;
    selectionButton.width = buttonWidth;
    insertionButton.width = buttonWidth;
    randomButton.width = buttonWidth;
    fpsUpButton.width = buttonWidth;
    fpsDownButton.width = buttonWidth;
    bubbleButton.height = buttonHeight;
    selectionButton.height = buttonHeight;
    insertionButton.height = buttonHeight;
    randomButton.height = buttonHeight;
    fpsUpButton.height = buttonHeight;
    fpsDownButton.height = buttonHeight;

    // Adjust buttons for a tighter layout with a 10px gap
    bubbleButton.x = screenWidth * 0.02f;
    selectionButton.x = bubbleButton.x + bubbleButton.width + 10;  // 10px gap
    insertionButton.x = selectionButton.x + selectionButton.width + 10;  // 10px gap
    randomButton.x = insertionButton.x + insertionButton.width + 10;  // 10px gap
    fpsUpButton.x = randomButton.x + randomButton.width + 10;  // 10px gap
    fpsDownButton.x = fpsUpButton.x + fpsUpButton.width + 10;  // 10px gap

    SetTargetFPS(FPS);

    BeginDrawing();
    ClearBackground(BLACK);

    msg = s + to_string(attempts);
    sortMethod = "Sorting Method: ";

    DrawText(("Attempts: " + to_string(attempts)).c_str(), 10, screenHeight - 130, 20, WHITE);
    DrawText((sortMethod + "Insertion Sort").c_str(), 10, screenHeight - 100, 20, WHITE);
    DrawText(("FPS: " + to_string(FPS)).c_str(), 10, screenHeight - 70, 20, WHITE);

    drawData(dataArray, WHITE, screenWidth, screenHeight);

    // Button drawing
    DrawRectangleRec(bubbleButton, DARKGRAY);
    DrawText("Bubble Sort", bubbleButton.x + 10, bubbleButton.y + 10, 12, WHITE);

    DrawRectangleRec(selectionButton, DARKGRAY);
    DrawText("Selection", selectionButton.x + 10, selectionButton.y + 10, 12, WHITE);

    DrawRectangleRec(insertionButton, DARKGRAY);
    DrawText("Insertion", insertionButton.x + 10, insertionButton.y + 10, 12, WHITE);

    DrawRectangleRec(randomButton, DARKGRAY);
    DrawText("Randomize", randomButton.x + 10, randomButton.y + 10, 12, WHITE);

    DrawRectangleRec(fpsUpButton, DARKGRAY);
    DrawText("FPS +", fpsUpButton.x + 10, fpsUpButton.y + 10, 12, WHITE);

    DrawRectangleRec(fpsDownButton, DARKGRAY);
    DrawText("FPS -", fpsDownButton.x + 10, fpsDownButton.y + 10, 12, WHITE);

    static int bubbleI = 0, bubbleJ = 0;
    static int selectionI = 0, selectionMinIndex = 0;
    static int insertionI = 0, insertionJ = 0;

    if (isTouchingButton(bubbleButton))
    {
        bubbleSort(dataArray, bubbleI, bubbleJ);
        sortMethod = "Bubble Sort";
        attempts++;
    }

    if (isTouchingButton(selectionButton))
    {
        selectionSort(dataArray, selectionI, selectionMinIndex);
        sortMethod = "Selection Sort";
        attempts++;
    }

    if (isTouchingButton(insertionButton))
    {
        insertionSort(dataArray, insertionI, insertionJ);
        sortMethod = "Insertion Sort";
        attempts++;
    }

    if (isTouchingButton(randomButton))
    {
        fillData(dataArray);
        attempts = 0;
        bubbleI = bubbleJ = 0;
        selectionI = selectionMinIndex = 0;
        insertionI = insertionJ = 0;
    }

    if (isTouchingButton(fpsUpButton) && FPS < 300)
    {
        FPS++;
    }

    if (isTouchingButton(fpsDownButton) && FPS > 2)
    {
        FPS--;
    }

    EndDrawing();
}

int main() 
{
    InitWindow(800, 500, "Sorting");
    fillData(dataArray);

    emscripten_set_main_loop(gameLoop, 0, 1);

    return 0;
}

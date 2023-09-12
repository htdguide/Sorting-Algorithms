#include <raylib.h>

int main() 
{
	InitWindow(800, 600, "Game");
	SetWindowState(FLAG_VSYNC_HINT);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
	return 0;
}
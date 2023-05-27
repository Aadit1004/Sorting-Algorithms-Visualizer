#include "raylib.h"

int main() {

	const int winWidth = 800, winHeight = 450;

	InitWindow(winWidth, winHeight, "Sorting Algorithms Visualizer");

	while (!WindowShouldClose()) {
		// Updated

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
	return 0;
}
#include "raylib.h"
#include <stdlib.h>
#include <functional>

int main() {

	const int winWidth = 800, winHeight = 450, rectWidth = 5;

	InitWindow(winWidth, winHeight, "Sorting Algorithms Visualizer");

	SetTargetFPS(60);

	int heights[72] = { 305, 224, 174, 187, 231, 139, 298, 83, 218,
		198, 63, 248, 320, 121, 326, 177, 160, 192, 55, 236, 332,
		64, 108, 250, 320, 327, 20, 315, 273, 185, 18, 91, 315, 232,
		295, 29, 347, 375, 174, 162, 43, 44, 299, 43, 6, 21, 320,
		201, 29, 40, 58, 102, 383, 349, 145, 352, 290, 266, 56, 221,
		197, 27, 245, 45, 305, 340, 235, 275, 400, 220, 123, 53 };
	

	while (!WindowShouldClose()) {
		// Updated

		// Draw
		BeginDrawing();
		ClearBackground(WHITE);
		for (int i = 0; i < 72; i++) {
			DrawRectangle(7 + (i * 11), winHeight - heights[i], rectWidth, heights[i], 
				Color{53, 181, 172, 255});
		}

		EndDrawing();

	}
	return 0;
}
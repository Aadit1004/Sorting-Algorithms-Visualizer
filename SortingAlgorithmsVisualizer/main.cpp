#include "raylib.h"
#include <stdlib.h>
#include <algorithm>
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
		bool swapped;
		for (int i = 0; i < 71; i++) {
			swapped = false;
			for (int j = 0; j < 71 - i; j++) {
				BeginDrawing();
				DrawText("Bubble Sort", 10, 10, 20, DARKPURPLE);
				ClearBackground(WHITE);
				if (heights[j] > heights[j + 1]) {
					std::swap(heights[j], heights[j + 1]);
					swapped = true;
				}
				for (int k = 0; k < 72; k++) {
					if (k == j) {
						DrawRectangle(7 + (k * 11), winHeight - heights[k], rectWidth, heights[k],RED);
					}
					else {
						DrawRectangle(7 + (k * 11), winHeight - heights[k], rectWidth, heights[k], Color{ 53, 181, 172, 255 });
					}
				}
				EndDrawing();
			}
			if (!swapped) break;
		}
		break;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		DrawText("Bubble Sort - Sorted!", 10, 10, 20, DARKPURPLE);
		ClearBackground(WHITE);
		for (int i = 0; i < 72; i++) {
			DrawRectangle(7 + (i * 11), winHeight - heights[i], rectWidth, heights[i], Color{ 53, 181, 172, 255 });
		}
		EndDrawing();
	}
	return 0;
}

// Implemented bubble sort algorithm and added visualisation for it.
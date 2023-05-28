#include "raylib.h"
#include <stdlib.h>
#include <algorithm>
#include <functional>

const int winWidth = 800, winHeight = 450, rectWidth = 4;

void drawCross() {
	DrawRectangle(0, (winHeight / 2) - 5, winWidth, 5, BLACK);
	DrawRectangle((winWidth / 2) - 5, 0, 5, winHeight, BLACK);
}

int main() {

	InitWindow(winWidth, winHeight, "Sorting Algorithms Visualizer");

	int heights[49] = { 155, 31, 74, 117, 24, 19, 198, 113, 181,
			98, 23, 48, 20, 121, 26, 177, 60, 92, 5, 36, 32,
			54, 85, 150, 20, 27, 112, 15, 73, 185, 8, 100, 15, 132,
			95, 109, 47, 75, 74, 162, 43, 44, 99, 3, 6, 121, 32,
			21, 129};

	int size = 49;
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		bool swapped;
		for (int i = 0; i < size - 1; i++) {
			swapped = false;
			for (int j = 0; j < size - 1 - i; j++) {
				BeginDrawing();
				DrawText("Bubble Sort", 5, 5, 22, DARKPURPLE);
				ClearBackground(WHITE);
				if (heights[j] > heights[j + 1]) {
					std::swap(heights[j], heights[j + 1]);
					swapped = true;
				}
				for (int k = 0; k < size; k++) {
					if (k == j) {
						DrawRectangle(2 + (k * 8), ((winHeight / 2) - 5) - heights[k], rectWidth, heights[k], RED);
					}
					else {
						DrawRectangle(2 + (k * 8), ((winHeight / 2) - 5) - heights[k], rectWidth, heights[k], Color{ 53, 181, 172, 255 });
					}
				}
				drawCross();
				DrawFPS(winWidth - 30, 10);
				EndDrawing();
			}
			if (!swapped) break;
		}
		break;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		DrawText("Bubble Sort - Sorted!", 5, 5, 22, DARKPURPLE);
		ClearBackground(WHITE);
		for (int i = 0; i < size; i++) {
			DrawRectangle(2 + (i * 8), ((winHeight / 2) - 5) - heights[i], rectWidth, heights[i], Color{ 53, 181, 172, 255 });
		}
		drawCross();
		DrawFPS(winWidth - 30, 10);
		EndDrawing();
	}
	
	return 0;
}
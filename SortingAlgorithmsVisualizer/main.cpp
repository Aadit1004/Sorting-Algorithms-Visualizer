#include "raylib.h"
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <thread>
#include <chrono>

const int winWidth = 800, winHeight = 450, rectWidth = 4;

bool doneSortingBubble = false;
int bubbleVal;

bool doneSortingSelection = false;
int selectionVal;

bool doneSortingMerge = false;
int mergeVal;

bool doneSortingQuick = false;
int quickVal;

void drawCross() {
	DrawRectangle(0, (winHeight / 2) - 5, winWidth, 5, BLACK);
	DrawRectangle((winWidth / 2) - 5, 0, 5, winHeight, BLACK);
}

int bubbleHeights[49] = { 155, 31, 74, 117, 24, 19, 198, 113, 181,
			98, 23, 48, 20, 121, 26, 177, 60, 92, 5, 36, 32,
			54, 85, 150, 20, 27, 112, 15, 73, 185, 8, 100, 15, 132,
			95, 109, 47, 75, 74, 162, 43, 44, 99, 3, 6, 121, 32,
			21, 129 };

int size = 49;

void bubbleSort() {
	bool swapped;
	for (int i = 0; i < size - 1; i++) {
		swapped = false;
		for (int j = 0; j < size - 1 - i; j++) {
			if (bubbleHeights[j] > bubbleHeights[j + 1]) {
				std::swap(bubbleHeights[j], bubbleHeights[j + 1]);
				swapped = true;
			}
			bubbleVal = j;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		if (!swapped) break;
	}
}

void bubbleSortThreadFn() {
	bubbleSort();
	doneSortingBubble = true;
}

int main() {

	InitWindow(winWidth, winHeight, "Sorting Algorithms Visualizer");

	SetTargetFPS(60);

	std::thread bubbleT(bubbleSortThreadFn);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		drawCross();
		DrawFPS(winWidth - 30, 10);

		if (doneSortingBubble) {
			DrawText("Bubble Sort - Sorted!", 5, 5, 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				DrawRectangle(2 + (i * 8), ((winHeight / 2) - 5) - bubbleHeights[i], rectWidth, bubbleHeights[i], Color{ 53, 181, 172, 255 });
			}
		}
		else {
			DrawText("Bubble Sort", 5, 5, 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				DrawRectangle(2 + (i * 8), ((winHeight / 2) - 5) - bubbleHeights[i], rectWidth, bubbleHeights[i],
					(i == bubbleVal) ? RED : Color{ 53, 181, 172, 255 });
			}
		}
		
		EndDrawing();

	}
	return 0;
}
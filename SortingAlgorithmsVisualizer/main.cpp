#include "raylib.h"
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <thread>
#include <chrono>
#include <iostream>

const int winWidth = 800, winHeight = 450, rectWidth = 4;

bool doneSortingBubble = false;
int bubbleVal;

bool doneSortingSelection = false;
int selectionVal1;
int selectionVal2;
int selectionValMin;

bool doneSortingMerge = false;
int mergeVal1;
int mergeVal2;
int mergeVal3;
int mergeVal4;

bool doneSortingQuick = false;
int quickVal;

void drawCross() {
	DrawRectangle(0, (winHeight / 2) - 5, winWidth, 5, BLACK);
	DrawRectangle((winWidth / 2) - 5, 0, 5, winHeight, BLACK);
}

int bubbleHeights[49] = { 155, 31, 74, 117, 24, 19, 168, 113, 181,
			98, 23, 48, 20, 121, 26, 167, 60, 92, 5, 36, 32,
			54, 85, 150, 20, 27, 112, 15, 73, 165, 8, 100, 15, 132,
			95, 109, 47, 75, 74, 162, 43, 44, 99, 3, 6, 121, 32,
			21, 129 };

int selectionHeights[49] = { 155, 31, 74, 117, 24, 19, 168, 113, 181,
			98, 23, 48, 20, 121, 26, 167, 60, 92, 5, 36, 32,
			54, 85, 150, 20, 27, 112, 15, 73, 165, 8, 100, 15, 132,
			95, 109, 47, 75, 74, 162, 43, 44, 99, 3, 6, 121, 32,
			21, 129 };

int mergeHeights[49] = { 155, 31, 74, 117, 24, 19, 168, 113, 181,
			98, 23, 48, 20, 121, 26, 167, 60, 92, 5, 36, 32,
			54, 85, 150, 20, 27, 112, 15, 73, 165, 8, 100, 15, 132,
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

void selectionSort() {
	for (int i = 0; i < size - 1; ++i) {
		int minIndex = i;
		selectionVal1 = i;
		for (int j = i + 1; j < size; ++j) {
			selectionVal2 = j;
			if (selectionHeights[j] < selectionHeights[minIndex]) {
				minIndex = j;
			}
			selectionValMin = minIndex;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		// Swap the minimum element with the first element of the unsorted part
		int temp = selectionHeights[i];
		selectionHeights[i] = selectionHeights[minIndex];
		selectionHeights[minIndex] = temp;
	}
}

// helper for merge sort, implementation from geeksforgeeks
void merge(int array[], int const left, int const mid, int const right) {
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Initial index of first sub-array
		indexOfSubArrayTwo
		= 0; // Initial index of second sub-array
	int indexOfMergedArray
		= left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end) {
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
	std::this_thread::sleep_for(std::chrono::milliseconds(210));
}

void bubbleSortThreadFn() {
	bubbleSort();
	doneSortingBubble = true;
}

void selectionSortThreadFn() {
	selectionSort();
	doneSortingSelection = true;
}

void mergeSortThreadFn() {
	mergeSort(mergeHeights, 0, size - 1);
	doneSortingMerge = true;
}

int main() {

	InitWindow(winWidth, winHeight, "Sorting Algorithms Visualizer");

	SetTargetFPS(60);

	std::thread selectionT(selectionSortThreadFn);
	std::thread bubbleT(bubbleSortThreadFn);
	std::thread mergeT(mergeSortThreadFn);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		drawCross();
		DrawFPS(winWidth - 30, 5);

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
		
		if (doneSortingSelection) {
			DrawText("Selection Sort - Sorted!", (winWidth / 2) + 5, 5, 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				DrawRectangle(((winWidth / 2) + 2) + (i * 8), ((winHeight / 2) - 5) - selectionHeights[i], rectWidth, selectionHeights[i], Color{ 53, 181, 172, 255 });
			}
		}
		else {
			DrawText("Selection Sort", (winWidth / 2) + 5, 5, 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				Color temp = Color{ 53, 181, 172, 255 };
				if (i == selectionVal1) temp = RED;
				if (i == selectionVal2) temp = DARKPURPLE;
				if (i == selectionValMin) temp = DARKBROWN;
				DrawRectangle(((winWidth / 2) + 2) + (i * 8), ((winHeight / 2) - 5) - selectionHeights[i], rectWidth, selectionHeights[i], temp);
			}
		}
		if (doneSortingMerge) {
			DrawText("Merge Sort - Sorted!", 5, ((winHeight / 2) + 5), 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				DrawRectangle(2 + (i * 8), winHeight - mergeHeights[i], rectWidth, mergeHeights[i], Color{ 53, 181, 172, 255 });
			}
		}
		else {
			DrawText("Merge Sort", 5, ((winHeight / 2) + 5), 22, DARKPURPLE);
			for (int i = 0; i < size; i++) {
				DrawRectangle(2 + (i * 8), winHeight - mergeHeights[i], rectWidth, mergeHeights[i], Color{ 53, 181, 172, 255 });
			}
			
		}

		EndDrawing();

	}
	bubbleT.join();
	selectionT.join();
	mergeT.join();
	CloseWindow();
	return 0;
}
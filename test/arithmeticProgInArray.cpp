#include "gtest/gtest.h"

extern "C" {
#include "testy/arithmeticProgInArray.h"
}

//All right
TEST(arithmeticalProgInArray, ok) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 2, 3, -6, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
    ASSERT_EQ(arithmeticProgInArray(arr, dist, size), 6);
    delete[] arr;
}

//Negative size
TEST(nagativeSizeInArray, fault) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 2, 3, -6, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
    ASSERT_DEATH(arithmeticProgInArray(arr, dist, -3), "size > 0");
    delete[] arr;
}

//All array is a progressive
TEST(allArrayIsProgressive, all) {
    int size = 10;
    int* arr = new int[size];
	int* dist;
	for (int i = 0; i < size; i++)
	{
		arr[i] = i;
	}
    ASSERT_EQ(arithmeticProgInArray(arr, dist, size), size);
    delete[] arr;
}

//Two elements in array
TEST(twoElementsInArray, two) {
    int size = 2;
    int* arr = new int[size];
	int* dist;
	int arr2[] = { 1, 8};
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr2[i];
	}
    ASSERT_EQ(arithmeticProgInArray(arr, dist, size), size);
    delete[] arr;
}
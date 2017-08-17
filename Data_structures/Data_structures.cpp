// Data_structures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<cmath>
using namespace std;
const int N = 100;

struct heap {
	int A[N], heapsize=0;
};

int Parent(int i) {
	return (i - 1) / 2;
}
int Left(int i) {
	return 2 * i + 1;
}
int Right(int i) {
	return 2 * i + 2;
}

void Swap(int* A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

void Heapify(heap H, int i) {
	int id_max = i;
	if (Left(i) <= H.heapsize && H.A[Left(i)] > H.A[id_max]) id_max = Left(i);
	if (Right(i) <= H.heapsize && H.A[Right(i)] > H.A[id_max]) id_max = Right(i);
	if (id_max != i) {
		Swap(H.A, i, id_max);
		Heapify(H, id_max);
	}
}

int Pop_queue(heap H) {
	if (H.heapsize > 0) {
		int max = H.A[0];
		H.A[0] = H.A[H.heapsize];
		H.heapsize--;
		Heapify(H, 0);
		return max;
	}
}





int main()
{
	heap H;

    return 0;
}


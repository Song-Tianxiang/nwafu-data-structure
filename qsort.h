#ifndef QSORT_H
#define QSORT_H

#include <stdlib.h>
#include <time.h>

void swap(int l, int r) {
  int tmp;

  tmp = l;
  l = r;
  r = tmp;
}

int part(int arr[], int low, int high) {
  int pivot;
  int i;
  int j;

  pivot = arr[low];
  i = low;
  j = low + 1;

  while (j <= high) {
    if (arr[j] < pivot) {
      swap(arr[i = i + 1], arr[j]);
    }
  }
  swap(arr[low], arr[i]);
  return i;
}

int rpart(int arr[], int low, int high) {
  int rnum;
  srand((unsigned)time(0));
  rnum = low + rand() % (high - low);

  swap(arr[rnum], arr[low]);

  return part(arr, low, high);
}

void rqsort(int arr[], int low, int high) {
  int pivot;

  if (low < high) {
    pivot = rpart(arr, low, high);

    rqsort(arr, low, pivot-1);
    rqsort(arr, pivot + 1, high);
  }
}

#endif /* QSORT_H */

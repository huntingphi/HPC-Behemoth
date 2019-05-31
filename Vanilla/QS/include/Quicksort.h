#ifndef QUICKSORT
#define QUICKSORT




/* C implementation QuickSort */
#include<stdio.h> 
#include<stdlib.h>

// A utility function to swap two elements 
void swap(int* a, int* b);


/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high);

/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high) ;

/* Function to print an array */
void printArray(int arr[], int size);
void quicksort(int Array[],int first,int last);
#endif // QUICKSORT
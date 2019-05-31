#include "../include/Quicksort.h"
#include <omp.h>


/* -----------------------------------------------------------------------
   Tests the result
 * ----------------------------------------------------------------------- */
void testit(int *v, int * nelements) {
  register int k;
	int not_sorted = 0;
  for (k = 0; k < (*nelements) - 1; k++)
    if (v[k] > v[k + 1]) {
      not_sorted = 1;
      break;
    }
    if (not_sorted)
    {
    printf("Array NOT sorted.\n");
        exit(1);
    }
    
//   if (not_sorted)
//     printf("Array NOT sorted.\n");
// 	else
//     printf("Array sorted.\n");
}

/* -----------------------------------------------------------------------
   Sets randomly the values for the array
 * ----------------------------------------------------------------------- */
void initialize(int *v, int seed, int nelements) {
  unsigned i;
   srandom(seed);
   for(i = 0; i < nelements; i++)
     v[i] = (int)random();
}
  
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void quicksort(int Array[],int first,int last){
    int pivot,j,temp,i;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(Array[i]<=Array[pivot]&&i<last)
                i++;
            while(Array[j]>Array[pivot])
                j--;
            if(i<j){
                temp=Array[i];
                Array[i]=Array[j];
                Array[j]=temp;
            }
        }
        temp=Array[pivot];
        Array[pivot]=Array[j];
        Array[j]=temp;
        quicksort(Array,first,j-1);
        quicksort(Array,j+1,last);
    }
}
  
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("n"); 
}

    int main(int argc, char** argv) {
    // #pragma omp parallel
    // {
    // printf("this\n");
    // printf("is\n");
    // printf("a test\n");

    // }
    int nelements= 1000000;
    int seed=1;
    if (argc==2){
        nelements = atoi(argv[1]);
        seed = 1;
    }else if (argc==3){
        nelements = atoi(argv[1]);
        seed = atoi(argv[2]);
    }
    int* a = (int *) malloc(sizeof(int)*nelements);
    initialize(a,seed,nelements);
    double start_time = omp_get_wtime();
    quicksort(a,0,nelements-1);
    double duration = omp_get_wtime() - start_time;
    printf("VanillaQS,%d,%f\n",nelements,duration);
    testit(a,&nelements);
    // free((void*) a);
    return 0;
    }
  

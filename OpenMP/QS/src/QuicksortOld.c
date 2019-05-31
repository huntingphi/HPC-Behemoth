#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <omp.h>

void swap(int *ptr1, int *ptr2 ){
        int temp;
        temp = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = temp;
    }


int choosePivot(int *a, int lo, int hi){
    return ((lo+hi)/2);
}

int partitionArray(int *a, int lo, int hi){
    int pivotIndex, pivotValue, storeIndex;
    pivotIndex = choosePivot(a, lo, hi);
    pivotValue = a[pivotIndex];
    (void) swap(&a[hi], &a[pivotIndex]);
    storeIndex = lo;
    for (int i=lo; i<= hi-1; i++){
        if (a[i] < pivotValue){
            (void) swap(&a[i], &a[storeIndex]);
            storeIndex++;
        }
    }
    (void) swap(&a[storeIndex],&a[hi]);
    return storeIndex;
}


void Quicksort(int *a, int lo, int hi){
    if (lo < hi){
        int p = partitionArray(a, lo, hi);

// #pragma omp task default(none) firstprivate(a,lo,p)
#pragma omp task shared(a) firstprivate(lo,p)
        {
            (void) Quicksort(a, lo, p-1);
        } //Left branch

(void) Quicksort(a, p+1, hi); //Right branch

#pragma omp taskwait
    }
}


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
     v[i] = (int)random()%1000;
}

int main(int argc, char** argv) {
    // #pragma omp parallel
    // {
    // printf("this\n");
    // printf("is\n");
    // printf("a test\n");

    // }
    int nelements;
    int seed;
    if (argc==1){
        nelements = 1000000;
        seed = 1;
    } else if (argc==2){
        nelements = atoi(argv[1]);
        seed = 1;
    }else if (argc==3){
        nelements = atoi(argv[1]);
        seed = atoi(argv[2]);
    }
        int *a = (int *) malloc(sizeof(int) * nelements);

    initialize(a,seed,nelements);
    double start_time = omp_get_wtime();
#pragma omp parallel default(none) shared(a, nelements)
    {
#pragma omp single nowait
        {
            (void) Quicksort(a,0,nelements-1);
    }
    }
    double duration = omp_get_wtime() - start_time;
        printf("OpenMP-QS,%d,%d,%f\n",omp_get_max_threads(),nelements,duration);

        testit(a,&nelements);
    return 0;
}